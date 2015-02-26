/*
 *   Copyright 2015 Marco Martin <mart@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
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

#include "thememodel.h"

#include <QDebug>
#include <QByteArray>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QIcon>
#include <QStandardPaths>
#include <QJsonDocument>

#include <Plasma/Theme>


ThemeModel::ThemeModel(QObject *parent)
    : QAbstractListModel(parent),
      m_theme(QStringLiteral("default"))
{
    m_roleNames.insert(ImagePath, "imagePath");

    

    load();
}

ThemeModel::~ThemeModel()
{
}

QHash<int, QByteArray> ThemeModel::roleNames() const
{
    return m_roleNames;
}

int ThemeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 0;//m_data.size();
}

QVariant ThemeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case ImagePath:
        return QVariant();
    }

    return QVariant();
}




void ThemeModel::load()
{
    qDebug() << "Loading theme description file";

    //QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonFile.readAll(), &e);
}

QString ThemeModel::theme() const
{
    return m_theme;
}

void ThemeModel::setTheme(const QString& theme)
{
    if (theme == m_theme) {
        return;
    }

    m_theme = theme;
    load();
    emit themeChanged();
}

#include "moc_thememodel.cpp"
