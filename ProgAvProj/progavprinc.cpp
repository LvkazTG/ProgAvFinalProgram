#include "progavprinc.h"
#include "ui_progavprinc.h"

#include "mapaobj.h"

#include "jsonop.h"
#include "xmlop.h"

#include "searchdeep.h"

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
    prinMap.setName("Lucas_test_2");

    JsonOp jsonOperator{};
    jsonOperator.saveMap(prinMap, "/home/lvkaz/teste_json_ease.json");

    xmlOp xmlOperator{};
    xmlOperator.saveMap(prinMap, "/home/lvkaz/teste_xml_ease.xml");

}

void ProgAvPrinc::on_btnTest2_clicked()
{
    qDebug() << "2- Lets say Hello!";

//    JsonOp jsonOperator{};
//    const auto mapLoad{jsonOperator.loadMap("/home/lvkaz/teste_json.json")};
//    mapLoad.PrintConnectEdelems();
//    qDebug() << QString::fromStdString(mapLoad.getName());

//    xmlOp xmlOperator{};
//    xmlOperator.saveMap(mapLoad, "/home/lvkaz/teste_xml.xml");

//    xmlOp xmlOperator{};
//    const auto mapLoad{xmlOperator.loadMap("/home/lvkaz/teste_xml.xml")};
//    mapLoad.PrintConnectEdelems();
//    qDebug() << QString::fromStdString(mapLoad.getName());


    xmlOp xmlOperator{};
    const auto mapLoad{xmlOperator.loadMap("/home/lvkaz/teste_xml_ease.xml")};
    mapLoad.PrintConnectEdelems();
    qDebug() << QString::fromStdString(mapLoad.getName());

    SearchDeep searchDeepTry{mapLoad, "point_1_4", "point_4_1"};
    bool returned{searchDeepTry.init()};

    if(returned)
    {
        qDebug() << "Very good";
    }
    else
    {
        qDebug() << "Fail, bad choice?";
    }

}
