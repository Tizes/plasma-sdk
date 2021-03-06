/*
 *   Copyright 2016 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import org.kde.kirigami 2.0 as Kirigami

TextField {
    id: field
    property string key
    text: lnfLogic[key]
    Layout.minimumWidth: Kirigami.Units.gridUnit * 15
    onAccepted: {
        lnfLogic.name = text;
        timer.running = false;
    }
    onTextChanged: timer.restart()
    Timer {
        id: timer
        interval: 1000
        onTriggered: lnfLogic[key] = field.text
    }
}
