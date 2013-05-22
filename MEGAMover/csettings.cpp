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

#include "csettings.h"
#include "ccore.h"

CSettings::CSettings(QObject *parent) :
    QObject(parent)
{
    m_settings = new QSettings(VDR,APP);
    m_dbName = new QString();
    m_dbServer = new QString();
    m_dbUser = new QString();
    m_dbPassword = new QString();
}

CSettings::~CSettings()
{
    delete m_dbName;
    delete m_dbServer;
    delete m_dbUser;
    delete m_dbPassword;
    delete m_settings;
}

void CSettings::readSettings()
{
    *m_dbName = m_settings->value("dbName").toString();
    *m_dbServer = m_settings->value("dbServer").toString();
    *m_dbUser = m_settings->value("dbUser").toString();
    *m_dbPassword = m_settings->value("dbPassword").toString();
    m_mandant = m_settings->value("appMandant",0).toInt();
}

QString CSettings::getDBserver()
{
    readSettings();
    return *m_dbServer;
}

QString CSettings::getDBname()
{
    readSettings();
    return *m_dbName;
}

QString CSettings::getDBuser()
{
    readSettings();
    return *m_dbUser;
}

QString CSettings::getDBpassword()
{
    readSettings();
    return *m_dbPassword;
}

int CSettings::getMandant()
{
    readSettings();
    return m_mandant;
}

void CSettings::setDBserver(QString *pServer)
{
    m_dbServer = pServer;
    m_settings->setValue("dbServer",*m_dbServer);
}

void CSettings::setDBname(QString *pName)
{
    m_dbName = pName;
    m_settings->setValue("dbName",*m_dbName);
}

void CSettings::setDBuser(QString *pUser)
{
    m_dbUser = pUser;
    m_settings->setValue("dbUser", *m_dbUser);
}

void CSettings::setDBpassword(QString *pPassword)
{
    m_dbPassword = pPassword;
    m_settings->setValue("dbPassword", *m_dbPassword);
}

void CSettings::setMandant(int pMandant)
{
    m_mandant = pMandant;
    m_settings->setValue("appMandant", m_mandant);
}
