/********************************************************************
*
*   File: cdata.cpp    Class: CData
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2016 Joerg Pauly
*   Created 02.03.2016 by joerg
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
/********************************************************************
 *
 *  CData dient als Basis-Klasse für alle Daten-Klassen
 *
 * *****************************************************************/

#include "cdata.h"

int CData::ID() const
{
    return m_ID;
}

QSqlQuery CData::query() const
{
    return m_query;
}

void CData::setQuery(const QSqlQuery &query)
{
    m_query = query;
}

CData::CData()
{

}

CData::CData(int pID)
{
    m_ID = pID;
}

CData::CData(int pID, QSqlQuery *pQuery)
{
    m_ID = pID;
    m_query = *pQuery;
}

CData::CData(int pID, QString pSql)
{
    m_ID = pID;
}

bool CData::isValid()
{
    return m_query.isValid();
}
