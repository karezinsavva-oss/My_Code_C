#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>

struct point{
    int a;
    int b;

    void print(){
        std::cout << a << ' ' << b << std::endl;
    }
};

class Triangle {
private:
    float a;
    float b;
    float c;
public:
    Triangle() : a(3.0), b(4.0), c(5.0) {};
    Triangle(float q1, float q2, float q3) {
        if (!((q1 < q2 + q3) and (q2 < q1 + q3) and (q3 < q2 + q1) and q1 > 0 and q2 > 0 and q3 > 0)) {
            throw std::runtime_error("no");
        }
        a = q1;
        b = q2;
        c = q3;
    }
    Triangle(float q1) {
        if (!(q1 > 0)) {
            throw std::runtime_error("no");
        }
        a = q1;
        b = q1;
        c = q1;
    }
    void print() {
        std::cout << a << ' ' << b << ' ' << c << ' ' << std::endl;
    }

    float get_a() { return a; }
    float get_b() { return b; }
    float get_c() { return c; }

    float perimetr(int flag = 0) {
        if (flag == 0) {
            return a + b + c;
        }
        else if (flag == 1) {
            return (a + b + c) / 2.0;
        }
    }

    float plohad() {
        return std::sqrt(perimetr(1) * (perimetr(1) - a) * (perimetr(1) - b) * (perimetr(1) - c));
    }
};

template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    try {
        Triangle popa;
        Triangle pisa(11.63, 15, 20.123);
        pisa.print();
        std::cout << pisa.perimetr() << std::endl;
        std::cout << pisa.perimetr(1) << std::endl;
        std::cout << pisa.plohad() << std::endl;
        std::cout << pisa.get_a() << std::endl;
        std::cout << pisa.get_b() << std::endl;
        std::cout << pisa.get_c() << std::endl;

        popa.print();
        std::cout << popa.perimetr() << std::endl;
        std::cout << popa.perimetr(1) << std::endl;
        std::cout << popa.plohad() << std::endl;
        std::cout << popa.get_a() << std::endl;
        std::cout << popa.get_b() << std::endl;
        std::cout << popa.get_c() << std::endl;

        Triangle pipohui(11.63);
        pipohui.print();
        std::cout << pipohui.perimetr() << std::endl;
        std::cout << pipohui.perimetr(1) << std::endl;
        std::cout << pipohui.plohad() << std::endl;
        std::cout << pipohui.get_a() << std::endl;
        std::cout << pipohui.get_b() << std::endl;
        std::cout << pipohui.get_c() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    {
        auto i = max(3.545, 3.34);
        auto d = max(3.14, 2.71);
    }
    
    
    {
        std::cout << std::endl;
        int a = 56;
        int* b = &a;
        *b += 8;
        int c = 43;

        std::cout << a << ' ' << *b << ' ' << *(&c) << std::endl << std::endl;
    }
    
    /*
    std::vector<int> a;
    for (int i = 0; i <= 100; i++) {
        a.push_back(i);
        }
        for (int num : a) {
            std::cout << num << ' ';
        }
        std::cout << std::endl;
        std::cout << std::endl;
    */

    std::ifstream file("17.txt");
    if (!file.is_open()) {
        std::cerr << "nono" << std::endl;
        return 1;
    }

    std::vector<int> arr;
    int number;

    while (file >> number) {
        arr.push_back(number);
    }

    file.close();

    //for (int i = 0; i < arr.size(); i++) {
        //std::cout << arr[i] << ' ';
    //}

    std::cout << std::endl;

    std::vector<int> b;

    for (int i : arr) {
        if (std::abs(i) % 10 == 8 and std::abs(i) >= 100 and std::abs(i) <= 999) b.push_back(i);
    }

    std::sort(b.begin(), b.end());

    int min = (b[0])*(b[0]);

    int count = 0;
    std::vector<int> minima;

    for (int i = 0; i < arr.size() - 2; i++) {
        if ((std::abs(arr[i]) >= 100 and std::abs(arr[i]) <= 999) or (std::abs(arr[i + 1]) >= 100 and std::abs(arr[i + 1]) <= 999) or (std::abs(arr[i + 2]) >= 100 and std::abs(arr[i + 2]) <= 999)) {
            std::vector<int> row;
            row.push_back(arr[i] * arr[i]); row.push_back(arr[i + 1] * arr[i + 1]); row.push_back(arr[i + 2] * arr[i + 2]); row.push_back(min);
            std::sort(row.begin(), row.end());
            if (row[2] == min) {
                count++;
                minima.push_back(arr[i] + arr[i + 1] + arr[i + 2]);
            }
            row.clear();
        }
    }

    std::sort(minima.begin(), minima.end());
    std::cout << count << ' ' << minima[minima.size() - 1] << std::endl;


    /*std::vector<int> b;

    for (int i : arr) {
        if (i >= 100 and i <= 999 and i % 10 == 7) b.push_back(i);
    }
    std::sort(b.begin(), b.end());
    
    int count = 0;

    for (int i = 0; i < arr.size() - 1; i++) {
        if ((arr[i] + arr[i + 1]) % b[0] == 0 and ((arr[i] >= 100 and arr[i] <= 999) or (arr[i + 1] >= 100 and arr[i + 1] <= 999))) {
            count++;
            std::cout << arr[i] + arr[i + 1] << std::endl;
        }
    }
    std::cout << count << std::endl;*/

    /*std::cout << std::endl;
    int count = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] >= 0 and arr[i + 1] >= 0) count++;
        if (arr[i] < 0 and arr[i + 1] < 0) count++;
    }
    std::cout << count << std::endl;*/

    return 0;
}