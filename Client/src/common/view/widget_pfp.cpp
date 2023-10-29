#include "widget_pfp.h"
#include "ui_widget_pfp.h"

Widget_PFP::Widget_PFP(QWidget *parent, const QPixmap &pfp) :
    QWidget(parent),
    ui(new Ui::Widget_PFP)
{
    ui->setupUi(this);
    ui->lbl_pfp->setPixmap(pfp);
}

Widget_PFP::~Widget_PFP()
{
    delete ui;
}

void Widget_PFP::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        this->deleteLater();
    }
}
