#include "login_file.h"

#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QString Login_File::s_fileName = "data/user.txt";

int Login_File::login(const LoginData &loginData)
{
    Login_File::initFile();

    QFile inFile(Login_File::s_fileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = inFile.readAll();
    inFile.close();

    QVector<QByteArray> strLines = byteArray.split('\n');
    for(int i=0; i<strLines.size() -1; i++){
        QJsonObject object = QJsonDocument::fromJson(strLines[i]).object();
        if(object["username"] == loginData.username()){
            if(object["password"] == loginData.password())
                return 1;
            else
                return 2;
        }
    }

    return 3;
}

int Login_File::signUp(const SignUpData &signUpData)
{
    Login_File::initFile();

    QFile inFile(Login_File::s_fileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = inFile.readAll();
    inFile.close();

    int maxID = 0;
    QVector<QByteArray> strLines = byteArray.split('\n');
    for(int i=0; i<strLines.size() -1; i++){
        QJsonObject object = QJsonDocument::fromJson(strLines[i]).object();
        if(object["username"] == signUpData.username())
            return 2;
        maxID = ( object["id"].toInt() > maxID ) ? object["id"].toInt() : maxID;
    }

    QJsonObject signUpObj;
    signUpObj["id"] = maxID + 1;
    signUpObj["username"] = signUpData.username();
    signUpObj["password"] = signUpData.password();
    signUpObj["nickname"] = signUpData.nickname();
    signUpObj["signature"] = "";
    QByteArray signUpByteArr = QJsonDocument(signUpObj).toJson();
    signUpByteArr.replace('\n',"");
    signUpByteArr.replace(' ',"");
    signUpByteArr.push_back('\n');

    QFile outFile(Login_File::s_fileName);
    outFile.open(QIODevice::Append | QIODevice::Text);
    outFile.write(signUpByteArr);
    outFile.close();

    return 1;
}

int Login_File::userID(const QString &username)
{
    Login_File::initFile();

    QFile inFile(Login_File::s_fileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray = inFile.readAll();
    inFile.close();

    QVector<QByteArray> strLines = byteArray.split('\n');
    for(int i=0; i<strLines.size() -1; i++){
        QJsonObject object = QJsonDocument::fromJson(strLines[i]).object();
        if(object["username"] == username)
            return object["id"].toInt();
    }

    return -1;
}

void Login_File::initFile()
{
    QVector<QString> folderNames = Login_File::s_fileName.split('/');
    QFile file(Login_File::s_fileName);
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
