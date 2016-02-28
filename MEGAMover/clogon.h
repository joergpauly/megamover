/********************************************************************
*
*   File: clogon.h    Class: CLogon
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 28.02.2016 by joerg on PSYS20.PSYS
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software:
*   Sie können sie unter den Bedingungen
*   der GNU Lesser General Public License, wie von der
*   Free Software Foundation, Version 3 der Lizenz oder
*   (nach Ihrer Option) jeder späteren veröffentlichten
*   Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich
*   sein wird, aber OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt;
*   sogar ohne die implizite Gewährleistung der MARKTFÄHIGKEIT
*   oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License
*   zusammen mit diesem Programm erhalten haben.
*   Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
********************************************************************/
#ifndef CLOGON_H
#define CLOGON_H

// System-Header
#include <QApplication>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtNetwork/QHostInfo>

// Project-Header
#include "ccore.h"

class CLogon
{
public:
    CLogon();

    int UserID() const;

private:
    QString     m_Client;
    QString     m_User;
    int         m_UserID;
};

#endif // CLOGON_H
