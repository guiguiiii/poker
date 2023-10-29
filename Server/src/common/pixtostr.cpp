#include "pixtostr.h"

#include <QBuffer>

QString PixToStr::pixToStr(const QPixmap &pixmap)
{
    QByteArray byteArr;
    QBuffer buffer(&byteArr);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer,"png");
    return QString(buffer.data().toBase64());
}

QPixmap PixToStr::strToPix(const QString &string)
{
    QPixmap pixmap;
    QByteArray byteArray = QByteArray::fromBase64(string.toLatin1());
    pixmap.loadFromData(byteArray);
    return pixmap;
}
