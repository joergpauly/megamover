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

#include "cdatabasemanager.h"
#include "ccore.h"
#include "mainwindow.h"


CDatabaseManager::CDatabaseManager(QObject *parent) :
    QObject(parent)
{
    /* CMainWindow-Objekt sichern */
    m_parent = parent;
    /* Verbindungs-Objekt erzeugen und initialisieren */
    dbcn = QSqlDatabase::addDatabase("QMYSQL");
    setupDB();
}

CDatabaseManager::~CDatabaseManager()
{
    // Wenn offen...
    if(dbcn.isOpen())
    {
        // ...dann schließen!
        dbcn.close();
    }
}

// Datenbank neu verbinden
void CDatabaseManager::reConnect()
{
    dbcn.close();
    setupDB();
}

// Initialisieren und Öffnen der Datenbankverbindung
void CDatabaseManager::setupDB()
{
    /* Verbindungs-Parameter aus
     * Konfiguration holen und im
     * Verbindungsobjekt setzen */
    CSettings *set = new CSettings();
    QString lsrv = set->getDBserver();
    QString ldbn = set->getDBname();
    QString lusr = set->getDBuser();
    QString lpwd = set->getDBpassword();
    dbcn.setHostName(lsrv);
    dbcn.setDatabaseName(ldbn);
    dbcn.setUserName(lusr);
    dbcn.setPassword(lpwd);
    /* Versuche, die Db zu öffnen */
    if(!dbcn.open())
    {
        /* Öffnen fehlgeschlagen; Fehlermeldung! */
        QMessageBox *dlg = new QMessageBox();
        dlg->setWindowTitle("Datenbank-Fehler");
        dlg->setText("Datenbank kann nicht geöffnet werden!");
        dlg->setInformativeText("Die Datenbank gab einen Fehler zurück.");
        dlg->setDetailedText(dbcn.lastError().text());
        dlg->setIcon(QMessageBox::Critical);
        dlg->setStandardButtons(QMessageBox::Ok);
        dlg->exec();
        delete dlg;
    }
    else
    {
        /* Öffnen erfolgreich; Statusbar-Daten setzen */
        QString status = "Datenbank: ";
        status.append(ldbn);
        status.append(" auf ");
        status.append(lsrv);
        QLabel *lbl = new QLabel(status);
        MainWindow *lmw = (MainWindow*)m_parent->parent();
        QStatusBar *bar = lmw->statusBar();
        bar->addPermanentWidget(lbl);
        lmw->setStatusBar(bar);
    }
    delete set;
}
