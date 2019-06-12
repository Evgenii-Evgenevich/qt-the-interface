#include "Beam.h"
#include <QLocale>
#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>
#include <QDoubleValidator>
#include <QLabel>

Beam::Beam()
	: Beam(nullptr)
{
}

template<class Widget> Widget* predata(Widget* widget)
{
	widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	return widget;
}

template<> QLabel* predata(QLabel* widget)
{
	//widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	widget->setScaledContents(true);
	return widget;
}

Beam::Beam(QWidget* parent)
	: QWidget(parent)
	, m_energy((new QLineEdit))
	, m_mass((new QLineEdit))
	, m_emit_x((new QLineEdit))
	, m_emit_y((new QLineEdit))
	, m_dp_p((new QLineEdit))
{
	setMinimumSize(300, 300);

	QGridLayout* layout = new QGridLayout(this);
	layout->setSizeConstraint(QLayout::SetMaximumSize);

	QDoubleValidator* validator = new QDoubleValidator(this);
	validator->setNotation(QDoubleValidator::ScientificNotation);
	m_energy->setValidator(validator);
	m_mass->setValidator(validator);
	m_emit_x->setValidator(validator);
	m_emit_y->setValidator(validator);
	m_dp_p->setValidator(validator);

	layout->addWidget(predata(new QLabel("Energy")), 1, 1, 1, 1);
	layout->addWidget(m_energy, 1, 3, 1, 8);

	layout->addWidget(predata(new QLabel("Mass")), 2, 1, 1, 1);
	layout->addWidget(m_mass, 2, 3, 1, 8);

	layout->addWidget(predata(new QLabel("emit x")), 4, 1, 1, 1);
	layout->addWidget(m_emit_x, 4, 3, 1, 4);

	layout->addWidget(predata(new QLabel("emit y")), 4, 8, 1, 1);
	layout->addWidget(m_emit_y, 4, 10, 1, 4);

	layout->addWidget(predata(new QLabel("D*Pover/P")), 5, 1, 1, 1);
	layout->addWidget(m_dp_p, 5, 3, 1, 8);
}

QString Beam::energy() const
{
	return m_energy->text();
}

QString Beam::mass() const
{
	return m_mass->text();
}

QString Beam::emit_x() const
{
	return m_emit_x->text();
}

QString Beam::emit_y() const
{
	return m_emit_y->text();
}

QString Beam::dp_p() const
{
	return m_dp_p->text();
}

double Beam::gamma() const
{
	QLocale locale{};
	return 1. + (locale.toDouble(energy()) / locale.toDouble(mass()));
}

double Beam::beta() const
{
	double const gamma_ = gamma();
	return sqrt((gamma_ * gamma_) - 1.) / gamma_;
}
