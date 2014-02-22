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
    ui->toolBox->setCurrentIndex(0);
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

/* Aufruf des Optionen-Dialoges */
void MainWindow::on_action_Datenbank_triggered()
{
    /* Widgets mit frisch ausgelesenen Werten füllen */
    m_opts = new COptions(this);
    m_opts->setDBserver(core->getSettings()->getDBserver());
    m_opts->setDBname(core->getSettings()->getDBname());
    m_opts->setDBUser(core->getSettings()->getDBuser());
    m_opts->setDBPassword(core->getSettings()->getDBpassword());
    // Dialog anzeigen
    if(m_opts->exec() == QDialog::Accepted)
    {        
        /* Dialog wurde akzeptiert:
         * Konfiguration aus dem Core holen */
        CSettings *lset = core->getSettings();
        /* Eingabedaten des Dialogs in
         * die Konfiguration schreiben. */
        lset->setDBserver(m_opts->getDBserver());
        lset->setDBname(m_opts->getDBname());
        lset->setDBuser(m_opts->getDBUser());
        lset->setDBpassword(m_opts->getDBPassword());
        /* Der Core soll die Verbindung zur
         * Datenbank mit den neuen Werten
         * neu aufbauen. */
        core->reConnectDB();
    }
    delete m_opts;
}

// Mandantenstamm aufrufen
void MainWindow::on_actionMan_danten_triggered()
{
    /* Dialog initialisieren */
    CMandant *mandant = new CMandant(this);
    /* Das Mandant-Objekt braucht
     * Zugriff auf den Core. */
    mandant->setCore(core);
    mandant->exec();
    delete mandant;
}

// Dialog "Über Qt..."
void MainWindow::on_action_ber_Qt_triggered()
{
    QApplication::aboutQt();
}

// Dialog "Über MEGAMover..."
void MainWindow::on_action_ber_triggered()
{
    CAbout *dlg = new CAbout(this);
    dlg->exec();
    delete dlg;
}

// Aufruf Auftragsbearbeitung
void MainWindow::on_actionNeu_Be_arbeiten_triggered()
{    
    openOrder();
}

// Aufruf Mandantenauswahl
void MainWindow::on_action_aus_w_hlen_triggered()
{
    /* Dialog initialisieren */
    CMdtWahl *dlg = new CMdtWahl(this);
    /* Die Daten des aktuellen Mandanten
     * werden im Core hinterlegt. */
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

/* Programmende über Button */
void MainWindow::on_cmdClose_clicked()
{
    this->close();
}

// Wrapper für Aufruf Auftragsbearbeitung
void MainWindow::openOrder()
{
    m_orders = new COrders(this);
    m_orders->setSubWindow(ui->mdiArea->addSubWindow(m_orders));
    m_orders->show();
}

// Wrapper für Aufruf Kundenstamm
void MainWindow::openClients()
{
    m_clients = new CClient(this);
    QMdiSubWindow *wn = ui->mdiArea->addSubWindow(m_clients);
    m_clients->setSubWindow(wn);
    m_clients->show();
}

// Wrapper für Aufruf Adressenverwaltung
void MainWindow::openAdresses()
{    
    m_adresses = new CAdresses(this);
    QMdiSubWindow *wn = ui->mdiArea->addSubWindow(m_adresses);
    m_adresses->setSubWnd(wn);
    m_adresses->show();    
}

// Aufruf Kundenstamm über Menü
void MainWindow::on_action_Kunden_triggered()
{
    openClients();
}

// Aufruf Kundenstamm über Button
void MainWindow::on_cmdClients_clicked()
{
    openClients();
}

// Aufruf Adressenverwaltung über Menü
void MainWindow::on_action_Zentrale_Adressen_Verwaltung_triggered()
{
    openAdresses();
}
