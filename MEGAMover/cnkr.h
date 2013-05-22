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

#ifndef CNKR_H
#define CNKR_H

//System-Header
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QTextStream>
#include <QDate>

//Projekt-Header
#include "corders.h"

class CNkr
{
private:
    int m_mandant;
    int m_year;
    int m_month;
    int m_number;
    QString m_full;

    int newAnr();

public:
    CNkr(int pMnr);
    CNkr(int pMnr, int pYear, int pMonth, int pNumber);
    int mandant();
    int year();
    int month();
    int number();
    QString fullNumber();





};

#endif // CNKR_H
