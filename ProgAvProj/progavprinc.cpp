#include "progavprinc.h"
#include "ui_progavprinc.h"

#include "mapaobj.h"
#include "jsonop.h"

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
    qDebug() << "1 - Lets say Hello!";

    MapaObj prinMap{5, 5};
    prinMap.createNew();
//    MapaObj prinMap{};
    prinMap.PrintConnectEdelems();
    prinMap.setName("Lucas_test");

    JsonOp jsonOperator{};
    jsonOperator.saveMap(prinMap, "/home/lvkaz/teste_json.json");
}

void ProgAvPrinc::on_btnTest2_clicked()
{
    qDebug() << "2- Lets say Hello!";

    MapaObj prinMap{5, 5};
    prinMap.createNew();
//    MapaObj prinMap{};
    prinMap.PrintConnectEdelems();
    prinMap.setName("Lucas_test");

    JsonOp jsonOperator{};
    jsonOperator.saveMap(prinMap, "/home/lvkaz/teste_json.json");

}
