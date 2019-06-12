#pragma once

#include <QDialog>

class ElementDialog :
	public QDialog
{
Q_OBJECT

public:
	explicit ElementDialog(class Element&);

	~ElementDialog();

public Q_SLOTS:
	void accept() override;

protected:
	bool event(QEvent*) override;

	void enterEvent(QEvent*) override;
	void leaveEvent(QEvent*) override;
	void focusInEvent(QFocusEvent*) override;
	void focusOutEvent(QFocusEvent*) override;

private:
	class Element& m_element;
	class QLineEdit* m_name;
	class QLineEdit* m_length;
	class QLineEdit* m_m;
	class QLineEdit* m_b;
	class QLineEdit* m_gradient;
	class QLineEdit* m_tilt;

};

