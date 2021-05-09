/* Use a stack to pass in a string and reverse each word in the string. For instance, if you
have the string “When Chuck Norris falls in water, Chuck Norris doesn't get wet. Water
gets Chuck Norris.” It should now say, “nehW kcuhC sirroN sllaf ni retaw, …” That is, it
should take in one string and be a function (or multiple functions) that use a stack (or
multiple stacks) to reverse each word in the sentence. Create a text file that you input of
Chuck Norris jokes and have the program reverse each of the jokes.  */

#include <iostream> 
#include <iomanip>
#include <string>
#include <algorithm>
#include <stack>
#include <fstream>
#include <string>

using namespace std;
//Reverse function to reverse string
void reverse();

int main() {

    reverse();

    return 0;
}

// Reverse function that reverses the string from file
void reverse() {
    
    // Open the file that has the Chuck Norris joke in it
    ifstream inFile;
    inFile.open("jokes.txt");

    // If file doesn't open, exit program with error
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Read in the text file and put it into a string using this in-built stream iterator
    // This will read through all of the characters in the file and assign them to string joke.
    string joke { istreambuf_iterator<char>(inFile), istreambuf_iterator<char>() };

    cout << "Original File Text is: " << joke << endl;
    cout << "\nReversed text is: ";
    
    // Reverse the joke using in-built stack and print it out
    stack<char> stack;

    // Traverse string from file & check for a space.
    for (int i = 0; i < joke.length(); i++) {
        // If a space is not present at index, push value to stack.
        if (joke[i] != ' ') {
            stack.push(joke[i]); 
        }
        // If a space does show up, we will print the stack's first element out and pop to print the remaining
        else {
            while(!stack.empty()) {
                cout << stack.top();
                stack.pop();
            }
            // Once stack is empty, simply add a space and leave the else statement
            cout << " ";
        }
    }
    // In the case of the last word, there might not be a space after the word so we use this to print it.
    while (!stack.empty()) {
        // Print out topmost element of stack
        cout << stack.top();
        //After printing, pop it off
        stack.pop();
    }

    inFile.close();
}

