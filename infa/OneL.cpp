#include <iostream>

struct Node {
    int value;
    Node* next;
    Node(int x){
        value = x;
        next = nullptr;
    }
};

struct OneLinkedList {
    Node* first;
    Node* last;
    OneLinkedList(){
    first = nullptr;
    last = nullptr;
    }


    void push_back(int value) {
        Node* node = new Node(value);
        if (first == nullptr) first = node;
        if (last != nullptr) last->next = node;
        last = node;
    }


    void push_front(int value) {
        Node* node = new Node(value);
        node->next = first;
        first = node;
        if (last == nullptr) last = node;
    }


    void print(){
        if (first == nullptr) return;
        for (Node* node = first; node != nullptr; node = node->next) {
            std::cout << node->value << " ";
        }
        std::cout << std::endl;
    }


    void pop_front() {
        if (first == nullptr) return;
        if (first == last) {
                 delete last;
                 first = last = nullptr;
                 return;
        }
        Node* node = first;
        first = node->next; // first = first->next; 
        delete node;
    }


    void pop_back() {
        if (last == nullptr) return;
        if (first == last) {
                 delete last;
                 first = last = nullptr;
                 return;
        }

        Node* node = first;
        for (; node->next != last; node = node->next);
        node->next = nullptr;
        delete last;
        last = node;
    }


    Node* getAt(int k) {
        if (k < 0) return nullptr;

        Node* node = first;
        int n = 0;
        while (node != nullptr and n != k and node->next != nullptr) {
                 node = node->next;
                 n++;
        }
        return (n == k) ? node : nullptr;
    }


    void insert(int k, int value) {
        Node* left = getAt(k);
        if (left == nullptr) return;

        Node* right = left->next;
        Node* node = new Node(value);
        
        left->next = node;
        node->next = right;
        if (right == nullptr) last = node;
    }


    void erase(int k) {
        if (k < 0) return;
        if (k == 0) {
                pop_front();
                return;
        }

        Node* left = getAt(k - 1);
        Node* node = left->next;
        if (node == nullptr) return;

        Node* right = node->next;
        left->next = right;
        if (node == last) last = left;
        delete node;
    }


    bool is_empty(){
        return first == nullptr;
    }
    
    
    
    // Homework
    
    
    
    void count_element(){
        int n = 0;
        
        for(Node* node = first; node != nullptr; node = node->next){
            n++;
        }
        
        std::cout << n << std::endl;
        return;
    }
    
    void if_data(int k){
        Node* node = first;
        for(; node != nullptr; node = node->next){
            if (node->value == k){ 
                std::cout << 1 << std::endl;
                return;
            }
        }
        std::cout << 0 << std::endl;
        return;
    }
    
    void max_data(){
        int max_data = first->value;
        Node* max_data_ukazatel = first;
        
        for(Node* node = first; node != nullptr; node = node->next){
            if (node->value > max_data){
                max_data = node->value;
                max_data_ukazatel = node;
            }
        }
        std::cout << max_data_ukazatel << std::endl;
        return;
    }
    
    void refactor(int k, int znach){
        Node* node = getAt(k);
        if (node == nullptr) return;
        node->value = znach;
        return;
    }
    
    void del_elem(int k){
        int i = -1;
        
        for(Node* node = first; node != nullptr; node = node->next) {
            i++;
            if(node->value == k){
                erase(i);
                i--;
            }
        }
        
        if(last->value == k) pop_back();
        
        return;
    }
    
    void swap(int a, int b){
        if (a == b) return;
        
        if (a > b){
            int tmp = a;
            a = b;
            b = tmp;
        }
        
        if(a == 0 and getAt(b) == nullptr){
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);
            
            Node* last_2 = getAt(b - 1);
            
            Node* next_1 = getAt(a + 1);
            Node* next_2 = nullptr;
            
            first = node_2;
            node_2->next = next_1;
            
            last_2->next = node_1;
            node_1->next = next_2;
            last = node_1;
        }
        else if (a == 0 and b == 1){
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);
            
            Node* next_2 = getAt(b + 1);
            
            first = node_2;
            node_2->next = node_1;
            node_1->next = next_2;
        }
        else if(a == 0){
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);
            
            Node* last_2 = getAt(b - 1);
            
            Node* next_1 = getAt(a + 1);
            Node* next_2 = getAt(b + 1);
            
            first = node_2;
            node_2->next = next_1;
            
            last_2->next = node_1;
            node_1->next = next_2;
        }
        else if (getAt(b) == nullptr){
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);
            
            Node* last_1 = getAt(a - 1);
            Node* last_2 = getAt(b - 1);
            
            Node* next_1 = getAt(a + 1);
            
            last_1->next = node_2;
            node_2->next = next_1;
            
            last_2->next = node_1;
            node_1->next = nullptr;
            
            last = node_1;
        }
        else if (a + 1 == b){
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);
            
            Node* last_1 = getAt(a - 1);
            
            Node* next_2 = getAt(b + 1);
            
            last_1->next = node_2;
            node_2->next = node_1;
            node_1->next = next_2;
        }
        else{
            Node* node_1 = getAt(a);
            Node* node_2 = getAt(b);
            
            Node* last_1 = getAt(a - 1);
            Node* last_2 = getAt(b - 1);
            
            Node* next_1 = getAt(a + 1);
            Node* next_2 = getAt(b + 1);
            
            last_1->next = node_2;
            node_2->next = next_1;
            
            last_2->next = node_1;
            node_1->next = next_2;
        }
        
        return;
    }
    void sort(){
        int size = 0;
        for (Node* node = first; node != nullptr; node = node->next) {
            size++;
        }
        
        for (int i = size; i > 0; i--) {
            for (int j = size - 1; j > 0; j--) {
                
                if (getAt(j - 1)->value > getAt(j)->value){
                    swap(j - 1, j);
                }
                
            }
        }
        return;
    }

    void deleted_povt() {
        if (first == nullptr) {
            return;
        }

        Node* node = first;
        while (node->next != nullptr) {
            if (node->value == node->next->value) {
                Node* sled = node->next;
                node->next = node->next->next;
                if (sled == last) {
                    last = node;
                }
                delete sled;
            }
            else {
                node = node->next;
            }
        }
        return;
    }
    
    ~OneLinkedList() {
        while (first != nullptr)  pop_front();
}
};

int main(){
    OneLinkedList my_list;
    std::cout << my_list.is_empty() << std::endl;
    /*
    my_list.push_back(9);
    my_list.push_back(8);
    my_list.push_back(7);
    my_list.push_back(6);
    my_list.push_back(5);
    my_list.push_back(4);
    my_list.push_back(3);
    my_list.push_back(2);
    my_list.push_back(1);
    my_list.push_back(0);
    my_list.print();
    my_list.count_element();
    my_list.if_data(4);
    my_list.max_data();
    my_list.refactor(5, 5);
    my_list.print();
    my_list.del_elem(2);
    my_list.swap(3, 8);
    my_list.print();
    my_list.swap(8, 3);
    my_list.print();
    my_list.sort();
    my_list.print();
    */
    my_list.push_back(3);
    my_list.push_back(3);
    my_list.push_back(3);
    my_list.push_back(1);
    my_list.push_back(10);
    my_list.push_back(3);
    my_list.push_back(3);
    my_list.push_back(8);
    my_list.push_back(3);
    my_list.push_back(8);
    my_list.push_back(3);
    my_list.push_back(9);
    my_list.push_back(9);
    my_list.push_back(9);
    my_list.push_back(9);
    my_list.sort();
    my_list.print();
    my_list.deleted_povt();
    my_list.print();

    return 0;
}