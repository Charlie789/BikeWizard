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

private:
    QSqlDatabase db;
    QMap<CustomTypes::PartType, QString> m_map_part_table;

signals:
    void db_ready(QSqlDatabase* db);
    void model_ready(QSqlTableModel* model, CustomTypes::PartType part_type);

};

#endif // DBCONNECTOR_H
