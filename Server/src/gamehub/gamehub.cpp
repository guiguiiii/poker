#include "gamehub.h"

#include "src/common/public_file.h"

GameHub::GameHub(QObject *parent)
    : QObject{parent}
{

}

QVector<LoungeData> GameHub::getLounges()
{
    QVector<LoungeData> lounges;
    for(auto it = m_lounges.begin(); it != m_lounges.end(); it++){
        LoungeData loungeData;
        loungeData.setLoungeID(it.value().loungeID());
        loungeData.setPlayerNum(it.value().playerNum());
        lounges.push_back(loungeData);
    }
    return lounges;
}

PublicData GameHub::getPublicData(int id)
{
    return Public_File::publicData(id);
}

int GameHub::enterLounge(int id, int loungeID)
{
    // 房间不存在，返回3
    if(m_lounges.contains(loungeID) == false)
        return 3;

    // 房间满员，返回2
    Lounge &lounge = m_lounges[loungeID];
    if(lounge.playerNum() >= 3)
        return 2;

    // 加入房间
    PublicData publicData = this->getPublicData(id);
    lounge.enterLounge(publicData);

    // 向房间内所有玩家发送信息
    QVector<int> IDs = lounge.playerIDs();
    for(int &playerID: IDs)
        emit playerJoin(playerID,publicData);

    // 加入成功，返回1
    return 1;
}

int GameHub::quickStart(int id)
{
    /* 查找人数为 2 的房间，若不存在，则查找人数为 1 的房间
        若仍不存在，则创建房间 */
    int loungeID;
    bool exists = false;
    for(int num = 2; num >= 1 and exists == false; num--){
        for(auto it = m_lounges.begin(); it != m_lounges.end(); it++){
            if(it.value().playerNum() == num){
                loungeID = it.value().loungeID();
                exists = true;
                break;
            }
        }
    }

    // 若房间存在，加入房间。若不存在，则创建房间
    if(exists == true){
        int status = this->enterLounge(id,loungeID);
        if(status == 1)
            return loungeID;
        else
            return this->quickStart(id);
    }else
        return this->newLounge(id);
    return -1;
}

int GameHub::newLounge(int id)
{
    // 获取一个不存在的房间号
    for(int loungeID=1; loungeID<INT_MAX; loungeID++){
        if(m_lounges.contains(loungeID))
            continue;

        // 创建房间
        Lounge lounge(loungeID);
        lounge.enterLounge(this->getPublicData(id));
        m_lounges.insert(loungeID,lounge);
        return loungeID;
    }

    return -1;
}

QVector<PlayerData> GameHub::getPlayers(int id, int loungeID)
{
    // 获取该房间的玩家列表
    if(loungeID != -1 and m_lounges[loungeID].containsID(id) == true)
        return m_lounges[loungeID].players();

    for(auto it = m_lounges.begin(); it != m_lounges.end(); it++)
        if(it.value().containsID(id) == true)
            return it.value().players();

    return QVector<PlayerData>();
}

void GameHub::readyGame(int id, bool isReady, int loungeID)
{
    // 获取房间号
    int newLoungeID = loungeID;
    if(loungeID == -1 or m_lounges.contains(loungeID) == false){
        for(auto it = m_lounges.begin(); it != m_lounges.end(); it++)
            if(it.value().containsID(id) == true){
                newLoungeID = it.key();
            }
        if(newLoungeID == -1)
            return;
    }

    // 准备游戏
    Lounge &lounge = m_lounges[newLoungeID];
    lounge.readyGame(id,isReady);

    // 获取房间状态
    bool start = lounge.isReadyGame();
    if(start == true)
        // 若准备就绪，则返回所有玩家ID，等待游戏模块创建游戏
        emit signal_gameStart(lounge.playerIDs());

    else{
        // 若三个人其一未准备就绪，则向房间内所有人发送有玩家准备信息
        QVector<int> playerIDs = lounge.playerIDs();
        for(int &playerId: playerIDs)
            emit playerReady(playerId,id,isReady);
    }

}

void GameHub::leaveLounge(int id, int loungeID)
{
    // 获取房间号
    int newLoungeID = loungeID;
    if(loungeID == -1 or m_lounges.contains(loungeID) == false){
        for(auto it = m_lounges.begin(); it != m_lounges.end(); it++)
            if(it.value().containsID(id) == true){
                newLoungeID = it.key();
            }
        if(newLoungeID == -1)
            return;
    }

    // 离开房间
    Lounge &lounge = m_lounges[newLoungeID];
    lounge.leaveLounge(id);

    // 若房间人数不为零，向房间内所有玩家发送有玩家离开信息
    if(lounge.playerNum() != 0){
        QVector<int> playerIDs = lounge.playerIDs();
        for(int &playerID: playerIDs)
            emit playerLeave(playerID,id);

    // 若房间为空，删除房间
    }else
        m_lounges.remove(newLoungeID);
}
