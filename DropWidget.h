#ifndef DROPWIDGET_H
#define DROPWIDGET_H 1

#include <QScrollArea>

class DropWidget : public QScrollArea
{
Q_OBJECT

public:
	DropWidget();

	explicit DropWidget(QWidget* parent);

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
	class HBoxLayout* m_layout;

};


#endif // DROPWIDGET_H