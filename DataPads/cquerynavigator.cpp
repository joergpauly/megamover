#include "cquerynavigator.h"
#include "ui_cquerynavigator.h"

CQueryNavigator::CQueryNavigator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CQueryNavigator)
{
    ui->setupUi(this);
}

void CQueryNavigator::setQuery(QSqlQuery *pQry)
{
    m_qry = pQry;
}

CQueryNavigator::~CQueryNavigator()
{
    delete ui;
}
