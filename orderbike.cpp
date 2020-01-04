#include "orderbike.h"
#include <QDebug>
#include <QTextDocument>
#include <QPrinter>
#include <QDesktopServices>
#include <QDebug>
#include <QDate>

OrderBike::OrderBike(QObject *parent) : QObject(parent)
{

}

QString OrderBike::generate_order_frame()
{
    QString offer_frame = QString("<table style=\"height: 125px; background-color:#000;\" cellspacing=\"0\" width=\"200\" align=right>"
                                "<tbody>"
                                "<tr>"
                                "<td style='padding:1px '>"
                                "<table width= 100% style='background-color:#fff;'>"
                                "<tr>"
                                "<td>Numer przesunięcia: 1</td>"
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

QString OrderBike::generate_parts_header()
{
    QString table_headers = QString(
                    "<table width='100%' border = '1' cellspacing = '0'>"
                    "<tr>"
                    "<td width='5%'><b>Poz</b></td>"
                    "<td width='10%'><b>ID</b></td>"
                    "<td width='65%'><b>Nazwa</b></td>"
                    "<td width='10%'><b>Ilość</b></td>"
                    "</tr>");
    return table_headers;
}

QString OrderBike::generate_part_rows()
{
    QString parts = generate_parts_header();
    for (int part_number = 0; part_number < m_selected_parts_model->rowCount(); part_number++){
        if (m_selected_parts_model->data(m_selected_parts_model->index(part_number, TableProperties::SelectedParts::ColumnPartID)).toString() == "-1") {
            continue;
        }
        int quantity = 1;
        if (part_number == CustomTypes::PartTire || part_number == CustomTypes::PartInnerTube)
            quantity = 2;
        parts += QString(
                    "<tr>"
                    "<td width='5%'>%1</td>"
                    "<td width='10%'>%2</td>"
                    "<td width='65%'>%3</td>"
                    "<td width='10%'>%4</td>"
                    "</tr>")
                .arg(part_number + 1)
                .arg(m_selected_parts_model->data(m_selected_parts_model->index(part_number, TableProperties::SelectedParts::ColumnPartID)).toString())
                .arg(m_selected_parts_model->data(m_selected_parts_model->index(part_number, TableProperties::SelectedParts::ColumnPartName)).toString())
                .arg(quantity);
    }
    parts += "</table>";
    return parts;
}

QString OrderBike::generate_sign_space()
{
    QString sign_space = QString(
                                "<table width=100%>"
                                "<tr>"
                                "<td width = 50% align = left>..............................................</td>"
                                "<td width = 50% align = right>..............................................</td>"
                                "</tr>"
                                "<tr>"
                                "<td width = 50% align = left>Podpis osoby wystawiającej</td>"
                                "<td width = 50% align = right>Podpis osoby przyjmującej</td>"
                                "</tr>"
                                "</table>");

    return sign_space;
}

void OrderBike::order_bike()
{
    //decrease_quantity();
    generate_order();
}

void OrderBike::set_selected_parts_model(QStandardItemModel* model)
{
    m_selected_parts_model = model;
}

void OrderBike::generate_order()
{
    QString html = QString("%1"
                           "<p>&nbsp;</p>"
                           "%2"
                           "<br>"
                           "<br>"
                           "<br>"
                           "%3")
            .arg(generate_order_frame())
            .arg(generate_part_rows())
            .arg(generate_sign_space());
    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName("order.pdf");
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);
    QDesktopServices::openUrl(QUrl("order.pdf"));
}

void OrderBike::decrease_quantity()
{
    for (int i = 0; i < m_selected_parts_model->rowCount(); i++){
        if (m_selected_parts_model->item(i, TableProperties::SelectedParts::ColumnPartID)->data(Qt::DisplayRole).toString() == "-1")
            continue;
        QString part_ID = m_selected_parts_model->item(i, TableProperties::SelectedParts::ColumnPartID)->data(Qt::DisplayRole).toString();
        if (i == CustomTypes::PartTire || i == CustomTypes::PartInnerTube)
            emit send_part_ID(part_ID, 2);
        else
            emit send_part_ID(part_ID, 1);
    }
}
