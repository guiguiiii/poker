#ifndef FORM_START_H
#define FORM_START_H

#include <QWidget>

namespace Ui {
class Form_Start;
}

class Form_Start : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Start(QWidget *parent);
    ~Form_Start();

signals:
    void signal_moveToGameHub();
    void signal_moveToPersonal();
    void signal_moveToSettings();

private:
    Ui::Form_Start *ui;

private slots:
    void on_btn_gameHub_clicked();
    void on_btn_personal_clicked();
    void on_btn_settings_clicked();
};

#endif // FORM_START_H
