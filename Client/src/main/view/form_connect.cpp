#include "form_connect.h"
#include "ui_form_connect.h"

Form_Connect::Form_Connect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Connect)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
    ui->Widget_Config->setVisible(false);
    ui->le_addr->setText("127.0.0.1");
    ui->le_port->setText("10523");
}

Form_Connect::~Form_Connect()
{
    delete ui;
}

void Form_Connect::on_btn_config_clicked()
{
    ui->Widget_Connect->setVisible(false);
    ui->Widget_Config->setVisible(true);
}

void Form_Connect::on_btn_cancel_clicked()
{
    ui->Widget_Config->setVisible(false);
    ui->Widget_Connect->setVisible(true);
    ui->le_addr->setText("127.0.0.1");
    ui->le_port->setText("10523");
}

void Form_Connect::on_btn_confirm_clicked()
{
    ui->Widget_Config->setVisible(false);
    ui->Widget_Connect->setVisible(true);
}

void Form_Connect::on_btn_connect_clicked()
{
    QString addr = ui->le_addr->text();
    QString port = ui->le_port->text();
    emit signal_connectToHost(addr,port.toInt());
}
