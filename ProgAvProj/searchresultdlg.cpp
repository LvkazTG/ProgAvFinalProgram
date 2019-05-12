#include "searchresultdlg.h"
#include "ui_searchresultdlg.h"

#include "mapaobj.h"
#include "basesearch.h"


SearchResultDlg::SearchResultDlg(const MapaObj* map,const std::shared_ptr<BaseSearch>& searchUsing,
                                 QWidget *parent) :
    QDialog{parent}, ui{new Ui::SearchResultDlg}
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->lnMapName->setText(QString::fromStdString(map->getName()));
    ui->lnSearchType->setText(QString::fromStdString(searchUsing->getSearchType()));
    ui->lnTotalCost->setText(QString::number(searchUsing->getBestPathCost()));


    const QStringList headerInfo{"Nome", "pos X", "pos Y", "Custo"};
    ui->tblPath->setHorizontalHeaderLabels(headerInfo);

    for(const auto& singleElem : searchUsing->getBestPath())
    {
        addRow(ui->tblPath, map->getPoint(singleElem.getPointHash()),
               static_cast<uint8_t>(singleElem.getActualConnCost()));
    }

    // Remove last line cost
    ui->tblPath->item((ui->tblPath->rowCount()-1),3)->setData(0, "");
}

SearchResultDlg::~SearchResultDlg()
{
    delete ui;
}

void SearchResultDlg::addRow(QTableWidget* tbl, const std::shared_ptr<PointObj>& pointInfo, const uint8_t pointCost)
{
    const auto lastRow{tbl->rowCount()};

    tbl->setRowCount(lastRow+1);

    tbl->setItem(lastRow, 0, new QTableWidgetItem{QString::fromStdString(pointInfo->getName())});
    tbl->setItem(lastRow, 1, new QTableWidgetItem{QString::number(pointInfo->getX())});
    tbl->setItem(lastRow, 2, new QTableWidgetItem{QString::number(pointInfo->getY())});
    tbl->setItem(lastRow, 3, new QTableWidgetItem{QString::number(pointCost)});
}

void SearchResultDlg::on_btnClose_clicked()
{
    close();
}
