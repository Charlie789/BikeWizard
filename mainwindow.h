#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "customtypes.h"
#include <QStandardItemModel>

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
    QStandardItemModel* m_selected_parts_model;

public slots:
    void set_model(CustomTypes::PartType part_type, QSqlTableModel* model);
    void set_selected_parts_model(QStandardItemModel* model);

private slots:
    void select_part_button_clicked();
    void on_accept_pushbutton_clicked();

signals:
    void part_changed(CustomTypes::PartType part_type, QModelIndexList* list);
};
#endif // MAINWINDOW_H
