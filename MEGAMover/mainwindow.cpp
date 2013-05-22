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

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBox->setItemText(0, "Auftragswesen");
    ui->toolBox->setItemText(1, "Abrechnungswesen");
    ui->dockWidget->setFixedWidth(200);
    core = new CCore(this);
    QString lTitle;
    lTitle = APP;
    lTitle.append(" ");
    lTitle.append(MAJ);
    lTitle.append(".");
    lTitle.append(MIN);
    lTitle.append(" Build ");
    lTitle.append(REL);
    this->setWindowTitle(lTitle);        
    buildStatusBar();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete core;    
}

void MainWindow::on_actionProgramm_schli_e_en_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox *l_msg = new QMessageBox(this);
    l_msg->setWindowTitle("Programm beenden");
    l_msg->setText("Möchten Sie das Programm beenden?");
    l_msg->setInformativeText("Die Datenbank wird aktualisiert und die Verbindung wird geschlossen.");
    l_msg->setIcon(QMessageBox::Question);
    l_msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    l_msg->setButtonText(QMessageBox::Yes, "Ja, bin fertig!");
    l_msg->setButtonText(QMessageBox::No, "Nein, hab noch was vergessen...");
    l_msg->setDefaultButton(QMessageBox::No);

    if(l_msg->exec() == QMessageBox::Yes)
    {
        e->accept();
    }
    else
    {
        e->ignore();
    }
}

CCore *MainWindow::getCore()
{
    return core;
}

QLabel* MainWindow::setMandantStatus()
{
    QString *lbar = new QString("Mandant: ");
    QSqlQuery *qry = new QSqlQuery();
    int lmnr = core->getMandant();
    lbar->append(QString::number(lmnr));
    lbar->append(" - ");
    qry->prepare("SELECT adressID FROM tblAdressMap WHERE mnr = ?;");
    qry->addBindValue(lmnr);
    qry->exec();
    qry->first();
    int ladr = qry->value(0).toInt();
    qry->prepare("SELECT vorname, name1, ort FROM tblAdresses WHERE ID = ?;");
    qry->addBindValue(ladr);
    qry->exec();
    qry->first();

    if(qry->value(0).toString().size() > 1)
    {
        lbar->append(qry->value(0).toString());
        lbar->append(" ");
    }

    lbar->append(qry->value(1).toString());
    lbar->append(", ");
    lbar->append(qry->value(2).toString());
    QLabel *lbl = new QLabel(*lbar);
    return lbl;
}

void MainWindow::buildStatusBar()
{
    QStatusBar *bar = new QStatusBar();

    QLabel *mlbl = setMandantStatus();
    bar->addPermanentWidget(mlbl);

    /*QString status = "Datenbank: ";
    status.append(core->getSettings()->getDBname());
    status.append(" auf ");
    status.append(core->getSettings()->getDBserver());
    QLabel *dlbl = new QLabel(status);
    bar->addPermanentWidget(dlbl);*/

    setStatusBar(bar);
}


void MainWindow::on_action_Datenbank_triggered()
{
    m_opts = new COptions(this);
    m_opts->setDBserver(core->getSettings()->getDBserver());
    m_opts->setDBname(core->getSettings()->getDBname());
    m_opts->setDBUser(core->getSettings()->getDBuser());
    m_opts->setDBPassword(core->getSettings()->getDBpassword());
    if(m_opts->exec() == QDialog::Accepted)
    {        
        CSettings *lset = core->getSettings();
        lset->setDBserver(m_opts->getDBserver());
        lset->setDBname(m_opts->getDBname());
        lset->setDBuser(m_opts->getDBUser());
        lset->setDBpassword(m_opts->getDBPassword());
        core->reConnectDB();
    }
    delete m_opts;
}

void MainWindow::on_actionMan_danten_triggered()
{
    CMandant *mandant = new CMandant(this);
    mandant->setCore(core);
    mandant->exec();
    delete mandant;
}




void MainWindow::on_action_ber_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_ber_triggered()
{
    CAbout *dlg = new CAbout(this);
    dlg->exec();
    delete dlg;
}

void MainWindow::on_actionNeu_Be_arbeiten_triggered()
{    
    openOrder();
}



void MainWindow::on_action_aus_w_hlen_triggered()
{
    CMdtWahl *dlg = new CMdtWahl(this);
    dlg->setMandant(core->getMandant());
    if(dlg->exec() == QDialog::Accepted)
    {
        core->setMandant(dlg->choice());
    }

    delete dlg;
}

void MainWindow::on_cmdAuftrag_clicked()
{
    openOrder();
}

void MainWindow::on_cmdClose_clicked()
{
    this->close();
}

void MainWindow::openOrder()
{
    m_orders = new COrders(this);
    m_orders->setSubWindow(ui->mdiArea->addSubWindow(m_orders));
    m_orders->show();
}

void MainWindow::openClients()
{
    m_clients = new CClient(this);
    QMdiSubWindow *wn = ui->mdiArea->addSubWindow(m_clients);
    m_clients->setSubWindow(wn);
    m_clients->show();
}

void MainWindow::on_action_Kunden_triggered()
{
    openClients();
}

void MainWindow::on_cmdClients_clicked()
{
    openClients();
}
