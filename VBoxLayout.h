#pragma once

#include <QWidget>

class VBoxLayout :
	public QWidget
{
Q_OBJECT

public:
	VBoxLayout();

	explicit VBoxLayout(QWidget* parent);

	void add(QWidget* widget);

	void drop(QWidget* widget, QPoint offset);

	void setLayout(QLayout*) = delete;

protected:
	void resizeEvent(QResizeEvent* event) override;
};

