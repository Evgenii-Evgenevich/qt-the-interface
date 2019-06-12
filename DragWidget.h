#pragma once

#include <QScrollArea>

class QDragEnterEvent;
class QDropEvent;

class DragWidget : public QScrollArea
{
Q_OBJECT

public:
	DragWidget();

	explicit DragWidget(QWidget *parent);

protected:
	void dragEnterEvent(QDragEnterEvent*) override;
	void dragMoveEvent(QDragMoveEvent*) override;
	void dropEvent(QDropEvent*) override;

	void mousePressEvent(QMouseEvent*) override;

	void enterEvent(QEvent*) override;
	void leaveEvent(QEvent*) override;

	void focusInEvent(QFocusEvent*) override;
	void focusOutEvent(QFocusEvent*) override;

	void resizeEvent(QResizeEvent*) override;

private:
	class VBoxLayout* m_layout;
};
