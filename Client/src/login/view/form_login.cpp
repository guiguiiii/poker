#include "form_login.h"
#include "ui_form_login.h"

#include "src/common/view/widget_tips.h"

Form_Login::Form_Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Login)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
    ui->le_username->setFocus();
}

Form_Login::~Form_Login()
{
    delete ui;
}

void Form_Login::loginFailed(int status)
{
    if(status == 2){
        (new Widget_Tips(this, "登录", "密码有误，请重新输入"))->setVisible(true);
    }else if(status == 3){
        (new Widget_Tips(this, "登录", "输入的账号不存在"))->setVisible(true);
    }else if(status == 4){
        (new Widget_Tips(this, "登录", "登陆失败，账号已在线"))->setVisible(true);
    }
}

void Form_Login::on_btn_quit_clicked()
{
    QApplication::quit();
}

void Form_Login::on_btn_login_clicked()
{
    QString username = ui->le_username->text();
    QString password = ui->le_password->text();

    if(username == ""){
        (new Widget_Tips(this, "登录", "账号不能为空"))->setVisible(true);
    }else if(password == ""){
        (new Widget_Tips(this, "登录", "密码不能为空"))->setVisible(true);
    }else if(username.size() > 20){
        (new Widget_Tips(this, "登录", "账号过长，请重新输入"))->setVisible(true);
    }else if(password.size() > 20){
        (new Widget_Tips(this, "登录", "密码过长，请重新输入"))->setVisible(true);

    }else{
        LoginData loginData(username,password);
        emit signal_login(loginData);
    }
}

void Form_Login::on_btn_signUp_clicked()
{
    emit signal_moveToSignUp();
}

void Form_Login::on_le_username_returnPressed()
{
    ui->le_password->setFocus();
}

void Form_Login::on_le_password_returnPressed()
{
    this->on_btn_login_clicked();
}
