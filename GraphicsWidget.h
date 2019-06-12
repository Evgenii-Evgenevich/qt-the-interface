#pragma once
#include <QScrollArea>


class GraphicsWidget :
	public QScrollArea
{
Q_OBJECT

public:
	GraphicsWidget();

	explicit GraphicsWidget(QWidget* parent);

protected:
	void enterEvent(QEvent*) override;
	void leaveEvent(QEvent*) override;
	void focusInEvent(QFocusEvent*) override;
	void focusOutEvent(QFocusEvent*) override;

private:
	class VBoxLayout* m_layout;
	class GraphicsView* m_view;

};

