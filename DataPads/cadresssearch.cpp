/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   18.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#include "cadresssearch.h"
#include "ui_cadresssearch.h"

CAdressSearch::CAdressSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAdressSearch)
{
    QSqlQuery lq;
    // Unauffindbare Adressen löschen
    lq.exec("DELETE from tblAdresses WHERE name1 = '' AND name2 = '' AND ort = '';");
    ui->setupUi(this);
    model = new QSqlQueryModel();
    model->setQuery("SELECT ID, name1, vorname, ort FROM tblAdresses ORDER BY name1 ASC;");
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Vorname");
    model->setHeaderData(3, Qt::Horizontal, "Ort");

    ui->tblAdresses->setModel(model);
    ui->tblAdresses->hideColumn(0);
    ui->tblAdresses->setColumnWidth(1, 200);
    ui->tblAdresses->setColumnWidth(2, 130);
    ui->tblAdresses->setColumnWidth(3, 200);
    ui->tblAdresses->show();
}

CAdressSearch::~CAdressSearch()
{
    delete ui;
    delete model;
}

void CAdressSearch::on_tblAdresses_clicked(const QModelIndex &index)
{
    m_adrID = model->record(index.row()).value(0).toInt();
}


int CAdressSearch::getAdrID()
{
    return m_adrID;
}

void CAdressSearch::on_tblAdresses_doubleClicked(const QModelIndex &index)
{
    m_adrID = model->record(index.row()).value(model->record().indexOf("ID")).toInt();
    this->accept();
}

void CAdressSearch::on_txtNameFilter_textEdited(const QString &arg1)
{
    QString lphrase = "SELECT ID, name1, vorname, ort FROM tblAdresses WHERE name1 LIKE '%";
    lphrase.append(arg1);
    lphrase.append("%' OR vorname LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%' OR ort LIKE '%");
    lphrase.append(arg1);
    lphrase.append("%' ORDER BY name1 ASC;");
    model->setQuery(lphrase);
    ui->tblAdresses->setModel(model);
    ui->tblAdresses->show();
}
