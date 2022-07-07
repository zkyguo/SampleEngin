#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionDrawSomething_triggered()
{
    ui->openGLWidget->drawShape(seopenglwidget::Shape::Rect);
}

void MainWindow::on_actionClear_triggered()
{
    ui->openGLWidget->drawShape(seopenglwidget::Shape::None);
}

void MainWindow::on_actionWireFrame_triggered()
{
    ui->openGLWidget->setWireFrame(ui->actionWireFrame->isChecked());
}


