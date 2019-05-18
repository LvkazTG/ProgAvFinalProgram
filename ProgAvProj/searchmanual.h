#ifndef SEARCHMANUAL_H
#define SEARCHMANUAL_H

#include <QDialog>
#include <QTableWidget>

#include "basesearch.h"

class MapaObj;

namespace Ui
{
    class SearchManual;
}

class SearchManual : public QDialog
{
    Q_OBJECT

public:
    explicit SearchManual(const MapaObj* map, const std::shared_ptr<PointObj> startPoint, QWidget *parent);
    ~SearchManual() override;

private:
    Ui::SearchManual *ui{nullptr};

    const MapaObj* _mapInUse{nullptr};
    ConnList const* _connMapList{nullptr};

    void addOptions(const std::shared_ptr<PointObj>& startPoint);
    void addRow(QTableWidget* tbl, const std::shared_ptr<PointObj>& pointInfo, const uint8_t pointCost);

private slots:
    void on_btnSelect_clicked();
    void on_btnBack_clicked();
    void on_btnClose_clicked();

};

#endif // SEARCHMANUAL_H
