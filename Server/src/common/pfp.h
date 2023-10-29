#ifndef PFP_H
#define PFP_H

#include <QPixmap>

class PFP
{
public:
    static QPixmap getPFP(int id);
    static void setPFP(int id, const QPixmap &pfp);

private:
    static QString s_dir;

private:
    static void initDir();
};

#endif // PFP_H
