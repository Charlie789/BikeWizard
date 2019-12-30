#ifndef BIKEWIZARDAPPLICATION_H
#define BIKEWIZARDAPPLICATION_H

#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include "dbconnector.h"
#include "modelhandler.h"
#include "propertycontainter.h"

class BikeWizardApplication : public QApplication
{
    Q_OBJECT
public:
    explicit BikeWizardApplication(int &argc, char **argv);

private:
    MainWindow w;
    DbConnector db;
    ModelHandler m_model_handler;
    PropertyContainer m_prop_handler;

signals:
    void property_handler_ready(PropertyContainer* prop);

};

#endif // BIKEWIZARDAPPLICATION_H
