#ifndef DLGINITUSERMAP_H
#define DLGINITUSERMAP_H

#include <QDialog>
#include <memory>
#include "mapaobj.h"

namespace Ui {
class DlgInitUserMap;
}

class DlgInitUserMap : public QDialog
{
    Q_OBJECT

public:
    explicit DlgInitUserMap(std::shared_ptr<MapaObj>& mapToCreate,
                            QWidget *parent = nullptr);
    ~DlgInitUserMap();

private slots:
    void on_btnClose_clicked();

    void on_brnConfirm_clicked();

private:
    Ui::DlgInitUserMap *ui;
    std::shared_ptr<MapaObj>& _map;
};

#endif // DLGINITUSERMAP_H
