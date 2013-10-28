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

#include "corders.h"
#include "ui_corders.h"
#include "mainwindow.h"


COrders::COrders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::COrders)
{    
    ui->setupUi(this);    
    m_parent = parent;
    m_qry = new QSqlQuery();
}

COrders::~COrders()
{
    delete ui;
}

void COrders::setSubWindow(QWidget *pSubWnd)
{
    m_subwindow = pSubWnd;
}

void COrders::on_cmdClose_clicked()
{
    ((QMdiSubWindow*)m_subwindow)->close();
}

void COrders::on_cmdNewAuf_clicked()
{
    CNkr nkr(((MainWindow*)m_parent)->getCore()->getMandant());
    ui->txtAnr->setText(nkr.fullNumber());
    ui->cmbStatus->setCurrentIndex(0);
    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("INSERT INTO tblOrders (mnr, year, month, number, created, lastupdated, status) VALUES (?, ?, ?, ?, ?, ?, ?);");
    qry->addBindValue(nkr.mandant());
    qry->addBindValue(nkr.year());
    qry->addBindValue(nkr.month());
    qry->addBindValue(nkr.number());
    qry->addBindValue(QDate::currentDate());
    qry->addBindValue(QDate::currentDate());    
    qry->addBindValue(ui->cmbStatus->currentIndex());
    qry->exec();
    m_aufID = qry->lastInsertId().toInt();
    updateUI();
}

void COrders::updateUI()
{
    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("SELECT * FROM tblOrders WHERE ID = ?;");
    qry->addBindValue(m_aufID);
    qry->exec();
    qry->first();
    QSqlRecord lrec = qry->record();
    CNkr *fanr = new CNkr(qry->value(lrec.indexOf("mnr")).toInt(),
              qry->value(lrec.indexOf("year")).toInt(),
              qry->value(lrec.indexOf("month")).toInt(),
              qry->value(lrec.indexOf("number")).toInt());
    ui->txtAnr->setText(fanr->fullNumber());
    ui->txtCreated->setText(qry->value(lrec.indexOf("created")).toDate().toString("dd.MM.yyyy"));
    ui->txtUpdated->setText(qry->value(lrec.indexOf("lastupdated")).toDate().toString("dd.MM.yyyy"));
    ui->cmbStatus->setCurrentIndex(lrec.value(lrec.indexOf("status")).toInt());
}

void COrders::on_cmdNewAG_clicked()
{
    //Neuen Satz von adressPad erzeugen lassen und ID sichern.
    int adrID = ui->padAG->insertNew();    
    QSqlQuery* qryMap = new QSqlQuery();
    qryMap->prepare("SELECT * FROM tblAdressMap WHERE orderID = ? AND pos = 1;");
    qryMap->addBindValue(m_aufID);
    qryMap->exec();

    QString error;

    //Gibt es schon einen Eintrag?
    if(qryMap->isValid()) //Ja! Neue Adress-ID eintragen und editieren.
    {
        qryMap->prepare("UPDATE tblAdressMap SET adressID = ?;");
        qryMap->addBindValue(adrID);
        qryMap->exec();
    }
    else //ansonsten neuen Map-Eintrag erzeugen
    {
        qryMap = new QSqlQuery();
        qryMap->prepare("INSERT INTO tblAdressMap (adressID, orderID, pos) VALUES (?, ?, ?);");
        qryMap->addBindValue(adrID);
        qryMap->addBindValue(m_aufID);
        qryMap->addBindValue(1);
        if(!qryMap->exec())
        {
            error = qryMap->lastError().text();
        }
    }
    ui->padAG->beginEdit();
}

void COrders::on_cmdSrchAG_clicked()
{
    //TODO: AdressMap anlegen oder updaten mit Pos=1, adressID=gefundene Adress-ID, orderID=m_id
}

void COrders::on_cmdNewRE_clicked()
{
    //AdressMap anlegen oder updaten mit Pos=2, adressID=neue Adress-ID, orderID=m_id
    //Neuen Satz von adressPad erzeugen lassen und ID sichern.
    int adrID = ui->padRE->insertNew();
    QSqlQuery* qryMap = new QSqlQuery();
    qryMap->prepare("SELECT * FROM tblAdressMap WHERE orderID = ? AND pos = 2;");
    qryMap->addBindValue(m_aufID);
    qryMap->exec();

    QString error;

    //Gibt es schon einen Eintrag?
    if(qryMap->isValid()) //Ja! Neue Adress-ID eintragen und editieren.
    {
        qryMap->prepare("UPDATE tblAdressMap SET adressID = ?;");
        qryMap->addBindValue(adrID);
        qryMap->exec();
    }
    else //ansonsten neuen Map-Eintrag erzeugen
    {
        qryMap = new QSqlQuery();
        qryMap->prepare("INSERT INTO tblAdressMap (adressID, orderID, pos) VALUES (?, ?, ?);");
        qryMap->addBindValue(adrID);
        qryMap->addBindValue(m_aufID);
        qryMap->addBindValue(2);
        if(!qryMap->exec())
        {
            error = qryMap->lastError().text();
        }
    }
    ui->padAG->beginEdit();
}

void COrders::on_cmdSrchRE_clicked()
{
    //TODO: AdressMap anlegen oder updaten mit Pos=2, adressID=gefundene Adress-ID, orderID=m_id
}
