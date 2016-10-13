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

#ifndef CCORE_H
#define CCORE_H

//System-Header
#include <QObject>
#include <QString>
#include <QtWidgets/QStatusBar>

//Projekt-Header
#include "cdatabasemanager.h"
#include "csettings.h"


//Globale Defines
#define APP "MEGAMover"
#define MAJ "3"
#define MIN "0"
#define REL "1001"
#define CPR "2013 - 2016 (C) J. Pauly"
#define VDR "MEGAMover.de"

class CCore : public QObject
{
    Q_OBJECT

//Private Properties
private:
    CDatabaseManager    *m_db;
    CSettings           *m_settings;
    QObject             *m_parent;
    int                 m_mandant;

//Private Member



public:
    explicit CCore(QObject *parent = 0);
    ~CCore();

    CDatabaseManager *getDBManager();
    CSettings *getSettings();
    int getMandant();
    void setMandant(int mid);
    void reConnectDB();
    
signals:
    
public slots:
    
};

#endif // CCORE_H
