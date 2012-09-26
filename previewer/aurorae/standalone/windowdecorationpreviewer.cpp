/*
Copyright 2012 Antonis Tsiapaliokas <kok3rs@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "windowdecorationpreviewer.h"
#include <QLabel>
#include <KLocale>
#include <KDesktopFile>
#include <KDebug>

WindowDecorationPreviewer::WindowDecorationPreviewer(QWidget* parent)
        : KDialog(parent)
{
    setMinimumSize(400,370);
    tmpWidget = new QWidget();
    tmpLayout = new QVBoxLayout();
    m_previewer = new AuroraePreviewer(i18nc("Window Title", "Window Decoration Previewer"));
    m_filePath = new KUrlRequester(tmpWidget);
    QLabel *welcome = new QLabel(tmpWidget);
    QLabel *correctFile = new QLabel(tmpWidget);

    m_filePath->setFilter("*.desktop");
    welcome->setText(i18n("Welcome to the Window Decoration Previewer"));
    correctFile->setText(i18n("Please choose the metadata.desktop file which is inside your package"));
    m_previewer->hide();

    tmpLayout->addWidget(welcome);
    tmpLayout->addWidget(m_previewer);
    tmpLayout->addWidget(correctFile);
    tmpLayout->addWidget(m_filePath);

    connect(m_filePath, SIGNAL(textChanged(const QString&)), this, SLOT(loadPreviewer(const QString&)));

    tmpWidget->setLayout(tmpLayout);
    setMainWidget(tmpWidget);
}

void WindowDecorationPreviewer::loadPreviewer(const QString& filePath)
{
    m_previewer->showPreview(m_filePath->text());
    m_previewer->show();
}

#include "moc_windowdecorationpreviewer.cpp"