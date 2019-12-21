#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "customtypes.h"

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
    Ui::MainWindow *ui;
    QSqlTableModel* m_model_frame;
    QSqlTableModel* m_model_fork;

public slots:
    void set_model(QSqlTableModel* model, CustomTypes::PartType part_type);

private slots:
    void on_frame_tableview_clicked(const QModelIndex &index);
    void on_fork_tableview_clicked(const QModelIndex &index);

signals:
    void part_changed(CustomTypes::PartType part_type, const QString value);
};
#endif // MAINWINDOW_H
