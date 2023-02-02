#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        data = 0;
        next = NULL;
    }
    Node(char input)
    {
        this->data = input;
        this->next = NULL;
    }
};
class Stack
{
    Node *top;

public:
    Stack() { top = NULL; }
    void push(int input)
    {
        Node *temp = new Node(input);
        temp->data = input;
        temp->next = top;
        top = temp;
    };
    void pop()
    {
        Node *temp = new Node();
        if (top == NULL)
        {
            return;
        }
        else
        {
            temp = top;
            top = top->next;
            free(temp);
        }
    };
    bool isEmpty()
    {
        if (top == NULL)
        {
            return true;
        }
        return false;
    }
    char topValue()
    {
        return top->data;
    }
};
int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
string infixToPostfix(string infix)
{
    string postfix;
    Stack pfStack;
    for (int i = 0; i < infix.length(); i++)
    {
        char c = infix[i];
        if (c >= '0' && c <= '9')
        {
            postfix += c;
        }
        else if (c == '(')
        {
            pfStack.push('(');
        }
        else if (c == ')')
        {
            while (pfStack.topValue() != '(')
            {
                postfix += pfStack.topValue();
                pfStack.pop();
            }
            pfStack.pop();
        }
        else
        {
            while (!pfStack.isEmpty() && (precedence(c) <= precedence(pfStack.topValue())))
            {
                postfix += pfStack.topValue();
                pfStack.pop();
            }
            pfStack.push(c);
        }
    }
    while (!pfStack.isEmpty())
    {
        postfix += pfStack.topValue();
        pfStack.pop();
    }
    return postfix;
};
int postfixEvaluate(string postfix)
{
    Stack stack;
    string result;
    for (int i = 0; i < postfix.length(); i++)
    {
        char c = postfix[i];
        if (c >= '0' && c <= '9')
        {
            stack.push(c);
        }
        else
        {
            int a = stack.topValue() - '0';
            stack.pop();
            int b = stack.topValue() - '0';
            stack.pop();
            int operation;
            switch (c)
            {
            case '+':
                operation = b + a;
                stack.push(operation);
                break;
            case '-':
                operation = b - a;
                stack.push(operation);
                break;
            case '*':
                operation = b * a;
                stack.push(operation);
                break;
            case '/':
                operation = b / a;
                stack.push(operation);
                break;
            case '^':
                operation = pow(b, a);
                stack.push(operation);
                break;
            }
        }
    }
    return stack.topValue();
}
int main()
{
    string infix;
    cout << "Enter infix expression: ";
    cin >> infix;
    string postfix;
    postfix = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfix << endl;
    cout << "Postfix Evaluation: " << postfixEvaluate(postfix) << endl;
}
