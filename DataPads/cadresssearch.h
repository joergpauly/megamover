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

#ifndef CADRESSSEARCH_H
#define CADRESSSEARCH_H

//System-Header
#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include "DataPads_global.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlError>


namespace Ui {
class CAdressSearch;
}

class DATAPADSSHARED_EXPORT CAdressSearch : public QDialog
{
    Q_OBJECT
    
public:
    explicit CAdressSearch(QWidget *parent = 0);
    ~CAdressSearch();

//Private Properties
private slots:
    void on_tblAdresses_clicked(const QModelIndex &index);    

    void on_tblAdresses_doubleClicked(const QModelIndex &index);

    void on_txtNameFilter_textEdited(const QString &arg1);

private:
    Ui::CAdressSearch *ui;
    QSqlQueryModel *model;
    int m_adrID;

//Öffentliche Member
public:
    int getAdrID();

};

#endif // CADRESSSEARCH_H
