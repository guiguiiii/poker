#ifndef PIXTOSTR_H
#define PIXTOSTR_H

#include <QPixmap>

class PixToStr
{
public:
    static QString pixToStr(const QPixmap &pixmap);
    static QPixmap strToPix(const QString &string);
};

#endif // PIXTOSTR_H
