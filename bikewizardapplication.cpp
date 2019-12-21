#include "bikewizardapplication.h"

BikeWizardApplication::BikeWizardApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    w.show();

    connect(&w, &MainWindow::part_changed, &m_model_handler, &ModelHandler::set_properties);
    connect(&db, &DbConnector::db_ready, &m_model_handler, &ModelHandler::init);
    connect(&db, &DbConnector::model_ready, &m_model_handler, &ModelHandler::set_model);
    connect(&db, &DbConnector::model_ready, &w, &MainWindow::set_model);
    connect(&m_model_handler, &ModelHandler::map_part_table_ready, &db, &DbConnector::set_map_part);


    db.connect_to_db();
}
