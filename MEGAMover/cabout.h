/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   09.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef CABOUT_H
#define CABOUT_H

#include "../MEGAMover/qtversion.h"
#ifdef QT5
#include <QtWidgets/QDialog>
#else
#include <QtGui/QDialog>
#endif

namespace Ui {
class CAbout;
}

class CAbout : public QDialog
{
    Q_OBJECT
    
public:
    explicit CAbout(QWidget *parent = 0);
    ~CAbout();
    
private slots:
    void on_cmdClose_clicked();

private:
    Ui::CAbout *ui;
};

#endif // CABOUT_H
