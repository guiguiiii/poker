#include "pixtostr.h"

#include <QBuffer>
#include <QPainter>
#include <QBitmap>

PixToStr::PixToStr()
{

}

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

QPixmap PixToStr::toCircle(const QPixmap &pixmap, int radius)
{
    if(pixmap.isNull())
        return pixmap;
    QPixmap resPixmap = pixmap;

    int diameter = 2 * radius;

    //裁剪成正方形
    int w = resPixmap.width();
    int h = resPixmap.height();
    if( w > h ){
        int x = ( w - h ) / 2;
        resPixmap = resPixmap.copy(x,0,h,h);
    }else if( w < h ){
        int y = ( h - w ) / 2;
        resPixmap = resPixmap.copy(0,y,w,w);
    }

    //等比例缩放
    resPixmap = resPixmap.scaled(diameter,diameter);

    //裁剪成圆形
    QBitmap mark(diameter,diameter);
    QPainter painter(&mark);
    painter.fillRect(0,0,diameter,diameter,Qt::white);
    painter.setBrush(QColor(0,0,0));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawRoundedRect(0,0,diameter,diameter,radius,radius);
    resPixmap.setMask(mark);
    return resPixmap;
}
