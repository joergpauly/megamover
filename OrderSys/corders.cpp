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
