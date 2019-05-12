#include "searchuserstart.h"
#include "ui_searchuserstart.h"

searchUserStart::searchUserStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchUserStart)
{
    ui->setupUi(this);
}

searchUserStart::~searchUserStart()
{
    delete ui;
}
