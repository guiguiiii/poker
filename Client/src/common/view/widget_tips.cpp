#include "widget_tips.h"
#include "ui_widget_tips.h"

Widget_Tips::Widget_Tips(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_Tips)
{
    this->grabKeyboard();
    ui->setupUi(this);
}

Widget_Tips::Widget_Tips(QWidget *parent, const QString &text) :
    QWidget(parent),
    ui(new Ui::Widget_Tips)
{
    ui->setupUi(this);
    this->grabKeyboard();
    ui->lbl_text->setText(text);
}

Widget_Tips::Widget_Tips(QWidget *parent, const QString &title, const QString &text) :
    QWidget(parent),
    ui(new Ui::Widget_Tips)
{
    ui->setupUi(this);
    this->grabKeyboard();
    ui->lbl_title->setText(title);
    ui->lbl_text->setText(text);
}

Widget_Tips::~Widget_Tips()
{
    delete ui;
}

void Widget_Tips::setTitle(const QString &title)
{
    ui->lbl_title->setText(title);
}

void Widget_Tips::setText(const QString &text)
{
    ui->lbl_text->setText(text);
}

void Widget_Tips::setBtnText(const QString &text)
{
    ui->btn_close->setText(text);
}

void Widget_Tips::on_btn_close_clicked()
{
    this->deleteLater();
}

void Widget_Tips::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Enter or ev->key() == Qt::Key_Return or ev->key() == Qt::Key_Space){
        this->on_btn_close_clicked();
    }else{
        QWidget::keyPressEvent(ev);
    }
}
