#include "DragWidget.h"
#include "Element.h"
#include "VBoxLayout.h"
#include <QScrollBar>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QMouseEvent>

DragWidget::DragWidget()
	: DragWidget(nullptr)
{
}

DragWidget::DragWidget(QWidget *parent)
	: QScrollArea(parent)
	, m_layout(new VBoxLayout(this))
{
	QPalette palette{};
	palette.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(palette);
	setWindowFlags(Qt::WindowType::Tool | Qt::WindowType::CustomizeWindowHint | Qt::WindowType::WindowTitleHint);
	setAcceptDrops(true);
	setMinimumSize(30, 300);
	setMaximumWidth(300);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	verticalScrollBar()->resize(0, 0);
	setWidgetResizable(true);
	setWidget(m_layout);
	for (int i = 0; i < Elements::type_count; ++i)
	{
		m_layout->add(new Element(Elements::Type(i)));
	}
	setWindowTitle("Elements");
	resize(55, 480);
}

void DragWidget::dragEnterEvent(QDragEnterEvent* event)
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

void DragWidget::dragMoveEvent(QDragMoveEvent* event)
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

void DragWidget::dropEvent(QDropEvent* event)
{
	if (event->source() != this && event->mimeData()->hasFormat("application/x-pole"))
	{
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else 
	{
		event->ignore();
	}
}

void DragWidget::mousePressEvent(QMouseEvent* event)
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

		drag->exec();
		child->show();
	}
	else
	{
		child->dialog();
	}
}

void DragWidget::enterEvent(QEvent* event)
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

void DragWidget::leaveEvent(QEvent* event)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}

void DragWidget::focusInEvent(QFocusEvent* event)
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

void DragWidget::focusOutEvent(QFocusEvent* event)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}

void DragWidget::resizeEvent(QResizeEvent* event)
{
	int const width = event->size().width();
	int height = 0;
	for (QObject* child : m_layout->children())
	{
		if (Element* element = dynamic_cast<Element*>(child))
		{
			element->setWidth(width);
			height += element->height();
		}
	}
}
