#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../controller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Init main_controller
    new Controller(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
