#include "MainWindow.h"
#include <QLocale>
#include <QScrollArea>
#include <QTabWidget>
#include <QPushButton>
#include <QStatusBar>
#include <QMenuBar>
#include <QShowEvent>
#include "Beam.h"

MainWindow::MainWindow()
	: QMainWindow()
{
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setWidgetResizable(true);

	m_beam = new Beam(this);
	setWindowTitle("Beam");

	setCentralWidget(scrollArea);
	scrollArea->setWidget(m_beam);

	QMenu* fileMenu = menuBar()->addMenu("&File");

	statusBar()->addWidget(new QPushButton("Start Simulation"));

	const QIcon exitIcon = QIcon::fromTheme("application-exit");
	QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
}

void MainWindow::showEvent(QShowEvent* event)
{
	QMainWindow::showEvent(event);
}
