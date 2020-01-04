#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, &MainWindow::part_changed, this, &MainWindow::prepare_delete_button);
    connect(this, &MainWindow::unlock_part, this, &MainWindow::set_button_available);
    connect(this, &MainWindow::block_part, this, &MainWindow::set_button_unavailable);
    ui->part_tableview->setItemDelegate(&m_bg_delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton* MainWindow::add_select_button(int row_index)
{
    QPushButton* select_button = new QPushButton("Wybierz");
    select_button->setProperty("part_type",m_selected_parts_model->data(m_selected_parts_model->index(row_index, TableProperties::SelectedParts::ColumnPartType)).toInt());
    ui->selected_parts_tableview->setIndexWidget(m_selected_parts_model->index(row_index, TableProperties::SelectedParts::ColumnPartType), select_button);
    connect(select_button, &QPushButton::clicked, this, &MainWindow::select_part_button_clicked);

    return select_button;
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
    case CustomTypes::PartSeatpost:
        m_model_seatpost = model;
        break;
    case CustomTypes::PartSaddle:
        m_model_saddle = model;
        break;
    case CustomTypes::PartTire:
        m_model_tire = model;
        break;
    case CustomTypes::PartInnerTube:
        m_model_inner_tube = model;
        break;
    case CustomTypes::PartBB:
        m_model_bb = model;
        break;
    case CustomTypes::PartGrip:
        m_model_grip = model;
        break;
    case CustomTypes::PartCassette:
        m_model_cassette = model;
        break;
    case CustomTypes::PartChain:
        m_model_chain = model;
        break;
    case CustomTypes::PartRearDerailleur:
        m_model_rear_derailleur = model;
        break;
    case CustomTypes::PartFrontDerailleur:
        m_model_front_derailleur = model;
        break;
    case CustomTypes::PartCrank:
        m_model_crank = model;
        break;
    case CustomTypes::PartFrontShifter:
        m_model_front_shifter = model;
        break;
    case CustomTypes::PartRearShifter:
        m_model_rear_shifter = model;
        break;
    case CustomTypes::PartFrontDisc:
        m_model_front_disc = model;
        break;
    case CustomTypes::PartRearDisc:
        m_model_rear_disc = model;
        break;
    case CustomTypes::PartFrontDiscBrakeSet:
        m_model_front_disc_brake_set = model;
        break;
    case CustomTypes::PartRearDiscBrakeSet:
        m_model_rear_disc_brake_set = model;
        break;
    case CustomTypes::PartFrontVBrake:
        m_model_front_vbrake = model;
        break;
    case CustomTypes::PartRearVBrake:
        m_model_rear_vbrake = model;
        break;
    case CustomTypes::PartFrontLever:
        m_model_front_lever = model;
        break;
    case CustomTypes::PartRearLever:
        m_model_rear_lever = model;
        break;
    }
}

void MainWindow::set_selected_parts_model(QStandardItemModel* model)
{
    m_selected_parts_model = model;
    ui->selected_parts_tableview->setModel(m_selected_parts_model);

    for (int i = 0; i < m_selected_parts_model->rowCount(); ++i){
        if (i == CustomTypes::PartInnerTube){
            inner_tube_button = add_select_button(i);
            inner_tube_button->setEnabled(false);
            inner_tube_row = i;
        } else if(i == CustomTypes::PartFrontDisc) {
            front_disc_button = add_select_button(i);
        } else if(i == CustomTypes::PartRearDisc) {
            rear_disc_button = add_select_button(i);
        } else if(i == CustomTypes::PartFrontDiscBrakeSet) {
            front_disc_brake_set_button = add_select_button(i);
        } else if(i == CustomTypes::PartRearDiscBrakeSet) {
            rear_disc_brake_set_button = add_select_button(i);
        } else if(i == CustomTypes::PartFrontVBrake) {
            front_vbrake_button = add_select_button(i);
        } else if(i == CustomTypes::PartRearVBrake) {
            rear_vbrake_button = add_select_button(i);
        } else if(i == CustomTypes::PartFrontLever) {
            front_lever_button = add_select_button(i);
        } else if(i == CustomTypes::PartRearLever) {
            rear_lever_button = add_select_button(i);
        } else {
            add_select_button(i);
        }
    }
    ui->selected_parts_tableview->setColumnWidth(TableProperties::SelectedParts::ColumnPartName, 500);
    ui->selected_parts_tableview->hideColumn(TableProperties::SelectedParts::ColumnPartID);
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
    case CustomTypes::PartSeatpost:
        ui->part_tableview->setModel(m_model_seatpost);
        break;
    case CustomTypes::PartSaddle:
        ui->part_tableview->setModel(m_model_saddle);
        break;
    case CustomTypes::PartTire:
        ui->part_tableview->setModel(m_model_tire);
        break;
    case CustomTypes::PartInnerTube:
        ui->part_tableview->setModel(m_model_inner_tube);
        break;
    case CustomTypes::PartBB:
        ui->part_tableview->setModel(m_model_bb);
        break;
    case CustomTypes::PartGrip:
        ui->part_tableview->setModel(m_model_grip);
        break;
    case CustomTypes::PartCassette:
        ui->part_tableview->setModel(m_model_cassette);
        break;
    case CustomTypes::PartChain:
        ui->part_tableview->setModel(m_model_chain);
        break;
    case CustomTypes::PartRearDerailleur:
        ui->part_tableview->setModel(m_model_rear_derailleur);
        break;
    case CustomTypes::PartFrontDerailleur:
        ui->part_tableview->setModel(m_model_front_derailleur);
        break;
    case CustomTypes::PartCrank:
        ui->part_tableview->setModel(m_model_crank);
        break;
    case CustomTypes::PartFrontShifter:
        ui->part_tableview->setModel(m_model_front_shifter);
        break;
    case CustomTypes::PartRearShifter:
        ui->part_tableview->setModel(m_model_rear_shifter);
        break;
    case CustomTypes::PartFrontDisc:
        ui->part_tableview->setModel(m_model_front_disc);
        break;
    case CustomTypes::PartRearDisc:
        ui->part_tableview->setModel(m_model_rear_disc);
        break;
    case CustomTypes::PartFrontDiscBrakeSet:
        ui->part_tableview->setModel(m_model_front_disc_brake_set);
        break;
    case CustomTypes::PartRearDiscBrakeSet:
        ui->part_tableview->setModel(m_model_rear_disc_brake_set);
        break;
    case CustomTypes::PartFrontVBrake:
        ui->part_tableview->setModel(m_model_front_vbrake);
        break;
    case CustomTypes::PartRearVBrake:
        ui->part_tableview->setModel(m_model_rear_vbrake);
        break;
    case CustomTypes::PartFrontLever:
        ui->part_tableview->setModel(m_model_front_lever);
        break;
    case CustomTypes::PartRearLever:
        ui->part_tableview->setModel(m_model_rear_lever);
        break;
    }
    ui->part_tableview->hideColumn(TableProperties::Parts::ColumnID);
    ui->part_tableview->setColumnWidth(TableProperties::Parts::ColumnCompany, 200);
    ui->part_tableview->setColumnWidth(TableProperties::Parts::ColumnName, 400);
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
            if(part_type == CustomTypes::PartFrontDisc) {
                front_disc_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartRearDisc) {
                rear_disc_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartFrontDiscBrakeSet) {
                front_disc_brake_set_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartRearDiscBrakeSet) {
                rear_disc_brake_set_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartFrontVBrake) {
                front_vbrake_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartRearVBrake) {
                rear_vbrake_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartFrontLever) {
                front_lever_button = add_select_button(i);
            } else if(part_type == CustomTypes::PartRearLever) {
                rear_lever_button = add_select_button(i);
            } else {
                add_select_button(i);
            }
        }
    }
    emit part_has_to_be_remove(part_type);
    if(part_type == CustomTypes::PartTire){
        emit part_has_to_be_remove(CustomTypes::PartInnerTube);
        inner_tube_button = add_select_button(inner_tube_row);
        emit block_part(CustomTypes::PartInnerTube);
    }
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
    if(part_type == CustomTypes::PartTire)
        emit unlock_part(CustomTypes::PartInnerTube);
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

void MainWindow::set_button_available(CustomTypes::PartType part_type)
{
    switch (part_type){
    case CustomTypes::PartInnerTube:
        if(inner_tube_button)
            inner_tube_button->setEnabled(true);
        break;
    case CustomTypes::PartFrontDisc:
        if(front_disc_button)
            front_disc_button->setEnabled(true);
        break;
    case CustomTypes::PartRearDisc:
        if(rear_disc_button)
            rear_disc_button->setEnabled(true);
        break;
    case CustomTypes::PartFrontDiscBrakeSet:
        if(front_disc_brake_set_button)
            front_disc_brake_set_button->setEnabled(true);
        break;
    case CustomTypes::PartRearDiscBrakeSet:
        if(rear_disc_brake_set_button)
            rear_disc_brake_set_button->setEnabled(true);
        break;
    case CustomTypes::PartFrontVBrake:
        if(front_vbrake_button)
            front_vbrake_button->setEnabled(true);
        break;
    case CustomTypes::PartRearVBrake:
        if(rear_vbrake_button)
            rear_vbrake_button->setEnabled(true);
        break;
    case CustomTypes::PartFrontLever:
        if(front_lever_button)
            front_lever_button->setEnabled(true);
        break;
    case CustomTypes::PartRearLever:
        if(rear_lever_button)
            rear_lever_button->setEnabled(true);
        break;
    default:
        break;
    }
}

void MainWindow::set_button_unavailable(CustomTypes::PartType part_type)
{
    switch (part_type){
    case CustomTypes::PartInnerTube:
        if(inner_tube_button)
            inner_tube_button->setEnabled(false);
        break;
    case CustomTypes::PartFrontDisc:
        if(front_disc_button)
            front_disc_button->setEnabled(false);
        break;
    case CustomTypes::PartRearDisc:
        if(rear_disc_button)
            rear_disc_button->setEnabled(false);
        break;
    case CustomTypes::PartFrontDiscBrakeSet:
        if(front_disc_brake_set_button)
            front_disc_brake_set_button->setEnabled(false);
        break;
    case CustomTypes::PartRearDiscBrakeSet:
        if(rear_disc_brake_set_button)
            rear_disc_brake_set_button->setEnabled(false);
        break;
    case CustomTypes::PartFrontVBrake:
        if(front_vbrake_button)
            front_vbrake_button->setEnabled(false);
        break;
    case CustomTypes::PartRearVBrake:
        if(rear_vbrake_button)
            rear_vbrake_button->setEnabled(false);
        break;
    case CustomTypes::PartFrontLever:
        if(front_lever_button)
            front_lever_button->setEnabled(false);
        break;
    case CustomTypes::PartRearLever:
        if(rear_lever_button)
            rear_lever_button->setEnabled(false);
        break;
    default:
        break;
    }
}

void MainWindow::on_generate_offer_pushbutton_clicked()
{
    emit generate_offer_pushbutton_clicked();
}

void MainWindow::on_part_tableview_clicked(const QModelIndex &index)
{
    int quantity_column = index.model()->columnCount();
    if (index.sibling(index.row(), quantity_column - 2).data().toInt() == 0)
        ui->accept_pushbutton->setDisabled(true);
    else
        ui->accept_pushbutton->setDisabled(false);
}

void MainWindow::on_order_bike_pushbutton_clicked()
{
    emit order_bike_pushbutton_clicked();
}

void MainWindow::on_save_bike_pushbutton_clicked()
{
    emit save_bike_pushbutton_clicked();
}
