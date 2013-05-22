/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   07.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#include "cmandant.h"
#include "ui_cmandant.h"

CMandant::CMandant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMandant)
{
    ui->setupUi(this);
    m_qryMap = new QSqlQuery();
}

CMandant::~CMandant()
{
    delete ui;
    delete m_qryMap;    
}

void CMandant::setCore(CCore *pCore)
{
    m_core = pCore;
    setupQuery(false);
}

void CMandant::on_cmdNew_clicked()
{
    ui->Adresse->clearUI();
    int lastID = ui->Adresse->insertNew();
    m_qryMap->exec("SELECT mnr FROM tblAdressMap WHERE mandant = 1 ORDER BY mnr ASC;");
    m_qryMap->last();
    int lmnr = m_qryMap->value(0).toInt();
    m_qryMap->prepare("INSERT INTO tblAdressMap (adressID, mandant, mnr)"
                      "VALUES (?, 1, ?)");
    m_qryMap->addBindValue(lastID);
    m_mnr = lmnr + 1;
    m_qryMap->addBindValue(m_mnr);
    m_qryMap->exec();
    setupQuery(true);
}


void CMandant::setupQuery(bool pNew)
{
    m_qryMap->clear();

    if(pNew)
    {
        m_qryMap->prepare("SELECT ID, adressID, mnr from tblAdressMap WHERE mnr = ?;");
        m_qryMap->addBindValue(m_mnr);
        m_qryMap->exec();
    }
    else
    {
        m_qryMap->exec("SELECT ID, adressID, mnr from tblAdressMap WHERE mandant = 1;");
    }

    m_qryMap->first();
    ui->cmdPrev->setEnabled(false);
    updateUI();
}

void CMandant::updateUI()
{
    QSqlRecord lrec = m_qryMap->record();
    m_mnr = m_qryMap->value(lrec.indexOf("mnr")).toInt();
    ui->txtMnr->setText(QString::number(m_mnr));
    ui->Adresse->setAdressID(m_qryMap->value(lrec.indexOf("adressID")).toInt());
    ui->padAcc->setMandantID(m_mnr);
}

void CMandant::on_cmdPrev_clicked()
{
    ui->Adresse->updateDB();
    ui->cmdNext->setEnabled(true);
    if(!m_qryMap->previous())
    {
        m_qryMap->first();
        ui->cmdPrev->setEnabled(false);
    }
    updateUI();
}

void CMandant::on_cmdNext_clicked()
{
    ui->Adresse->updateDB();
    ui->cmdPrev->setEnabled(true);
    if(!m_qryMap->next())
    {
        m_qryMap->last();
        ui->cmdNext->setEnabled(false);
    }
    updateUI();
}

void CMandant::on_cmdClose_clicked()
{
    ui->Adresse->updateDB();
    this->close();
}

void CMandant::on_cmdDelete_clicked()
{
    QSqlRecord lrec = m_qryMap->record();
    if(m_qryMap->size() == 1)
    {
        QMessageBox *dlg = new QMessageBox();
        dlg->setWindowTitle("Löschen nicht möglich!");
        dlg->setText("Der letzte Mandant kann nicht gelöscht werden!");
        dlg->setInformativeText("Um die Konsistenz der Datenbank aufrecht zu erhalten,\nwurde die Anforderung abgewiesen!");
        dlg->setIcon(QMessageBox::Critical);
        dlg->exec();
        delete dlg;
        return;
    }

    QMessageBox *dlg = new QMessageBox();
    dlg->setLocale(QLocale(QLocale::German, QLocale::Germany));
    dlg->setWindowTitle("Löschen eines Mandanten");
    dlg->setText("Wollen Sie diesen Mandanten wirklich löschen?");
    dlg->setInformativeText("Die Aktion kann nicht rückgängig gemacht werden.\nSiehe \"Details\"");
    dlg->setDetailedText("Alle ggf. noch dem Mandanten zugehörigen Aufträge\nwerden dem ersten Mandanten zugeordnet.\n\nDie betroffenen Auftrags-Nummern werden zum Ausdruck vorbereitet.");
    dlg->setIcon(QMessageBox::Warning);
    dlg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dlg->setDefaultButton(QMessageBox::No);
    dlg->setButtonText(QMessageBox::Yes, "Ja, hinfort mit ihm!");
    dlg->setButtonText(QMessageBox::No, "Nein, besser nicht...!");   
    dlg->setButtonText(QMessageBox::Information,"Details...");

    if(dlg->exec() == QMessageBox::Yes)
    {
        int lmapID = m_qryMap->value(lrec.indexOf("ID")).toInt();
        m_qryMap->prepare("DELETE FROM tblAdressMap WHERE ID = ?;");
        m_qryMap->addBindValue(lmapID);
        m_qryMap->exec();
        //TODO: Loeschen blockieren, wenn Mandant Auftaege hat.
    }
    else
    {
        QMessageBox *dlg = new QMessageBox();
        dlg->setWindowTitle("Löschen verworfen");
        dlg->setText("FEIGLING!!!");
        QFont font;
        font.setBold(true);
        font.setPointSize(24);
        dlg->setFont(font);
        QPixmap icon(":/icons/face-raspberry.png");
        dlg->setIconPixmap(icon);
        dlg->exec();        
    }

    delete dlg;
    setupQuery(false);
}
