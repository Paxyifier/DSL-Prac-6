#include <iostream>
#include <string>
#include <math.h>

using namespace std;
template <typename T>
class Node{
    protected:
        T data;
        Node *next;
    public:
        Node(T data){
            this->data = data;
        }
        Node(T data, Node *next){
            this->data = data;
            this->next = next;
        }
        void setData(T data){
            this->data = data;
        }
        T getData(){
            return this->data;
        }
        void setNext(Node *next){
            this->next = next;
        }
        Node *getNext(){
            return this->next;
        }
};

template <typename T>
class Stack{
    protected:
            Node<T> *top;
            int size;
        public:
            Stack(){
                this->top = NULL;
                this->size = 0;
            }
            void push(char data){
                Node *new_node = new Node(data);
                new_node->setNext(top);
                top = new_node;
                this->size++;
            }
            char pop(){
                if(top == NULL){
                    cout << "Stack Underflow" << endl;
                    return '`';
                }
                Node *temp = top;
                char chr = this->top->getData();
                top = top->getNext();
                this->size--;
                delete temp;
                return chr;
            }
            char head() {
                if(top == NULL){
                    // cout << "Stack Underflow" << endl;
                    return NULL;
                }
                return top->getData();
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
        string output;
        Stack<char>  *stack;
        Stack<char>  *stack2;
        string vars;
        int precedence(char op){
            switch(op){
                case '+':
                    return 0;
                case '-':
                    return 1;
                case '*':
                    return 2;
                case '/':
                    return 3;
                case '^':
                    return 4;
                case '%':
                    return 5;
                default:
                    return -1;
            }
        }
        void popTillPrecedence(char op){
            while(precedence(this->stack->head())>precedence(op) && this->stack->head() != NULL){
                this->output.append(1,this->stack->pop());
            }
        }
    public:
        Postfix(string infix){
            for(int i=0; i<infix.size(); i++){
                switch(infix[i]){
                    case '(':
                        this->stack->push('(');
                        break;
                    case ')':
                        while(this->stack->head() != '(' && this->stack->head() != NULL){
                            char c = this->stack->pop();
                            output.append(1,c);
                        }
                        this->stack->pop();
                        break;
                    
                    case '[':
                        this->stack->push('(');
                        break;
                    case ']':
                        while(this->stack->head() != '[' && this->stack->head() != NULL){
                            char c = this->stack->pop();
                            output.append(1,c);
                        }
                        this->stack->pop();
                        break;
                    
                    case '{':
                        this->stack->push('(');
                        break;
                    case '}':
                        while(this->stack->head() != '}' && this->stack->head() != NULL){
                            char c = this->stack->pop();
                            output.append(1,c);
                        }
                        this->stack->pop();
                        break;
                    case '+':
                        popTillPrecedence(infix[i]);
                        this->stack->push('+');
                        break;
                    case '-':
                        popTillPrecedence(infix[i]);
                        this->stack->push('-');
                        break;
                    case '*':
                        popTillPrecedence(infix[i]);
                        this->stack->push('*');
                        break;
                    case '/':
                        popTillPrecedence(infix[i]);
                        this->stack->push('/');
                        break;
                    case '^':
                        popTillPrecedence(infix[i]);
                        this->stack->push('^');
                        break;
                    case '%':
                        this->stack->push('%');
                        break;
                    default:
                        this->output.append(1,infix[i]);
                        this->vars.append(1,infix[i]);
                        break;
                }
            }
            if (this->stack->getSize() != 0) {
                cout << "Equation is not balanced.\n";
                exit(0);
            }
        }
        void display(){
            cout<<output<<endl;
        }
        string toString(){
            return this->output;
        }
        string getVars(){
            return this->vars;
        }
        int findValue(int arr[], char c){
            for(int i=0; i<this->vars.size(); i++){
                if(this->vars[i]==c){
                    return i;
                }
            }
            return -1;
        }
        char returnUnusedVar(int arr[]){
            char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIKJLMNOPQRSTUVWXYZ";
            for (int i = 0; i< this->vars.size(); i++){
                if (findValue(arr,characters[i])){
                    return characters[i];
                }
            }
            return '!';
        }
        int evaluate(){
            int arr[this->vars.size()*2];
            int op1,op2,rslt;
            char c;
            for(int i = 0; i < this->vars.size(); i ++){
                cout << "Value for " << this->vars[i] << " : ";
                cin >> arr[i];
            }
            for(int i = 0; i < this->output.size(); i ++){
                switch (output[i]){
                {
                case '+':
                    op1 = findValue(arr,this->stack->pop());
                    op2 = findValue(arr,this->stack->pop());
                    rslt = op1+op2;
                    c = *to_string(rslt).c_str();
                    this->stack->push(c);
                    break;
                case '-':
                    op1 = findValue(arr,this->stack->pop());
                    op2 = findValue(arr,this->stack->pop());
                    rslt = op1-op2;
                    c = *to_string(rslt).c_str();
                    this->stack->push(c);
                    break;
                case '*':
                    op1 = findValue(arr,this->stack->pop());
                    op2 = findValue(arr,this->stack->pop());
                    rslt = op1*op2;
                    c = *to_string(rslt).c_str();
                    this->stack->push(c);
                    break;
                case '/':
                    op1 = findValue(arr,this->stack->pop());
                    op2 = findValue(arr,this->stack->pop());
                    rslt = op1/op2;
                    c = *to_string(rslt).c_str();
                    this->stack->push(c);
                    break;
                case '^':
                    op1 = findValue(arr,this->stack->pop());
                    op2 = findValue(arr,this->stack->pop());
                    rslt = pow(op1,op2);
                    c = *to_string(rslt).c_str();
                    this->stack->push(c);
                    break;
                case '%':
                    op1 = findValue(arr,this->stack->pop());
                    op2 = findValue(arr,this->stack->pop());
                    rslt = op1%op2;
                    c = *to_string(rslt).c_str();
                    this->stack->push(c);
                    break;
                default:
                    break;
                }
                return atoi((const char*)this->stack->pop());
                }
            }
        }
};

int main(){
    string str = "(a/b+c/d-e*f)";
    Postfix pf = Postfix(str);
    pf.display();
    // ABC-/D*E+
    cout << pf.getVars()<<endl;  
    cout << pf.evaluate()<<endl;  
    return 0;
    //::TODO evaluation
}