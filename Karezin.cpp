#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

class Circle {
private:
	double centerX;
	double centerY;
	double radius;

public:
	Circle(double x, double y, double r) : centerX(x), centerY(y), radius(r) {}

	double getCircumference() const {
		return 2 * 3.1415 * radius;
	}

	double getArea() const {
		return 3.1415 * radius * radius;
	}

	bool isPointOnCircle(double x, double y) const {
		double distance = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
		if (distance == radius) return 1;
		else return 0;
	}
};

int otv_21(int a, int step = 0) {
	if (step == 0 and a > 87) return otv_21(a - 2, step + 1) and otv_21(a / 2, step + 1);
	if (step == 1 and a <= 87) return 0;
	if (step == 1 and a > 87) return otv_21(a - 2, step + 1) or otv_21(a / 2, step + 1);
	if (step == 2 and a <= 87) return 1;
	if (step == 2 and a > 87) return 0;
}

int otv_22(int a, int step = 0) {
	if (step == 0 and a > 87) return otv_22(a - 2, step + 1) or otv_22(a / 2, step + 1);
	if (step == 1 and a <= 87) return 0;
	if (step == 1 and a > 87) return otv_22(a - 2, step + 1) and otv_22(a / 2, step + 1);
	if (step == 2 and a <= 87) return 0;
	if (step == 2 and a > 87) return otv_22(a - 2, step + 1) or otv_22(a / 2, step + 1);
	if (step == 3 and a <= 87) return 1;
	if (step == 3 and a > 87) return 0;
}

int otv_23(int a, int step = 0) {
	if (step == 0 and a > 87) return otv_23(a - 2, step + 1) and otv_23(a / 2, step + 1);
	if (step == 1 and a <= 87) return 0;
	if (step == 1 and a > 87) return otv_23(a - 2, step + 1) or otv_23(a / 2, step + 1);
	if (step == 2 and a <= 87) return 1;
	if (step == 2 and a > 87) return otv_23(a - 2, step + 1) and otv_23(a / 2, step + 1);
	if (step == 3 and a <= 87) return 0;
	if (step == 3 and a > 87) return otv_23(a - 2, step + 1) or otv_23(a / 2, step + 1);
	if (step == 4 and a <= 87) return 1;
	if (step == 4 and a > 87) return 0;
}

int otv_23_5(int a, int step = 0) {
	if (step == 0 and a > 87) return otv_23_5(a - 2, step + 1) and otv_23_5(a / 2, step + 1);
	if (step == 1 and a <= 87) return 0;
	if (step == 1 and a > 87) return otv_23_5(a - 2, step + 1) or otv_23_5(a / 2, step + 1);
	if (step == 2 and a <= 87) return 1;
	if (step == 2 and a > 87) return 0;
}

int otv_3(int start, int end) {
	if (start == end) return 1;
	if (start == 13) return 0;
	if (start > end) return 0;
	if (start < end) return otv_3(start + 1, end) + otv_3(start * 2, end) + otv_3(start * 3, end);
}

int search_M(int a) {
	int m = 0;
	for (int i = 2; i < a; i++) {
		if (a % i == 0) {
			m = i + (a / i);
			return m;
		}
	}
	return m;
}

std::vector<int> peresech(const std::vector<int>& arr1, const std::vector<int>& arr2) {
	std::vector<int> arr1_sort = arr1;
	std::vector<int> arr2_sort = arr2;
	std::sort(arr1_sort.begin(), arr1_sort.end());
	std::sort(arr2_sort.begin(), arr2_sort.end());

	std::vector<int> peresecheni;
	size_t i = 0, j = 0;
	while (i < arr1_sort.size() && j < arr2_sort.size()) {
		if (arr1_sort[i] == arr2_sort[j]) {
			if (peresecheni.empty() || peresecheni.back() != arr1_sort[i]) {
				peresecheni.push_back(arr1_sort[i]);
			}
			i++;
			j++;
		}
		else if (arr1_sort[i] < arr2_sort[j]) {
			i++;
		}
		else {
			j++;
		}
	}

	return peresecheni;
}

int main() {

	// 1.

	std::cout << 'w' << ' ' << 'x' << ' ' << 'y' << ' ' << 'z' << "  " << 'F' << std::endl;

	for (int w = 0; w <= 1; w++) {
		for (int x = 0; x <= 1; x++) {
			for (int y = 0; y <= 1; y++) {
				for (int z = 0; z <= 1; z++) {
					bool f = (!((!w and !1) or (w and 1)) or z) and (!y and x);
					std::cout << w << ' ' << x << ' ' << y << ' ' << z << "  " << f << std::endl;
				}
			}
		}
	}

	std::cout << std::endl;

	// 2.1.
	for (int i = 89; i < 1000; i++) {
		if (otv_21(i) == 1) {
			std::cout << i << ' ';
		} //наждо один минимум взять
	}

	std::cout << std::endl;

	//2.2

	for (int i = 89; i < 1000; i++) {
		if (otv_22(i) == 1) {
			std::cout << i << ' ';
		} // надо два минимума взять
	}

	//2.3

	std::cout << std::endl;

	for (int i = 89; i < 1000; i++) {
		if (otv_23(i) == 1 and otv_23_5(i) != 1) {
			std::cout << i << ' ';
		} // надо один минимум взять
	}
	
	std::cout << std::endl;

	// 3.

	std::cout << otv_3(3, 8) * otv_3(8, 18) << std::endl;

	std::cout << std::endl;

	// 5.

	for (int i = 800001; i < 800050; i++) {
		int m = search_M(i);
		if (m % 10 == 4) {
			std::cout << i << ' ' << m << std::endl;
		}
	}

	// 10.

	std::vector<int> arr1 = { 1, 2, 2, 3, 4 };
	std::vector<int> arr2 = { 1, 4, 3, 4, 2, 3};

	std::vector<int> result = peresech(arr1, arr2);

	for (int value : result) {
		std::cout << value << " ";
	}
	std::cout << std::endl;

	// 4.

	Circle circle(0, 0, 5);

	std::cout << "dlina okr " << circle.getCircumference() << std::endl;

	std::cout << "plochad kruga " << circle.getArea() << std::endl;

	std::cout << (circle.isPointOnCircle(4, 3) ? "Yes" : "No") << std::endl;
	return 0;
}