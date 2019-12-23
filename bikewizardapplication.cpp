#include "bikewizardapplication.h"

BikeWizardApplication::BikeWizardApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    w.show();

    connect(&w, &MainWindow::part_changed, &m_model_handler, &ModelHandler::set_selected_part);
    connect(&w, &MainWindow::part_changed, &m_model_handler, &ModelHandler::set_properties);
    connect(&w, &MainWindow::part_has_to_be_remove, &m_model_handler, &ModelHandler::delete_selected_part);
    connect(&db, &DbConnector::db_ready, &m_model_handler, &ModelHandler::init);
    connect(&db, &DbConnector::model_ready, &m_model_handler, &ModelHandler::set_model);
    connect(&db, &DbConnector::model_ready, &w, &MainWindow::set_model);
    connect(&m_model_handler, &ModelHandler::map_part_table_ready, &db, &DbConnector::set_map_part);
    connect(&m_model_handler, &ModelHandler::selected_parts_model_ready, &w, &MainWindow::set_selected_parts_model);


    db.connect_to_db();
}
