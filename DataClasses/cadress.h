/********************************************************************
*
*   File: cadress.h    Class: CAdress
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
#ifndef CADRESS_H
#define CADRESS_H

// Projekt-Header
#include "dataclasses_global.h"
#include "cdata.h"

class DATACLASSESSHARED_EXPORT CAdress : public CData
{
private:
    QString         m_Anrede;
    QString         m_Titel;
    QString         m_VName;
    QString         m_Name1;
    QString         m_Strasse;
    QString         m_StrNummer;
    QString         m_Ldkz;
    QString         m_PLZ;
    QString         m_Ort;
    QString         m_Tel;
    QString         m_MobTel;
    QString         m_Fax;
    QString         m_Email;

public:
    // De- und Konstruktoren
    CAdress();
    CAdress(int pID);
    ~CAdress();

    // Get-/Set-Member
    QString Anrede() const;
    void setAnrede(const QString &Anrede);
    QString Titel() const;
    void setTitel(const QString &Titel);
    QString VName() const;
    void setVName(const QString &VName);
    QString Name1() const;
    void setName1(const QString &Name1);
    QString Strasse() const;
    void setStrasse(const QString &Strasse);
    QString StrNummer() const;
    void setStrNummer(const QString &StrNummer);
    QString Ldkz() const;
    void setLdkz(const QString &Ldkz);
    QString PLZ() const;
    void setPLZ(const QString &PLZ);
    QString Ort() const;
    void setOrt(const QString &Ort);
    QString Tel() const;
    void setTel(const QString &Tel);
    QString MobTel() const;
    void setMobTel(const QString &MobTel);
    QString Fax() const;
    void setFax(const QString &Fax);
    QString Email() const;
    void setEmail(const QString &Email);

    // Public Member

};

#endif // CADRESS_H
