/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   07.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef CMANDANT_H
#define CMANDANT_H

#include "../MEGAMover/qtversion.h"
#ifdef QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QtWidgets/QMessageBox>
#include "ccore.h"


namespace Ui {
class CMandant;
}

class CMandant : public QDialog
{
    Q_OBJECT

//Private Properties
private:
    CCore *m_core;
    CDatabaseManager *m_db;
    QSqlQuery *m_qryMap;    
    int m_mnr;

//Private Members
    void setupQuery(bool pNew);
    void updateUI();
public:
    explicit CMandant(QWidget *parent = 0);
    ~CMandant();

    void setCore(CCore* pCore);
    
private slots:
    void on_cmdNew_clicked();

    void on_cmdPrev_clicked();

    void on_cmdNext_clicked();

    void on_cmdClose_clicked();

    void on_cmdDelete_clicked();

private:
    Ui::CMandant *ui;
};

#endif // CMANDANT_H
