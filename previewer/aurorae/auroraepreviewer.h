/********************************************************************
 * This file is part of the KDE project.
 *
 * Copyright (C) 2012 Antonis Tsiapaliokas <kok3rs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *********************************************************************/

#ifndef AURORAEPREVIEWER_H
#define AURORAEPREVIEWER_H

#include "../previewer.h"
#include "kwindecoration.h"

class AuroraePreviewer : public Previewer {

    Q_OBJECT

public:
    AuroraePreviewer(const QString & title, QWidget * parent = 0, Qt::WindowFlags flags = 0);
    void showPreview(const QString &packagePath);

    /**
     * Here we are initializing our object
     */
    void init();

public Q_SLOTS:
    void refreshPreview();

private:
    KWin::KWinDecorationModule *m_view;
    QString m_packagePath;

};

#endif // AURORAEPREVIEWER_H