#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::part_changed, this, &MainWindow::prepare_delete_button);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_select_button(int row_index)
{
    QPushButton* select_button = new QPushButton("Wybierz");
    select_button->setProperty("part_type",m_selected_parts_model->data(m_selected_parts_model->index(row_index, TableProperties::SelectedParts::ColumnPartType)).toInt());
    ui->selected_parts_tableview->setIndexWidget(m_selected_parts_model->index(row_index, TableProperties::SelectedParts::ColumnPartType), select_button);
    connect(select_button, &QPushButton::clicked, this, &MainWindow::select_part_button_clicked);
}

void MainWindow::add_delete_button(int row_index)
{
    QPushButton* delete_button = new QPushButton("Usuń");
    delete_button->setProperty("part_type",m_selected_parts_model->data(m_selected_parts_model->index(row_index, TableProperties::SelectedParts::ColumnPartType)).toInt());
    ui->selected_parts_tableview->setIndexWidget(m_selected_parts_model->index(row_index, TableProperties::SelectedParts::ColumnPartType), delete_button);
    connect(delete_button, &QPushButton::clicked, this, &MainWindow::delete_part_button_clicked);
    connect(delete_button, &QPushButton::clicked, delete_button, &QPushButton::deleteLater);
}

void MainWindow::set_model(CustomTypes::PartType part_type, QSqlTableModel* model)
{
    switch (part_type){
    case CustomTypes::PartFrame:
        m_model_frame = model;
        break;
    case CustomTypes::PartFork:
        m_model_fork = model;
        break;
    case CustomTypes::PartFrontWheel:
        m_model_front_wheel = model;
        break;
    case CustomTypes::PartRearWheel:
        m_model_rear_wheel = model;
        break;
    case CustomTypes::PartHeadset:
        m_model_headset = model;
        break;
    case CustomTypes::PartHandlebar:
        m_model_handlebar = model;
        break;
    case CustomTypes::PartStem:
        m_model_stem = model;
        break;
    }
}

void MainWindow::set_selected_parts_model(QStandardItemModel* model)
{
    m_selected_parts_model = model;
    ui->selected_parts_tableview->setModel(m_selected_parts_model);

    for (int i = 0; i < m_selected_parts_model->rowCount(); ++i){
        add_select_button(i);
        ui->selected_parts_tableview->setColumnWidth(1, 400);
        ui->selected_parts_tableview->hideColumn(3);
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
    case CustomTypes::PartFrontWheel:
        ui->part_tableview->setModel(m_model_front_wheel);
        break;
    case CustomTypes::PartRearWheel:
        ui->part_tableview->setModel(m_model_rear_wheel);
        break;
    case CustomTypes::PartHeadset:
        ui->part_tableview->setModel(m_model_headset);
        break;
    case CustomTypes::PartHandlebar:
        ui->part_tableview->setModel(m_model_handlebar);
        break;
    case CustomTypes::PartStem:
        ui->part_tableview->setModel(m_model_stem);
        break;
    }
    ui->part_tableview->hideColumn(2);
    ui->part_tableview->setProperty("part_type", part_type);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::delete_part_button_clicked()
{
    QObject* button = QObject::sender();
    CustomTypes::PartType part_type = (CustomTypes::PartType)button->property("part_type").toInt();
    for (int i = 0; i < ui->selected_parts_tableview->model()->rowCount(); ++i){
        QModelIndex index_part_type = ui->selected_parts_tableview->model()->index(i, TableProperties::SelectedParts::ColumnPartType);
        if (ui->selected_parts_tableview->model()->data(index_part_type).toInt() == part_type){
            add_select_button(i);
        }
    }
    emit part_has_to_be_remove(part_type);
}

void MainWindow::on_accept_pushbutton_clicked()
{
    CustomTypes::PartType part_type = (CustomTypes::PartType)ui->part_tableview->property("part_type").toInt();
    QList<QString> list;
    QModelIndex index = ui->part_tableview->selectionModel()->currentIndex();
    for (int column = 0; column < ui->part_tableview->model()->columnCount(); column++) {
        list << ui->part_tableview->model()->index(index.row(), column).data().toString();
    }
    emit part_changed(part_type, &list);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::prepare_delete_button(CustomTypes::PartType part_type, QList<QString> *)
{
    for (int i = 0; i < ui->selected_parts_tableview->model()->rowCount(); ++i){
        QModelIndex index_part_type = ui->selected_parts_tableview->model()->index(i, TableProperties::SelectedParts::ColumnPartType);
        if (ui->selected_parts_tableview->model()->data(index_part_type).toInt() == part_type){
            add_delete_button(i);
        }
    }
}

void MainWindow::on_back_pushbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
