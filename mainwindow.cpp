#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_model(QSqlTableModel *model, CustomTypes::PartType part_type)
{
    switch (part_type){
    case CustomTypes::PartFrame:
        m_model_frame = model;
        ui->frame_tableview->setModel(m_model_frame);
        break;
    case CustomTypes::PartFork:
        m_model_fork = model;
        ui->fork_tableview->setModel(m_model_fork);
        break;
    }
}

void MainWindow::on_frame_tableview_clicked(const QModelIndex &index)
{
    emit part_changed(CustomTypes::PartFrame, m_model_frame->data(m_model_frame->index(index.row(), 2)).toString());
}

void MainWindow::on_fork_tableview_clicked(const QModelIndex &index)
{
    emit part_changed(CustomTypes::PartFork, m_model_fork->data(m_model_fork->index(index.row(), 2)).toString());
}
