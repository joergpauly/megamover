/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   13.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef CCLIENT_H
#define CCLIENT_H

//System-Header
#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include <QtWidgets/QMdiSubWindow>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include "StData_global.h"

//Projekt-Header
#include "adresspad.h"
#include "cdatabasemanager.h"
#include "cadresssearch.h"
#include "cclientsearch.h"

namespace Ui {
class CClient;
}

class STDATASHARED_EXPORT CClient : public QWidget
{
    Q_OBJECT
    
public:
    explicit CClient(QWidget *parent = 0);
    ~CClient();
    void setSubWindow(QMdiSubWindow *pSubWnd);
    
private slots:
    void on_cmdClose_clicked();

    void on_cmdPrevClient_clicked();

    void on_cmdNextClient_clicked();

    void on_cmdNewClient_clicked();

    void on_cmdSrchClient_clicked();

    void on_cmdDeleteClient_clicked();

    void on_cmdNewAdrAG_clicked();

    void on_cmdSrchAdrAG_clicked();

    void on_cmdNewAdrRE_clicked();

    void on_cmdSrchAdrRE_clicked();

    void on_cmdSaveClient_clicked();

    void on_txtMatch_lostFocus();

//Private Properties
    void on_padAccount_dataChanged();

private:
    Ui::CClient *ui;
    QMdiSubWindow* m_subwnd;
    QSqlQuery *m_qry;
    int m_id;
    int m_agadrid;
    int m_readrid;
    QString m_ustID;
    QString m_myaccref;

//Private Member
    void updateUI();
    void updateDB();
    void checkClientTablePosition();
    void moveToClient(int pID);
};

#endif // CCLIENT_H
