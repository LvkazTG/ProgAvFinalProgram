#include "searchuserstart.h"
#include "ui_searchuserstart.h"

#include "mapaobj.h"
#include "pointobj.h"

#include <QDebug>

searchUserStart::searchUserStart(const MapaObj* map, std::shared_ptr<BaseSearch> searchUsing,  QWidget *parent) :
    QDialog{parent}, ui{new Ui::searchUserStart}, _map{map}, _searchMetUsing{searchUsing}
{
    ui->setupUi(this);

    ui->lnMapName->setText(QString::fromStdString(_map->getName()));
    ui->lnSearchType->setText(QString::fromStdString(_searchMetUsing->getSearchType()));


}

searchUserStart::~searchUserStart()
{
    delete ui;
}

void searchUserStart::on_btnClose_clicked()
{
    close();
}

void searchUserStart::on_btnStart_clicked()
{
    auto [startPoint, okStart] = searchUserInfoSinglePoint(ui->lnStartPName,
                                                           ui->lnStartPX,
                                                           ui->lnStartPY);

    auto [endPoint, okEnd] = searchUserInfoSinglePoint(ui->lnEndPName,
                                                       ui->lnEndPX,
                                                       ui->lnEndPY);

    if(okStart && okEnd)
    {
        _searchMetUsing->definePoints(startPoint->getHash(), endPoint->getHash());

        informRunning();
        const bool returned{_searchMetUsing->init()};

        if(returned)
        {
            qDebug() << "Very good4";
        }
        else
        {
            qDebug() << "Fail, bad choice?4";
        }

        informRunningStop();
    }
    else
    {
        // warn user
    }
}

std::tuple<std::shared_ptr<PointObj>, const bool>
    searchUserStart::searchUserInfoSinglePoint(const QLineEdit* lnName,
                                               const QLineEdit* lnX,
                                               const QLineEdit* lnY)
{
    std::shared_ptr<PointObj> pointObj{nullptr};

    const auto startPName{lnName->text()};
    if(!startPName.isEmpty())
    {
        pointObj =_map->getPointByName(startPName.toStdString());
    }
    else
    {
        bool okConvX{false};
        bool okConvY{false};
        const auto pXVal{lnX->text().toInt(&okConvX)};
        const auto pYVal{lnY->text().toInt(&okConvY)};

        if(okConvX && okConvY)
        {
            pointObj =_map->getPointByCoord(static_cast<uint8_t>(pXVal),
                                             static_cast<uint8_t>(pYVal));
        }
    }

    return std::make_tuple<std::shared_ptr<PointObj>, const bool>(std::move(pointObj),
                                                                  (nullptr != pointObj));
}

void searchUserStart::informRunning()
{
    ui->btnStart->setText("Running");
    ui->btnStart->setEnabled(false);
    ui->btnClose->setEnabled(false);
}

void searchUserStart::informRunningStop()
{
    ui->btnStart->setText("Start");
    ui->btnStart->setEnabled(true);
    ui->btnClose->setEnabled(true);
}
