/**************************************************************************
** This file is part of the MEGAMover-Project
** (C) 2013 Joerg Pauly
** Author:    joerg
** Created:   11.05.2013
**
** This program is provided under the terms of GNU LGPL.
**
** It is provided in the hope that it will be usefull, but with absolutely
** NO WARRATY.
**************************************************************************/

#ifndef DATAPADS_GLOBAL_H
#define DATAPADS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATAPADS_LIBRARY)
#  define DATAPADSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DATAPADSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DATAPADS_GLOBAL_H
