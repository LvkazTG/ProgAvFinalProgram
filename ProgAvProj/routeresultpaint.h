#ifndef ROUTERESULTPAINT_H
#define ROUTERESULTPAINT_H

#include <QWidget>

#include <list>

class PointConnIter;
class MapaObj;

class RouteResultPaint : public QWidget
{
    Q_OBJECT
public:
    explicit RouteResultPaint(QWidget *parent = nullptr);

    void addRouteAndMap(const std::list<PointConnIter>* routeList,
                        const MapaObj* map);

protected:
    void paintEvent(QPaintEvent *);

private:
    std::list<PointConnIter> const* _listRoute{nullptr};
    MapaObj const* _map{nullptr};
};

#endif // ROUTERESULTPAINT_H
