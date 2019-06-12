#include "GraphicsWidget.h"
#include "GraphicsView.h"
#include "VBoxLayout.h"

GraphicsWidget::GraphicsWidget()
	: GraphicsWidget(nullptr)
{
}

GraphicsWidget::GraphicsWidget(QWidget* parent)
	: QScrollArea(parent)
	, m_layout(new VBoxLayout(this))
	, m_view(new GraphicsView)
{
	QPalette palette{};
	palette.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(palette);
	setWindowFlags(Qt::WindowType::Tool | Qt::WindowType::CustomizeWindowHint | Qt::WindowType::WindowTitleHint);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setWidgetResizable(true);
	setWidget(m_layout);
	m_layout->add(m_view);
	setWindowTitle("Graphics");
}

void GraphicsWidget::enterEvent(QEvent* event)
{
	if (isActiveWindow())
	{
		setWindowOpacity(1);
	}
	else
	{
		qreal opacity = windowOpacity();
		setWindowOpacity(opacity + 0.2);
	}
}

void GraphicsWidget::leaveEvent(QEvent* event)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}

void GraphicsWidget::focusInEvent(QFocusEvent* event)
{
	if (isActiveWindow())
	{
		setWindowOpacity(1);
	}
	else
	{
		qreal opacity = windowOpacity();
		setWindowOpacity(opacity + 0.2);
	}
}

void GraphicsWidget::focusOutEvent(QFocusEvent* event)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}
