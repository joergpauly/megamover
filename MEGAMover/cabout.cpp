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

#include "cabout.h"
#include "ui_cabout.h"

CAbout::CAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAbout)
{
    ui->setupUi(this);
}

CAbout::~CAbout()
{
    delete ui;
}

void CAbout::on_cmdClose_clicked()
{
    this->close();
}
