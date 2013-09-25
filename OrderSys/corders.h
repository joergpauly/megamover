﻿/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   11.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef CORDERS_H
#define CORDERS_H

#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include <QtWidgets/QMdiSubWindow>
#include <QSqlQuery>
#include <QDate>

#include "adresspad.h"
#include "cnkr.h"


namespace Ui {
class COrders;
}

class COrders : public QWidget
{
    Q_OBJECT
    
public:
    explicit COrders(QWidget *parent = 0);
    ~COrders();
    void setSubWindow(QWidget* pSubWnd);
private slots:


    void on_cmdClose_clicked();

    void on_cmdNewAuf_clicked();

private:
    Ui::COrders *ui;
    QSqlQuery *m_qry;
    QWidget *m_parent;
    QWidget *m_subwindow;
    int m_aufID;

//Private Members
private:
    void updateUI();
    void setupQuery();

};

#endif // CORDERS_H
