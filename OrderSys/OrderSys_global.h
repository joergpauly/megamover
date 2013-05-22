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

#ifndef ORDERSYS_GLOBAL_H
#define ORDERSYS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ORDERSYS_LIBRARY)
#  define ORDERSYSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ORDERSYSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ORDERSYS_GLOBAL_H
