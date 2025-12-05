/*#include <bits/stdc++.h>
using namespace std;

int otv(int a, int b, int c = 0) {
    if (a == b and c == 3) return 0;
    if (a == b and c != 3) return 1;
    if (a > b) return 0;
    if (a < b) return otv(a + 2, b, 1) + otv(a + 5, b, 2) + otv(a * 2, b, 3);
}

int main() {

    std::cout << otv(8, 40) << std::endl;

    return 0;
}

/*

#include <bits/stdc++.h>
using namespace std;

int otv(int a, int step){
    if (step == 0 and a < 21) return otv(a + 1, step + 1) or otv(a * 2, step + 1);
    if (step == 1 and a >= 21) return 0;
    if (step == 1 and a < 21) return otv(a + 1, step + 1) and otv(a * 2, step + 1);
    if (step == 2 and a >= 21) return 0;
    if (step == 2 and a < 21) return otv(a + 1, step + 1) or otv(a * 2, step + 1);
    if (step == 3 and a >= 21) return 1;
    if (step == 3 and a < 21) return 0;
}

int otv_2(int a, int step){
    if (step == 0 and a < 21) return otv_2(a + 1, step + 1) and otv_2(a * 2, step + 1);
    if (step == 1 and a >= 21) return 0;
    if (step == 1 and a < 21) return otv_2(a + 1, step + 1) or otv_2(a * 2, step + 1);
    if (step == 2 and a >= 21) return 1;
    if (step == 2 and a < 21) return 0;
}

int otv_3(int a, int step){
    if (step == 0 and a < 21) return otv_3(a + 1, step + 1) and otv_3(a * 2, step + 1);
    if (step == 1 and a >= 21) return 0;
    if (step == 1 and a < 21) return otv_3(a + 1, step + 1) or otv_3(a * 2, step + 1);
    if (step == 2 and a >= 21) return 1;
    if (step == 2 and a < 21) return otv_3(a + 1, step + 1) and otv_3(a * 2, step + 1);
    if (step == 3 and a >= 21) return 0;
    if (step == 3 and a < 21) return otv_3(a + 1, step + 1) or otv_3(a * 2, step + 1);
    if(step == 4 and a >= 21) return 1;
    if(step == 4 and a < 21) return 0;
}

int otv_4(int a, int step){
    if (step == 0 and a < 21) return otv_4(a + 1, step + 1) or otv_4(a * 2, step + 1);
    if (step == 1 and a >= 21) return 1;
    if (step == 1 and a < 21) return otv_4(a + 1, step + 1) and otv_4(a * 2, step + 1);
    if (step == 2 and a >= 21) return 0;
    if (step == 2 and a < 21) return otv_4(a + 1, step + 1) or otv_4(a * 2, step + 1);
    if (step == 3 and a >= 21) return 1;
    if (step == 3 and a < 21) return otv_4(a + 1, step + 1) and otv_4(a * 2, step + 1);
    if(step == 4 and a >= 21) return 0;
    if(step == 4 and a < 21) return otv_4(a + 1, step + 1) or otv_4(a * 2, step + 1);
    if(step == 5 and a >= 21) return 1;
    if(step == 5 and a < 21) return 0;
}

int otv_4_5(int a, int step){
    if (step == 0 and a < 21) return otv_4_5(a + 1, step + 1) or otv_4_5(a * 2, step + 1);
    if (step == 1 and a >= 21) return 0;
    if (step == 1 and a < 21) return otv_4_5(a + 1, step + 1) and otv_4_5(a * 2, step + 1);
    if (step == 2 and a >= 21) return 0;
    if (step == 2 and a < 21) return otv_4_5(a + 1, step + 1) or otv_4_5(a * 2, step + 1);
    if (step == 3 and a >= 21) return 1;
    if (step == 3 and a < 21) return 0;
}

int otv_4_5_6(int a, int step){
    if (step == 0 and a < 21) return otv_4_5_6(a + 1, step + 1) or otv_4_5_6(a * 2, step + 1);
    if (step == 1 and a >= 21) return 1;
    if (step == 1 and a < 21) return 0;
}

int main() {
 for (int i = 1; i <= 20; i++){
     int f = otv(i, 0);
     if (f == 1) std::cout << i << ' ';
 }

 std::cout << std::endl;

 for (int i = 1; i <= 20; i++){
     int f = otv_3(i, 0);
     if (f == 1 and otv_2(i, 0) == 0) std::cout << i << ' ';
 }

 std::cout << std::endl;

 for (int i = 1; i <= 20; i++){
     int f = otv_4(i, 0);
     if (f == 1 and otv_4_5(i, 0) == 0 and otv_4_5_6(i, 0) == 0) std::cout << i << ' ';
 }

 return 0;
}

*/

/*

#include <bits/stdc++.h>
using namespace std;

int otv(int a, int b, int c = 0){
    if (a == b and c == 3) return 0;
    if (a == b and c != 3) return 1;
    if (a > b) return 0;
    if (a < b) return otv(a + 2, b, 1) + otv(a + 5, b, 2) + otv(a * 2, b, 3);
}

int main() {

 std::cout << otv(8, 40)<< std::endl;

 return 0;
}

*/

/*

#include <bits/stdc++.h>
using namespace std;

int odin(int b){
    int a = b*b;
    while (a>=10) {
        a /= 10;
    }
    return b-a;
}

int otv(int a){
*/

/*if (a == 1) return 1;
    if (a < 1) return 0;
    if (a > 1) return otv(odin(a)) + otv(a - (a / 10 + a % 10));
}

int main() {

 std::cout << otv(32) << std::endl;

 return 0;
}


#include <bits/stdc++.h>
using namespace std;

int otv(int a, int b, int step = 0) {
    if (step == 0 and a != b) {
        if (a > b) return otv(a, b + 1, step + 1) and otv(a, b + 3, step + 1);
        else return otv(a + 1, b, step + 1) and otv(a + 3, b, step + 1);
    }
    if (step == 1 and a == b) return 0;
    if (step == 1 and a != b) {
        if (a > b) return otv(a, b + 1, step + 1) or otv(a, b + 3, step + 1);
        else return otv(a + 1, b, step + 1) or otv(a + 3, b, step + 1);
    }
    if (step == 2 and a == b) return 1;
    if (step == 2 and a != b) return 0;

}

int main() {
    for (int i = 1; i <= 23; i++) {
        int f = otv(13, i);
        if (f == 1) std::cout << i << ' ';
    }
    return 0;
}


#include <bits/stdc++.h>
using namespace std;

int otv(int a, int b, int step = 0) {
    if (step == 0 and a != b) {
        if (a > b) return otv(a, b + 1, step + 1) or otv(a, b + 3, step + 1);
        else return otv(a + 1, b, step + 1) or otv(a + 3, b, step + 1);
    }
    if (step == 1 and a == b) return 0;
    if (step == 1 and a != b) {
        if (a > b) return otv(a, b + 1, step + 1) and otv(a, b + 3, step + 1);
        else return otv(a + 1, b, step + 1) and otv(a + 3, b, step + 1);
    }
    if (step == 2 and a == b) return 0;
    if (step == 2 and a != b) {
        if (a > b) return otv(a, b + 1, step + 1) or otv(a, b + 3, step + 1);
        else return otv(a + 1, b, step + 1) or otv(a + 3, b, step + 1);
    }
    if (step == 3 and a == b) return 1;
    if (step == 3 and a != b) return 0;
}

int main() {
    for (int i = 1; i <= 23; i++) {
        int f = otv(13, i);
        if (f == 1) std::cout << i << ' ';
    }
    return 0;
}


#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

int main() {
    std::ifstream inputFile("numbers.txt");
    int arr[50];

    for (int i = 0; i < 50; ++i) {
        inputFile >> arr[i];
    }

    inputFile.close();

    for (int i = 0; i < 50; ++i) {
        std::cout << arr[i] << " ";
    }

    std::ifstream stringFile("string.txt");
    std::string str;

    if (stringFile.is_open()) {
        std::getline(stringFile, str);
        stringFile.close();
    }

    std::cout << str << std::endl;
    std::cout << str[0] << std::endl;


    return 0;
}
*/