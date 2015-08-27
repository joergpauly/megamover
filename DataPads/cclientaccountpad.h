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

#ifndef CCLIENTACCOUNTPAD_H
#define CCLIENTACCOUNTPAD_H

#include "../MEGAMover/qtversion.h"
#ifdef QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "DataPads_global.h"

#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QFont>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlError>


namespace Ui {
class CClientAccountPad;
}

/*!
 *ClientAccountPad stellt ein einbindbares Widget fuer Kundendaten dar.
 */
class DATAPADSSHARED_EXPORT CClientAccountPad : public QWidget
{
    Q_OBJECT
    
//Private Properties
private:
    //! Das Haupt-Abfrageobjekt regelt den Datenverkehr von und zur Datenbank.
    QSqlQuery *m_qry;
    QString *m_UstID;
    QString *m_myAccRef;
    bool m_client;
    int m_id;

    QAction* m_acDelete;
    QAction* m_acStandard;
    QMenu* m_menu;

public:
    //! Der Zeiger des einbindenden Widgets muss uebergeben werden.
    explicit CClientAccountPad(QWidget *parent = 0);
    ~CClientAccountPad();
    //! Initialisiert das Pad fuer die Kundentabelle.
    void setClientID(int pID);
    //! Initialisiert das Pad fuer die Mandantentabelle.
    void setMandantID(int pID);
    void setUstID(QString pValue);
    void setMyAccRef(QString pValue);
    QString getUstID();
    QString getMyAccRef();
    
private slots:    

    void on_tbvwBankAccounts_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void deleteAccount();

    void makeAccStandard();

    void on_txtUstID_lostFocus();

    void on_txtMyAccRef_lostFocus();

private:
    Ui::CClientAccountPad *ui;
    void setupMenu();
    void addNewRow(int row, int col);
    void updateUI();    
    void contextMenuEvent(QContextMenuEvent *e);
    void keyPressEvent(QKeyEvent *e);

signals:
    void dataChanged();
};

#endif // CCLIENTACCOUNTPAD_H
