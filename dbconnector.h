#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "customtypes.h"

class DbConnector : public QObject
{
    Q_OBJECT
public:
    explicit DbConnector(QObject *parent = nullptr);

    void connect_to_db();
    void set_map_part(QMap<CustomTypes::PartType, QString> map_part_table);
    void create_models();
    void decrease_quantity(QString part_ID, int quantity);
    void insert_bike(QStringList part_list, QStringList part_id_list);
    void create_bike_model();

private:
    QSqlDatabase db;
    QMap<CustomTypes::PartType, QString> m_map_part_table;

signals:
    void db_ready(QSqlDatabase* db);
    void model_ready(CustomTypes::PartType part_type, QSqlTableModel* model);
    void bike_model_ready(QSqlTableModel* model);

};

#endif // DBCONNECTOR_H
