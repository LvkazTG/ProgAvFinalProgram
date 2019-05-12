#include "mapvisual.h"
#include "ui_mapvisual.h"

#include "mapaobj.h"

MapVisual::MapVisual(const MapaObj* map,QWidget *parent) : QDialog{parent}, ui{new Ui::MapVisual{}}
{
    ui->setupUi(this);
    ui->mapDraw->addMap(map);

    ui->lnMapName->setText(QString::fromStdString(map->getName()));
    ui->lnXSize->setText(QString::number(map->getXSize()));
    ui->lnYSize->setText(QString::number(map->getYSize()));
}

MapVisual::~MapVisual()
{
    delete ui;
}

void MapVisual::on_btnClose_clicked()
{
    close();
}
