#ifndef MAPPAINT_H
#define MAPPAINT_H

#include <QWidget>

class MapaObj;

class MapPaint : public QWidget
{
    Q_OBJECT
public:
    explicit MapPaint(QWidget *parent = nullptr);

    void addMap(const MapaObj* map);

protected:
    void paintEvent(QPaintEvent *);

private:
    MapaObj const* _map{nullptr};
};

#endif // MAPPAINT_H
