#include <iostream>
using namespace std;

template <typename T>
struct node {
    T val;
    node *next;
    node(T x) : val(x), next(nullptr){}
};

template <typename T>
class simple_linked_list {
private:
    node<T> *head;
    int tamanho;
public:
    simple_linked_list(){head = nullptr; tamanho = 0;}

    T front() {
        if (head == nullptr) {return T();}
        return head->val;
    }

    T back() {
        if (head == nullptr){return T();}
        node<T> *temp = head;
        while (temp->next != nullptr) {temp = temp->next;}
        return temp->val;
    }

    void push_front(T val) {
        node<T> *temp = new node<T>(val);
        temp->next = head;
        head = temp;
        tamanho++;
    }

    void push_back(T val) {
        node<T> *new_nodo= new node<T>(val);
        if (head == nullptr){head = new_nodo;}
        else {
            node<T> *temp =head;
            while (temp->next != nullptr) {temp = temp->next;}
            temp->next = new_nodo;
        }
        tamanho++;
    }

    void pop_front() {
        if (head == nullptr){return;}
        node<T> *temp = head;
        head = temp->next;
        delete temp;
        tamanho--;
    }

    void pop_back(){
        if (head == nullptr){return;}
        if (head->next == nullptr){head = nullptr;}
        node<T> *temp = head;
        while (temp->next->next != nullptr){temp=temp->next;}
        delete temp->next;
        temp->next = nullptr;
        tamanho--;
    }

    T operator[](int position) const {
        node<T> *temp = head;
        for (int i = 0; i<position; i++) {
            temp = temp->next;
        }
        return temp->val;
    }

    bool empty() {
        if (head == nullptr) {return true;}
        else{return false;}
    }

    int size() const {
        return tamanho;
    }

    void clear() {
        if (head == nullptr){return;}
        node<T> *temp = head;
        while (temp->next != nullptr) {
            head = temp->next;
            delete temp;
            temp = head;
        }
        head = nullptr;
        delete temp;
        tamanho = 0;
    }

    void reverse() {
        node<T> *copia_head = head;
        node<T> *reverse_head = nullptr;
        while (copia_head != nullptr) {
            node<T> *next = copia_head->next; //El nodo siguiente guardado
            node<T> *ingresar = copia_head; //El nodo actual
            ingresar->next = reverse_head; //El que ingresa apunte al head (push_back)
            reverse_head = ingresar; //Actualizo el head
            copia_head = next; //Avanzo
        }
        head = reverse_head;
    }

    simple_linked_list merge(const simple_linked_list<T> &left,const simple_linked_list<T> &right) {
        simple_linked_list<T> result;
        int i=0, j=0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                result.push_back(left[i]);
                i++;
            } else {
                result.push_back(right[j]);
                j++;
            }
        }

        // Añadir lo que quede
        while (j == right.size() && i < left.size()) {
            result.push_back(left[i]);
            i++;
        }
        while (i == left.size() && j < right.size()) {
            result.push_back(right[j]);
            j++;
        }

        return result;
    }

    simple_linked_list merge_sort(simple_linked_list<T> &list){
        if (list.size()<=1){return list;}

        int mid = list.size() /2;

        simple_linked_list<T> left;
        simple_linked_list<T> right;

        for (int i = 0; i<mid; i++) {left.push_back(list[i]);}
        for (int i = mid; i<list.size(); i++) {right.push_back(list[i]);}

        return merge(merge_sort(left), merge_sort(right));
    }

    void sort() {
        simple_linked_list<T> copia = merge_sort(*this);
        *this = copia;
    }

    void print() {
        if (head==nullptr){return;}
        node<T> *temp = head;
        cout<<"List: {"<<temp->val;
        temp = temp->next;
        while (temp) {
            cout<<", "<<temp->val;
            temp = temp->next;
        }
        cout<<"}"<<endl;
    }

};

int main() {
    simple_linked_list<int> list;

    //VOID PUSH FRONT
    list.push_front(2);
    list.push_back(1);
    list.push_back(30);
    list.push_back(5);

    //VOID PUSH BACK
    list.push_back(44);
    list.push_back(22);
    list.push_back(6);
    list.push_back(9);
    list.push_back(7);
    list.push_back(10);

    //VOID PRINT
    list.print();


    //T FRONT
    cout<<endl<<"T FRONT: "<<list.front()<<endl;

    //T BACK
    cout<<endl<<"T BACK: "<<list.back()<<endl;

    //INT SIZE
    cout<<endl<<"INT SIZE: "<<list.size()<<endl;

    //VOID POP FRONT
    cout<<endl<<"VOID POP FRONT"<<endl;
    list.pop_front();

    //VOID POP BACK
    cout<<"VOID POP BACK"<<endl<<endl;
    list.pop_back();

    //VOID PRINT
    list.print();

    //T OPERATOR[]
    cout<<endl<<"T OPERATOR[3]: "<<list[3]<<endl;

    //BOOL EMPTY
    cout<<endl<<"BOOL EMPTY: "<<list.empty()<<endl;

    //VOID REVERSE
    cout<<endl<<"VOID REVERSE"<<endl;
    list.print();
    list.reverse();
    list.print();

    //VOID SORT
    cout<<endl<<"VOID SORT"<<endl;
    list.print();
    list.sort();
    list.print();

    //VOID CLEAR
    cout<<endl<<"VOID CLEAR"<<endl;
    list.clear();
    cout<<"BOOL EMPTY: "<<list.empty()<<endl;

    return 0;
}