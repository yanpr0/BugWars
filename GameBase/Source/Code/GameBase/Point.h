#pragma once

struct Point
{
	Point() = default;

	Point(float x_, float y_)
		: x(x_)
		, y(y_)
	{}

	Point(int x_, int y_)
		: x((float)x_)
		, y((float)y_)
	{}

	Point(double x_, double y_)
		: x((float)x_)
		, y((float)y_)
	{}

	Point operator + (Point other) const
	{
		return Point(x + other.x, y + other.y);
	}

	Point operator - (Point other) const
	{
		return Point(x - other.x, y - other.y);
	}

	Point operator * (float value) const
	{
		return Point(x * value, y * value);
	}

	Point operator / (float value) const
	{
		return Point(x / value, y / value);
	}

	float Length() const
	{
		return sqrt(Length2());
	}

	float Length2() const
	{
		return x * x + y * y;
	}

	Point Normalized() const
	{
		return *this / Length();
	}

	float Distance(Point p) const
	{
		return (p - *this).Length();
	}

	float Distance2(Point p) const
	{
		return (p - *this).Length2();
	}

	float Dot(Point p) const
	{
		return x * p.x + y * p.y;
	}

	float x = 0.0f;
	float y = 0.0f;
};

template <>
struct std::formatter<Point> : std::formatter<std::string> {
	auto format(Point p, format_context& ctx) {
		return formatter<string>::format(
			std::format("({:.1f}, {:.1f})", p.x, p.y), ctx);
	}
};