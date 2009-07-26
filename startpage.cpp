/*
  Copyright (c) 2009 Riccardo Iaconelli <riccardo@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
*/

#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QValidator>

#include <KUser>
// #include <KLocalizedString>
#include <KDebug>
#include <KLineEdit>
#include <KPushButton>
#include <KSeparator>
#include <KUrlRequester>
#include <KStandardDirs>
#include <QMessageBox>

#include "packagemodel.h"
#include "startpage.h"
#include "mainwindow.h"
#include "ui_startpage.h"

StartPage::StartPage(MainWindow *parent) // TODO set a palette so it will look identical with any color scheme.
	: QWidget(parent),
	m_parent(parent)
{
	setupWidgets();
	refreshRecentProjectsList();
}

StartPage::~StartPage()
{
	delete ui;
}

void StartPage::setupWidgets()
{
	ui = new Ui::StartPage;
	ui->setupUi(this);

	// Enforce the security restriction from package.cpp in the input field
	connect(ui->projectName, SIGNAL(textEdited( const QString& )),
			this, SLOT( processProjectName(const QString& ) ) );

	connect(ui->projectName, SIGNAL(returnPressed()),
			this, SLOT(createNewProject()));
	connect(ui->recentProjects, SIGNAL(clicked(const QModelIndex)),
			this, SLOT(emitProjectSelected(const QModelIndex)));
	connect(ui->contentTypes, SIGNAL(clicked(const QModelIndex)),
			this, SLOT(changeStackedWidgetPage()));
	connect(ui->contentTypes, SIGNAL(clicked(const QModelIndex)),
			ui->projectName, SLOT(setFocus()));
	connect(ui->newProjectButton, SIGNAL(clicked()),
			this, SLOT(createNewProject()));
	connect(ui->cancelNewProjectButton, SIGNAL(clicked()),
			this, SLOT(cancelNewProject()));

	new QListWidgetItem(KIcon("application-x-plasma"), i18n("Plasmoid"), ui->contentTypes);
	new QListWidgetItem(KIcon("kexi"), i18n("Data Engine"), ui->contentTypes);
	QListWidgetItem *runnerItem = new QListWidgetItem(KIcon("system-run"), i18n("Runner"), ui->contentTypes);
	runnerItem->setHidden(true);
	new QListWidgetItem(KIcon("inkscape"), i18n("Theme"), ui->contentTypes);

//     connect(ui->newProjectButton, SIGNAL(clicked()), this, SLOT(launchNewProjectWizard()));
}

void StartPage::processProjectName( const QString& name )
{
	QRegExp validatePluginName("[a-zA-Z0-9_.]*");
	if( !validatePluginName.exactMatch( name ) )
	{
		int pos = 0;
		for( int i = 0; i < name.size(); i++)
		{
			if( validatePluginName.indexIn( name, pos, QRegExp::CaretAtZero ) == -1 )
				break;
			pos += validatePluginName.matchedLength();
		}
		ui->projectName->setText( QString( name ).remove( pos, 1 ) );
	}
}

void StartPage::changeStackedWidgetPage()
{
	ui->layoutHackStackedWidget->setCurrentIndex(1);
	if( ui->contentTypes->currentRow() == 3 )
	{
		ui->frame->setEnabled( false );
		//ui->radioButtonJs->setEnabled( false );
		//ui->radioButtonPy->setEnabled( false );
		//ui->radioButtonRb->setEnabled( false );
	}
}

void StartPage::resetStatus()
{
	kDebug() << "Reset status!";
	ui->layoutHackStackedWidget->setCurrentIndex(0);
	refreshRecentProjectsList();
}

void StartPage::refreshRecentProjectsList()
{
	ui->recentProjects->clear();
	QStringList recentFiles = m_parent->recentProjects();

	for (int i = 0; i < recentFiles.size(); i++) {
		Plasma::PackageMetadata metadata(KStandardDirs::locateLocal("appdata", recentFiles.at(i) + '/'));
		QString projectName = metadata.name();

//         if (projectName.isEmpty()) {
//             continue;
//         }

		kDebug() << "adding" << projectName << "to the list of recent projects...";
		QListWidgetItem *item = new QListWidgetItem(projectName); // TODO make me the user "nice" name
		item->setData(FullPathRole, projectName);

		QString serviceType = metadata.serviceType();

		if ( serviceType == QString("Plasma/Applet") ) {
			item->setIcon(KIcon("application-x-plasma"));
		} else if ( serviceType == QString("Plasma/DataEngine") ) {
			item->setIcon(KIcon("kexi"));
		} else if ( serviceType == QString("Plasma/Theme") ) {
			item->setIcon(KIcon("inkscape"));
		} else if ( serviceType == QString("Plasma/Runner") ) {
			item->setIcon(KIcon("system-run"));
		} else {
			kWarning() << "Unknown service type" << serviceType;
		}

		ui->recentProjects->addItem(item);
	}
}

void StartPage::createNewProject()
{
// TODO
//     metadata->setPluginName( view->pluginname_edit->text() );

	QString type;
	if (ui->contentTypes->currentRow() == 0) {
		type = "Plasma/Applet";
	} else if (ui->contentTypes->currentRow() == 1) {
		type = "Plasma/DataEngine";
	} else if (ui->contentTypes->currentRow() == 2) {
		type = "Plasma/Theme";
	} else if (ui->contentTypes->currentRow() == 3) {
		type = "Plasma/Runner";
	}

	emit projectSelected(ui->projectName->text().toLower(), type);
}

void StartPage::cancelNewProject()
{
	resetStatus();
}

void StartPage::emitProjectSelected(const QModelIndex &index)
{
	QAbstractItemModel *m = ui->recentProjects->model();
	QString url = m->data(index, FullPathRole).value<QString>();
	kDebug() << "Loading project file:" << m->data(index, FullPathRole);
	emit projectSelected(url, QString());
}

