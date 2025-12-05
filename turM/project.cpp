#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <sstream>

struct machine {
    std::vector<char> P; // Лента
    int head;            // Позиция головки

    machine() : head(1) {
        P.push_back('.'); // Начальный символ (пустой)
        P.push_back('.'); // Начальный символ (пустой)
    }

    void add_el(char l) {
        P.pop_back();
        P.push_back(l);
        P.push_back('.');
    }

    void print() {
        for (int i = 1; i < P.size() - 1; i++) {
            if (i == head) {
                std::cout << "[" << P[i] << "]"; // Отмечаем текущую позицию головки
            }
            else {
                std::cout << P[i];
            }
        }
        std::cout << std::endl;
    }

    char read() {
        return P[head]; // Чтение символа под головкой
    }

    void write(char c) {
        P[head] = c; // Запись символа в текущую позицию
    }

    void move(char direction) {
        if (direction == 'R') {
            head++;
            if (head >= P.size()) {
                P.push_back('.'); // Расширяем ленту при необходимости
            }
        }
        else if (direction == 'L') {
            head--;
            if (head < 0) {
                P.insert(P.begin(), '.'); // Расширяем ленту влево при необходимости
                head = 0;
            }
        }
    }

    ~machine() {
        while (P.size() > 0) {
            P.pop_back();
        }
    }
};

int main() {
    // Считываем ленту из файла tape.txt
    std::ifstream tapeFile("tape.txt");
    std::string tapeStr;
    if (!tapeFile.is_open()) {
        std::cerr << "error" << std::endl;
        return 1;
    }
    tapeFile >> tapeStr;
    tapeFile.close();

    // Инициализация ленты
    machine m;
    for (char c : tapeStr) {
        m.add_el(c);
    }

    // Считываем правила из файла rules.txt
    std::ifstream rulesFile("rules.txt");
    if (!rulesFile.is_open()) {
        std::cerr << "error" << std::endl;
        return 1;
    }

    std::map<std::pair<char, std::string>, std::tuple<char, char, std::string>> rules;
    std::string line;
    while (std::getline(rulesFile, line)) {
        std::cout << line << std::endl;
        std::istringstream iss(line);
        std::string inputSymState, outputSymMoveState;
        char inputSym;
        std::string state, nextState;
        char outputSym, move;

        // Парсим строку правил
        iss >> inputSym >> state >> outputSym >> move >> nextState;
        rules[{inputSym, state}] = { outputSym, move, nextState };

    }

    for (const auto& rule : rules) {
        std::cout << "Rule: (" << rule.first.first << ", " << rule.first.second << ") -> " << std::get<0>(rule.second) << ", " << std::get<1>(rule.second) << ", " << std::get<2>(rule.second) << std::endl;
    }

    rulesFile.close();

    // Инициализация состояния
    std::string currentState = "q0";

    // Выполнение шагов машины Тьюринга
    while (true) {
        m.print(); // Выводим текущее состояние ленты

        // Определяем текущий символ и состояние
        char currentSymbol = m.read();
        auto ruleKey = std::make_pair(currentSymbol, currentState);

        // Проверяем, существует ли правило для текущего состояния и символа
        if (rules.find(ruleKey) == rules.end()) {
            std::cout << "error " << currentState << " error " << currentSymbol << std::endl;
            break;
        }

        // Применяем правило
        char outputSym, move;
        std::string nextState;
        std::tie(outputSym, move, nextState) = rules[ruleKey];

        // Записываем новый символ
        m.write(outputSym);

        // Двигаем головку
        m.move(move);

        // Переходим в новое состояние
        currentState = nextState;

        // Если достигли состояния остановки
        if (currentState == "S") {
            std::cout << "stop" << std::endl;
            break;
        }
    }

    // Выводим финальное состояние ленты
    std::cout << "final:" << std::endl;
    m.print();

    return 0;
}