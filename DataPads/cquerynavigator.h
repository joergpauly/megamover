#ifndef CQUERYNAVIGATOR_H
#define CQUERYNAVIGATOR_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class CQueryNavigator;
}

class CQueryNavigator : public QWidget
{
    Q_OBJECT

public:
    explicit CQueryNavigator(QWidget *parent = 0);
    void setQuery(QSqlQuery* pQry);
    ~CQueryNavigator();

private:
    Ui::CQueryNavigator *ui;
    QSqlQuery* m_qry;
};

#endif // CQUERYNAVIGATOR_H
