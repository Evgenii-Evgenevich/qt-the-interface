#include "DropWidget.h"
#include "Element.h"
#include "HBoxLayout.h"
#include <QScrollBar>
#include <QDropEvent>
#include <QMimeData>
#include <QScrollArea>
#include <QDrag>
#include <QPainter>


DropWidget::DropWidget()
	: DropWidget(nullptr)
{
}

DropWidget::DropWidget(QWidget* parent)
	: QScrollArea(parent)
	, m_layout(new HBoxLayout(this))
{
	QPalette palette{};
	palette.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(palette);
	setWindowFlags(Qt::WindowType::Tool | Qt::WindowType::CustomizeWindowHint | Qt::WindowType::WindowTitleHint);
	setAcceptDrops(true);
	setMaximumHeight(300);
	setMinimumSize(300, 30);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setWidgetResizable(true);
	setWidget(m_layout);
	resize(640, 55);
	setWindowTitle("Model");
}

void DropWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-pole"))
	{
		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else 
		{
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}

void DropWidget::dragMoveEvent(QDragMoveEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-pole"))
	{
		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		}
		else 
		{
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}

void DropWidget::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasFormat("application/x-pole")) 
	{
		QByteArray itemData = event->mimeData()->data("application/x-pole");
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		size_t map;
		dataStream >> map;

		Element* label = reinterpret_cast<Element*>(map);

		if (event->source() == this)
		{
			m_layout->drop(label, event->pos());
			event->setDropAction(Qt::TargetMoveAction);
			event->accept();
		}
		else
		{
			m_layout->drop(new Element(*label), event->pos());
			updateGeometry();
			event->acceptProposedAction();
		}
	}
	else
	{
		event->ignore();
	}
}

void DropWidget::mousePressEvent(QMouseEvent* event)
{
	Element* child = nullptr;

	for (QObject* object : m_layout->children())
	{
		if (Element* element = dynamic_cast<Element*>(object))
		{
			if (element->underMouse())
			{
				child = element;
				break;
			}
		}
	}

	if (!child) return;

	if (event->button() == Qt::MouseButton::LeftButton)
	{
		QByteArray itemData;
		QDataStream dataStream(&itemData, QIODevice::WriteOnly);
		dataStream << reinterpret_cast<size_t>(child);

		QMimeData* mimeData = new QMimeData;
		mimeData->setData("application/x-pole", itemData);

		QDrag* drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(child->pixmap());
		drag->setHotSpot(event->pos());

		if (drag->exec(Qt::TargetMoveAction) == Qt::MoveAction)
		{
			child->close();
		}
	}
	else
	{
		child->dialog();
	}
}

void DropWidget::enterEvent(QEvent* event)
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

void DropWidget::leaveEvent(QEvent* event)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}

void DropWidget::focusInEvent(QFocusEvent* event)
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

void DropWidget::focusOutEvent(QFocusEvent* event)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}

void DropWidget::resizeEvent(QResizeEvent* event)
{
	int const height = event->size().height();
	int width = 0;
	for (QObject* child : m_layout->children())
	{
		if (Element* element = dynamic_cast<Element*>(child))
		{
			element->setHeight(height);
			width += element->width();
		}
	}
}
