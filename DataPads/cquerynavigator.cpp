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

void CQueryNavigator::previous()
{
    m_qry->previous();
}

void CQueryNavigator::next()
{
    m_qry->next();
}

void CQueryNavigator::search()
{

}

void CQueryNavigator::delet()
{

}

void CQueryNavigator::save()
{

}
