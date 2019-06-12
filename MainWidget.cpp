#include "TabWidget.h"
#include "Beam.h"
#include "Twiss.h"
#include <QTabWidget>

MainWidget::MainWidget()
	: QScrollArea()
	, m_widget(new QTabWidget(this))
	, m_beam(new Beam(this))
	, m_twiss(new Twiss(this))
	
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setWidgetResizable(true);
	setWidget(m_widget);

	m_widget->addTab(m_beam, "Beam");
	m_widget->addTab(m_twiss, "Twiss");
}
