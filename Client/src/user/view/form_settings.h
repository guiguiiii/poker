#ifndef FORM_SETTINGS_H
#define FORM_SETTINGS_H

#include <QWidget>

namespace Ui {
class Form_Settings;
}

class Form_Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Settings(QWidget *parent);
    ~Form_Settings();

signals:
/*    void signal_setSettings();    */
    void signal_cancel();

private:
    Ui::Form_Settings *ui;

private slots:
    void on_btn_cancel_clicked();
};

#endif // FORM_SETTINGS_H
