#include "progavprinc.h"
#include "ui_progavprinc.h"

#include "mapaobj.h"

#include "jsonop.h"
#include "xmlop.h"

#include "searchdeep.h"
#include "searchlevel.h"
#include "searchastart.h"
#include "searchgraphplanadapt.h"

#include <QDebug>

#include "mappaint.h"

#include <QDialog>
//#include <QPainter>

#include "searchmanual.h"

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

    MapaObj prinMap{10, 10};
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

    SearchLevel searchLvlTry{mapLoad, "point_1_4", "point_4_1"};;
    bool returned2{searchLvlTry.init()};

    if(returned2)
    {
        qDebug() << "Very good2";
    }
    else
    {
        qDebug() << "Fail, bad choice?2";
    }

    searchAStart searchAStarTry{mapLoad, "point_1_4", "point_4_1"};;
    bool returned3{searchAStarTry.init()};

    if(returned3)
    {
        qDebug() << "Very good3";
    }
    else
    {
        qDebug() << "Fail, bad choice?3";
    }


    SearchGraphplanAdapt searchGraphplanTry{mapLoad, "point_1_4", "point_4_1"};;
    bool returned4{searchGraphplanTry.init()};

    if(returned4)
    {
        qDebug() << "Very good4";
    }
    else
    {
        qDebug() << "Fail, bad choice?4";
    }

}

void ProgAvPrinc::on_btnTest3_clicked()
{
    xmlOp xmlOperator{};
//    const auto mapLoad{xmlOperator.loadMap("/home/lvkaz/teste_xml_ease.xml")};
    _mapLoad = new MapaObj{xmlOperator.loadMap("/home/lvkaz/teste_xml_ease.xml")};

    MapPaint* mapPaintDlg{new MapPaint{_mapLoad, this}};
    mapPaintDlg->setAttribute(Qt::WA_DeleteOnClose);

    mapPaintDlg->show();

    QDialog* bla{new QDialog{this}};
    bla->setAttribute(Qt::WA_DeleteOnClose);

    QGridLayout* ble{new QGridLayout{bla}};
    ble->addWidget(mapPaintDlg);

    bla->setLayout(ble);
    bla->show();
}

void ProgAvPrinc::on_btnTest4_clicked()
{
    xmlOp xmlOperator{};
//    const auto mapLoad{xmlOperator.loadMap("/home/lvkaz/teste_xml_ease.xml")};
    _mapLoad = new MapaObj{xmlOperator.loadMap("/home/lvkaz/teste_xml_ease.xml")};

    SearchManual* testManual{new SearchManual{_mapLoad, this}};
    testManual->setAttribute(Qt::WA_DeleteOnClose);

    testManual->show();

}












