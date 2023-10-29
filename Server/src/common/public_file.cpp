#include "public_file.h"

#include "src/common/pfp.h"

#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QString Public_File::s_fileName = "data/user.txt";

PublicData Public_File::publicData(int id)
{
    Public_File::initFile();

    QFile inFile(Public_File::s_fileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = inFile.readAll();
    inFile.close();

    QString nickname;
    QVector<QByteArray> strLines = byteArray.split('\n');
    for(int i=0; i<strLines.size() -1; i++){
        QJsonObject object = QJsonDocument::fromJson(strLines[i]).object();
        if(object["id"] == id){
            nickname = object["nickname"].toString();
            break;
        }
    }

    PublicData publicData;
    publicData.setId(id);
    publicData.setNickname(nickname);
    publicData.setPfp(PFP::getPFP(id));

    return publicData;
}

void Public_File::initFile()
{
    QVector<QString> folderNames = Public_File::s_fileName.split('/');
    QFile file(Public_File::s_fileName);
    if(file.exists())
        return;

    QDir dir(folderNames.front());
    for(int i=0; i<folderNames.size() -1; i++){
        if(dir.exists() == false)
            dir.mkdir("../" + folderNames[i]);
        dir.setPath(dir.path() + '/' + folderNames[i+1]);
    }

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.close();
}
