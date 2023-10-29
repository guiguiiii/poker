#include "form_personal.h"
#include "ui_form_personal.h"

#include "widget_setpfp.h"
#include "src/common/view/widget_tips.h"
#include "src/common/view/widget_pfp.h"

Form_Personal::Form_Personal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Personal)
{
    ui->setupUi(this);
    ui->BACKGROUND->setPixmap(QPixmap(":/images/background.jpg"));
}

Form_Personal::~Form_Personal()
{
    delete ui;
}

void Form_Personal::initPersonalData(const UserData &userData)
{
    ui->le_username->setText(userData.username());
    ui->le_password->setText(userData.password());
    ui->le_nickname->setText(userData.nickname());
    ui->te_signature->setText(userData.signature());
    ui->lbl_pfp->setPixmap(userData.pfp());
    m_pfp = userData.pfp();
}

void Form_Personal::setPersonalStatus(int status)
{
    if(status == 1){
        (new Widget_Tips(this, "个人信息", "个人信息设置成功！"))->setVisible(true);
    }else if(status == 2){
        (new Widget_Tips(this, "个人信息", "账号已存在，请重新输入"))->setVisible(true);
    }
}

void Form_Personal::on_btn_ok_clicked()
{
    QString username = ui->le_username->text();
    QString password = ui->le_password->text();
    QString nickname = ui->le_nickname->text();
    QString signature = ui->te_signature->toPlainText();

    if(username == ""){
        (new Widget_Tips(this, "个人信息", "账号不能为空"))->setVisible(true);
    }else if(password == ""){
        (new Widget_Tips(this, "个人信息", "密码不能为空"))->setVisible(true);
    }else if(nickname == ""){
        (new Widget_Tips(this, "个人信息", "昵称不能为空"))->setVisible(true);
    }else if(username.size() > 20){
        (new Widget_Tips(this, "个人信息", "账号过长，请重新输入"))->setVisible(true);
    }else if(password.size() > 20){
        (new Widget_Tips(this, "个人信息", "密码过长，请重新输入"))->setVisible(true);
    }else if(nickname.size() > 20){
        (new Widget_Tips(this, "个人信息", "昵称过长，请重新输入"))->setVisible(true);

    }else{
        UserData userData(username,password,nickname,signature,m_pfp);
        emit signal_setPersonal(userData);
    }
}

void Form_Personal::on_btn_cancel_clicked()
{
    emit signal_cancel();
}

void Form_Personal::on_btn_pfp_clicked()
{
    (new Widget_PFP(this, m_pfp))->setVisible(true);
}

void Form_Personal::on_btn_setPFP_clicked()
{
    Widget_SetPFP *widget_setPFP = new Widget_SetPFP(this);
    connect(widget_setPFP, &Widget_SetPFP::signal_savePFP, this, [=](const QPixmap &pfp){
        ui->lbl_pfp->setPixmap(pfp);
        m_pfp = pfp;
    });
    widget_setPFP->setVisible(true);
}

void Form_Personal::on_le_nickname_returnPressed()
{
    ui->le_username->setFocus();
}

void Form_Personal::on_le_username_returnPressed()
{
    ui->le_password->setFocus();
}

void Form_Personal::on_le_password_returnPressed()
{
    ui->te_signature->setFocus();
}
