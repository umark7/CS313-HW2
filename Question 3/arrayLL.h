//Question 3: Test a stack's speed (with millions of operations) as to which is faster: an array based
//stack or a linked list based stack. THIS IS HEADER FILE

#ifndef H_arrayLL // defining header file
#define H_arrayLL // defining header file
 
#include <iostream> // including iostream library
#include <cassert>  // importing assert.h header file

// by using this namespace, we don't need to prefix things with the std:: namespace
using namespace std; 


// LINKED LIST STACK DECLARATION HERE

template <class Type> // Declare a template of class Type
struct nodeType // Declare a nodeType template for LL nodes
{
    Type info; // Type stores the info of the node
    nodeType<Type> *link; // node type that will have a pointer to the link of the node
};

template <class Type> // declare a template of class Type
// From the linkedStackType class we inherit the stackADT file we included (not inheriting in this func)
class linkedStackType
{

// Declaring public functions:
public:
    // Operator= function
    const linkedStackType<Type>& operator= (const linkedStackType<Type>&);

    //Function that returns true if the stack is empty
    bool isEmptyStack() const;

    // Function that returns true if the stack is Full
    bool isFullStack() const; 

    // Builds and initializes stack we want
    void initializeStack(); 

    // Push new values into the stack, takes in const reference to newItem
    void push(const Type& newItem); 

    // Returns the topmost element of the stack
    Type top() const; 

    // Removes the most recently added element at the top of the stack
    void pop(); 

    // LLStackType constructor, detailed below
    linkedStackType(); 

    //Copy constructor
    linkedStackType(const linkedStackType<Type>& otherStack); 

    // Destructor for the linkedStackType function
    ~linkedStackType(); 

// Privately declared variables
private:

    //stackTop is a pointer to a stack (detailed later)
    nodeType<Type> *stackTop; 

    // Function to make a copy of otherStack
    void copyStack(const linkedStackType<Type>& otherStack); 

};
    

template <class Type> // Create template function from class Type
// Constructor for the LL Stack
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr; // variable named stackTop(the top of the stack) will initially be set as nullptr
                        // By setting it nullptr, we are saying that the stack is initially empty.
}

template <class Type>// Create Template function from class Type
// Function that checks whether stack is empty
bool linkedStackType<Type>::isEmptyStack() const
{
    // If top of stack is nullptr, then return
    return(stackTop == nullptr);
} 

template <class Type>// Create Template function from class Type
// Function that returns false if the stack is not full
bool linkedStackType<Type>:: isFullStack() const
{
    // If stack is not full, return false
    return false;
} 

template <class Type>// Create template function from class Type
// This function initializes the stack with the basic stack structure
void linkedStackType<Type>:: initializeStack()
{
    //Initialize temp pointer of nodeType
    nodeType<Type> *temp; 

    // While stack is not empty,
    while (stackTop != nullptr) 
    {
        // Set temp to the value of stackTop, the topmost value in the stack
        temp = stackTop;    

        // Now, set stackTop equal to link
        stackTop = stackTop->link; 
        
        // Delete temp variable we created to save memory
        delete temp;   
    }
} 


template <class Type> // Create template function from class Type
// This is the push function, which will "push" a constant ref element to the top of the stack.
void linkedStackType<Type>::push(const Type& newElement) 
{

    // Initialize newNode pointer of type nodeType
    nodeType<Type> *newNode; 

    //First thing we do is create a new node of nodeType 
    newNode = new nodeType<Type>;  

    newNode->info = newElement;  // We insert the info or data of newNode into the variable newElement
    newNode->link = stackTop;    // We set the link part of the newNode as the existing top, stackTop
    stackTop = newNode;          // Now we set top = temp, so stackTop=newNode
                             
} //end push


template <class Type> // Create template function from class Type
Type linkedStackType<Type>::top() const //The top function basically tells us what value is in the topmost element of the stack
{
    assert(stackTop != nullptr);  //Assert function check whether stackTop does not equal nullptr. If true, everything 
                                  // is fine and the function will continue to the next part. 
                                  // If stackTop != nullptr, then the program will stop executing.   

    return stackTop->info;        // If the assert function executed, then return the value of stackTop, the top of the stack
}//end top

template <class Type>  // Create template function from class Type
void linkedStackType<Type>::pop() // The pop element is used to delete the topmost value of the stack
{
    nodeType<Type> *temp; // Initialize a temp pointer from nodeType template

    // If the stack is not empty (nullptr)
    if (stackTop != nullptr) 
    {
        temp = stackTop;  // We need point the temp value to the top node in the stack
                          // So, temp equals stackTop's value

        stackTop = stackTop->link;  // Now we set stackTop equal to its link
                                    
        delete temp;                // We delete the temp variable to save memory
    }

    // If the stack is empty (nullptr) then we will print the following message.
    else                            
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type> // Create template function from class Type
// The copyStack function will copy a stack
void linkedStackType<Type>::copyStack (const linkedStackType<Type>& otherStack) 
{
    // Initializing  newNode, current, and last pointers
    nodeType<Type> *newNode, *current, *last; 

    //If the stack is not empty,
    if (stackTop != nullptr)  
        initializeStack();    // Then we will call the initializeStack function

    // If the otherStack we have referenced is empty, 
    if (otherStack.stackTop == nullptr) 
        stackTop = nullptr;             // then we will set the topmost value to nullptr for that stack

    // If otherStack is not empty, then do the following
    else
    {
        current = otherStack.stackTop;  // Set the current pointer value to otherStack's top value, stackTop.
        
        stackTop = new nodeType<Type>;  // Now we set stackTop to the value of a new nodeType

        stackTop->info = current->info;  // We set the stackTop node's data to the same as our current stack's topmost value
        
        stackTop->link = nullptr;        // Then, we set stackTop's link to be nullptr
                               
        last = stackTop;            // The last value in the stack is now stackTop

        current = current->link;    // Then, we set the current value stack value to what our link points to.

        // While the current stack value is not empty,
        while (current != nullptr) 
        {
            newNode = new nodeType<Type>; // Set the newNode value to a new node using the nodeType class

            newNode->info = current->info; // We set the new node's info (data) to the data found in the current node
            
            newNode->link = nullptr; // Link the newNode to an empty value
            
            last->link = newNode; // Set the last value's link to the value of newNode that we just initialize
            
            last = newNode;       // Then, set the value of the last node in the new stack to be the same as newNode
            
            current = current->link; // Set the current node to the link of the current node.
        }
    }
} 

template <class Type>    // Create template function from class Type
// The linkedStackType function takes in a const reference to the otherStack we copy values into 
linkedStackType<Type>::linkedStackType(const linkedStackType<Type>& otherStack) 
{
    stackTop = nullptr; //When initializing, the topmost value of the stack is set to be empty

    copyStack(otherStack); //We then call the copyStack function, taking in the const reference of the otherStack we created
}

  
template <class Type>  // Create template function from class Type
// This is the destructor for the linkedStackType function we called. Essentially destroys the function we made earlier. 
linkedStackType<Type>::~linkedStackType()  
{
    // Calls the initializeStack method. This function initializes the fundamental variables needed for a stack.
    initializeStack();                      
}

template <class Type>    // Create Template function from class Type
//this function compares values from other stack. Comes from operator= function
const linkedStackType<Type>& linkedStackType<Type>::operator=(const linkedStackType<Type>& otherStack)  
{ 
    // If the current stack is not equivalent to the otherStack,
    if (this != &otherStack)   
        copyStack(otherStack); //Copy the stack information into this stack

    return *this;             //Then, return the otherStack here.
}


//ARRAY BASED STACK AFTER THIS:

template <class type>
class arrayStack {
    //Space in stack: 1 million for the numbers
    const int max = 1000000;

public:
    //constructor that sets basic stack values
    arrayStack();
    //Const takes in int
    arrayStack(int n);
    //Destructor
    ~arrayStack();
    //Size of stack, push, pop, top, variables
    void push(const type & newItem);
    void pop();
    type top() const;
    int size() const;
    //Function that returns true if the stack is empty
    bool isEmptyStack() const;
    // Function that returns true if the stack is Full
    bool isFullStack() const;
    int stackTop;
private:
    //Pointer to top of stack
    
    type *array;
    int maxSize;

};

template <class type>
arrayStack<type> :: arrayStack()
{
    // Maximum size of stack will be equivalent to max size we set
    maxSize = max;
    // Set array space to be that of the max value
    array = new type[max];
    // Set topmost value of stack to -1
    stackTop = -1;
}

//Same as top function, just adjust when input is inserted 
template <class type>
arrayStack<type> :: arrayStack(int n)
{
    maxSize = n;
    array = new type[maxSize];
    stackTop = -1;
}

// Destructor
template <class type>
arrayStack<type> :: ~arrayStack()
{
    // Delete the array we created
    delete[] array;
}

//Push values into stack
template <class type>
void arrayStack<type> :: push(const type& newItem)
{
    // If stack is full, print the following message
    if(size() == max) {
        cout << "Cannot add to full stack. Stack Overflow";
    }
    // Insert newItem (newest stack value) into the stack
    array[stackTop++] = newItem;
}

// Pop values off the stack
template <class type>
void arrayStack<type> :: pop()
{
    // If the stack is empty, print this
    if (isEmptyStack() == true) {
        cout << "Cannot remove from an empty stack." << endl;
    }
    // Pop topmost element from stack
    stackTop--;
}

//Function to find stack size
template <class type>
int arrayStack<type> :: size() const 
{
    // Total size is stacktops value +1 
    return stackTop + 1;
}

template <class type>
type arrayStack<type>:: top() const 
{
    // If stack is empty,
    if(isEmptyStack()==true) {
        cout << "Stack is empty, no top";
    }
    // Return stackTops value which is essentially topmost value
    return array[stackTop];
}

template <class type>
bool arrayStack<type>:: isEmptyStack() const
{
    // If top of stack is nullptr, then return
    return(stackTop < 0);
}

template <class type>// Create Template function from class Type
// Function that returns false if the stack is not full
bool arrayStack<type>:: isFullStack() const
{
    // If stack is not full, return true
    if (size >= max) {
        return true;
    }
} 






#endif // End of arrayLL file
//Umar Kagzi
