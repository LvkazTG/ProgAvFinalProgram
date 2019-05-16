#include "dlginitusermap.h"
#include "ui_dlginitusermap.h"

#include "mapaobj.h"
//--------------------------------------------------------------------------------------------------
DlgInitUserMap::DlgInitUserMap(std::shared_ptr<MapaObj>& mapToCreate, QWidget *parent) :
    QDialog(parent), ui(new Ui::DlgInitUserMap), _map{mapToCreate}
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}
//--------------------------------------------------------------------------------------------------
DlgInitUserMap::~DlgInitUserMap()
{
    delete ui;
}
//--------------------------------------------------------------------------------------------------
void DlgInitUserMap::on_btnClose_clicked()
{
    close();
}
//--------------------------------------------------------------------------------------------------
void DlgInitUserMap::on_btnConfirm_clicked()
{
    bool okConvX{false};
    bool okConvY{false};
    const uint8_t sizeX{static_cast<uint8_t>(ui->lnMapSizeX->text().toInt(&okConvX))};
    const uint8_t sizeY{static_cast<uint8_t>(ui->lnMapSizeY->text().toInt(&okConvY))};

    if(okConvX && okConvY)
    {
        _map = std::make_shared<MapaObj>(sizeX, sizeY);
        _map->createNew();
        _map->setName(ui->lnMapName->text().toStdString());
//        _map->PrintConnectEdelems();

        close();
    }
    else
    {
        // Warn user
    }
}
//--------------------------------------------------------------------------------------------------
