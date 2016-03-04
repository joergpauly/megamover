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

#include "adresspad.h"
#include "ui_adresspad.h"
#include <QtWidgets/QLineEdit>

AdressPad::AdressPad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdressPad)
{
    ui->setupUi(this);
    connect(ui->txtAnrede,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtEmail,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtFax,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtHnr,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtLDKZ,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtMobil,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtName1,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtName2,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtOrt,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtPLZ,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtStrasse,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtTelefon,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtTitel,SIGNAL(editingFinished()),this, SLOT(dirty()));
    connect(ui->txtVorname,SIGNAL(editingFinished()),this, SLOT(dirty()));
    m_query = new QSqlQuery();
}

AdressPad::~AdressPad()
{
    delete ui;        
    delete m_query;
}

void AdressPad::setAdressID(int pAdrID)
{
    m_id = pAdrID;
    m_query->prepare("SELECT * FROM tblAdresses WHERE ID = ?;");
    m_query->addBindValue(pAdrID);
    m_query->exec();
    m_query->first();
    updateUI();
}

bool AdressPad::next()
{
    updateDB();
    bool res = m_query->next();
    updateUI();
    return res;
}

bool AdressPad::previous()
{
    updateDB();
    bool res = m_query->previous();
    updateUI();
    return res;
}

bool AdressPad::first()
{
    updateDB();
    bool res = m_query->first();
    updateUI();
    return res;
}

bool AdressPad::last()
{
    updateDB();
    bool res = m_query->last();
    updateUI();
    return res;
}

bool AdressPad::seek(int pField, QString *pValue)
{
    updateDB();
    bool res;
    res = m_query->first();

    while(m_query->value(pField).toString() != *pValue && res == true)
    {
        res = m_query->next();
    }

    if(res)
    {
        updateUI();
    }

    return res;
}

void AdressPad::updateUI()
{
    if(!m_query->isValid()) //Gültiger Datensatz? Sonst Felder disabeln und raus hier...
    {
        setFieldsEditable(false);
        return;
    }

    setFieldsEditable(true);
    QSqlRecord lrec = m_query->record();
    m_id = m_query->value(lrec.indexOf("ID")).toInt();
    ui->txtAnrede->setText(m_query->value(lrec.indexOf("anrede")).toString());
    ui->txtTitel->setText(m_query->value(lrec.indexOf("title")).toString());
    ui->txtVorname->setText(m_query->value(lrec.indexOf("vorname")).toString());
    ui->txtName1->setText(m_query->value(lrec.indexOf("name1")).toString());
    ui->txtName2->setText(m_query->value(lrec.indexOf("name2")).toString());
    ui->txtStrasse->setText(m_query->value(lrec.indexOf("strasse")).toString());
    ui->txtHnr->setText(m_query->value(lrec.indexOf("strnummer")).toString());
    ui->txtLDKZ->setText(m_query->value(lrec.indexOf("ldkz")).toString());
    ui->txtPLZ->setText(m_query->value(lrec.indexOf("plz")).toString());
    ui->txtOrt->setText(m_query->value(lrec.indexOf("ort")).toString());
    ui->txtTelefon->setText(m_query->value(lrec.indexOf("tel")).toString());
    ui->txtMobil->setText(m_query->value(lrec.indexOf("mobil")).toString());
    ui->txtFax->setText(m_query->value(lrec.indexOf("fax")).toString());
    ui->txtEmail->setText(m_query->value(lrec.indexOf("email")).toString());
}

void AdressPad::updateDB()
{
    m_query->prepare("UPDATE tblAdresses SET anrede = ?, title = ?, vorname = ?, name1 = ?, name2 = ?, strasse = ?, strnummer = ?, ldkz = ?, plz = ?, ort = ?, tel = ?, mobil = ?, fax = ?, email = ? WHERE ID = ?;");
    m_query->addBindValue(ui->txtAnrede->text());
    m_query->addBindValue(ui->txtTitel->text());
    m_query->addBindValue(ui->txtVorname->text());
    m_query->addBindValue(ui->txtName1->text());
    m_query->addBindValue(ui->txtName2->text());
    m_query->addBindValue(ui->txtStrasse->text());
    m_query->addBindValue(ui->txtHnr->text());
    m_query->addBindValue(ui->txtLDKZ->text());
    m_query->addBindValue(ui->txtPLZ->text());
    m_query->addBindValue(ui->txtOrt->text());
    m_query->addBindValue(ui->txtTelefon->text());
    m_query->addBindValue(ui->txtMobil->text());
    m_query->addBindValue(ui->txtFax->text());
    m_query->addBindValue(ui->txtEmail->text());
    m_query->addBindValue(m_id);
    m_query->exec();
    setAdressID(m_id);
}

void AdressPad::clearUI()
{
    ui->txtAnrede->setText("");
    ui->txtTitel->setText("");
    ui->txtVorname->setText("");
    ui->txtName1->setText("");
    ui->txtName2->setText("");
    ui->txtStrasse->setText("");
    ui->txtHnr->setText("");
    ui->txtLDKZ->setText("");
    ui->txtPLZ->setText("");
    ui->txtOrt->setText("");
    ui->txtTelefon->setText("");
    ui->txtMobil->setText("");
    ui->txtFax->setText("");
    ui->txtEmail->setText("");
}

int AdressPad::insertNew()
{
    m_query->prepare("INSERT INTO tblAdresses (anrede, title, vorname, name1, name2, strasse, strnummer, ldkz, plz, ort, tel, mobil, fax, email)"
                     "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    m_query->addBindValue(ui->txtAnrede->text());
    m_query->addBindValue(ui->txtTitel->text());
    m_query->addBindValue(ui->txtVorname->text());
    m_query->addBindValue(ui->txtName1->text());
    m_query->addBindValue(ui->txtName2->text());
    m_query->addBindValue(ui->txtStrasse->text());
    m_query->addBindValue(ui->txtHnr->text());
    m_query->addBindValue(ui->txtLDKZ->text());
    m_query->addBindValue(ui->txtPLZ->text());
    m_query->addBindValue(ui->txtOrt->text());
    m_query->addBindValue(ui->txtTelefon->text());
    m_query->addBindValue(ui->txtMobil->text());
    m_query->addBindValue(ui->txtFax->text());
    m_query->addBindValue(ui->txtEmail->text());
    m_query->exec();
    m_id = m_query->lastInsertId().toInt();
    setAdressID(m_id);
    return m_id;
}

void AdressPad::beginEdit()
{
    ui->txtAnrede->setFocus();
}

void AdressPad::setFieldsEditable(bool pEnable)
{
    ui->txtAnrede->setEnabled(pEnable);
    ui->txtVorname->setEnabled(pEnable);
    ui->txtTitel->setEnabled(pEnable);
    ui->txtName1->setEnabled(pEnable);
    ui->txtName2->setEnabled(pEnable);
    ui->txtStrasse->setEnabled(pEnable);
    ui->txtHnr->setEnabled(pEnable);
    ui->txtLDKZ->setEnabled(pEnable);
    ui->txtPLZ->setEnabled(pEnable);
    ui->txtOrt->setEnabled(pEnable);
    ui->txtTelefon->setEnabled(pEnable);
    ui->txtMobil->setEnabled(pEnable);
    ui->txtFax->setEnabled(pEnable);
    ui->txtEmail->setEnabled(pEnable);
}

void AdressPad::on_txtLDKZ_textChanged(const QString &arg1)
{
    ui->txtLDKZ->setText(arg1.toUpper());
}

void AdressPad::on_txtOrt_editingFinished()
{
    updateDB();
}

void AdressPad::dirty()
{
    updateDB();
}
