#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../main_controller.h"

#include <QFile>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    // Init window
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // ( event: move window )
    m_pressed = false;
    ui->Widget_TitleBar->installEventFilter(this);

    // ( style )
    this->loadQSS();
    ui->lbl_icon->setPixmap(QPixmap(":/icons/poker.png"));

    // Init main_controller and start it
    Main_Controller *main_controller = new Main_Controller(ui->Widget);
    ui->Widget->layout()->addWidget(main_controller);
    main_controller->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadQSS()
{
    QFile file(":/qss/style.qss");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    this->setStyleSheet(file.readAll());
    file.close();
}

void MainWindow::on_btn_quit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_btn_minSize_clicked()
{
    this->showMinimized();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){
        if(target->objectName() == ui->Widget_TitleBar->objectName()){
            m_pressed = true;
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent != nullptr){
                m_posMouse = mouseEvent->globalPosition().toPoint();
                event->ignore();
            }
        }

    }else if(event->type() == QEvent::MouseMove){
        if(m_pressed == true){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent != nullptr){
                QPoint posMouse = mouseEvent->globalPosition().toPoint();
                this->move(this->geometry().topLeft() + posMouse - m_posMouse);
                m_posMouse = posMouse;
                event->ignore();
            }
        }

    }else if(event->type() == QEvent::MouseButtonRelease){
        m_pressed = false;
    }

    return QWidget::eventFilter(target,event);
}
