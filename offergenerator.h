#ifndef OFFERGENERATOR_H
#define OFFERGENERATOR_H

#include <QObject>
#include <QStandardItemModel>

class OfferGenerator : public QObject
{
    Q_OBJECT
public:
    explicit OfferGenerator(QObject *parent = nullptr);

private:
    QStandardItemModel* m_selected_parts_model;
    double total_cost;

public slots:
    void set_selected_parts_model(QStandardItemModel* model);
    void generate_offer();
    QString generate_parts_header();
    QString generate_part_rows();
    QString generate_offer_frame();

signals:

};

#endif // OFFERGENERATOR_H
