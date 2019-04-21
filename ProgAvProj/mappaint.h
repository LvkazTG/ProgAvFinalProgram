#ifndef MAPPAINT_H
#define MAPPAINT_H

#include <QWidget>

class MapaObj;

class MapPaint : public QWidget
{
    Q_OBJECT
public:
    explicit MapPaint(const MapaObj* map, QWidget *parent = nullptr);

signals:

public slots:


protected:
    void paintEvent(QPaintEvent *);

private:
    const MapaObj* _map;
};

#endif // MAPPAINT_H
