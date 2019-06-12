#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	MainWindow();


protected:
	void showEvent(QShowEvent* event) override;

private:
	class QTabWidget* m_tabWidget;
	class Beam* m_beam;
};
