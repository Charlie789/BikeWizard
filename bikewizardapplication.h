#ifndef BIKEWIZARDAPPLICATION_H
#define BIKEWIZARDAPPLICATION_H

#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include "dbconnector.h"
#include "modelhandler.h"
#include "propertycontainter.h"
#include "propertymanager.h"
#include "offergenerator.h"

class BikeWizardApplication : public QApplication
{
    Q_OBJECT
public:
    explicit BikeWizardApplication(int &argc, char **argv);

private:
    MainWindow w;
    DbConnector db;
    ModelHandler m_model_handler;
    PropertyContainer m_property_container;
    PropertyManager m_property_manager;
    OfferGenerator m_offer_generator;

signals:
    void property_container_ready(PropertyContainer* prop);

};

#endif // BIKEWIZARDAPPLICATION_H
