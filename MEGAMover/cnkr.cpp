/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   12.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#include "cnkr.h"

/*!
 * \brief CNkr::CNkr
 * \param pMnr
 *  Bei Instanzierung mit diesem Konstruktor wird sofort eine neue Auftragsnummer erzeugt.
 */
CNkr::CNkr(int pMnr)
{
    m_mandant = pMnr;
    m_number = newAnr();
}


/*!
 * \brief CNkr::CNkr
 * \param pMnr
 * \param pYear
 * \param pMonth
 * \param pNumber
 *  Mit diesem Konstruktor wird eine vorhandene Auftragsnummer zum Voll-String verarbeitet.
 */
CNkr::CNkr(int pMnr, int pYear, int pMonth, int pNumber)
{
    m_mandant = pMnr;
    m_year = pYear;
    m_month = pMonth;
    m_number = pNumber;
}

// Get-Funktionen

int CNkr::mandant()
{
    return m_mandant;
}

int CNkr::year()
{
    return m_year;
}

int CNkr::month()
{
    return m_month;
}

int CNkr::number()
{
    return m_number;
}

/* Ausgabe der Auftragsnummer als String */
QString CNkr::fullNumber()
{
    /* Ausgabestring... */
    QString lFullNr;
    /* ...über Stream befüllen */
    QTextStream out(&lFullNr);
    out.setPadChar('0');
    out.setFieldAlignment(QTextStream::AlignRight);
    out.setFieldWidth(2);
    out << m_mandant;
    out.setFieldWidth(0);
    out << "/";
    out.setFieldWidth(2);
    QString str(QString::number(m_year));
    out << str.right(2);
    out.setFieldWidth(0);
    out << "/";
    out.setFieldWidth(2);
    out.setPadChar('0');
    out.setFieldAlignment(QTextStream::AlignRight);
    out << m_month ;
    out.setFieldWidth(0);
    out << "/";
    out.setFieldWidth(4);
    out << m_number;
    return lFullNr;
}

/* Neue Auftragsnummer generieren */
int CNkr::newAnr()
{
    /* Nkr-Tabelle über Mandant, Jahr und Monat abfragen */
    m_month = QDate::currentDate().month();
    m_year = QDate::currentDate().year();
    QSqlQuery *qry = new QSqlQuery();
    qry->prepare("SELECT ID, lfdnr FROM tblNkr WHERE mnr = ? AND jahr = ? AND monat = ?;");
    qry->addBindValue(m_mandant);
    qry->addBindValue(m_year);
    qry->addBindValue(m_month);
    qry->exec();
    if(qry->first())
    {
        /* Es gibt im laufenden Monat
         * bereits erzeugte Auftragsnummern.
         * Es wird die nächste freie Nummer
         * verwendet. */
        int id = qry->value(0).toInt();
        int anr = qry->value(1).toInt();
        qry->prepare("UPDATE tblNkr SET lfdnr = ? where ID = ?;");
        qry->addBindValue(anr + 1);
        qry->addBindValue(id);
        qry->exec();
        return anr;
    }
    else
    {
        /* Es muss ein neuer Monat angelegt
         * werden. Die Zählung beginnt
         * wieder mit '1' */
        qry->prepare("INSERT INTO tblNkr (mnr, jahr, monat, lfdnr) VALUES (?, ?, ?, 2);");
        qry->addBindValue(m_mandant);
        qry->addBindValue(m_year);
        qry->addBindValue(m_month);
        qry->exec();
        return 1;
    }
}
