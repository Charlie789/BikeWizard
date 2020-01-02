#include "offergenerator.h"
#include <QTextDocument>
#include <QPrinter>
#include <QDesktopServices>
#include <QDebug>
#include <QDate>
#include "customtypes.h"

OfferGenerator::OfferGenerator(QObject *parent) :
    QObject(parent),
    total_cost(0)
{

}

void OfferGenerator::set_selected_parts_model(QStandardItemModel *model)
{
    m_selected_parts_model = model;
}

void OfferGenerator::generate_offer()
{
    QString html = QString("%1"
                           "<p>&nbsp;</p>"
                           "<hr>"
                           "%2"
                           "<hr>"
                           "%4"
                           "<hr>"
                           "<p align=right>Koszt całkowity: %3 zł</p>"
                           "<br>"
                           "<br>"
                           "<br>"
                           "<br>"
                           "%5")
            .arg(generate_offer_frame())
            .arg(generate_parts_header())
            .arg(total_cost)
            .arg(generate_part_rows())
            .arg(generate_sign_space());
    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("offer.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);
    QDesktopServices::openUrl(QUrl("offer.pdf"));
}

QString OfferGenerator::generate_parts_header()
{
    QString table_headers = QString(
                    "<table width='100%'>"
                    "<tr>"
                    "<td width='5%'>Poz</td>"
                    "<td width='10%'>ID</td>"
                    "<td width='65%'>Nazwa</td>"
                    "<td width='10%'>Ilość</td>"
                    "<td width='10%'>Cena</td>"
                    "</tr>"
                    "</table>");
    return table_headers;
}

QString OfferGenerator::generate_part_rows()
{
    QString parts = "<table width='100%'>";
    for (int part_number = 0; part_number < m_selected_parts_model->rowCount(); part_number++){
        double price = m_selected_parts_model->data(m_selected_parts_model->index(part_number,TableProperties::SelectedParts::ColumnPartPrice)).toDouble();
        parts += QString(
                    "<tr>"
                    "<td width='5%'>%1</td>"
                    "<td width='10%'>%2</td>"
                    "<td width='65%'>%3</td>"
                    "<td width='10%'>%4</td>"
                    "<td width='10%'>%5</td>"
                    "</tr>")
                .arg(part_number + 1)
                .arg(m_selected_parts_model->data(m_selected_parts_model->index(part_number, TableProperties::SelectedParts::ColumnPartID)).toString())
                .arg(m_selected_parts_model->data(m_selected_parts_model->index(part_number, TableProperties::SelectedParts::ColumnPartName)).toString())
                .arg(1)
                .arg(QString::number(price) + " zł");
        total_cost += price;
    }
    parts += "</table>";
    return parts;
}

QString OfferGenerator::generate_offer_frame()
{
    QString offer_frame = QString("<table style=\"height: 125px; background-color:#000;\" cellspacing=\"0\" width=\"200\" align=right>"
                                "<tbody>"
                                "<tr>"
                                "<td style='padding:1px '>"
                                "<table width= 100% style='background-color:#fff;'>"
                                "<tr>"
                                "<td>Numer oferty: 1</td>"
                                "</tr>"
                                "<tr>"
                                "<td>Data wystawienia: %1</td>"
                                "</tr>"
                                "</td>"
                                "</tr>"
                                "</tbody>"
                                "</table>").arg(QDate::currentDate().toString("dd.MM.yyyy"));
    return offer_frame;
}

QString OfferGenerator::generate_sign_space()
{
    QString sign_space = QString(
                                "<table width=100%>"
                                "<tr>"
                                "<td width = 50% align = left>........................................</td>"
                                "<td width = 50% align = right>........................................</td>"
                                "</tr>"
                                "<tr>"
                                "<td width = 50% align = left>Podpis pracownika</td>"
                                "<td width = 50% align = right>Podpis klienta</td>"
                                "</tr>"
                                "</table>");

    return sign_space;
}
