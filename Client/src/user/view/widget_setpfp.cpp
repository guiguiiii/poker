#include "widget_setpfp.h"
#include "ui_widget_setpfp.h"

#include "src/common/pixtostr.h"

#include <QMimeData>

Widget_SetPFP::Widget_SetPFP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_SetPFP)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
}

Widget_SetPFP::~Widget_SetPFP()
{
    delete ui;
}

void Widget_SetPFP::on_btn_ok_clicked()
{
    emit signal_savePFP(m_pfp);
    this->deleteLater();
}

void Widget_SetPFP::on_btn_cancel_clicked()
{
    this->deleteLater();
}

void Widget_SetPFP::dragEnterEvent(QDragEnterEvent *ev)
{
    if(ev->mimeData()->hasUrls()){
        ev->acceptProposedAction();
    }else{
        ev->ignore();
    }
}

void Widget_SetPFP::dropEvent(QDropEvent *ev)
{
    // Get a image and crop it to a circle
    const QMimeData *mimedata = ev->mimeData();
    if(mimedata->hasUrls()){
        QList<QUrl> urls = mimedata->urls();
        QString filename = urls.front().toLocalFile();
        QPixmap pixmap(filename);
        pixmap = PixToStr::toCircle(pixmap,300);
        this->m_pfp = pixmap;
        ui->lbl_pfp->setPixmap(m_pfp);
    }
}
