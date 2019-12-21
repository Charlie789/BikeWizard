#ifndef BIKEWIZARDAPPLICATION_H
#define BIKEWIZARDAPPLICATION_H

#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include "dbconnector.h"
#include "modelhandler.h"

class BikeWizardApplication : public QApplication
{
    Q_OBJECT
public:
    explicit BikeWizardApplication(int &argc, char **argv);

private:
    MainWindow w;
    DbConnector db;
    ModelHandler m_model_handler;

};

#endif // BIKEWIZARDAPPLICATION_H
