#ifndef CADRESSES_H
#define CADRESSES_H

#include <QWidget>
#include <QMdiSubWindow>
#include "StData_global.h"


namespace Ui {
class CAdresses;
}

class STDATASHARED_EXPORT CAdresses : public QWidget
{
    Q_OBJECT

public:

    QMdiSubWindow* m_subwnd;
    explicit CAdresses(QWidget *parent = 0);
    ~CAdresses();

    void setSubWnd(QMdiSubWindow* pSubWnd);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CAdresses *ui;
};

#endif // CADRESSES_H
