/********************************************************************
*
*   File: ccoworker.h    Class: CCoworker
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
#ifndef CCOWORKER_H
#define CCOWORKER_H

// Projekt-Header
#include "dataclasses_global.h"
#include "cdata.h"
#include "cadress.h"

class DATACLASSESSHARED_EXPORT CCoworker : public CData
{

private:
    CAdress*    m_Adress;



public:
    // De- und Konstruktoren
    CCoworker();
    CCoworker(int pID);
    ~CCoworker();

    // Public Member


};

#endif // CCOWORKER_H
