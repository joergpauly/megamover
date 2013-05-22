/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   05.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef COPTIONS_H
#define COPTIONS_H

#include "qtversion.h"
#ifdef QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

namespace Ui {
class COptions;
}

class COptions : public QDialog
{
    Q_OBJECT

private:
    QString *m_dbServer;
    QString *m_dbName;
    QString *m_dbUser;
    QString *m_dbPassword;
    
public:
    explicit COptions(QWidget *parent = 0);
    ~COptions();
    
    QString* getDBserver();
    QString* getDBname();
    QString* getDBUser();
    QString* getDBPassword();
    void setDBserver(QString pDBserver);
    void setDBname(QString pDBname);
    void setDBUser(QString pDBuser);
    void setDBPassword(QString pDBpassword);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::COptions *ui;
};

#endif // COPTIONS_H
