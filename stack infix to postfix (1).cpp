
#include <iostream>
#include <string>
#define maxSize 20
using namespace std;
template <class KeyType> class stack {
private:
    KeyType* item;
    int top;
public:
    stack();
    ~stack();
    bool IsFull();
    bool IsEmpty();
    void Push(KeyType& x);
    KeyType pop();
    KeyType topElement();
};

template <class KeyType>  stack<KeyType>::stack() {
    item = new KeyType[maxSize];
    top = -1;
}
template <class KeyType>  stack<KeyType>::~stack() {
    delete[] item;
    cout << endl;
    cout << "end :)))";
}

template <class KeyType> void stack<KeyType>::Push(KeyType& x) {
    if (IsFull()) {

        cout << "Stack is full\n";
    }

    item[++top] = x;
}
template <class KeyType> bool stack<KeyType>::IsEmpty()
{
    if (top == -1)
        return true;
    else
        return false;
}
template <class KeyType> bool stack<KeyType>::IsFull()
{
    if (top == (maxSize - 1))
        return true;
    else

        return false;
}

template <class KeyType> KeyType stack<KeyType>::pop()
{
    if (IsEmpty()) {
        cout << "stack is epmty";
    }
    else {
        KeyType popped_element = item[top];

        top--;

        return popped_element;
    }

}
template <class KeyType> KeyType stack<KeyType>::topElement()
{

    KeyType top_element = item[top];

    return top_element;
}

string getInfix();

void convertinfixToPostfix(string infix);

void postfixToInfix(string postfix);

int main()
{
    convertinfixToPostfix(getInfix());

}

string getInfix()
{
    string infix;
    cout << "Please enter infix phrase : ";
    cin >> infix;
    return infix;
}

void convertinfixToPostfix(string infix) {

    string postfix = "";
    stack<char> s;

    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z' || infix[i] >= '0' && infix[i] <= '9') {
            postfix += infix[i];
        }
        else if (infix[i] == '(') {
            s.Push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (s.topElement() != '(') {//rrrrrrrr
                postfix += s.topElement();
                s.pop();
            }
            s.pop();
        }
        else {
            s.Push(infix[i]);
        }
    }

    while (!s.IsEmpty()) {
        postfix += s.topElement();
        s.pop();
    }
    cout << "\nThe Postfix is : " << postfix << "\n";
    postfixToInfix(postfix);
}

bool isOperator(char operatorr)
{
    if (operatorr == '-' || operatorr == '+' || operatorr == '*' || operatorr == '/')
    {
        return true;
    }
    else
        return false;
}

bool isOperand(char operand)
{
    if (operand >= 'a' && operand <= 'z' || operand >= 'A' && operand <= 'Z' || operand >= '0' && operand <= '9')
        return true;
    else
        return false;
}



////////////
void postfixToInfix(string postfix)
{
    stack<string> s;
    for (int i = 0; i < postfix.size(); i++)
    {
        if (isOperand(postfix[i]))
        {
            string op(1, postfix[i]);
            s.Push(op);
        }
        else {
            string op1 = s.topElement();
            s.pop();
            string op2 = s.topElement();
            s.pop();
            string t = "(" + op2 + postfix[i] + op1 + ")";
            s.Push(t);
        }
    }
    cout << s.topElement();
}