#include "VBoxLayout.h"
#include <QVBoxLayout>
#include <QPoint>

VBoxLayout::VBoxLayout()
	: VBoxLayout(nullptr)
{
}

VBoxLayout::VBoxLayout(QWidget* parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setAlignment(Qt::AlignTop);
	layout->setSpacing(0);
}

void VBoxLayout::add(QWidget* widget)
{
	widget->setParent(this);
	layout()->addWidget(widget);
}

void VBoxLayout::drop(QWidget* widget, QPoint pos)
{
	QVBoxLayout* m_layout = static_cast<QVBoxLayout*>(layout());
	pos.setX(width() / 2);
	if (QWidget* child = childAt(pos))
	{
		if (child == widget) return;
		int idx = m_layout->indexOf(child);
		int const x = pos.x() - child->pos().x();
		int const h = child->height() / 2;
		if (x > h) ++idx;
		m_layout->insertWidget(idx, widget);
	}
	else
	{
		m_layout->addWidget(widget);
	}
	widget->setParent(this);
}

void VBoxLayout::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}
