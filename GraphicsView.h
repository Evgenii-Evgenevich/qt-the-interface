#pragma once

#include <QChartView>

QT_CHARTS_USE_NAMESPACE

class GraphicsView : public QChartView
{
Q_OBJECT

public:
	GraphicsView();

	explicit GraphicsView(QWidget* parent);

protected:
	void mouseMoveEvent(QMouseEvent*) override;
	void resizeEvent(QResizeEvent*) override;

public slots:
	void tooltip(QPointF point, bool state);

};

