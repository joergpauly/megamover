/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   13.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#include "cclient.h"
#include "ui_cclient.h"

CClient::CClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CClient)
{
    ui->setupUi(this);
    m_qry = new QSqlQuery();
    m_qry->exec("SELECT * FROM tblClients;");
    m_qry->first();
    updateUI();
}

CClient::~CClient()
{
    delete ui;
}

void CClient::setSubWindow(QMdiSubWindow *pSubWnd)
{
    m_subwnd = pSubWnd;
}

void CClient::on_cmdClose_clicked()
{
    updateDB();
    m_subwnd->close();
}

void CClient::updateUI()
{    
    checkClientTablePosition();    
    QSqlRecord lrec(m_qry->record());
    m_id = m_qry->value(lrec.indexOf("ID")).toInt();
    ui->txtKdNr->setText(QString::number(m_id));
    ui->txtMatch->setText(m_qry->value(lrec.indexOf("mc")).toString());
    m_agadrid = m_qry->value(lrec.indexOf("agadrid")).toInt();
    m_readrid = m_qry->value(lrec.indexOf("readrid")).toInt();
    ui->padAG->setAdressID(m_agadrid);
    ui->padRE->setAdressID(m_readrid);
    ui->padAccount->setUstID(m_ustID);
    ui->padAccount->setMyAccRef(m_myaccref);
    ui->padAccount->setClientID(m_id);
}

void CClient::updateDB()
{
    // Alle UI-Werte schreiben
    ui->padAG->updateDB();
    ui->padRE->updateDB();
    m_qry->prepare("UPDATE tblClients SET mc = ?, agadrid = ?, readrid = ?, ustid = ?, myaccid = ? WHERE ID = ?;");
    m_qry->addBindValue(ui->txtMatch->text());
    m_qry->addBindValue(m_agadrid);
    m_qry->addBindValue(m_readrid);
    m_qry->addBindValue(ui->padAccount->getUstID());
    m_qry->addBindValue(ui->padAccount->getMyAccRef());
    m_qry->addBindValue(m_id);
    m_qry->exec();

    // Neu einlesen und auf aktuellen Kunden positionieren
    moveToClient(m_id);
}

void CClient::checkClientTablePosition()
{
    ui->cmdNextClient->setEnabled(true);
    ui->cmdPrevClient->setEnabled(true);

    if(m_qry->at() == 0)
    {
        ui->cmdPrevClient->setEnabled(false);
    }

    if(m_qry->at() == (m_qry->size() - 1))
    {
        ui->cmdNextClient->setEnabled(false);
    }
}

void CClient::moveToClient(int pID)
{
    // m_qry neu einlesen
    m_qry->exec("SELECT * FROM tblClients ORDER BY ID ASC;");
    QSqlRecord lrec = m_qry->record();
    m_qry->first();
    while(m_qry->value(lrec.indexOf("ID")).toInt() != pID)
    {
        m_qry->next();
    }
    if(m_qry->isValid())
    {
        m_id = m_qry->value(lrec.indexOf("ID")).toInt();
    }    
}

void CClient::on_cmdPrevClient_clicked()
{
    updateDB();
    m_qry->previous();
    updateUI();
}

void CClient::on_cmdNextClient_clicked()
{
    updateDB();
    m_qry->next();
    updateUI();
}

void CClient::on_cmdNewClient_clicked()
{
    updateDB();
    ui->padAG->clearUI();
    ui->padRE->clearUI();
    m_qry->exec("INSERT INTO tblClients (mc, agadrid, readrid, ustid, myaccid)"
                "VALUES ('', 0, 0, '', '');");
    m_id = m_qry->lastInsertId().toInt();
    moveToClient(m_id);
    updateUI();
}

void CClient::on_cmdSrchClient_clicked()
{
    //updateDB();
    CClientSearch *lsrch = new CClientSearch(this);
    if(lsrch->exec() == QDialog::Accepted)
    {        
        moveToClient(lsrch->getClientID());
        updateUI();
    }
}

void CClient::on_cmdDeleteClient_clicked()
{
    QMessageBox *dlg = new QMessageBox();
    dlg->setWindowTitle("Kunden löschen");
    dlg->setText("Möchten Sie diesen Kundenstammsatz wirklich löschen?");
    dlg->setInformativeText("(Siehe \"Details\" für mehr Informationen)");
    dlg->setDetailedText("Es wird nur der Kunden-Kopfsatz inkl.\n der Kontodaten gelöscht,\n\bnicht\b jedoch die Adressen.\n\nDiese müssen ggf. in der \"Zentralen Adressverwaltung\"\ngelöscht werden.");
    dlg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dlg->setButtonText(QMessageBox::Yes, "Ja, löschen!");
    dlg->setButtonText(QMessageBox::No, "Nein");
    dlg->setIcon(QMessageBox::Question);
    if(dlg->exec() == QMessageBox::Yes)
    {
        QSqlQuery lqry;
        //Zunächst Bank-Daten löschen:
        lqry.prepare("DELETE FROM tblBankAccs WHERE clientid = ?;");
        lqry.addBindValue(m_id);
        lqry.exec();
        //Dann den Kunden-Kopfsatz:
        lqry.prepare("DELETE FROM tblClients WHERE ID = ?;");
        lqry.addBindValue(m_id);
        lqry.exec();
        //Query neu einlesen und auf nun ersten Satz positionieren
        m_qry->exec("SELECT * FROM tblClients;");
        m_qry->first();
        updateUI();
    }
}

void CClient::on_cmdNewAdrAG_clicked()
{
    ui->padAG->clearUI();
    m_agadrid = ui->padAG->insertNew();
    ui->padAG->beginEdit();
}

void CClient::on_cmdSrchAdrAG_clicked()
{
    CAdressSearch *lsrch = new CAdressSearch(this);

    if(lsrch->exec() == QDialog::Accepted)
    {
        m_agadrid = lsrch->getAdrID();
        updateDB();
        updateUI();
    }
}

void CClient::on_cmdNewAdrRE_clicked()
{
    ui->padRE->clearUI();
    m_readrid = ui->padRE->insertNew();
    ui->padRE->beginEdit();
}

void CClient::on_cmdSrchAdrRE_clicked()
{
    CAdressSearch *lsrch = new CAdressSearch(this);

    if(lsrch->exec() == QDialog::Accepted)
    {
        m_readrid = lsrch->getAdrID();
        updateDB();
        updateUI();
    }
}

void CClient::on_cmdSaveClient_clicked()
{
    updateDB();
}

void CClient::on_padAccount_dataChanged()
{
    m_ustID = ui->padAccount->getUstID();
    m_myaccref = ui->padAccount->getMyAccRef();
}

void CClient::on_txtMatch_textChanged(const QString &arg1)
{
    ui->txtMatch->setText(arg1.toUpper());
}
