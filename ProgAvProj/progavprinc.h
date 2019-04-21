#ifndef PROGAVPRINC_H
#define PROGAVPRINC_H

#include <QMainWindow>

class MapaObj;

namespace Ui {
class ProgAvPrinc;
}

class ProgAvPrinc : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProgAvPrinc(QWidget *parent = nullptr);
    ~ProgAvPrinc();

private:
    Ui::ProgAvPrinc *ui;

    MapaObj* _mapLoad{nullptr};

private slots:
    void on_btnTest_clicked();
    void on_btnTest2_clicked();
    void on_btnTest3_clicked();
};

#endif // PROGAVPRINC_H
