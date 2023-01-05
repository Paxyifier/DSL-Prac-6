#include <iostream>

using namespace std;

class Node{
    protected:
        int data;
        Node *next;
    public:
        Node(int data){
            this->data = data;
        }
        Node(int data, Node *next){
            this->data = data;
            this->next = next;
        }
        Node(){
            this->data = 0;
            this->next = NULL;
        }
        void setData(int data){
            this->data = data;
        }
        int getData(){
            return this->data;
        }
        void setNext(Node *next){
            this->next = next;
        }
        Node *getNext(){
            return this->next;
        }
};
class Stack{
    protected:
            Node *top;
            int size;
        public:
            Stack(){
                this->top = NULL;
                this->size = 0;
            }
            void push(int data){
                Node *new_node = new Node(data);
                new_node->setNext(top);
                top = new_node;
                this->size++;
            }
            void pop(){
                if(top == NULL){
                    cout << "Stack Underflow" << endl;
                    return;
                }
                Node *temp = top;
                top = top->getNext();
                this->size--;
                delete temp;
            }
            void display(){
                if(top == NULL){
                    cout << "Stack is Empty" << endl;
                    return;
                }
                Node *temp = top;
                while(temp!= NULL){
                    cout << temp->getData() << " ";
                    temp = temp->getNext();
                }
                cout << endl;
            }
            int getSize(){
                return this->size;
            }
            void clear(){
                Node *temp = this->top;
                Node *prev = NULL;
                while(temp != NULL){
                    prev = temp;
                    temp = temp->getNext();
                    delete prev;
                }
                top = NULL;
                this->size = 0;
            }

};
class Postfix{
    protected:
        Stack  *stack;
    public:
        Postfix(){
            this->stack = new Stack();
        }
        
};

int main(){

}