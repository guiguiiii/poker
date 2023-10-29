#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    bool m_pressed;
    QPoint m_posMouse;

private:
    void loadQSS();

private slots:
    void on_btn_quit_clicked();
    void on_btn_minSize_clicked();

protected:
    bool eventFilter(QObject *target, QEvent *event);
};
#endif // MAINWINDOW_H
