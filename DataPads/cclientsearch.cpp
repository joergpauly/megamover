/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   19.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#include "cclientsearch.h"
#include "ui_cclientsearch.h"

CClientSearch::CClientSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CClientSearch)
{
    ui->setupUi(this);
    m_clientID = -1;
    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM viewClients ORDER BY agname ASC;");
    model->setHeaderData(0, Qt::Horizontal, "Kd.-Nr.");
    model->setHeaderData(1, Qt::Horizontal, "Matchcode");
    model->setHeaderData(2, Qt::Horizontal, "Auftraggeber Name");
    model->setHeaderData(3, Qt::Horizontal, "Auftraggeber Ort");
    model->setHeaderData(4, Qt::Horizontal, "Rg.-Empfänger Name");
    model->setHeaderData(5, Qt::Horizontal, "Rg.-Empfänger Ort");
    ui->tblClients->setModel(model);

    ui->tblClients->setColumnWidth(0, 60);
    ui->tblClients->setColumnWidth(1, 100);
    ui->tblClients->setColumnWidth(2, 180);
    ui->tblClients->setColumnWidth(3, 180);
    ui->tblClients->setColumnWidth(4, 180);
    ui->tblClients->setColumnWidth(5, 180);

    ui->tblClients->show();
}

CClientSearch::~CClientSearch()
{
    delete ui;
    delete model;
}

int CClientSearch::getClientID()
{
    if(m_clientID == -1)
    {
        ui->tblClients->selectRow(0);
        m_clientID = model->record(0).value("kdnr").toInt();
    }
    return m_clientID;
}

void CClientSearch::on_tblClients_clicked(const QModelIndex &index)
{
    m_clientID = model->record(index.row()).value(0).toInt();
}

void CClientSearch::on_tblClients_doubleClicked(const QModelIndex &index)
{
    m_clientID = model->record(index.row()).value(0).toInt();
    this->accept();
}

void CClientSearch::on_txtFilter_textEdited(const QString &arg1)
{
    QString lphrase = "SELECT * FROM viewClients WHERE kdnr LIKE ";
    lphrase.append(arg1);
    lphrase.append(" OR mc LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%' OR agname LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%' OR agort LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%' OR rgname LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%' OR rgort LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%';");
    model->setQuery(lphrase);
    ui->tblClients->setModel(model);
    ui->tblClients->show();
}


