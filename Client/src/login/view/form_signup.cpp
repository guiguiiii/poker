#include "form_signup.h"
#include "ui_form_signup.h"

#include "src/common/view/widget_tips.h"

Form_SignUp::Form_SignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_SignUp)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
    ui->le_username->setFocus();
}

Form_SignUp::~Form_SignUp()
{
    delete ui;
}

void Form_SignUp::signUpFailed()
{
    (new Widget_Tips(this, "注册", "输入的账号已存在"))->setVisible(true);
}

void Form_SignUp::on_btn_signUp_clicked()
{
    QString username = ui->le_username->text();
    QString password = ui->le_password->text();
    QString nickname = ui->le_nickname->text();

    if(username == ""){
        (new Widget_Tips(this, "注册", "账号不能为空"))->setVisible(true);
    }else if(password == ""){
        (new Widget_Tips(this, "注册", "密码不能为空"))->setVisible(true);
    }else if(nickname == ""){
        (new Widget_Tips(this, "注册", "昵称不能为空"))->setVisible(true);
    }else if(username.size() > 20){
        (new Widget_Tips(this, "注册", "账号过长，请重新输入"))->setVisible(true);
    }else if(password.size() > 20){
        (new Widget_Tips(this, "注册", "密码过长，请重新输入"))->setVisible(true);
    }else if(nickname.size() > 20){
        (new Widget_Tips(this, "注册", "昵称过长，请重新输入"))->setVisible(true);

    }else{
        SignUpData signUpData(username,password,nickname);
        emit signal_signUp(signUpData);
    }
}

void Form_SignUp::on_btn_cancel_clicked()
{
    emit signal_signUpCancel();
}

void Form_SignUp::on_le_username_returnPressed()
{
    ui->le_password->setFocus();
}

void Form_SignUp::on_le_password_returnPressed()
{
    ui->le_password_2->setFocus();
}

void Form_SignUp::on_le_password_2_returnPressed()
{
    ui->le_nickname->setFocus();
}

void Form_SignUp::on_le_nickname_returnPressed()
{
    this->on_btn_signUp_clicked();
}
