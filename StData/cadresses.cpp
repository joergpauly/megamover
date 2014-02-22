#include "cadresses.h"
#include "ui_cadresses.h"

CAdresses::CAdresses(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CAdresses)
{
    ui->setupUi(this);
}

CAdresses::~CAdresses()
{
    delete ui;
}

void CAdresses::setSubWnd(QMdiSubWindow *pSubWnd)
{
    m_subwnd = pSubWnd;
}

void CAdresses::on_buttonBox_accepted()
{
    this->close();
}
