#include "form_start.h"
#include "ui_form_start.h"

Form_Start::Form_Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Start)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
    ui->lbl_png->setPixmap(QPixmap(":/icons/poker.png"));
}

Form_Start::~Form_Start()
{
    delete ui;
}

void Form_Start::on_btn_gameHub_clicked()
{
    emit signal_moveToGameHub();
}

void Form_Start::on_btn_personal_clicked()
{
    emit signal_moveToPersonal();
}

void Form_Start::on_btn_settings_clicked()
{
    emit signal_moveToSettings();
}
