#include <iostream>

struct Node
{
    double data; // поле данных
    struct Node* next; // указатель на следующий элемент
    struct Node* prev; // указатель на предыдущий элемент
    Node(double value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

struct TwoLinkedList {
    Node* first;
    Node* last;

    TwoLinkedList() {
        first = nullptr;
        last = nullptr;
    }

    Node* push_front(double data) {
        Node* node = new Node(data);

        node->next = first;
        if (first != nullptr)
            first->prev = node;
        if (last == nullptr)
            last = node;
        first = node;

        return node;
    }


    Node* push_back(double data) {
        Node* node = new Node(data);

        node->prev = last;
        if (last != nullptr)
            last->next = node;
        if (first == nullptr)
            first = node;
        last = node;

        return node;
    }

    void pop_front() {
        if (first == nullptr) return;

        Node* node = first->next;
        if (node != nullptr)
            node->prev = nullptr;
        else
            last = nullptr;

        delete first;
        first = node;
    }


    void pop_back() {
        if (last == nullptr) return;

        Node* node = last->prev;
        if (node != nullptr)
            node->next = nullptr;
        else
            first = nullptr;

        delete last;
        last = node;
    }

    Node* getAt(int index) {
        Node* node = first;
        int n = 0;

        while (n != index) {
            if (node == nullptr) return nullptr;
            node = node->next;
            n++;
        }

        return node;
    }

    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* insert(int index, double data) {
        Node* right = getAt(index);
        if (right == nullptr)
            return push_back(data);

        Node* left = right->prev;
        if (left == nullptr)
            return push_front(data);

        Node* node = new Node(data);

        node->prev = left;
        node->next = right;
        left->next = node;
        right->prev = node;

        return node;
    }

    void erase(int index) {
        Node* node = getAt(index); //node[index]
        if (node == nullptr)
            return;

        if (node->prev == nullptr) {
            pop_front();
            return;
        }

        if (node->next == nullptr) {
            pop_back();
            return;
        }

        Node* left = node->prev;
        Node* right = node->next;
        left->next = right;
        right->prev = left;

        delete node;
    }

    void print(bool reverse = false) {
        if (!reverse) {
            for (Node* node = first; node != nullptr; node = node->next)
                std::cout << node->data << " ";
            std::cout << std::endl;
        }
        else {
            for (Node* node = last; node != nullptr; node = node->prev)
                std::cout << node->data << " ";
            std::cout << std::endl;
        }
    }

    void count_element() {
        int n = 0;
        Node* node = first;
        while (node != nullptr) {
            n++;
            node = node->next;
        }
        std::cout << n << std::endl;
        return;
    }

    void if_number(double k) {
        for (Node* node = last; node != nullptr; node = node->prev) {
            if (node->data == k) {
                std::cout << "YES" << std::endl;
                return;
            }
        }
        std::cout << "NO" << std::endl;
    }

    void min_znach() {
        int min = last->data;
        for (Node* node = last; node != nullptr; node = node->prev) {

            if (node->data < min) {
                min = node->data;
            }

        }
        std::cout << min << std::endl;
        return;
    }

    void refactor(int k, int znach) {
        Node* node = getAt(k);
        if (node == nullptr) return;
        node->data = znach;
        return;
    }

    bool is_empty() {
        return first == nullptr;
    }

    void swap(int a, int b) {
        if (a == b) return;

        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }

        if (a == 0 and getAt(b) == nullptr) {
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);

            Node* last_2 = getAt(b - 1);

            Node* next_1 = getAt(a + 1);

            node_2->next = next_1;
            node_2->prev = nullptr;
            next_1->prev = node_2;
            first = node_2;

            last_2->next = node_1;
            node_1->next = nullptr;
            node_1->prev = last_2;
            last = node_1;
        }
        else if (a == 0 and b == 1) {
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);

            Node* next_2 = getAt(b + 1);

            first = node_2;
            node_2->prev = nullptr;
            node_2->next = node_1;
            node_1->prev = node_2;

            node_1->next = next_2;
            next_2->prev = node_1;
        }
        else if (a == 0) {
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);

            Node* last_2 = getAt(b - 1);

            Node* next_1 = getAt(a + 1);
            Node* next_2 = getAt(b + 1);

            first = node_2;
            node_2->prev = nullptr;
            node_2->next = next_1;
            next_1->prev = node_2;

            last_2->next = node_1;
            node_1->prev = last_2;
            next_2->prev = node_1;
            node_1->next = next_2;
        }
        else if (getAt(b) == nullptr) {
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);

            Node* last_1 = getAt(a - 1);
            Node* last_2 = getAt(b - 1);

            Node* next_1 = getAt(a + 1);
            Node* next_2 = nullptr;

            last_1->next = node_2;
            node_2->prev = last_1;
            node_2->next = next_1;
            next_1->prev = node_2;

            last_2->next = node_1;
            node_1->prev = last_2;
            node_1->next = next_2;

            last = node_1;
        }
        else if (a + 1 == b) {
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);

            Node* last_1 = getAt(a - 1);

            Node* next_2 = getAt(b + 1);

            last_1->next = node_2;
            node_2->prev = last_1;
            node_2->next = node_1;
            node_1->prev = node_2;
            node_1->next = next_2;
            next_2->prev = node_1;
        }
        else {
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);

            Node* last_1 = getAt(a - 1);
            Node* last_2 = getAt(b - 1);

            Node* next_1 = getAt(a + 1);
            Node* next_2 = getAt(b + 1);

            last_1->next = node_2;
            node_2->prev = last_1;
            node_2->next = next_1;
            next_1->prev = node_2;

            last_2->next = node_1;
            node_1->prev = last_2;
            node_1->next = next_2;
            next_2->prev = node_1;
        }

        return;
    }

    void sort() {
        int size = 0;
        for (Node* node = last; node != nullptr; node = node->prev) {
            size++;
        }

        for (int i = size; i > 0; i--) {
            for (int j = size - 1; j > 0; j--) {

                if (getAt(j - 1)->data > getAt(j)->data) {
                    swap(j - 1, j);
                }

            }
        }
        return;
    }
    
    void block_refactor(int a, int b, int c) {
    Node* i = getAt(a);
    Node* j = getAt(b);
    Node* k = getAt(c);
    
    Node* i_prev = i->prev;
    Node* j_next = j->next;
    Node* k_prev = k->prev;
    Node* k_next = k->next;

    if (i_prev != nullptr) {
        i_prev->next = j_next;
    }
    else {
        first = j_next;
    }

    if (j_next != nullptr) {
        j_next->prev = i_prev;
    }
    else {
        last = i_prev;
    }

    if (k_next != nullptr) {
        k_next->prev = j;
    }

    j->next = k_next;
    i->prev = k;
    k->next = i;
    
    if (i == first) {
        first = j_next;
    }
    if (j == last) {
        last = i_prev;
    }
}
    
    
    
    ~TwoLinkedList() {
        while (first != nullptr)
            pop_front();
    }


};

int main() {
    TwoLinkedList my_list;
    std::cout << my_list.is_empty() << std::endl;
    my_list.push_back(0);
    my_list.push_back(1);
    my_list.push_front(2);
    my_list.push_front(3);
    my_list.push_back(4);
    my_list.push_back(5);
    my_list.push_front(6);
    my_list.push_back(7);
    my_list.push_front(8);
    my_list.push_back(9);
    my_list.print();
    my_list.if_number(11);
    my_list.min_znach();
    my_list.refactor(0, 5);
    my_list.print();
    my_list.swap(0, 1);
    my_list.print();
    my_list.sort();
    my_list.print();
    return 0;
}