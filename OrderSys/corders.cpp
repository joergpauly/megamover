/**************************************************************************
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
    m_qry->prepare("SELECT * FROM tblOrders;");
    m_qry->exec();
    m_qry->first();
    m_aufID = m_qry->value(0).toInt();
    updateUI();
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
    m_qry = new QSqlQuery();
    m_qry->prepare("INSERT INTO tblOrders (mnr, year, month, number, created, lastupdated, status) VALUES (?, ?, ?, ?, ?, ?, ?);");
    m_qry->addBindValue(nkr.mandant());
    m_qry->addBindValue(nkr.year());
    m_qry->addBindValue(nkr.month());
    m_qry->addBindValue(nkr.number());
    m_qry->addBindValue(QDate::currentDate());
    m_qry->addBindValue(QDate::currentDate());
    m_qry->addBindValue(ui->cmbStatus->currentIndex());
    m_qry->exec();
    m_aufID = m_qry->lastInsertId().toInt();
    updateUIonOrder();
}

void COrders::updateUIonOrder()
{
    m_qry = new QSqlQuery();
    m_qry->prepare("SELECT * FROM tblOrders WHERE ID = ?;");
    m_qry->addBindValue(m_aufID);
    m_qry->exec();
    m_qry->first();
    updateUI();
}

void COrders::on_cmdNewAG_clicked()
{
    //Neuen Satz von adressPad erzeugen lassen und ID sichern.
    int adrID = ui->padAG->insertNew();    
    QSqlQuery* qryMap = new QSqlQuery();
    qryMap->prepare("SELECT * FROM tblAdressMap WHERE orderID = ? AND pos = 1;");
    qryMap->addBindValue(m_aufID);
    qryMap->exec();

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
        qryMap->exec();
    }
    ui->padAG->beginEdit();
}

void COrders::on_cmdSrchAG_clicked()
{    
    //Adressauswahl aufrufen
    CAdressSearch* dlgSrch = new CAdressSearch(this);
    int adrID;
    if(dlgSrch->exec() == QDialog::Accepted)
    {
        adrID = dlgSrch->getAdrID();
        ui->padAG->setAdressID(adrID);
        ui->padAG->updateUI();
    }

    //AdressMap anlegen oder updaten mit Pos=1, adressID=gefundene Adress-ID, orderID=m_id
    QSqlQuery* qryMap = new QSqlQuery();
    qryMap->prepare("SELECT * FROM tblAdressMap WHERE orderID = ? AND pos = 1;");
    qryMap->addBindValue(m_aufID);
    qryMap->exec();

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
        qryMap->exec();
    }
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
        qryMap->exec();
    }
    ui->padAG->beginEdit();
}

void COrders::on_cmdSrchRE_clicked()
{
    CAdressSearch* dlgSrch = new CAdressSearch(this);
    int adrID;
    if(dlgSrch->exec() == QDialog::Accepted)
    {
        adrID = dlgSrch->getAdrID();
        ui->padRE->setAdressID(adrID);
        ui->padRE->updateUI();
    }

    //AdressMap anlegen oder updaten mit Pos=2, adressID=gefundene Adress-ID, orderID=m_id
    QSqlQuery* qryMap = new QSqlQuery();
    qryMap->prepare("SELECT * FROM tblAdressMap WHERE orderID = ? AND pos = 2;");
    qryMap->addBindValue(m_aufID);
    qryMap->exec();

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
        qryMap->exec();
    }
}

void COrders::on_cmdPrevAuf_clicked()
{
    if(!m_qry->previous())
    {
        m_qry->first();
    }
    m_aufID = m_qry->value(0).toInt();
    updateUI();
}

void COrders::on_cmdNextAuf_clicked()
{
    if(!m_qry->next())
    {
        m_qry->last();
    }
    m_aufID = m_qry->value(0).toInt();
    updateUI();
}

void COrders::updateUI()
{
    QSqlRecord lrec = m_qry->record();
    CNkr *fanr = new CNkr(m_qry->value(lrec.indexOf("mnr")).toInt(),
              m_qry->value(lrec.indexOf("year")).toInt(),
              m_qry->value(lrec.indexOf("month")).toInt(),
              m_qry->value(lrec.indexOf("number")).toInt());
    ui->txtAnr->setText(fanr->fullNumber());
    ui->txtCreated->setText(m_qry->value(lrec.indexOf("created")).toDate().toString("dd.MM.yyyy"));
    ui->txtUpdated->setText(m_qry->value(lrec.indexOf("lastupdated")).toDate().toString("dd.MM.yyyy"));
    ui->cmbStatus->setCurrentIndex(lrec.value(lrec.indexOf("status")).toInt());
    ui->padAG->clearUI();
    ui->padRE->clearUI();
    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("SELECT * FROM tblAdressMap WHERE orderID = ?;");
    qry->addBindValue(m_aufID);
    qry->exec();
    qry->first();
    while(qry->isValid())
    {
        switch (qry->value(qry->record().indexOf("pos")).toInt())
        {
            case 1:
                ui->padAG->setAdressID(qry->value(qry->record().indexOf("adressID")).toInt());
                break;
            case 2:
                ui->padRE->setAdressID(qry->value(qry->record().indexOf("adressID")).toInt());
                break;
        }
        qry->next();
    }
}

void COrders::on_cmdDeleteAuf_clicked()
{

}
