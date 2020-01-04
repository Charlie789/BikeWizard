#include "dbconnector.h"
#include <QDebug>
#include <QSqlQuery>

DbConnector::DbConnector(QObject *parent) : QObject(parent)
{

}

void DbConnector::connect_to_db()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("bike_wizard");
    db.setUserName("root");
    db.setPassword("");
    if (db.open())
        emit db_ready(&db);
    else
        qWarning() << "Nie udało się otworzyć połączenia z bazą danych!";
}

void DbConnector::set_map_part(QMap<CustomTypes::PartType, QString> map_part_table)
{
    m_map_part_table = map_part_table;
    create_models();
}

void DbConnector::create_models()
{
    for(auto e : m_map_part_table.keys()){
        QSqlTableModel *model = new QSqlTableModel(this, db);
        model->setTable(m_map_part_table.value(e));
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();
        emit model_ready(e, model);
    }
}

void DbConnector::decrease_quantity(QString part_ID, int quantity)
{
    QSqlQuery query(QString("UPDATE part SET quantity = quantity - %1 WHERE ID_part = %2;").arg(quantity).arg(part_ID));
    query.exec(part_ID);
}

void DbConnector::insert_bike(QStringList part_list, QStringList part_id_list)
{
    for (int i = 0; i < part_id_list.length(); i++){
        if (part_id_list[i] == "-1")
            part_id_list[i] = "NULL";
    }
    QString query_string = QString("INSERT INTO bike (%1) VALUES (%2)").arg(part_list.join(", ")).arg(part_id_list.join(", "));
    qDebug() << query_string;
    QSqlQuery query;
    query.exec(query_string);
}
