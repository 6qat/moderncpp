//
// Created by guiga on 23/09/2020.
//

// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

#include <iostream>

class Rectangle {
protected:
	int width, height;
public:
	Rectangle(const int width, const int height)
			:width{ width }, height{ height } { }

	[[nodiscard]] int get_width() const { return width; }
	[[maybe_unused]] virtual void set_width(const int w) { this->width = w; }
	[[maybe_unused]] [[nodiscard]] int get_height() const { return height; }
	virtual void set_height(const int h) { this->height = h; }

	[[nodiscard]] int area() const { return width*height; }
};

class Square : public Rectangle {
public:
	explicit Square(int size)
			:Rectangle(size, size) { }
	void set_width(const int width) override
	{
		this->width = height = width;
	}
	void set_height(const int height) override
	{
		this->height = width = height;
	}
};

struct RectangleFactory {
	static Rectangle create_rectangle(int w, int h)
	{
		return Rectangle(w, h);
	}
	static Rectangle create_square(int size)
	{
		return Rectangle(size, size);
	}
};

void process(Rectangle& r)
{
	int w = r.get_width();
	r.set_height(10);

	std::cout << "expected area = " << (w*10)
			  << ", got " << r.area() << std::endl;
}

int main()
{
	Rectangle r{ 5, 5 };
	process(r);

	Square s{ 5 };
	process(s);

	auto r2 = RectangleFactory::create_rectangle(5, 5);
	process(r2);

	auto s2 = RectangleFactory::create_square(5);
	process(s2);

//	getchar();
	return 0;
}