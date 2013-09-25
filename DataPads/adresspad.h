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

#ifndef ADRESSPAD_H
#define ADRESSPAD_H

#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "DataPads_global.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtWidgets/QMessageBox>



namespace Ui {
class AdressPad;
}

class DATAPADSSHARED_EXPORT AdressPad : public QWidget
{
    Q_OBJECT

//Private Properties
private:

    Ui::AdressPad *ui;
    QSqlQuery *m_query;    
    int m_id;

//Private Member
    void setFieldsEditable(bool pEnable);
    
public:        

    explicit AdressPad(QWidget *parent = 0);
    ~AdressPad();
    void setAdressID(int pAdrID);
    bool next();
    bool previous();
    bool first();
    bool last();
    bool seek(int pField, QString* pValue);
    void updateUI();
    void updateDB();
    void clearUI();
    int insertNew();
    void beginEdit();

private slots:

    void on_txtLDKZ_lostFocus();
};

#endif // ADRESSPAD_H
