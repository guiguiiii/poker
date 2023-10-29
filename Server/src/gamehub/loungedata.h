#ifndef LOUNGEDATA_H
#define LOUNGEDATA_H

class LoungeData
{
public:
    LoungeData();
    LoungeData(int loungeID, int playerNum);

    int loungeID() const;
    void setLoungeID(int newLoungeID);
    int playerNum() const;
    void setPlayerNum(int newPlayerNum);

private:
    int m_loungeID;
    int m_playerNum;
};

#endif // LOUNGEDATA_H
