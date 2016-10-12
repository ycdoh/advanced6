#include <iostream>
#include <string>

template <class T>
void print(T a)
{
	std::cout << a << std::endl;
}

int main()
{
	print(1);
	print(2.345f);
	print("Hellow World");
	return 0;
}