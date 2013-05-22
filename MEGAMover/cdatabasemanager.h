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

#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <QMessageBox>
#include <QStatusBar>
#include "csettings.h"


class CDatabaseManager : public QObject
{
    Q_OBJECT

//Private properties
private:
    QObject *m_parent;

    void setupDB();

public:
    QSqlDatabase dbcn;

    void reConnect();


    explicit CDatabaseManager(QObject *parent = 0);
    ~CDatabaseManager();
    
signals:
    
public slots:
    
};

#endif // CDATABASEMANAGER_H
