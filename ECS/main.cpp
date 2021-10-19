#include <iostream>

int main() {
	int arr[2] = { 3, 5 };
	
	auto [a, b] = arr;

	std::cout << a << b << std::endl;

	return 0;
}