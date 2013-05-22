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

#include "cclientaccountpad.h"
#include "ui_cclientaccountpad.h"

CClientAccountPad::CClientAccountPad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CClientAccountPad)
{
    ui->setupUi(this);
    setupMenu();
    ui->tbvwBankAccounts->setColumnWidth(0, 150);
    ui->tbvwBankAccounts->setColumnWidth(2, 100);
    ui->tbvwBankAccounts->setColumnWidth(3, 200);
    ui->tbvwBankAccounts->setColumnWidth(4, 150);
    m_qry = new QSqlQuery();
    m_UstID = new QString();
    m_myAccRef = new QString();
}

CClientAccountPad::~CClientAccountPad()
{
    delete ui;
    delete m_qry;
    delete m_UstID;
    delete m_myAccRef;
}

void CClientAccountPad::setClientID(int pID)
{
    m_id = pID;
    m_client = true;
    m_qry->prepare("SELECT ID, clientid, mandantid, blz, bankname, accnumber, iban, swift, standard FROM tblBankAccs WHERE clientid = ?;");
    m_qry->addBindValue(pID);
    m_qry->exec();
    updateUI();
}

void CClientAccountPad::setMandantID(int pID)
{    
    m_id = pID;
    m_client = false;
    m_qry->prepare("SELECT ID, clientid, mandantid, blz, bankname, accnumber, iban, swift, standard FROM tblBankAccs WHERE mandantid = ?;");
    m_qry->addBindValue(pID);
    m_qry->exec();
    updateUI();
}

void CClientAccountPad::setUstID(QString pValue)
{
    *m_UstID = pValue;
    updateUI();
}

void CClientAccountPad::setMyAccRef(QString pValue)
{
    *m_myAccRef = pValue;
    updateUI();
}

QString CClientAccountPad::getUstID()
{
    if(*m_UstID != ui->txtUstID->text())
    {
        *m_UstID = ui->txtUstID->text();
    }

    return *m_UstID;
}

QString CClientAccountPad::getMyAccRef()
{
    if(*m_myAccRef != ui->txtMyAccRef->text())
    {
        *m_myAccRef = ui->txtMyAccRef->text();
    }

    return *m_myAccRef;
}

void CClientAccountPad::updateUI()
{
    /*
     * Falls Kundensatz, aus der tblClients die UstID und die eigene Kundenreferenz holen und darstellen.
     */
    if(m_client)
    {
        ui->lblUstID->setVisible(true);
        ui->lblMyAccRef->setVisible(true);
        ui->txtUstID->setVisible(true);
        ui->txtMyAccRef->setVisible(true);
        ui->txtUstID->setText(*m_UstID);
        ui->txtMyAccRef->setText(*m_myAccRef);
    }
    else    // ansonsten txtUstID und txtMyAccRef unsichtbar machen
    {
        ui->lblUstID->setVisible(false);
        ui->lblMyAccRef->setVisible(false);
        ui->txtUstID->setVisible(false);
        ui->txtMyAccRef->setVisible(false);
    }

    QTableWidget *ltbl = ui->tbvwBankAccounts; // Macht den Code etwas lesbarer
    // zunächst das TableWidget löschen
    ltbl->clear();
    // Header anlegen
    QStringList lheader;
    lheader.append("Bank");
    lheader.append("BLZ");
    lheader.append("Konto-Nr.");
    lheader.append("IBAN");
    lheader.append("S.W.I.F.T.");
    ui->tbvwBankAccounts->setHorizontalHeaderLabels(lheader);
    //Wenn wir ein gültiges Resultset für die Konten haben...
    if(m_qry->first())
    {
        ltbl->setRowCount(m_qry->size()+1); //...Anzahl Konten + 1 (für Neuanlage) Zeilen anlegen.
        int row = 0;
        do          // Iteration der Konto-Sätze
        {            
            QSqlRecord lrec = m_qry->record();
            QTableWidgetItem *litem0 = new QTableWidgetItem(m_qry->value(lrec.indexOf("bankname")).toString());
            litem0->setData(QTableWidgetItem::UserType, m_qry->value(lrec.indexOf("ID")));           
            ltbl->setItem(row, 0, litem0);            
            QTableWidgetItem *litem1 = new QTableWidgetItem(m_qry->value(lrec.indexOf("blz")).toString());            
            ltbl->setItem(row, 1, litem1);
            QTableWidgetItem *litem2 = new QTableWidgetItem(m_qry->value(lrec.indexOf("accnumber")).toString());            
            ltbl->setItem(row, 2, litem2);
            QTableWidgetItem *litem3 = new QTableWidgetItem(m_qry->value(lrec.indexOf("iban")).toString());            
            ltbl->setItem(row, 3, litem3);
            QTableWidgetItem *litem4 = new QTableWidgetItem(m_qry->value(lrec.indexOf("swift")).toString());            
            ltbl->setItem(row, 4, litem4);

            if(m_qry->value(lrec.indexOf("standard")).toBool() == true) // Standard-Konto; wird markiert.
            {
                QTableWidgetItem *item = new QTableWidgetItem("->");
                QFont fnt = item->font();
                fnt.setBold(true);
                item->setFont(fnt);
                ui->tbvwBankAccounts->setVerticalHeaderItem(row, item);
            }

            row++;
        }while(m_qry->next());
    }
    else        // es gibt noch keine Kontodaten für den Mandant/Kunden...
    {
        ui->tbvwBankAccounts->setRowCount(1); // ...also Zeile für Header und Neuanlage erzeugen.
    }
}

void CClientAccountPad::contextMenuEvent(QContextMenuEvent *e)
{
    if(!ui->tbvwBankAccounts->currentItem())
    {
        return;
    }

    QString ltitle = ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(),0)->text();
    ltitle.append("; Kto.-Nr. ");
    ltitle.append(ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(),2)->text());
    m_menu->setTitle(ltitle);
    m_menu->setWindowTitle(ltitle);
    m_menu->exec(e->globalPos());
}

void CClientAccountPad::keyPressEvent(QKeyEvent *e)
{
    if(!ui->tbvwBankAccounts->hasFocus())
    {
        QWidget::keyPressEvent(e);
        return;
    }

    if(e->key() == Qt::Key_Delete)
    {
        deleteAccount();
    }
}

void CClientAccountPad::on_tbvwBankAccounts_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(currentRow == -1)
    {
        return;
    }
    QTableWidget *ltbl = ui->tbvwBankAccounts;    /* macht den Code lesbarer... */
    int maxrow = ltbl->rowCount();
    int lid;
    int row;

    if(currentRow == (maxrow - 1))
    {
        QTableWidgetItem *it = new QTableWidgetItem();
        ltbl->setItem(currentRow, currentColumn, it);
        addNewRow(currentRow,currentColumn);
        ltbl->setCurrentCell(currentRow, currentColumn);
    }

    if(previousRow == -1)
    {
        return;
    }

    if(currentRow != previousRow)
    {
        row = previousRow;
    }
    else
    {
        row = currentRow;
    }

    if(ltbl->item(row,0))
    {
        lid = ltbl->item(row,0)->data(QTableWidgetItem::UserType).toInt(); /* Db-ID der Zeile, die wir verlassen haben... */
    }
    else
    {
        lid = 0;
    }

    if(lid > 0) /* vorhandener Satz; mit 'UPDATE' speichern... */
    {
        if(m_client)
        {
            m_qry->prepare("UPDATE tblBankAccs SET clientid = ?, blz = ?, bankname = ?, accnumber = ?, iban = ?, swift = ? WHERE ID = ?;");
        }
        else
        {
            m_qry->prepare("UPDATE tblBankAccs SET mandantid = ?, blz = ?, bankname = ?, accnumber = ?, iban = ?, swift = ? WHERE ID = ?;");
        }

        m_qry->addBindValue(m_id);
        QString blz = ltbl->item(row, 1)->text();
        QString bname = ltbl->item(row, 0)->text();
        QString acno = ltbl->item(row, 2)->text();
        QString iban = ltbl->item(row, 3)->text();
        QString swift = ltbl->item(row, 4)->text();
        m_qry->addBindValue(blz);
        m_qry->addBindValue(bname);
        m_qry->addBindValue(acno);
        m_qry->addBindValue(iban);
        m_qry->addBindValue(swift);
        m_qry->addBindValue(lid);
        m_qry->exec();
    }
    else
    {
        addNewRow(previousRow, previousColumn);
    }
}

void CClientAccountPad::deleteAccount()
{
    if(!ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(), 0))
    {
        return;
    }

    QMessageBox *dlg = new QMessageBox();
    dlg->setWindowTitle("Kontoverbindung löschen");
    dlg->setText("Möchten Sie diese Kontoverbindung löschen?");
    QString litext = ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(), 0)->text();
    litext.append("\nKto.-Nr.: ");
    litext.append(ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(), 2)->text());
    dlg->setInformativeText(litext);
    dlg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    dlg->setButtonText(QMessageBox::Yes, "Ja, bitte löschen!");
    dlg->setButtonText(QMessageBox::No, "Nein, nicht löschen!");
    dlg->setDefaultButton(QMessageBox::No);

    if(dlg->exec() == QMessageBox::Yes)
    {
        int lid = ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(), 0)->data(QTableWidgetItem::UserType).toInt();
        QSqlQuery lq;
        lq.prepare("DELETE FROM tblBankAccs WHERE ID = ?;");
        lq.addBindValue(lid);
        lq.exec();

        if(m_client)
        {
            setClientID(m_id);
        }
        else
        {
            setMandantID(m_id);
        }
    }
}

void CClientAccountPad::makeAccStandard()
{
    // ID sichern
    int lid = ui->tbvwBankAccounts->item(ui->tbvwBankAccounts->currentRow(), 0)->data(QTableWidgetItem::UserType).toInt();
    QSqlQuery lq;
    // zunächst alle auf "Nicht-Standard" setzen
    QString qstr = "UPDATE tblBankAccs SET standard = 0 WHERE ";

    if (m_client)
    {
        qstr.append("clientid = ?;");
    }
    else
    {
        qstr.append("mandantid = ?;");
    }

    lq.prepare(qstr);
    lq.addBindValue(m_id);
    lq.exec();
    // Jetzt ausgewählten flaggen
    lq.prepare("UPDATE tblBankAccs SET standard = 1 WHERE ID = ?;");
    lq.addBindValue(lid);
    lq.exec();

    //Ansicht aktualisieren
    if(m_client)
    {
        setClientID(m_id);
    }
    else
    {
        setMandantID(m_id);
    }
}

void CClientAccountPad::setupMenu()
{
    m_menu = new QMenu(this);
    QList<QAction*> lActions;

    m_acDelete = new QAction("Kontoverbindung löschen...", this);
    lActions.append(m_acDelete);
    m_acStandard = new QAction("Als Standard setzen", this);
    lActions.append(m_acStandard);
    m_menu->addActions(lActions);
    connect(m_acDelete, SIGNAL(triggered()), SLOT(deleteAccount()));
    connect(m_acStandard, SIGNAL(triggered()), SLOT(makeAccStandard()));
}

void CClientAccountPad::addNewRow(int row, int col)
{
    QString txt;
    if(ui->tbvwBankAccounts->item(row, col))
    {
        txt = ui->tbvwBankAccounts->item(row, col)->text();
    }
    if(m_client)
    {
        m_qry->prepare("INSERT INTO tblBankAccs (clientid) VALUES (?);");
    }
    else
    {
        m_qry->prepare("INSERT INTO tblBankAccs (mandantid) VALUES (?);");
    }
    m_qry->addBindValue(m_id);
    m_qry->exec();
    QTableWidgetItem *litem = new QTableWidgetItem();
    litem->setData(QTableWidgetItem::UserType, m_qry->lastInsertId().toInt());
    ui->tbvwBankAccounts->setRowCount(ui->tbvwBankAccounts->rowCount() + 1);
    ui->tbvwBankAccounts->setItem((ui->tbvwBankAccounts->rowCount() - 2), 0, litem);

    if(ui->tbvwBankAccounts->item(row, col))
    {
        ui->tbvwBankAccounts->item(row, col)->setText(txt);
    }

    if(m_client)
    {
        setClientID(m_id);
    }
    else
    {
        setMandantID(m_id);
    }
}


void CClientAccountPad::on_txtUstID_lostFocus()
{
    emit dataChanged();
}

void CClientAccountPad::on_txtMyAccRef_lostFocus()
{
    emit dataChanged();
}
