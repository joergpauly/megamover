/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   05.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//System-Header
#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include <QWidget>
#include <QMessageBox>
#include <QCloseEvent>
#include <QString>
#include <QLabel>
#include <QStatusBar>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

//Projekt-Header
#include "ccore.h"
#include "coptions.h"
#include "cmandant.h"
#include "cabout.h"
#include "corders.h"
#include "cmdtwahl.h"
#include "cclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
// Private Properties
    CCore *core;

//Child-Windows
    Ui::MainWindow *ui;
    COptions    *m_opts;
    COrders     *m_orders;
    CClient     *m_clients;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void closeEvent(QCloseEvent *e);
    CCore *getCore();
    QLabel *setMandantStatus();
    void buildStatusBar();
    void closeMdiSubWindow();

private slots:
    void on_actionProgramm_schli_e_en_triggered();

    void on_action_Datenbank_triggered();

    void on_actionMan_danten_triggered();

    void on_action_ber_Qt_triggered();

    void on_action_ber_triggered();

    void on_actionNeu_Be_arbeiten_triggered();

    void on_action_Kunden_triggered();

    void on_action_aus_w_hlen_triggered();

    void on_cmdAuftrag_clicked();

    void on_cmdClose_clicked();

//Private Member
    void on_cmdClients_clicked();

private:
    void openOrder();
    void openClients();


private:

};

#endif // MAINWINDOW_H
