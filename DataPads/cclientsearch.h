/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   19.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef CCLIENTSEARCH_H
#define CCLIENTSEARCH_H

//System-Header
#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

#include "DataPads_global.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace Ui {
class CClientSearch;
}

class DATAPADSSHARED_EXPORT CClientSearch : public QDialog
{
    Q_OBJECT
    
public:
    explicit CClientSearch(QWidget *parent = 0);
    ~CClientSearch();
    int getClientID();
    
private slots:
    void on_tblClients_clicked(const QModelIndex &index);

    void on_tblClients_doubleClicked(const QModelIndex &index);

    void on_txtFilter_textEdited(const QString &arg1);    

private:
    Ui::CClientSearch *ui;
    QSqlQueryModel *model;
    int m_clientID;

};

#endif // CCLIENTSEARCH_H
