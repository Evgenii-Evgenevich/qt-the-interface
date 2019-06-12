#pragma once

#include <QWidget>


class HBoxLayout :
	public QWidget
{
Q_OBJECT

public:
	HBoxLayout();

	explicit HBoxLayout(QWidget* parent);

	void drop(QWidget* widget, QPoint offset);

	void setLayout(QLayout*) = delete;

protected:
	void resizeEvent(QResizeEvent* event) override;
};

