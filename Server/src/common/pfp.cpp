#include "pfp.h"

#include <QDir>

QString PFP::s_dir = "data/pfp";

QPixmap PFP::getPFP(int id)
{
    PFP::initDir();

    QDir dir(PFP::s_dir);
    QStringList nameFilters;
    nameFilters.push_back("*.png");
    QStringList pfpNames = dir.entryList(nameFilters);
    QString userPFPName = QString::number(id) + ".png";
    if(pfpNames.contains(userPFPName)){
        return QPixmap(PFP::s_dir + '/' + userPFPName);
    }else{
        return QPixmap(PFP::s_dir + "/-1.png");
    }
}

void PFP::setPFP(int id, const QPixmap &pfp)
{
    PFP::initDir();

    if(QPixmap(PFP::s_dir + "/-1.png").toImage() != pfp.toImage()){
        QString path = PFP::s_dir + '/' + QString::number(id) + ".png";
        pfp.save(path);
    }
}

void PFP::initDir()
{
    QVector<QString> folderNames = PFP::s_dir.split('/');
    QDir dir(folderNames.front());
    for(int i=0; i<folderNames.size(); i++){
        if(dir.exists() == false)
            dir.mkdir("../" + folderNames[i]);
        if(i != folderNames.size() -1)
            dir.setPath(dir.path() + '/' + folderNames[i+1]);
    }
}
