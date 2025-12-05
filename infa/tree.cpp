#include <iostream>
// сложность log(n)

struct tree_elem{
     int data; // данные
     tree_elem * left; // указатель на левое поддерево
     tree_elem * right; // указатель на правое поддерево
     tree_elem(int value = 0){ // конструктор узла 
         left = nullptr; 
         right = nullptr;
         data = value;
     }
};


struct binary_tree{ // структура бинарного дерева
    tree_elem * root; // указатель на корень
    int size;

    binary_tree(int key){ // конструктор бинарного дерева
        root = new tree_elem(key); // выделение памяти и сохранение key (value)
        size = 1; // количество элементов в дереве
    }

    ~binary_tree(){
        delete_tree(root);
    }

    // удаление дерева
    void delete_tree(tree_elem * curr){
        if (curr != nullptr){ 
            delete_tree(curr->left); 
            delete_tree(curr->right);
            delete curr;
        }
    }

    void print(){
        print_tree(root);
        std::cout << std::endl;
    }
        
    void print_tree(tree_elem * curr){
        if (curr != nullptr){
            print_tree(curr->left);
            std::cout << curr->data << " ";
            print_tree(curr->right);
        }
    }

    // поиск значения по данным
    bool find(int key){
        tree_elem * curr = root; // сохранение корня
        while (curr && curr->data != key){
            // определяем в какую сторону искать (левые элементы меньше корня)
            if (curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr != nullptr;
    }   

    // вставка элемента по значению
    void insert(int key){
        tree_elem * curr = root;
        // пока не дошли до конца (nullptr) или не нашли нужные данные
        while (curr && curr->data != key){
            // определяем место нового элемента (вставка всегда вниз)
            if (curr->data > key && curr->left == nullptr){ // вставка ключа влево 
                curr->left = new tree_elem(key);
                ++size;
                return;
            }
            if (curr->data < key && curr->right == nullptr){ // вставка ключа вправо
                curr->right = new tree_elem(key);
                ++size;
                return;
            }
            // если не дошли до узла
            if (curr->data > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }    

    // удаление выбранного элемента
    void erase(int key)
    {
        tree_elem * curr = root; // указатель на корень
        tree_elem * parent = nullptr; // указатель на предыдущий узел
        while (curr && curr->data != key){
            parent = curr; // сохраняем указатель на предыдущий узел 
            // спускаемся ниже
            if (curr->data > key) 
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (!curr) // if (curr == nullptr)
            return;
        
        // удаление листа 
        if (curr->left == nullptr){
            // Вместо curr подвешивается его правое поддерево
            if (parent && parent->left == curr)
                parent->left = curr->right;
            if (parent && parent->right == curr)
                parent->right = curr->right;
            --size;
            delete curr;
            return;
        }
        if (curr->right == nullptr){
            // Вместо curr подвешивается его левое поддерево
            if (parent && parent->left == curr)
                parent->left = curr->left;
            if (parent && parent->right == curr)
                parent->right = curr->left;
            --size;
            delete curr;
            return;
        }
        // У элемента есть два потомка, тогда на место элемента поставим
        // наименьший элемент из его правого поддерева
        tree_elem * replace = curr->right;
        while (replace->left)
            replace = replace->left;
        int replace_value = replace->data; // запоминаем 
        erase(replace_value);
        curr->data = replace_value;
    }
};


// высота дерева (поиск самой длинной ветки) 
int tree_height(tree_elem* tree) {
    if (tree == nullptr)
        return 0;
    int left = tree_height(tree->left);
    int right = tree_height(tree->right);
    return std::max(left, right) + 1;
}

// сумма всех элементов дерева
int tree_sum(tree_elem* tree){
    int left_sum, right_sum;
    if(tree != nullptr){
        left_sum = (tree->left  != nullptr) ? tree_sum(tree->left)  : 0;
        right_sum = (tree->right != nullptr) ? tree_sum(tree->right) : 0;
        return left_sum + right_sum + tree->data;
    }
    return 0;
}

int tree_max(tree_elem* tree) { 
    if (tree == nullptr){
        std::cout << "Tree is empty" << std::endl;
        return 0;
    }
    tree_elem* tmp = tree;
    while (tmp->right != nullptr)
        tmp = tmp->right;
    return tmp->data;
}


int tree_second_max(tree_elem* tree)
{
    tree_elem* tmp = tree;
    while (tmp->right != nullptr)
    {
        if (tmp->right->right == nullptr)
            return tmp->data;
        tmp = tmp->right;
    }
    return tmp->left->data;
}

bool is_balanced(tree_elem* root) {
    if (root == nullptr) {
        return true;
    }

    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);

    if (std::abs(left_height - right_height) <= 1 && is_balanced(root->left) && is_balanced(root->right)) {
        return true;
    }
    else {
        return false;
    }
}

int tree_sum_3(tree_elem* tree) {
    int left_sum, right_sum;
    if (tree != nullptr) {
        left_sum = (tree->left != nullptr and tree->data % 3 == 0) ? tree_sum_3(tree->left) : 0;
        right_sum = (tree->right != nullptr and tree->data % 3 == 0) ? tree_sum_3(tree->right) : 0;
        return (tree->data % 3 == 0) ? left_sum + right_sum + tree->data : left_sum + right_sum;
    }
    return 0;
}

int tree_sum_3_2(tree_elem* tree) {
    int left_sum = 0, right_sum = 0;
    if (tree != nullptr) {
        left_sum = (tree->left != nullptr) ? tree_sum_3_2(tree->left) : 0;
        right_sum = (tree->right != nullptr) ? tree_sum_3_2(tree->right) : 0;
        return (tree->data % 3 == 0) ? left_sum + right_sum + tree->data : left_sum + right_sum;
    }
    return 0;
}

void traverser(tree_elem* node, int* count, double* sum) {
    if (node == nullptr) {
        return;
    }

    if (node->left != nullptr && node->right != nullptr) {
        *sum += node->data;
        (*count)++;
    }

    traverser(node->left, count, sum);
    traverser(node->right, count, sum);
}

double sum_3(tree_elem* tree) {
    if (tree == nullptr) {
        return 0.0;
    }

    double sum = 0;
    int count = 0;

    traverser(tree, &count, &sum);

    if (count == 0) {
        return 0.0;
    }

    return sum / count;
}

int main() {
    binary_tree tree(3);
    tree.insert(1);
    tree.insert(6);
    tree.insert(5);
    tree.insert(9);

    tree.print();

    std::cout << "balansed? " << (is_balanced(tree.root) ? "Yes" : "No") << std::endl;
    std::cout << "sum_3 = " << tree_sum_3_2(tree.root) << std::endl;
    std::cout << "f_2 = " << sum_3(tree.root) << std::endl;

    return 0;
}