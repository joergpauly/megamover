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

public slots:
    void previous();
    void next();
    void search();
    void delet();
    void save();

private:
    Ui::CQueryNavigator *ui;
    QSqlQuery* m_qry;
};

#endif // CQUERYNAVIGATOR_H
