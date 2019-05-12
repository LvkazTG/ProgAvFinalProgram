#include "progavprinc.h"
#include "ui_progavprinc.h"

#include "jsonop.h"
#include "xmlop.h"

#include "searchdeep.h"
#include "searchlevel.h"
#include "searchastart.h"
#include "searchgraphplanadapt.h"

#include <QDebug>

#include "mappaint.h"

#include <QDialog>

#include "searchmanual.h"

#include <QFileDialog>

ProgAvPrinc::ProgAvPrinc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProgAvPrinc)
{
    ui->setupUi(this);
    ui->stkOptions->setCurrentWidget(ui->stkMainWid);
}

ProgAvPrinc::~ProgAvPrinc()
{
    delete ui;
}

void ProgAvPrinc::on_btnCreateLoadMap_clicked()
{
    // Add window to choose size

    _mapLoad = std::make_shared<MapaObj>(10,10);
    _mapLoad->createNew();

//    _mapLoad->PrintConnectEdelems();

    _mapLoad->setName("Lucas_test_3");
}

void ProgAvPrinc::on_btnSDeep_clicked()
{
    _searchMethod = std::make_shared<SearchDeep>(*_mapLoad, "point_1_4", "point_4_1");
    startSearch();
}

void ProgAvPrinc::on_btnSLevel_clicked()
{
    _searchMethod = std::make_shared<SearchLevel>(*_mapLoad, "point_1_4", "point_4_1");
    startSearch();
}

void ProgAvPrinc::on_btnSAStar_clicked()
{
    _searchMethod = std::make_shared<searchAStart>(*_mapLoad, "point_1_4", "point_4_1");
    startSearch();
}

void ProgAvPrinc::on_btnSGraphPlan_clicked()
{
    _searchMethod = std::make_shared<SearchGraphplanAdapt>(*_mapLoad, "point_1_4", "point_4_1");
    startSearch();
}

void ProgAvPrinc::on_btnSManual_clicked()
{
//    SearchManual* manSearch{new SearchManual{"point_1_4", &(*_mapLoad), this}};
    SearchManual* manSearch{new SearchManual{&(*_mapLoad), this}};
    manSearch->setAttribute(Qt::WA_DeleteOnClose);
    manSearch->show();
}

void ProgAvPrinc::on_btnViewMap_clicked()
{
    MapPaint* mapPaintDlg{new MapPaint{&(*_mapLoad), this}};
    mapPaintDlg->setAttribute(Qt::WA_DeleteOnClose);

    mapPaintDlg->show();

    QDialog* bla{new QDialog{this}};
    bla->setAttribute(Qt::WA_DeleteOnClose);

    QGridLayout* ble{new QGridLayout{bla}};
    ble->addWidget(mapPaintDlg);

    bla->setLayout(ble);
    bla->show();
}


std::string ProgAvPrinc::openUserFileChoice()
{
    const QString expectedFilename{QFileDialog::getOpenFileName(this, "Choose to load")};
    return expectedFilename.toStdString();
}

std::string ProgAvPrinc::getSaveUserFileChoice()
{
    const QString expectedFilename{QFileDialog::getSaveFileName(this, "Choose to save")};
    return expectedFilename.toStdString();
}

void ProgAvPrinc::startSearch()
{
    const bool returned4{_searchMethod->init()};

    if(returned4)
    {
        qDebug() << "Very good4";
    }
    else
    {
        qDebug() << "Fail, bad choice?4";
    }
}

void ProgAvPrinc::on_btnSaveMapJson_clicked()
{
    const auto saveFileName{getSaveUserFileChoice()};

    if(!saveFileName.empty())
    {
        JsonOp jsonOperator{};
        jsonOperator.saveMap(*_mapLoad, saveFileName);
    }
    else
    {
        // warn user
    }
}

void ProgAvPrinc::on_btnSaveMapXml_clicked()
{
    const auto saveFileName{getSaveUserFileChoice()};

    if(!saveFileName.empty())
    {
        xmlOp xmlOperator{};
        xmlOperator.saveMap(*_mapLoad, saveFileName);
    }
    else
    {
        // warn user
    }
}

void ProgAvPrinc::on_btnLoadMapJson_clicked()
{
    const auto loadFileName{openUserFileChoice()};

    if(!loadFileName.empty())
    {
        JsonOp jsonOperator{};
        _mapLoad = std::shared_ptr<MapaObj>(
                    new MapaObj{jsonOperator.loadMap(loadFileName)});
    }
    else
    {
        // warn user
    }
}

void ProgAvPrinc::on_btnLoadMapXml_clicked()
{
    const auto loadFileName{openUserFileChoice()};

    if(!loadFileName.empty())
    {
    xmlOp xmlOperator{};
    _mapLoad = std::shared_ptr<MapaObj>(
                new MapaObj{xmlOperator.loadMap(loadFileName)});
    }
    else
    {
        // warn user
    }
}

void ProgAvPrinc::on_btnSaveStatisticsJson_clicked()
{
    const auto saveFileName{getSaveUserFileChoice()};

    if(!saveFileName.empty())
    {
        JsonOp jsonOperator{};
        jsonOperator.saveStatistics(_searchMethod->getSearchStatistics(), *_mapLoad, saveFileName);
    }
    else
    {
        // warn user
    }

}

void ProgAvPrinc::on_btnSaveStatisticsXml_clicked()
{
    ui->btnSaveStatisticsXml->setStyleSheet("");
    const auto saveFileName{getSaveUserFileChoice()};

    if(!saveFileName.empty())
    {
        xmlOp xmlOperator{};
        xmlOperator.saveStatistics(_searchMethod->getSearchStatistics(), *_mapLoad, saveFileName);
    }
    else
    {
        ui->btnSaveStatisticsXml->setStyleSheet("background-color:red");
    }

}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void ProgAvPrinc::on_btnMapOpt_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMap);
}

void ProgAvPrinc::on_btnSearchOpt_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkSearch);
}

void ProgAvPrinc::on_btnVisualOpt_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkVisual);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void ProgAvPrinc::on_btnBackMap_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMainWid);
}

void ProgAvPrinc::on_btnBackSearch_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMainWid);
}

void ProgAvPrinc::on_btnBackVisual_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMainWid);
}

void ProgAvPrinc::on_btnBackLoadMap_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMap);
}

void ProgAvPrinc::on_btnBackSaveMap_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMap);
}

void ProgAvPrinc::on_btnBackSaveStat_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkSearch);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void ProgAvPrinc::on_btnSaveMap_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMapSave);
}

void ProgAvPrinc::on_btnLoadMap_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkMapLoad);
}

void ProgAvPrinc::on_btnSaveStatistics_clicked()
{
    ui->stkOptions->setCurrentWidget(ui->stkStatSave);
}
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void ProgAvPrinc::on_btnFRoute_clicked()
{
    qDebug() << "Not yet imp";
}

void ProgAvPrinc::on_btnAbout_clicked()
{
    qDebug() << "Not yet imp";
}


















