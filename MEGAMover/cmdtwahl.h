/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   10.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef CMDTWAHL_H
#define CMDTWAHL_H

#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include <QSqlQuery>
#include <QListWidgetItem>

namespace Ui {
class CMdtWahl;
}

class CMdtWahl : public QDialog
{
    Q_OBJECT
    
//Private Member
private:
int m_choice;

public:
    explicit CMdtWahl(QWidget *parent = 0);
    ~CMdtWahl();

    int choice();
    void setMandant(int pMandant);

private slots:
    void on_tblMandant_itemActivated(QListWidgetItem *item);

private:
    Ui::CMdtWahl *ui;
};

#endif // CMDTWAHL_H
