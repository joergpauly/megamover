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

#include "coptions.h"
#include "ui_coptions.h"

COptions::COptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::COptions)
{
    ui->setupUi(this);
    m_dbServer = new QString();
    m_dbName = new QString();
    m_dbUser = new QString();
    m_dbPassword = new QString();
}

COptions::~COptions()
{
    delete ui;
    delete m_dbServer;
    delete m_dbName;
    delete m_dbUser;
    delete m_dbPassword;
}

QString *COptions::getDBserver()
{
    return m_dbServer;
}

QString *COptions::getDBname()
{
    return m_dbName;
}

QString *COptions::getDBUser()
{
    return m_dbUser;
}

QString *COptions::getDBPassword()
{
    return m_dbPassword;
}

void COptions::setDBserver(QString pDBserver)
{
    *m_dbServer = pDBserver;
    ui->txtServer->setText(*m_dbServer);
}


void COptions::setDBname(QString pDBname)
{
    *m_dbName = pDBname;
    ui->txtDBname->setText(*m_dbName);
}

void COptions::setDBUser(QString pDBuser)
{
    *m_dbUser = pDBuser;
    ui->txtUser->setText(*m_dbUser);
}

void COptions::setDBPassword(QString pDBpassword)
{
    *m_dbPassword = pDBpassword;
    ui->txtPassword->setText(*m_dbPassword);
}

void COptions::on_buttonBox_accepted()
{
    *m_dbName = ui->txtDBname->text();
    *m_dbServer = ui->txtServer->text();
    *m_dbUser = ui->txtUser->text();
    *m_dbPassword = ui->txtPassword->text();
}
