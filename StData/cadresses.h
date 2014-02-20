/****************************************************************************************
*
*   This file is part of the ChartButler Project.
*   Copyright (C) 2014 Joerg Pauly
*   Created 20.02.2014 by joerg
*   All Rights reserved
*
*   ChartButler ist Freie Software: Sie können es unter den Bedingungen
*   der GNU Lesser General Public License, wie von der Free Software Foundation,
*   Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren
*   veröffentlichten Version, weiterverbreiten und/oder modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*****************************************************************************************/

#ifndef CADRESSES_H
#define CADRESSES_H

#include <QWidget>

namespace Ui {
class CAdresses;
}

class CAdresses : public QWidget
{
    Q_OBJECT

public:
    explicit CAdresses(QWidget *parent = 0);
    ~CAdresses();

private:
    Ui::CAdresses *ui;
};

#endif // CADRESSES_H
