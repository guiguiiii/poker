#include "form_settings.h"
#include "ui_form_settings.h"

Form_Settings::Form_Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Settings)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
}

Form_Settings::~Form_Settings()
{
    delete ui;
}

void Form_Settings::on_btn_cancel_clicked()
{
    emit signal_cancel();
}
