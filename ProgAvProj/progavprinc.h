#ifndef PROGAVPRINC_H
#define PROGAVPRINC_H

#include <QMainWindow>
#include <memory>

#include "mapaobj.h"
#include "basesearch.h"

namespace Ui
{
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

    std::shared_ptr<MapaObj> _mapLoad{nullptr};
    std::shared_ptr<BaseSearch> _searchMethod{nullptr};

    std::string openUserFileChoice();
    std::string getSaveUserFileChoice();

    void createSearchUserDlg();


private slots:
    void on_btnCreateLoadMap_clicked();

    void on_btnLoadMapJson_clicked();
    void on_btnLoadMapXml_clicked();


    void on_btnSDeep_clicked();
    void on_btnSLevel_clicked();
    void on_btnSAStar_clicked();
    void on_btnSGraphPlan_clicked();
    void on_btnSManual_clicked();

    void on_btnSaveMapJson_clicked();
    void on_btnSaveMapXml_clicked();

    void on_btnSaveStatisticsJson_clicked();
    void on_btnSaveStatisticsXml_clicked();


    void on_btnViewMap_clicked();
    void on_btnFRoute_clicked();

    void on_btnMapOpt_clicked();
    void on_btnSearchOpt_clicked();
    void on_btnVisualOpt_clicked();

    void on_btnSaveMap_clicked();
    void on_btnLoadMap_clicked();
    void on_btnSaveStatistics_clicked();


    void on_btnBackMap_clicked();
    void on_btnBackSearch_clicked();
    void on_btnBackVisual_clicked();
    void on_btnBackLoadMap_clicked();
    void on_btnBackSaveMap_clicked();
    void on_btnBackSaveStat_clicked();


};

#endif // PROGAVPRINC_H
