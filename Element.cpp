#include "Element.h"
#include <QResizeEvent>
#include <QGraphicsWidget>
#include <QToolTip>
#include <QLocale>
#include "ElementDialog.h"

Element::Element(QPixmap const& pixmap, int type, double length, double b, double g, double tilt)
	: QLabel(nullptr)
	, m_pixmap(pixmap)
	, m_dialog(false)
	, m_type(type)
	, m_length(length)
	, m_b(b)
	, m_gradient(g)
	, m_tilt(tilt)
{
	setMinimumSize(30, 30);
	setAttribute(Qt::WA_DeleteOnClose);
	setMaximumSize(pixmap.size());
	QLabel::setPixmap(pixmap);
	setText(Elements::instance().string[type]);
	show();
}

Element::Element(Elements::Type type)
	: Element(Elements::instance().pixmap[type], type)
{
}

Element::Element(Element const& o)
	: Element(o.m_pixmap, o.m_type, o.m_length, o.m_b, o.m_gradient, o.m_tilt)
{
}

void Element::setPixmap(QPixmap const& pixmap)
{
	m_pixmap = pixmap;
	setMaximumSize(pixmap.size());
	QLabel::setPixmap(pixmap);
	show();
}

QString Element::length() const
{
	return QLocale().toString(m_length);
}

QString Element::tilt() const
{
	return QLocale().toString(m_tilt);
}

QString Element::b() const
{
	return QLocale().toString(m_b);
}

QString Element::gradient() const
{
	return QLocale().toString(m_gradient);
}

QString Element::m() const
{
	return QLocale().toString(m_m);
}

void Element::setText(QString const& name)
{
	m_name = name;
	if (m_pixmap.isNull()) QLabel::setText(name);
}

void Element::setWidth(int w)
{
	setMinimumWidth(w);
	if (m_pixmap.isNull()) return;
	//setMinimumHeight((m_pixmap.height() * w) / m_pixmap.width());
	setMinimumHeight(w);
}

void Element::setHeight(int h)
{
	setMinimumHeight(h);
	if (m_pixmap.isNull()) return;
	//setMinimumWidth((m_pixmap.width() * h) / m_pixmap.height());
	setMinimumWidth(h);
}

void Element::dialog()
{
	if (m_dialog) return;
	(new ElementDialog(*this))->show();
	m_dialog = true;
}

QString Element::tooltip() const noexcept
{
	switch (m_type)
	{
	case Elements::drift:
	case Elements::lens:
		return m_name + "\nLength: " + length();
	case Elements::dipole:
		return m_name + "\nLength: " + length() + "\nB(magnetic field): " + b() + "\nGradient: " + gradient() + "\nTilt[deg]: " + tilt();
	case Elements::quadrupole:
	case Elements::sextipole:
	case Elements::octupole:
		return m_name + "\nLength: " + length() + "\nGradient: " + gradient() + "\nTilt[deg]: " + tilt();
	case Elements::solenoid:
		return m_name + "\nLength: " + length() + "\nB(magnetic field): " + b();
	}
	return {};
}

bool Element::event(QEvent* e)
{
	if (e->type() == QEvent::ToolTip)
	{
		QHelpEvent* event = static_cast<QHelpEvent*>(e);
		QToolTip::showText(event->globalPos(), tooltip());
		return true;
	}
	return QLabel::event(e);
}

void Element::resizeEvent(QResizeEvent* event)
{
	if (m_pixmap.isNull()) 
	{
		QLabel::resizeEvent(event);
	}
	else
	{
		QLabel::setPixmap(m_pixmap.scaled(event->size(), Qt::KeepAspectRatio));
	}
}

Elements& Elements::instance()
{
	static Elements instance;
	return instance;
}
