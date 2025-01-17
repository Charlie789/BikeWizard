#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "customtypes.h"
#include <QStandardItemModel>
#include <QPushButton>
#include <QPointer>
#include "backgroundcolordelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QSqlTableModel* m_model_frame;
    QSqlTableModel* m_model_fork;
    QSqlTableModel* m_model_front_wheel;
    QSqlTableModel* m_model_rear_wheel;
    QSqlTableModel* m_model_headset;
    QSqlTableModel* m_model_handlebar;
    QSqlTableModel* m_model_stem;
    QSqlTableModel* m_model_seatpost;
    QSqlTableModel* m_model_saddle;
    QSqlTableModel* m_model_tire;
    QSqlTableModel* m_model_inner_tube;
    QSqlTableModel* m_model_bb;
    QSqlTableModel* m_model_grip;
    QSqlTableModel* m_model_cassette;
    QSqlTableModel* m_model_chain;
    QSqlTableModel* m_model_rear_derailleur;
    QSqlTableModel* m_model_front_derailleur;
    QSqlTableModel* m_model_crank;
    QSqlTableModel* m_model_front_shifter;
    QSqlTableModel* m_model_rear_shifter;
    QSqlTableModel* m_model_front_disc;
    QSqlTableModel* m_model_rear_disc;
    QSqlTableModel* m_model_front_disc_brake_set;
    QSqlTableModel* m_model_rear_disc_brake_set;
    QSqlTableModel* m_model_front_vbrake;
    QSqlTableModel* m_model_rear_vbrake;
    QSqlTableModel* m_model_front_lever;
    QSqlTableModel* m_model_rear_lever;

    QSqlTableModel* m_model_bike;

    QStandardItemModel* m_selected_parts_model;

    int inner_tube_row;
    QPointer<QPushButton> inner_tube_button;
    QPointer<QPushButton> front_disc_button;
    QPointer<QPushButton> rear_disc_button;
    QPointer<QPushButton> front_disc_brake_set_button;
    QPointer<QPushButton> rear_disc_brake_set_button;
    QPointer<QPushButton> front_vbrake_button;
    QPointer<QPushButton> rear_vbrake_button;
    QPointer<QPushButton> front_lever_button;
    QPointer<QPushButton> rear_lever_button;

    QPushButton* add_select_button(int row_index);
    void add_delete_button(int row_index);

    BackgroundColorDelegate m_bg_delegate;

public slots:
    void set_model(CustomTypes::PartType part_type, QSqlTableModel* model);
    void set_bike_model(QSqlTableModel* model);
    void set_selected_parts_model(QStandardItemModel* model);
    void set_button_available(CustomTypes::PartType part_type);
    void set_button_unavailable(CustomTypes::PartType part_type);
    void part_loaded_from_db(CustomTypes::PartType part_type, QList<QString> *list);

private slots:
    void select_part_button_clicked();
    void delete_part_button_clicked();
    void on_accept_pushbutton_clicked();
    void prepare_delete_button(CustomTypes::PartType part_type, QList<QString> *);
    void on_back_pushbutton_clicked();
    void on_generate_offer_pushbutton_clicked();
    void on_part_tableview_clicked(const QModelIndex &index);
    void on_order_bike_pushbutton_clicked();
    void on_save_bike_pushbutton_clicked();
    void on_load_bike_pushbutton_clicked();
    void on_select_bike_pushbutton_clicked();
    void on_create_new_bike_pushbutton_clicked();

signals:
    void part_changed(CustomTypes::PartType part_type, QList<QString>* list);
    void part_has_to_be_remove(CustomTypes::PartType part_type);
    void unlock_part(CustomTypes::PartType part_type);
    void block_part(CustomTypes::PartType part_type);
    void generate_offer_pushbutton_clicked();
    void order_bike_pushbutton_clicked();
    void save_bike_pushbutton_clicked();
    void load_bike_pushbutton_clicked();
    void bike_selected(QList<QString>* part_list);
};
#endif // MAINWINDOW_H
