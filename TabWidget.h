#pragma once

#include <QScrollArea>

class TabWidget :
	public QScrollArea
{
Q_OBJECT

public:
	TabWidget();

	constexpr class Beam* beam() const noexcept { return m_beam; }
	constexpr class Twiss* twiss() const noexcept { return m_twiss; }

private:
	class QTabWidget* m_widget;
	class Beam* m_beam;
	class Twiss* m_twiss;

};

