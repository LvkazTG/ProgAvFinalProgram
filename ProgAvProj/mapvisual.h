#ifndef MAPVISUAL_H
#define MAPVISUAL_H

#include <QDialog>

class MapaObj;

namespace Ui
{
    class MapVisual;
}

class MapVisual : public QDialog
{
    Q_OBJECT

public:
    explicit MapVisual(const MapaObj* map, QWidget *parent);
    ~MapVisual();

private slots:
    void on_btnClose_clicked();

private:
    Ui::MapVisual *ui{nullptr};
};

#endif // MAPVISUAL_H
