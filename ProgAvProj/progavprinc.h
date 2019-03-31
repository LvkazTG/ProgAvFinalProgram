#ifndef PROGAVPRINC_H
#define PROGAVPRINC_H

#include <QMainWindow>

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

private slots:
    void on_btnTest_clicked();
};

#endif // PROGAVPRINC_H
