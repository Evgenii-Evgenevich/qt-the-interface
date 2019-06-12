#include "Twiss.h"
#include <QLineEdit>
#include <QValidator>
#include <QGridLayout>
#include <QLabel>

QLabel* predata(QLabel* widget)
{
	//widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	widget->setScaledContents(true);
	return widget;
}

Twiss::Twiss()
	: Twiss(nullptr)
{
}

Twiss::Twiss(QWidget* parent)
	: QWidget(parent)
	, m_beta_x((new QLineEdit))
	, m_beta_y((new QLineEdit))
	, m_alpha_x((new QLineEdit))
	, m_alpha_y((new QLineEdit))
	, m_disp_x((new QLineEdit))
	, m_disp_y((new QLineEdit))
	, m_disp_dx((new QLineEdit))
	, m_disp_dy((new QLineEdit))
{
	setMinimumSize(300, 300);

	QGridLayout* layout = new QGridLayout(this);
	layout->setSizeConstraint(QLayout::SetMaximumSize);

	QDoubleValidator* validator = new QDoubleValidator(this);
	validator->setNotation(QDoubleValidator::ScientificNotation);
	m_beta_x->setValidator(validator);
	m_beta_y->setValidator(validator);
	m_alpha_x->setValidator(validator);
	m_alpha_y->setValidator(validator);
	m_disp_x->setValidator(validator);
	m_disp_y->setValidator(validator);
	m_disp_dx->setValidator(validator);
	m_disp_dy->setValidator(validator);

	layout->addWidget(predata(new QLabel("Beta X")), 1, 1, 1, 1);
	layout->addWidget(m_beta_x, 1, 3, 1, 4);
	layout->addWidget(predata(new QLabel("Beta Y")), 1, 8, 1, 1);
	layout->addWidget(m_beta_y, 1, 10, 1, 4);

	layout->addWidget(predata(new QLabel("Alpha X")), 2, 1, 1, 1);
	layout->addWidget(m_alpha_x, 2, 3, 1, 4);
	layout->addWidget(predata(new QLabel("Alpha Y")), 2, 8, 1, 1);
	layout->addWidget(m_alpha_y, 2, 10, 1, 4);

	layout->addWidget(predata(new QLabel("Disp X")), 3, 1, 1, 1);
	layout->addWidget(m_disp_x, 3, 3, 1, 4);
	layout->addWidget(predata(new QLabel("Disp Y")), 3, 8, 1, 1);
	layout->addWidget(m_disp_y, 3, 10, 1, 4);

	layout->addWidget(predata(new QLabel("Disp dX")), 4, 1, 1, 1);
	layout->addWidget(m_disp_dx, 4, 3, 1, 4);
	layout->addWidget(predata(new QLabel("Disp dY")), 4, 8, 1, 1);
	layout->addWidget(m_disp_dy, 4, 10, 1, 4);
}

QString Twiss::beta_x() const
{
	return m_beta_x->text();
}

QString Twiss::beta_y() const
{
	return m_beta_y->text();
}

QString Twiss::alpha_x() const
{
	return m_alpha_x->text();
}

QString Twiss::alpha_y() const
{
	return m_alpha_y->text();
}

QString Twiss::disp_x() const
{
	return m_disp_x->text();
}

QString Twiss::disp_y() const
{
	return m_disp_y->text();
}

QString Twiss::disp_dx() const
{
	return m_disp_dx->text();
}

QString Twiss::disp_dy() const
{
	return m_disp_dy->text();
}
