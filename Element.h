#pragma once

#include <QLabel>
#include <QPixmap>


struct Elements
{
	enum Type : int
	{
		drift,
		dipole,
		quadrupole,
		sextipole,
		octupole,
		multipole,
		solenoid,
		lens,
		type_count
	};

	QString const string[type_count]{
		{ "drift" },
		{ "dipole" },
		{ "quadrupole" },
		{ "sextipole" },
		{ "octupole" },
		{ "multipole" },
		{ "solenoid" },
		{ "lens" },
	};

	QPixmap const pixmap[type_count]{
		{ ":/Resources/drift.png" },
		{ ":/Resources/dipole.png" },
		{ ":/Resources/quadrupole.png" },
		{ ":/Resources/sextipole.png" },
		{ ":/Resources/octupole.png" },
		{ ":/Resources/multipole.png" },
		{ ":/Resources/solenoid.png" },
		{ ":/Resources/lens.png" },
	};

	constexpr QPixmap const& dipole_pixmap() const noexcept { return pixmap[dipole]; }
	constexpr QPixmap const& quadrupole_pixmap() const noexcept { return pixmap[quadrupole]; }
	constexpr QPixmap const& sextipole_pixmap() const noexcept { return pixmap[sextipole]; }
	constexpr QPixmap const& octupole_pixmap() const noexcept { return pixmap[octupole]; }

	static Elements& instance();

	Elements(const Elements& other) = delete;
	Elements(Elements&& other) = delete;
	Elements& operator=(const Elements& other) = delete;
	Elements& operator=(Elements&& other) = delete;
private:
	Elements() = default;
};

class Element : public QLabel
{
Q_OBJECT

public:
	explicit Element(Elements::Type type);

	explicit Element(Element const&);

	void setPixmap(QPixmap const&);

	constexpr QPixmap const& pixmap() const noexcept
	{
		return m_pixmap;
	}

	constexpr Elements::Type type() const noexcept
	{
		return Elements::Type(m_type);
	}

	constexpr QString const& text() const noexcept
	{
		return m_name;
	}

	constexpr double& rlength() noexcept
	{
		return m_length;
	}

	QString length() const;

	constexpr double& rtilt() noexcept
	{
		return m_tilt;
	}

	QString tilt() const;

	constexpr double& rb() noexcept
	{
		return m_b;
	}

	constexpr double& rgradient() noexcept
	{
		return m_gradient;
	}

	QString b() const;

	QString gradient() const;

	constexpr int& rm() noexcept
	{
		return m_m;
	}

	QString m() const;

	void setText(QString const&);

	void setWidth(int w);

	void setHeight(int h);

	void dialog();

	QString tooltip() const noexcept;

protected:
	bool event(QEvent*) override;

	void resizeEvent(QResizeEvent*) override;

private:
	Element(QPixmap const& pixmap, int type, double length = 0, double b = 0, double g = 0, double tilt = 0);

	QPixmap m_pixmap;

	QString m_name;

	bool m_dialog;

	int m_type;

	int m_m;

	double m_length;

	double m_b;
	double m_gradient;

	double m_tilt;

	friend class ElementDialog;

};
