#include "searchmanual.h"
#include "ui_searchmanual.h"

#include "mapaobj.h"
#include "pointobj.h"

#include <QDebug>

SearchManual::SearchManual(const MapaObj* map, QWidget *parent) :
    QDialog{parent}, ui{new Ui::SearchManual}, _mapInUse{map}
{
    ui->setupUi(this);

    _connMapList = &_mapInUse->getConnList();

    const QStringList headerInfo{"Nome", "pos X", "pos Y", "Custo"};
    ui->tblPathChoice->setHorizontalHeaderLabels(headerInfo);
    ui->tblOptions->setHorizontalHeaderLabels(headerInfo);

    const auto& startPoint{_mapInUse->getPointByName("point_0_0")};

    addRow(ui->tblPathChoice, startPoint, 0);
    addOptions(startPoint);
}

SearchManual::~SearchManual()
{
    delete ui;
}

void SearchManual::addRow(QTableWidget* tbl, const std::shared_ptr<PointObj>& pointInfo, const uint8_t pointCost)
{
    const auto lastRow{tbl->rowCount()};

    tbl->setRowCount(lastRow+1);

    tbl->setItem(lastRow, 0, new QTableWidgetItem{QString::fromStdString(pointInfo->getName())});
    tbl->setItem(lastRow, 1, new QTableWidgetItem{QString::number(pointInfo->getX())});
    tbl->setItem(lastRow, 2, new QTableWidgetItem{QString::number(pointInfo->getY())});
    tbl->setItem(lastRow, 3, new QTableWidgetItem{QString::number(pointCost)});
}

void SearchManual::addOptions(const std::shared_ptr<PointObj>& startPoint)
{
    for(auto connsToPoint : _connMapList->getConnectedMapElem(startPoint))
    {
        const auto& pointConnected{_mapInUse->getPoint(connsToPoint.first)};
        addRow(ui->tblOptions, pointConnected, connsToPoint.second);

    }
}

void SearchManual::on_btnSelect_clicked()
{
    // It gets items in order
    const auto& selectedItems{ui->tblOptions->selectedItems()};
    if(selectedItems.size() == 4)
    {
        bool okConversionX{false};
        bool okConversionY{false};
        bool okConversionCost{false};

        const uint8_t xCoord{static_cast<uint8_t>(selectedItems.at(1)->text().toUInt(&okConversionX))};
        const uint8_t yCoord{static_cast<uint8_t>(selectedItems.at(2)->text().toUInt(&okConversionY))};
        const uint8_t connCost{static_cast<uint8_t>(selectedItems.at(3)->text().toUInt(&okConversionCost))};

        Q_ASSERT(okConversionX && okConversionY && okConversionCost);

        const auto& addPoint{_mapInUse->getPointByCoord(xCoord, yCoord)};
        addRow(ui->tblPathChoice, addPoint, connCost);

        ui->tblOptions->setRowCount(0);
        addOptions(addPoint);

    }
    else
    {
        qDebug() <<  "No selection";
    }

}

void SearchManual::on_btnBack_clicked()
{
    const auto pathCount{ui->tblPathChoice->rowCount()};
    if(pathCount > 1)
    {
        const auto newPathCount{pathCount-1};
        const auto itemsToGetInfo{newPathCount-1};


        ui->tblPathChoice->setRowCount(newPathCount);

        bool okConversionX{false};
        bool okConversionY{false};

        const auto xCoordCell{ui->tblPathChoice->item(itemsToGetInfo, 1)};
        const auto yCoordCell{ui->tblPathChoice->item(itemsToGetInfo, 2)};

        Q_ASSERT((nullptr != xCoordCell) && (nullptr != yCoordCell));

        const uint8_t xCoord{static_cast<uint8_t>(xCoordCell->text().toUInt(&okConversionX))};
        const uint8_t yCoord{static_cast<uint8_t>(yCoordCell->text().toUInt(&okConversionY))};

        Q_ASSERT(okConversionX && okConversionY);

        const auto& addPoint{_mapInUse->getPointByCoord(xCoord, yCoord)};

        ui->tblOptions->setRowCount(0);
        addOptions(addPoint);


    }
}









