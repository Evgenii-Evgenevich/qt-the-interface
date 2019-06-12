#include <QApplication>
#include <QMainWindow>
#include "DragWidget.h"
#include "DropWidget.h"
#include "GraphicsWidget.h"
#include "TabWidget.h"
#include <QPushButton>
#include <QStatusBar>
#include <QMenuBar>


QWidget* g_mainWindow = nullptr;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TabWidget* mainWidget = new TabWidget;
	QPushButton* button = new QPushButton("Start Simulation");

	QMainWindow mainWindow;
	mainWindow.setCentralWidget(mainWidget);
	mainWindow.setWindowTitle("The Interface");
	g_mainWindow = &mainWindow;

	DragWidget dragWidget;// { g_mainWindow };

	DropWidget dropWidget;// { g_mainWindow };

	GraphicsWidget graphicsWidget;// { g_mainWindow };

	{
		QMenu* fileMenu = mainWindow.menuBar()->addMenu("&File");

		mainWindow.statusBar()->addWidget(button);

		QAction* exitAct = fileMenu->addAction(QIcon::fromTheme("application-exit"), "E&xit", g_mainWindow, &QWidget::close);
		exitAct->setShortcuts(QKeySequence::Quit);
		exitAct->setStatusTip("Exit the Application");

		QMenu* windowMenu = mainWindow.menuBar()->addMenu("&Window");
		windowMenu->addAction("&Elements", &dragWidget, &QWidget::raise)->setStatusTip("Raise the Elements");
		windowMenu->addAction("&Model", &dropWidget, &QWidget::raise)->setStatusTip("Raise the Model");
		windowMenu->addAction("&Graphics", &graphicsWidget, &QWidget::raise)->setStatusTip("Raise the Graphics");
	}

	mainWindow.show();
	dragWidget.show();
	dropWidget.show();
	graphicsWidget.show();

	return a.exec();
}
