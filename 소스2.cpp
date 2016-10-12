#include <iostream>

template <class T>
class Vector2D
{
public:
	T x_, y_;
public:
	Vector2D(T x,T y) {
		x_ = x;
		y_ = y;
	}
	void print()
	{
		std::cout << x_ <<" "<< y_ << std::endl;
	}
};

int main()
{
	Vector2D<int> intvector(1,2);
	Vector2D<float> floatvector(1.34f, 2.345f);
	Vector2D<double> doublevector(1.34, 3.45);

	intvector.print();
	floatvector.print();
	doublevector.print();

	return 0;
}