#include "progavprinc.h"
#include "ui_progavprinc.h"

#include "mapaobj.h"

#include <QDebug>

ProgAvPrinc::ProgAvPrinc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgAvPrinc)
{
    ui->setupUi(this);
}

ProgAvPrinc::~ProgAvPrinc()
{
    delete ui;
}

void ProgAvPrinc::on_btnTest_clicked()
{
    qDebug() << "Lets say Hello!";

//    MapaObj prinMap{40, 40};
    MapaObj prinMap{};
    prinMap.PrintConnectEdelems();
}
