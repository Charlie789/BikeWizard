#include "bikewizardapplication.h"

BikeWizardApplication::BikeWizardApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
    w.showMaximized();

    connect(&w, &MainWindow::part_changed, &m_model_handler, &ModelHandler::set_selected_part);
    connect(&w, &MainWindow::part_changed, &m_model_handler, &ModelHandler::set_properties);
    connect(&w, &MainWindow::part_has_to_be_remove, &m_model_handler, &ModelHandler::delete_selected_part);
    connect(&w, &MainWindow::generate_offer_pushbutton_clicked, &m_offer_generator, &OfferGenerator::generate_offer);
    connect(&w, &MainWindow::order_bike_pushbutton_clicked, &m_order_bike, &OrderBike::order_bike);
    connect(&w, &MainWindow::save_bike_pushbutton_clicked, &m_model_handler, &ModelHandler::save_bike);
    connect(&w, &MainWindow::load_bike_pushbutton_clicked, &db, &DbConnector::create_bike_model);
    connect(&w, &MainWindow::bike_selected, &m_model_handler, &ModelHandler::set_parts);
    connect(&db, &DbConnector::db_ready, &m_model_handler, &ModelHandler::init_db);
    connect(&db, &DbConnector::model_ready, &m_model_handler, &ModelHandler::set_model);
    connect(&db, &DbConnector::model_ready, &w, &MainWindow::set_model);
    connect(&db, &DbConnector::bike_model_ready, &w, &MainWindow::set_bike_model);
    connect(&m_model_handler, &ModelHandler::map_part_table_ready, &db, &DbConnector::set_map_part);
    connect(&m_model_handler, &ModelHandler::selected_parts_model_ready, &w, &MainWindow::set_selected_parts_model);
    connect(&m_model_handler, &ModelHandler::selected_parts_model_ready, &m_offer_generator, &OfferGenerator::set_selected_parts_model);
    connect(&m_model_handler, &ModelHandler::selected_parts_model_ready, &m_order_bike, &OrderBike::set_selected_parts_model);
    connect(&m_model_handler, &ModelHandler::block_part, &w, &MainWindow::set_button_unavailable);
    connect(&m_model_handler, &ModelHandler::unlock_part, &w, &MainWindow::set_button_available);
    connect(&m_model_handler, &ModelHandler::property_attribute_list_ready, &m_property_manager, &PropertyManager::set_properties);
    connect(&m_model_handler, &ModelHandler::send_bike_to_save, &db, &DbConnector::insert_bike);
    connect(&m_model_handler, &ModelHandler::send_selected_part, &w, &MainWindow::part_loaded_from_db);
    connect(this, &BikeWizardApplication::property_container_ready, &m_model_handler, &ModelHandler::init_properties);
    connect(this, &BikeWizardApplication::property_container_ready, &m_property_manager, &PropertyManager::init_properties);
    connect(&m_property_container, &PropertyContainer::property_changed, &m_model_handler, &ModelHandler::filter_handler);
    connect(&m_property_container, &PropertyContainer::brake_property_changed, &m_model_handler, &ModelHandler::check_disc_allowed);
    connect(&m_order_bike, &OrderBike::send_part_ID, &db, &DbConnector::decrease_quantity);

    db.connect_to_db();
    emit property_container_ready(&m_property_container);
}
