#include <iostream>

enum Color { RED, BLACK };

// Структура узла дерева для мнимых частей
struct ImaginaryNode {
    int data;       // Мнимая часть числа
    Color color;    // Цвет узла
    ImaginaryNode* left;     // Указатель на левого потомка
    ImaginaryNode* right;    // Указатель на правого потомка
    ImaginaryNode* parent;   // Указатель на родительский узел
    explicit ImaginaryNode(int val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Класс красно-черного дерева для мнимых частей
class ImaginaryPartTree {

    ImaginaryNode* root; // Указатель на корень дерева

    // Левое вращение поддерева с корнем в узле x
    void leftRotate(ImaginaryNode* x) {
        if (x == nullptr || x->right == nullptr) return;
        ImaginaryNode* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Правое вращение поддерева с корнем в узле y
    void rightRotate(ImaginaryNode* y) {
        if (y == nullptr || y->left == nullptr) return;
        ImaginaryNode* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    // Функция для восстановления свойств красно-черного дерева после вставки узла z
    void fixInsert(ImaginaryNode* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                ImaginaryNode* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                ImaginaryNode* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Функция удаления узла z из дерева
    void deleteNode(ImaginaryNode* z) {
        if (z == nullptr) return;
        ImaginaryNode* y = z;
        ImaginaryNode* x = nullptr;
        Color y_original_color = y->color;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            }
            else {
                if (x != nullptr) x->parent = y->parent;
                transplant(y, y->right);
                if (y->right != nullptr) y->right->parent = y;
                y->right = z->right;
                if (y->right != nullptr) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == BLACK && x != nullptr) fixDelete(x);
        delete z;
    }

    // Функция восстановления свойств красно-черного дерева после удаления узла x
    void fixDelete(ImaginaryNode* x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                ImaginaryNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr) w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                ImaginaryNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK;
    }

    // Функция поиска минимального узла в поддереве с корнем в узле node
    ImaginaryNode* minimum(ImaginaryNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Функция замены одного поддерева другим в процессе удаления узла
    void transplant(ImaginaryNode* u, ImaginaryNode* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr) v->parent = u->parent;
    }

public:
    ImaginaryPartTree() : root(nullptr) {}

    // Функция вставки нового узла с данными val в дерево
    void insert(int val) {
        ImaginaryNode* newNode = new ImaginaryNode(val);
        ImaginaryNode* y = nullptr;
        ImaginaryNode* x = root;
        while (x != nullptr) {
            y = x;
            if (newNode->data < x->data) x = x->left;
            else x = x->right;
        }
        newNode->parent = y;
        if (y == nullptr) root = newNode;
        else if (newNode->data < y->data) y->left = newNode;
        else y->right = newNode;
        fixInsert(newNode);
    }

    // Функция удаления узла с данными val из дерева
    void remove(int val) {
        ImaginaryNode* z = root;
        while (z != nullptr) {
            if (val < z->data) z = z->left;
            else if (val > z->data) z = z->right;
            else {
                deleteNode(z);
                return;
            }
        }
        std::cout << "Node with value " << val << " not found in the tree." << std::endl;
    }

    // Функция для проверки, пусто ли дерево
    bool isEmpty() const {
        return root == nullptr;
    }

    // Функция для вывода структуры дерева
    void printTree() {
        printHelper(root, 0);
    }

    void printHelper(ImaginaryNode* root, int space) {
        constexpr int COUNT = 0;
        if (root == nullptr) return;
        space += COUNT;
        printHelper(root->right, space);;
        for (int i = COUNT; i < space; i++)
            std::cout << " ";
        std::cout << root->data << "i(" << ((root->color == RED) ? "RED" : "BLACK") << ")";
        printHelper(root->left, space);
    }
};

// Структура узла дерева для комплексных чисел
struct ComplexNode {
    int real;       // Действительная часть числа
    Color color;    // Цвет узла
    ComplexNode* left;     // Указатель на левого потомка
    ComplexNode* right;    // Указатель на правого потомка
    ComplexNode* parent;   // Указатель на родительский узел
    ImaginaryPartTree imaginaryParts; // Дерево мнимых частей чисел с одинаковой действительной частью
    explicit ComplexNode(int realVal) : real(realVal), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Класс красно-черного дерева для комплексных чисел
class ComplexNumberTree {

    ComplexNode* root; // Указатель на корень дерева

    // Левое вращение поддерева с корнем в узле x
    void leftRotate(ComplexNode* x) {
        if (x == nullptr || x->right == nullptr) return;
        ComplexNode* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Правое вращение поддерева с корнем в узле y
    void rightRotate(ComplexNode* y) {
        if (y == nullptr || y->left == nullptr) return;
        ComplexNode* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    // Функция для восстановления свойств красно-черного дерева после вставки узла z
    void fixInsert(ComplexNode* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                ComplexNode* y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else {
                ComplexNode* y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Функция удаления узла z из дерева
    void deleteNode(ComplexNode* z) {
        if (z == nullptr) return;
        ComplexNode* y = z;
        ComplexNode* x = nullptr;
        Color y_original_color = y->color;
        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            }
            else {
                if (x != nullptr) x->parent = y->parent;
                transplant(y, y->right);
                if (y->right != nullptr) y->right->parent = y;
                y->right = z->right;
                if (y->right != nullptr) y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) y->left->parent = y;
            y->color = z->color;
            y->imaginaryParts = z->imaginaryParts;
        }
        if (y_original_color == BLACK && x != nullptr) fixDelete(x);
        delete z;
    }

    // Функция восстановления свойств красно-черного дерева после удаления узла x
    void fixDelete(ComplexNode* x) {
        while (x != root && x != nullptr && x->color == BLACK) {
            if (x == x->parent->left) {
                ComplexNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) &&
                    (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr) w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else {
                ComplexNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) &&
                    (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK;
    }

    // Функция поиска минимального узла в поддереве с корнем в узле node
    ComplexNode* minimum(ComplexNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Функция замены одного поддерева другим в процессе удаления узла
    void transplant(ComplexNode* u, ComplexNode* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr) v->parent = u->parent;
    }

public:
    ComplexNumberTree() : root(nullptr) {}

    // Функция вставки нового узла с данными val в дерево
    void insert(int realVal, int imagVal) {
        ComplexNode* newNode = new ComplexNode(realVal);
        ComplexNode* y = nullptr;
        ComplexNode* x = root;
        while (x != nullptr) {
            y = x;
            if (newNode->real < x->real) x = x->left;
            else x = x->right;
        }
        newNode->parent = y;
        if (y == nullptr) root = newNode;
        else if (newNode->real < y->real) y->left = newNode;
        else y->right = newNode;
        newNode->imaginaryParts.insert(imagVal);
        fixInsert(newNode);
    }

    // Функция удаления узла с данными val из дерева
    void remove(int realVal, int imagVal) {
        ComplexNode* z = root;
        while (z != nullptr) {
            if (realVal < z->real) z = z->left;
            else if (realVal > z->real) z = z->right;
            else {
                z->imaginaryParts.remove(imagVal);
                if (z->imaginaryParts.isEmpty()) {
                    deleteNode(z);
                }
                return;
            }
        }
        std::cout << "Node with value " << realVal << "+" << imagVal << "i not found in the tree." << std::endl;
    }

    // Функция для вывода структуры дерева
    void printTree() {
        printHelper(root, 0);
    }

    void printHelper(ComplexNode* root, int space) {
        constexpr int COUNT = 1;
        if (root == nullptr) return;
        space += COUNT;
        printHelper(root->right, space);
        for (int i = COUNT; i < space; i++)
            std::cout << " ";
        std::cout << root->real << "+(";
        root->imaginaryParts.printTree();
        std::cout << ")(" << ((root->color == RED) ? "RED" : "BLACK") << ")" << std::endl;
        printHelper(root->left, space);
    }
};

int main() {
    ComplexNumberTree list;
    list.insert(2, 3);
    list.insert(2, -4);
    list.insert(5, 68);
    list.insert(5, 7);
    list.insert(1, 2);
    list.insert(1, -1);
    list.printTree();
    std::cout << std::endl;
    list.remove(5, 68);
    list.printTree();
    return 0;
}