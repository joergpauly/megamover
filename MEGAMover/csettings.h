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

#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>

class CSettings : public QObject
{
    Q_OBJECT



//Private Properties
private:
    QSettings   *m_settings;
    QString     *m_dbServer;
    QString     *m_dbName;
    QString     *m_dbUser;
    QString     *m_dbPassword;
    int         m_mandant;


public:
    explicit CSettings(QObject *parent = 0);
    ~CSettings();

    void readSettings();
    QString getDBserver();
    QString getDBname();
    QString getDBuser();
    QString getDBpassword();
    int     getMandant();
    void setDBserver(QString *pServer);
    void setDBname(QString *pName);
    void setDBuser(QString *pUser);
    void setDBpassword(QString *pPassword);
    void setMandant(int pMandant);
    
signals:
    
public slots:
    
};

#endif // CSETTINGS_H
