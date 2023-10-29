#ifndef PIXTOSTR_H
#define PIXTOSTR_H

#include <QPixmap>

class PixToStr
{
public:
    PixToStr();
    static QString pixToStr(const QPixmap &pixmap);
    static QPixmap strToPix(const QString &string);
    static QPixmap toCircle(const QPixmap &pixmap, int radius);
};

#endif // PIXTOSTR_H
