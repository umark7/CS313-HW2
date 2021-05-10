// 2. Write a prefix stack and show how it works (in main).

#include <iostream> 
#include <iomanip>
#include <string>
#include <algorithm>
#include <stack>
#include <fstream>

using namespace std;

// Class Template Declarations:

template <class Type>
class prefixStack {
    //Space in stack: prefix only needs a few, we can add more if we want but no need
    const int max = 15;

public:
    //constructor that sets basic stack values
    prefixStack();
    //Const takes in int
    prefixStack(int n);
    //Destructor
    ~prefixStack();
    //Size of stack, push, pop, top, variables
    void push(const Type & newItem);
    void pop();
    Type top() const;
    int size() const;
    //Function that returns true if the stack is empty
    bool isEmptyStack() const;
    // Function that returns true if the stack is Full
    bool isFullStack() const;
int stackTop;
private:
    //Pointer to top of stack
    
    Type *array;
    int maxSize;

};

template <class Type>
prefixStack<Type> :: prefixStack()
{
    // Maximum size of stack will be equivalent to max size we set
    maxSize = max;
    // Set array space to be that of the max value
    array = new Type[max];
    // Set topmost value of stack to -1
    stackTop = -1;
}

//Same as top function, just adjust when input is inserted 
template <class Type>
prefixStack<Type> :: prefixStack(int n)
{
    maxSize = n;
    array = new Type[maxSize];
    stackTop = -1;
}

// Destructor
template <class Type>
prefixStack<Type> :: ~prefixStack()
{
    // Delete the array we created
    delete[] array;
}

//Push values into stack
template <class Type>
void prefixStack<Type> :: push(const Type& newItem)
{
    // If stack is full, print the following message
    if(size() == max) {
        cout << "Cannot add to full stack. Stack Overflow";
    }
    // Insert newItem (newest stack value) into the stack
    array[stackTop++] = newItem;
}

// Pop values off the stack
template <class Type>
void prefixStack<Type> :: pop()
{
    // If the stack is empty, print this
    if (isEmptyStack() == true) {
        cout << "Cannot remove from an empty stack." << endl;
    }
    // Pop topmost element from stack
    stackTop--;
}

//Function to find stack size
template <class Type>
int prefixStack<Type> :: size() const 
{
    // Total size is stacktops value +1 
    return stackTop + 1;
}

template <class Type>
Type prefixStack<Type>:: top() const 
{
    // If stack is empty,
    if(isEmptyStack()==true) {
        cout << "Stack is empty, no top";
    }
    // Return stackTops value which is essentially topmost value
    return array[stackTop];
}

template <class Type>
bool prefixStack<Type>:: isEmptyStack() const
{
    // If top of stack is nullptr, then return
    return(stackTop < 0);
}

template <class Type>// Create Template function from class Type
// Function that returns false if the stack is not full
bool prefixStack<Type>:: isFullStack() const
{
    // If stack is not full, return true
    if (size >= max) {
        return true;
    }
} 

// Evaluate function that evaluates the prefix expression we enter in
double evaluate(string prefix) {

    // Instantiate a new stack of type double
    prefixStack<double> stack;

    //Check through values of the stack
    for (int i = prefix.size()-1; i >= 0; i--) {
        // If topmost element is a 
        if (isdigit(prefix[i])) {
            stack.push(prefix[i]-'0');
        }
        else {
            // Declare and pop op1 and op2 off the stack
            double op1 = stack.top();
            stack.pop();
            double op2 = stack.top();
            stack.pop();

            // Now, use a switch statement to check through the prefix expression
            // and push the appropriate expr. to stack

            switch(prefix[i]) {

            // In the case when prefix[i] is a '+' sign, do this:
            case '+':  
                stack.push(op1 + op2); // add both values of op1 and op2 and push it to the stack
                break; // break out of the switch statement

            // In the case when prefix[i] is a '-' sign, do this:
            case '-': 
                stack.push(op1 - op2); // Delete the first (op1) value from op2, then push onto stack
                break; // break out of the switch statement

            // In the case when prefix[i] is a '*' sign, do this:
            case '*': 
                stack.push(op1 * op2); // Multiply op1 by op2 and push the value onto the stack
                break; // break out of the switch statement
            
            // In the case when prefix[i] is a '/' sign, do this:
            case '/':  
                if (op2 != 0) // if op2 does not equal 0, do this:
                    stack.push(op1 / op2); // Divide op1 by op2 and push the value on to the stack
            }
        }
    }
    // Return the topmost value of the stack b/c that is the value we want
    return stack.top();
}


int main() {
    string prefix = "+4*83"; //should be 28
    cout << "The value of the prefix expression is: " << evaluate(prefix) << endl;

    return 0;
}

//Umar Kagzi
