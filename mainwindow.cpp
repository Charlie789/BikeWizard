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

void MainWindow::set_model(CustomTypes::PartType part_type, QSqlTableModel* model)
{
    switch (part_type){
    case CustomTypes::PartFrame:
        m_model_frame = model;
        break;
    case CustomTypes::PartFork:
        m_model_fork = model;
        ui->fork_tableview->setModel(m_model_fork);
        break;
    }
}

void MainWindow::set_selected_parts_model(QStandardItemModel* model)
{
    m_selected_parts_model = model;
    ui->selected_parts_tableview->setModel(m_selected_parts_model);

    for (int i = 0; i < m_selected_parts_model->rowCount(); ++i){
        QPushButton* select_button = new QPushButton("Wybierz");
        select_button->setProperty("part_type",m_selected_parts_model->data(m_selected_parts_model->index(i, TableProperties::SelectedParts::ColumnPartType)).toInt());
        ui->selected_parts_tableview->setIndexWidget(model->index(i, TableProperties::SelectedParts::ColumnPartType), select_button);
        ui->selected_parts_tableview->setColumnWidth(1, 400);
        ui->selected_parts_tableview->hideColumn(3);
        connect(select_button, &QPushButton::clicked, this, &MainWindow::select_part_button_clicked);
    }
}

void MainWindow::select_part_button_clicked()
{
    QObject* button = QObject::sender();
    CustomTypes::PartType part_type = (CustomTypes::PartType)button->property("part_type").toInt();
    switch (part_type){
    case CustomTypes::PartFrame:
        ui->part_tableview->setModel(m_model_frame);
        break;
    case CustomTypes::PartFork:
        ui->part_tableview->setModel(m_model_fork);
        break;
    }
    ui->part_tableview->setProperty("part_type", part_type);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_accept_pushbutton_clicked()
{
    CustomTypes::PartType part_type = (CustomTypes::PartType)ui->part_tableview->property("part_type").toInt();
    QModelIndexList list;
    for (int column = 0; column < ui->part_tableview->model()->columnCount(); column++) {
        QModelIndex index = ui->part_tableview->selectionModel()->currentIndex();
        list << (ui->part_tableview->model()->index(index.row(), column));
    }
    emit part_changed(part_type, &list);
    ui->stackedWidget->setCurrentIndex(0);
}
