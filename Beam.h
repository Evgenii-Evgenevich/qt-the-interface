#pragma once

#include <QWidget>

class Beam : public QWidget
{
Q_OBJECT

public:
	Beam();

	explicit Beam(QWidget* parent);

	QString energy() const;

	QString mass() const;

	QString emit_x() const;

	QString emit_y() const;

	QString dp_p() const;

	double gamma() const;

	double beta() const;

private:
	class QLineEdit* m_energy;
	class QLineEdit* m_mass;
	class QLineEdit* m_emit_x;
	class QLineEdit* m_emit_y;
	class QLineEdit* m_dp_p;

};

