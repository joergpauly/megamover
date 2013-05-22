/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   10.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#include "cmdtwahl.h"
#include "ui_cmdtwahl.h"

CMdtWahl::CMdtWahl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMdtWahl)
{
    ui->setupUi(this);
    QSqlQuery *qry = new QSqlQuery();
    //NUR Mandanten aus tblAdresses holen und in Auswahl anzeigen.
    qry->exec("select tblAdressMap.mnr AS mnr,tblAdresses.vorname AS vorname,tblAdresses.name1 AS name1,tblAdresses.ort AS ort from (tblAdressMap join tblAdresses) where ((tblAdressMap.adressID = tblAdresses.ID) and (tblAdressMap.mandant = 1)) ORDER BY mnr");
    qry->first();

    do
    {
        QString lentry(qry->value(0).toString());
        lentry.append("; ");
        lentry.append(qry->value(2).toString());
        lentry.append(", ");

        if(qry->value(1).toString().size() > 1)
        {
            lentry.append(qry->value(1).toString());
            lentry.append(", ");
        }

        lentry.append(qry->value(3).toString());
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(lentry);
        item->setData(QListWidgetItem::UserType, qry->value(0));
        ui->tblMandant->addItem(item);
    }
    while(qry->next());

    delete qry;
}

CMdtWahl::~CMdtWahl()
{
    delete ui;
}

int CMdtWahl::choice()
{
    return m_choice;
}

void CMdtWahl::setMandant(int pMandant)
{
    m_choice = pMandant;

    for(int i = 0; i < ui->tblMandant->count(); i++)
    {
        QListWidgetItem *item = ui->tblMandant->item(i);
        if(item->data(QListWidgetItem::UserType) == m_choice)
        {
                ui->tblMandant->setItemSelected(item,true);
                on_tblMandant_itemActivated(item);
        }
    }
}

void CMdtWahl::on_tblMandant_itemActivated(QListWidgetItem *item)
{
    ui->label_2->setText(item->text());
    m_choice = item->data(QListWidgetItem::UserType).toInt();
}
