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

#include "ccore.h"
#include "mainwindow.h"

CCore::CCore(QObject *parent) :
    QObject(parent)
{
    m_db = new CDatabaseManager(this);
    m_settings = new CSettings(this);
    m_mandant = m_settings->getMandant();
    m_parent = parent;
    ((MainWindow*)m_parent)->buildStatusBar();
}

CCore::~CCore()
{
    delete m_db;
    delete m_settings;
}

CDatabaseManager *CCore::getDBManager()
{
    return m_db;
}

CSettings *CCore::getSettings()
{
    return m_settings;
}

int CCore::getMandant()
{
    return m_mandant;
}

void CCore::setMandant(int mid)
{
    m_mandant = mid;
    m_settings->setMandant(m_mandant);
    ((MainWindow*)m_parent)->buildStatusBar();
}

void CCore::reConnectDB()
{
    m_db->reConnect();
    ((MainWindow*)m_parent)->buildStatusBar();
}




