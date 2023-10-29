#include "user_file.h"

#include "src/common/pfp.h"

#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QString User_File::s_fileName = "data/user.txt";

UserData User_File::getPersonal(int id)
{
    User_File::initFile();

    QFile inFile(User_File::s_fileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = inFile.readAll();
    inFile.close();

    QJsonObject userObj;
    QVector<QByteArray> strLines = byteArray.split('\n');
    for(int i=0; i<strLines.size() -1; i++){
        QJsonObject object = QJsonDocument::fromJson(strLines[i]).object();
        if(object["id"] == id){
            userObj = object;
            break;
        }
    }

    UserData userData;
    userData.setUsername(userObj["username"].toString());
    userData.setPassword(userObj["password"].toString());
    userData.setNickname(userObj["nickname"].toString());
    userData.setSignature(userObj["signature"].toString());
    userData.setPfp(PFP::getPFP(id));

    return userData;
}

int User_File::setPersonal(int id, const UserData &userData)
{
    User_File::initFile();

    QFile inFile(User_File::s_fileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = inFile.readAll();
    inFile.close();

    int status = 0;
    QVector<QJsonObject> saveObjs;
    QVector<QByteArray> strLines = byteArray.split('\n');
    for(int i=0; i<strLines.size() -1; i++){
        QJsonObject object = QJsonDocument::fromJson(strLines[i]).object();
        if(object["id"] != id){
            saveObjs.push_back(object);
            continue;
        }

        QJsonObject saveObj;
        saveObj["id"] = id;
        saveObj["username"] = userData.username();
        saveObj["password"] = userData.password();
        saveObj["nickname"] = userData.nickname();
        saveObj["signature"] = userData.signature();
        saveObjs.push_back(saveObj);

        PFP::setPFP(id,userData.pfp());
        status = 1;
    }

    QString string = "";
    for(const QJsonObject &object: saveObjs){
        QByteArray byteArray = QJsonDocument(object).toJson();
        byteArray.replace('\n',"");
        byteArray.replace(' ',"");
        byteArray.push_back('\n');
        string += byteArray;
    }

    QFile outFile(User_File::s_fileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Text);
    outFile.write(string.toUtf8());
    outFile.close();

    return status;
}

void User_File::initFile()
{
    QVector<QString> folderNames = User_File::s_fileName.split('/');
    QFile file(User_File::s_fileName);
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
