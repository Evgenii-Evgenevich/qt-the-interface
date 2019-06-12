#include "GraphicsView.h"
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>

GraphicsView::GraphicsView()
	: GraphicsView(nullptr)
{
}

GraphicsView::GraphicsView(QWidget* parent)
	: QChartView(new QChart, parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	chart()->setMinimumSize(640, 480);

	QLineSeries* a = new QLineSeries;
	a->setColor(QColor::fromRgb(qRgb(255, 255, 255)));
	a->append(0, 5);
	a->append(12, 30);
	chart()->addSeries(a);

	QSplineSeries* BetaX = new QSplineSeries;
	BetaX->setName("BetaX");
	BetaX->setColor(QColor::fromRgb(qRgb(255, 0, 0)));

	BetaX->append(0, 15);
	BetaX->append(6, 5.5);
	BetaX->append(12, 25);

	chart()->addSeries(BetaX);

	QSplineSeries* BetaY = new QSplineSeries;
	BetaY->setName("BetaY");
	BetaY->setColor(QColor::fromRgb(qRgb(0, 255, 0)));

	BetaY->append(0, 5);
	BetaY->append(6, 20);
	BetaY->append(12, 6);

	chart()->addSeries(BetaY);

	chart()->createDefaultAxes();
	chart()->setAcceptHoverEvents(true);

	setRenderHint(QPainter::Antialiasing);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event)
{
	QChartView::mouseMoveEvent(event);
}

void GraphicsView::resizeEvent(QResizeEvent* event)
{
	QChartView::resizeEvent(event);
	//if (scene()) scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
}

void GraphicsView::tooltip(QPointF point, bool state)
{
}
