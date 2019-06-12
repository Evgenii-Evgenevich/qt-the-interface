#pragma once

#include <QWidget>

class Twiss : public QWidget
{
Q_OBJECT
public:
	Twiss();

	explicit Twiss(QWidget* parent);

	QString beta_x() const;
	QString beta_y() const;
	QString alpha_x() const;
	QString alpha_y() const;
	QString disp_x() const;
	QString disp_y() const;
	QString disp_dx() const;
	QString disp_dy() const;

private:
	class QLineEdit* m_beta_x;
	class QLineEdit* m_beta_y;
	class QLineEdit* m_alpha_x;
	class QLineEdit* m_alpha_y;
	class QLineEdit* m_disp_x;
	class QLineEdit* m_disp_y;
	class QLineEdit* m_disp_dx;
	class QLineEdit* m_disp_dy;
};

