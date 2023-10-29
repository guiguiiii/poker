#include "widget_confirm.h"
#include "ui_widget_confirm.h"

Widget_Confirm::Widget_Confirm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_Confirm)
{
    ui->setupUi(this);
}

Widget_Confirm::Widget_Confirm(QWidget *parent, const QString &text) :
    QWidget(parent),
    ui(new Ui::Widget_Confirm)
{
    ui->setupUi(this);
    ui->lbl_text->setText(text);
}

Widget_Confirm::Widget_Confirm(QWidget *parent, const QString &title, const QString &text) :
    QWidget(parent),
    ui(new Ui::Widget_Confirm)
{
    ui->setupUi(this);
    ui->lbl_title->setText(title);
    ui->lbl_text->setText(text);
}

Widget_Confirm::~Widget_Confirm()
{
    delete ui;
}

void Widget_Confirm::setTitle(const QString &title)
{
    ui->lbl_title->setText(title);
}

void Widget_Confirm::setText(const QString &text)
{
    ui->lbl_text->setText(text);
}

void Widget_Confirm::setBtnConfirm(const QString &text)
{
    ui->btn_confirm->setText(text);
}

void Widget_Confirm::setBtnCancel(const QString &text)
{
    ui->btn_cancel->setText(text);
}

void Widget_Confirm::on_btn_confirm_clicked()
{
    emit confirm();
    this->deleteLater();
}

void Widget_Confirm::on_btn_cancel_clicked()
{
    emit cancel();
    this->deleteLater();
}
