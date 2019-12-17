#ifndef BIKEWIZARDAPPLICATION_H
#define BIKEWIZARDAPPLICATION_H

#include "mainwindow.h"
#include <QApplication>
#include <QObject>

class BikeWizardApplication : public QApplication
{
    Q_OBJECT
public:
    explicit BikeWizardApplication(int &argc, char **argv);

private:
    MainWindow w;

};

#endif // BIKEWIZARDAPPLICATION_H
