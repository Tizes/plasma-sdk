/********************************************************************
Copyright (C) 2012 Martin Gräßlin <mgraesslin@kde.org>
Copyright (C) 2012 Nuno Pinheiro <nuno@oxygen-icons.org>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
import QtQuick 1.1
import org.kde.qtextracomponents 0.1 as QtExtra
import org.kde.plasma.components 0.1 as PlasmaComponents

ListView {
    id: listView
    x: 0
    y: 0
    signal clicked;
    model: decorationModel
    highlight: Rectangle {
        width: listView.width
        height: 150
        color: highlightColor
        opacity: 0.5
    }
    highlightMoveDuration: 250
    boundsBehavior: Flickable.StopAtBounds
    delegate: Column {
        spacing: -10
        PlasmaComponents.ToolButton  {
            id: image
            iconSource: "view-refresh"
            smooth: true
            flat: true
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                listView.clicked();
            }
        }
        Item {
            objectName: "decorationItem"
            width: listView.width
            height: 150
            QtExtra.QPixmapItem {
                pixmap: preview
                anchors.fill: parent
                visible: type == 0
            }
            Loader {
                source: type == 1 ? "AuroraePreview.qml" : ""
                anchors.fill: parent
            }
            Loader {
                source: type == 2 ? "DecorationPreview.qml" : ""
                anchors.fill: parent
            }
            MouseArea {
                hoverEnabled: false
                anchors.fill: parent
                    onClicked: {
                    console.log("asdsdasdsdaadsdsa")
                    listView.currentIndex = index;
                }
            }
        }
    }
}
