/********************************************************************
*
*   File: cadress.cpp    Class: CAdress
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
#include "cadress.h"

// De- und Konstruktoren
CAdress::CAdress()
{

}

CAdress::CAdress(int pID)
{

}

CAdress::~CAdress()
{

}

// Get- / Set-Member

QString CAdress::Anrede() const
{
    return m_Anrede;
}

void CAdress::setAnrede(const QString &Anrede)
{
    m_Anrede = Anrede;
}

QString CAdress::Titel() const
{
    return m_Titel;
}

void CAdress::setTitel(const QString &Titel)
{
    m_Titel = Titel;
}

QString CAdress::VName() const
{
    return m_VName;
}

void CAdress::setVName(const QString &VName)
{
    m_VName = VName;
}

QString CAdress::Name1() const
{
    return m_Name1;
}

void CAdress::setName1(const QString &Name1)
{
    m_Name1 = Name1;
}

QString CAdress::Strasse() const
{
    return m_Strasse;
}

void CAdress::setStrasse(const QString &Strasse)
{
    m_Strasse = Strasse;
}

QString CAdress::StrNummer() const
{
    return m_StrNummer;
}

void CAdress::setStrNummer(const QString &StrNummer)
{
    m_StrNummer = StrNummer;
}

QString CAdress::Ldkz() const
{
    return m_Ldkz;
}

void CAdress::setLdkz(const QString &Ldkz)
{
    m_Ldkz = Ldkz;
}

QString CAdress::PLZ() const
{
    return m_PLZ;
}

void CAdress::setPLZ(const QString &PLZ)
{
    m_PLZ = PLZ;
}

QString CAdress::Ort() const
{
    return m_Ort;
}

void CAdress::setOrt(const QString &Ort)
{
    m_Ort = Ort;
}

QString CAdress::Tel() const
{
    return m_Tel;
}

void CAdress::setTel(const QString &Tel)
{
    m_Tel = Tel;
}

QString CAdress::MobTel() const
{
    return m_MobTel;
}

void CAdress::setMobTel(const QString &MobTel)
{
    m_MobTel = MobTel;
}

QString CAdress::Fax() const
{
    return m_Fax;
}

void CAdress::setFax(const QString &Fax)
{
    m_Fax = Fax;
}

QString CAdress::Email() const
{
    return m_Email;
}

void CAdress::setEmail(const QString &Email)
{
    m_Email = Email;
}

