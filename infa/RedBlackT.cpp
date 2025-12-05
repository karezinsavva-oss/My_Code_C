//
//  RedBlackTree.h
//  red-black-tree
//

#include <iostream>

enum Color { RED, BLACK };

// Структура узла дерева
struct Node {
    int data;       // Данные, хранящиеся в узле
    Color color;    // Цвет узла
    Node* left;     // Указатель на левого потомка
    Node* right;    // Указатель на правого потомка
    Node* parent;   // Указатель на родительский узел

    explicit Node(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Класс красно-черного дерева
class RedBlackTree {
private:
    Node* root; // Указатель на корень дерева

    // Левое вращение поддерева с корнем в узле x
    void leftRotate(Node* x) {
        if (x == nullptr || x->right == nullptr) // Если узел x или его правый потомок равны nullptr, выходим из функции
            return;

        Node* y = x->right; // y - правый потомок x
        x->right = y->left; // Левый потомок y становится правым потомком x
        if (y->left != nullptr) // Если левый потомок y существует
            y->left->parent = x; // Обновляем родителя левого потомка y на x
        y->parent = x->parent; // Родитель y становится родителем x
        if (x->parent == nullptr) // Если x был корнем дерева
            root = y; // Новый корень - y
        else if (x == x->parent->left) // Если x был левым потомком своего родителя
            x->parent->left = y; // Левым потомком родителя x становится y
        else // Если x был правым потомком своего родителя
            x->parent->right = y; // Правым потомком родителя x становится y
        y->left = x; // x становится левым потомком y
        x->parent = y; // Родитель x - y
    }

    // Правое вращение поддерева с корнем в узле y
    void rightRotate(Node* y) {
        if (y == nullptr || y->left == nullptr) // Если узел y или его левый потомок равны nullptr, выходим из функции
            return;

        Node* x = y->left; // x - левый потомок y
        y->left = x->right; // Правый потомок x становится левым потомком y
        if (x->right != nullptr) // Если правый потомок x существует
            x->right->parent = y; // Обновляем родителя правого потомка x на y
        x->parent = y->parent; // Родитель x становится родителем y
        if (y->parent == nullptr) // Если y был корнем дерева
            root = x; // Новый корень - x
        else if (y == y->parent->left) // Если y был левым потомком своего родителя
            y->parent->left = x; // Левым потомком родителя y становится x
        else // Если y был правым потомком своего родителя
            y->parent->right = x; // Правым потомком родителя y становится x
        x->right = y; // y становится правым потомком x
        y->parent = x; // Родитель y - x
    }

    // Функция для восстановления свойств красно-черного дерева после вставки узла z
    void fixInsert(Node* z) {
        while (z != root && z->parent->color == RED) { // Пока z не является корнем и его родитель - красный узел
            if (z->parent == z->parent->parent->left) { // Если родитель z - левый потомок своего родителя
                Node* y = z->parent->parent->right; // y - правый брат родителя z
                if (y != nullptr && y->color == RED) { // Если y существует и красный
                    z->parent->color = BLACK; // Цвет родителя z - черный
                    y->color = BLACK; // Цвет y - черный
                    z->parent->parent->color = RED; // Цвет дедушки z - красный
                    z = z->parent->parent; // Переходим к дедушке z
                }
                else { // Если y не существует или черный
                    if (z == z->parent->right) { // Если z - правый потомок своего родителя
                        z = z->parent; // Переходим к родителю z
                        leftRotate(z); // Выполняем левое вращение вокруг родителя z
                    }
                    z->parent->color = BLACK; // Цвет родителя z - черный
                    z->parent->parent->color = RED; // Цвет дедушки z - красный
                    rightRotate(z->parent->parent); // Выполняем правое вращение вокруг дедушки z
                }
            }
            else { // Если родитель z - правый потомок своего родителя
                Node* y = z->parent->parent->left; // y - левый брат родителя z
                if (y != nullptr && y->color == RED) { // Если y существует и красный
                    z->parent->color = BLACK; // Цвет родителя z - черный
                    y->color = BLACK; // Цвет y - черный
                    z->parent->parent->color = RED; // Цвет дедушки z - красный
                    z = z->parent->parent; // Переходим к дедушке z
                }
                else { // Если y не существует или черный
                    if (z == z->parent->left) { // Если z - левый потомок своего родителя
                        z = z->parent; // Переходим к родителю z
                        rightRotate(z); // Выполняем правое вращение вокруг родителя z
                    }
                    z->parent->color = BLACK; // Цвет родителя z - черный
                    z->parent->parent->color = RED; // Цвет дедушки z - красный
                    leftRotate(z->parent->parent); // Выполняем левое вращение вокруг дедушки z
                }
            }
        }
        root->color = BLACK; // Корень дерева черный
    }

    // Функция замены одного поддерева другим в процессе удаления узла
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) // Если u - корень дерева
            root = v; // Новый корень - v
        else if (u == u->parent->left) // Если u - левый потомок своего родителя
            u->parent->left = v; // Левым потомком родителя u становится v
        else // Если u - правый потомок своего родителя
            u->parent->right = v; // Правым потомком родителя u становится v
        if (v != nullptr) // Если v существует
            v->parent = u->parent; // Обновляем родителя v на родителя u
    }

    // Функция удаления узла z из дерева
    void deleteNode(Node* z) {
        if (z == nullptr) // Если узел z не существует, выходим из функции
            return;

        Node* y = z; // Узел y - удаляемый узел
        Node* x = nullptr; // Узел x - детё узла y (или nullptr, если у y нет детей)
        Color y_original_color = y->color; // Сохраняем исходный цвет y

        if (z->left == nullptr) { // Если у z нет левого потомка
            x = z->right; // Дочерним узлом y становится правый потомок z
            transplant(z, z->right); // Заменяем z на его правого потомка
        }
        else if (z->right == nullptr) { // Если у z нет правого потомка
            x = z->left; // Дочерним узлом y становится левый потомок z
            transplant(z, z->left); // Заменяем z на его левого потомка
        }
        else { // Если у z есть оба потомка
            y = minimum(z->right); // Находим минимальный узел в правом поддереве z
            y_original_color = y->color; // Сохраняем исходный цвет y
            x = y->right; // Дочерним узлом y становится правый потомок y

            if (y->parent == z) { // Если y - правый потомок z
                if (x != nullptr)
                    x->parent = y; // Обновляем родителя x на y
            }
            else { // Если y - не правый потомок z
                if (x != nullptr)
                    x->parent = y->parent; // Обновляем родителя x на родителя y
                transplant(y, y->right); // Заменяем y на его правого потомка
                if (y->right != nullptr) // Если правый потомок y есть
                    y->right->parent = y; // Обновляем родителя правого потомка y на y
                y->right = z->right; // Правым потомком y становится правый потомок z
                if (y->right != nullptr)
                    y->right->parent = y; // Обновляем родителя правого потомка y на y
            }
            transplant(z, y); // Заменяем z на y
            y->left = z->left; // Левым потомком y становится левый потомок z
            if (y->left != nullptr)
                y->left->parent = y; // Обновляем родителя левого потомка y на y
            y->color = z->color; // Цвет y становится цветом z
        }

        if (y_original_color == BLACK && x != nullptr) // Если исходный цвет y был черным и x существует
            fixDelete(x); // Восстанавливаем свойства красно-черного дерева

        delete z; // Освобождаем память, занятую удаляемым узлом z
    }

    // Функция восстановления свойств красно-черного дерева после удаления узла x
    void fixDelete(Node* x) {
        while (x != root && x != nullptr && x->color == BLACK) { // Пока x не является корнем, не равен nullptr и черный
            if (x == x->parent->left) { // Если x - левый потомок своего родителя
                Node* w = x->parent->right; // w - правый брат x
                if (w->color == RED) { // Если w красный
                    w->color = BLACK; // Цвет w - черный
                    x->parent->color = RED; // Цвет родителя x - красный
                    leftRotate(x->parent); // Выполняем левое вращение вокруг родителя x
                    w = x->parent->right; // Обновляем w на нового правого брата x
                }
                if ((w->left == nullptr || w->left->color == BLACK) && // Если левый потомок w черный или не существует
                    (w->right == nullptr || w->right->color == BLACK)) { // И правый потомок w черный или не существует
                    w->color = RED; // Цвет w - красный
                    x = x->parent; // Переходим к родителю x
                }
                else { // Если хотя бы один потомок w красный
                    if (w->right == nullptr || w->right->color == BLACK) { // Если правый потомок w черный или не существует
                        if (w->left != nullptr)
                            w->left->color = BLACK; // Цвет левого потомка w - черный
                        w->color = RED; // Цвет w - красный
                        rightRotate(w); // Выполняем правое вращение вокруг w
                        w = x->parent->right; // Обновляем w на нового правого брата x
                    }
                    w->color = x->parent->color; // Цвет w становится цветом родителя x
                    x->parent->color = BLACK; // Цвет родителя x - черный
                    if (w->right != nullptr)
                        w->right->color = BLACK; // Цвет правого потомка w - черный
                    leftRotate(x->parent); // Выполняем левое вращение вокруг родителя x
                    x = root; // Переходим к корню дерева
                }
            }
            else { // Если x - правый потомок своего родителя
                Node* w = x->parent->left; // w - левый брат x
                if (w->color == RED) { // Если w красный
                    w->color = BLACK; // Цвет w - черный
                    x->parent->color = RED; // Цвет родителя x - красный
                    rightRotate(x->parent); // Выполняем правое вращение вокруг родителя x
                    w = x->parent->left; // Обновляем w на нового левого брата x
                }
                if ((w->right == nullptr || w->right->color == BLACK) && // Если правый потомок w черный или не существует
                    (w->left == nullptr || w->left->color == BLACK)) { // И левый потомок w черный или не существует
                    w->color = RED; // Цвет w - красный
                    x = x->parent; // Переходим к родителю x
                }
                else { // Если хотя бы один потомок w красный
                    if (w->left == nullptr || w->left->color == BLACK) { // Если левый потомок w черный или не существует
                        if (w->right != nullptr)
                            w->right->color = BLACK; // Цвет правого потомка w - черный
                        w->color = RED; // Цвет w - красный
                        leftRotate(w); // Выполняем левое вращение вокруг w
                        w = x->parent->left; // Обновляем w на нового левого брата x
                    }
                    w->color = x->parent->color; // Цвет w становится цветом родителя x
                    x->parent->color = BLACK; // Цвет родителя x - черный
                    if (w->left != nullptr)
                        w->left->color = BLACK; // Цвет левого потомка w - черный
                    rightRotate(x->parent); // Выполняем правое вращение вокруг родителя x
                    x = root; // Переходим к корню дерева
                }
            }
        }
        if (x != nullptr) // Если x существует
            x->color = BLACK; // Цвет x - черный
    }

    // Функция поиска минимального узла в поддереве с корнем в узле node
    Node* minimum(Node* node) {
        while (node->left != nullptr) // Пока существует левый потомок node
            node = node->left; // Переходим к левому потомку node
        return node; // Возвращаем минимальный узел
    }

    // Функция для вывода структуры дерева
    void printHelper(Node* root, int space) {
        constexpr int COUNT = 0;
        if (root == nullptr) // Если узел не существует, выходим из функции
            return;
        space += COUNT; // Увеличиваем отступ для текущего уровня дерева
        printHelper(root->right, space); // Рекурсивный вызов для правого поддерева
        std::cout << std::endl; // Перевод строки
        for (int i = COUNT; i < space; i++) // Вывод отступов
            std::cout << " ";
        std::cout << root->data << "(" << ((root->color == RED) ? "RED" : "BLACK") << ")" << std::endl; // Вывод данных и цвета узла
        printHelper(root->left, space); // Рекурсивный вызов для левого поддерева
    }

public:
    RedBlackTree() : root(nullptr) {} // Конструктор класса, инициализирующий корень дерева как nullptr

    // Функция вставки нового узла с данными val в дерево
    void insert(int val) {
        Node* newNode = new Node(val); // Создаем новый узел с данными val
        Node* y = nullptr; // Указатель на родителя нового узла
        Node* x = root; // Указатель на текущий узел при поиске места для нового узла

        while (x != nullptr) { // Пока текущий узел существует
            y = x; // Обновляем родителя нового узла на текущий узел
            if (newNode->data < x->data) // Если данные нового узла меньше данных текущего узла
                x = x->left; // Переходим к левому потомку текущего узла
            else // Если данные нового узла больше или равны данным текущего узла
                x = x->right; // Переходим к правому потомку текущего узла
        }

        newNode->parent = y; // Устанавливаем родителя нового узла
        if (y == nullptr) // Если родитель нового узла не существует, значит новый узел будет корнем дерева
            root = newNode;
        else if (newNode->data < y->data) // Если данные нового узла меньше данных родителя
            y->left = newNode; // Новый узел становится левым потомком родителя
        else // Если данные нового узла больше или равны данным родителя
            y->right = newNode; // Новый узел становится правым потомком родителя

        fixInsert(newNode); // Восстанавливаем свойства красно-черного дерева
    }

    // Функция удаления узла с данными val из дерева
    void remove(int val) {
        Node* z = root; // Указатель на текущий узел при поиске удаляемого узла
        while (z != nullptr) { // Пока текущий узел существует
            if (val < z->data) // Если данные val меньше данных текущего узла
                z = z->left; // Переходим к левому потомку текущего узла
            else if (val > z->data) // Если данные val больше данных текущего узла
                z = z->right; // Переходим к правому потомку текущего узла
            else { // Если данные val равны данным текущего узла
                deleteNode(z); // Удаляем узел z
                return; // Завершаем выполнение функции
            }
        }
        std::cout << "Node with value " << val << " not found in the tree." << std::endl; // Вывод сообщения о том, что узел не найден
    }

    // Функция для вывода структуры дерева
    void printTree() {
        printHelper(root, 0); // Вызываем рекурсивную функцию вывода с начальным отступом 0
    }
};

int main() {

    RedBlackTree list;
    list.insert(50);
    list.insert(25);
    list.insert(76);
    list.insert(100);
    list.insert(79);
    list.insert(60);
    list.insert(30);
    list.insert(31);
    list.insert(32);
    list.insert(33);
    list.printTree();
        return 0;
}