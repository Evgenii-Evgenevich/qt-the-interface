#include "HBoxLayout.h"
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QPoint>
#include "Element.h"

HBoxLayout::HBoxLayout()
	: HBoxLayout(nullptr)
{
}

HBoxLayout::HBoxLayout(QWidget* parent)
	: QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setAlignment(Qt::AlignLeft);
	layout->setSpacing(0);
}

void HBoxLayout::drop(QWidget* widget, QPoint pos)
{
	QHBoxLayout* m_layout = static_cast<QHBoxLayout*>(layout());
	pos.setY(height() / 2);
	resize(size() + widget->size());
	if (QWidget* child = childAt(pos))
	{
		if (child == widget) return;
		int idx = m_layout->indexOf(child);
		int const x = pos.x() - child->pos().x();
		int const w = child->width() / 2;
		if (x > w) ++idx;
		m_layout->insertWidget(idx, widget);
	}
	else
	{
		m_layout->addWidget(widget);
	}
	widget->setParent(this);
}

void HBoxLayout::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
}
