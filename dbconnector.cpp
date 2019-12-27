#include "dbconnector.h"
#include <QDebug>

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
