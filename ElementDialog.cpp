#include "ElementDialog.h"
#include "Element.h"
#include <QEvent>
#include <QMessageBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QValidator>

extern QWidget* g_mainWindow;

ElementDialog::ElementDialog(Element& element)
	: QDialog(g_mainWindow)
	, m_element(element)
	, m_name(new QLineEdit(element.text(), this))
	, m_length(new QLineEdit(element.length(), this))
	, m_m(element.type() == Elements::multipole ? new QLineEdit(element.m(), this) : nullptr)
	, m_b(element.type() == Elements::dipole || element.type() == Elements::solenoid ? new QLineEdit(element.b(), this) : nullptr)
	, m_gradient(element.type() != Elements::drift && element.type() != Elements::solenoid && element.type() != Elements::lens ? new QLineEdit(element.gradient(), this) : nullptr)
	, m_tilt(element.type() != Elements::drift && element.type() != Elements::solenoid && element.type() != Elements::lens ? new QLineEdit(element.tilt(), this) : nullptr)
{
	QPalette palette{};
	palette.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(palette);
	setWindowTitle(element.text());
	setWhatsThis(Elements::instance().string[element.type()]);
	setAttribute(Qt::WA_DeleteOnClose);
	QFormLayout* layout = new QFormLayout(this);
	QLabel* label = new QLabel(this);
	label->setPixmap(element.pixmap());
	label->show();
	label->setAttribute(Qt::WA_DeleteOnClose);
	layout->addWidget(label);
	layout->addRow(new QLabel("name"), m_name);
	QDoubleValidator* validator = new QDoubleValidator(this);
	validator->setNotation(QDoubleValidator::ScientificNotation);
	m_length->setValidator(validator);
	layout->addRow(new QLabel("Length"), m_length);
	if (m_m)
	{
		m_m->setValidator(new QIntValidator);
		layout->addRow(new QLabel("Order"), m_m);
	}
	if (m_b)
	{
		m_b->setValidator(validator);
		layout->addRow(new QLabel("B(magnetic field)"), m_b);
	}
	if (m_gradient)
	{
		m_gradient->setValidator(validator);
		layout->addRow(new QLabel("Gradient"), m_gradient);
	}
	if (m_tilt)
	{
		m_tilt->setValidator(validator);
		layout->addRow(new QLabel("Tilt[deg]"), m_tilt);
	}
	QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
	layout->addWidget(buttonBox);
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

ElementDialog::~ElementDialog()
{
	m_element.m_dialog = false;
}

void ElementDialog::accept()
{
	double value = 0;

	value = QLocale().toDouble(m_length->text());
	m_element.rlength() = value;

	if (m_m)
	{
		int const m_order = m_m->text().toInt();
		m_element.rm() = m_order;
	}
	if (m_b)
	{
		double const magnetic_field = QLocale().toDouble(m_b->text());
		m_element.rb() = magnetic_field;
	}
	if (m_gradient)
	{
		value = QLocale().toDouble(m_gradient->text());
		m_element.rgradient() = value;
	}
	if (m_tilt)
	{
		value = QLocale().toDouble(m_tilt->text());
		m_element.rtilt() = value;
	}
	m_element.setText(m_name->text());
	QDialog::accept();
}

bool ElementDialog::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::Destroy:
		m_element.m_dialog = false;
		return true;

	case QEvent::QueryWhatsThis:
		//QMessageBox::about(nullptr, "", whatsThis());
		return true;

	default:
		return QDialog::event(event);
	}
}

void ElementDialog::enterEvent(QEvent* event)
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

void ElementDialog::leaveEvent(QEvent*)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}

void ElementDialog::focusInEvent(QFocusEvent* event)
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

void ElementDialog::focusOutEvent(QFocusEvent*)
{
	qreal opacity = windowOpacity();
	setWindowOpacity(opacity - 0.2);
}
