/********************************************************************
*
*   File: clogon.cpp    Class: CLogon
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
#include "clogon.h"

CLogon::CLogon()
{
    m_User = qgetenv("USER");
    if(m_User.isEmpty())
    {
        m_User = qgetenv("USERNAME");
    }
    m_Client = QHostInfo::localHostName();
    //TODO: Anwender aus tblLogon und tblCoworkers holen
    QSqlQuery lqry;
    lqry.prepare("SELECT * from tblLogon WHERE client = :CLIENT AND user = :USER;");
    lqry.bindValue(":CLIENT", m_Client);
    lqry.bindValue(":USER", m_User);
    lqry.exec();
    lqry.first();
    if(lqry.isValid())
    {
        m_UserID = lqry.value(lqry.record().indexOf("cwID")).toInt();
    }
}

int CLogon::UserID() const
{
    return m_UserID;
}
