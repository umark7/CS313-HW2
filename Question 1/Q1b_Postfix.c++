// import the following libraries to aid us in the program
#include <iostream> 
#include <iomanip>
#include <fstream> //File stream library to allow input/output reading/writing of files
#include "mystack.h" // Include header file of mystack.h
 
// Use std namespace so we don't have to mention it everytime we write a cstdlib function
using namespace std; 

// Function Declarations:

// evaluateExpression function: checks if the expression is solvable by evaluateOpr
// takes in: ifstream& inpF, ofstream& outF, stackType<double>& stack, char& ch, bool& isExpOk
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack, char& ch, bool& isExpOk);

// evaluateOpr function: Evaluates the given postfix operation and helps solve it
// takes in: ofstream& out, stackType<double>& stack, char& ch, bool& isExpOk)
void evaluateOpr(ofstream& out, stackType<double>& stack, char& ch, bool& isExpOk);

// discardExp function: Discards the given expression if it doesn't contain '=' sign
// Takes in:ifstream& in, ofstream& out, char& ch
void discardExp(ifstream& in, ofstream& out, char& ch);

// printResult function: prints out the result of our postfix function after it is evaluated
// Takes in: ofstream& outF, stackType<double>& stack, bool isExpOk
void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk);


// Main function
int main() {

    //Declaring Variables
    
    bool expressionOk; //Checks if the expression entered is properly formatted, returns true if so;

    char ch; // Declare a char variable named ch, this is how we evaluate the postfix characters

    stackType<double> stack(100); //Intialize a stack (type double) with 100 values.

    ifstream infile; // Declare ifstream variable that allows for file input

    ofstream outfile; // Declare outfile variable that allows for file output
    
    //Open a file(containing the postfix problem) 
    infile.open("RpnData.txt"); 

    // If file doesn't open
    if (!infile)
    {   //Print this message out if file doesn't open and terminate this program completely.
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }

    // Open this file
    outfile.open("RpnOutput.txt");

    outfile << fixed << showpoint; // We use the insertion operator on the file for 2 stdlib functions:
                                    // 1) fixed - this will write float values in fixed notation
                                    // 2) showpoint - the decimal point is always written for float values inserted in the stream
    
    // This sets decimal precision to 2 places
    outfile << setprecision(2);
    // Essentially all our outputs will now be in the specified formats if the outfile is used.


    // Read in the char values from the file
    // It will essentially extract and parse characters from the input file.
    infile >> ch; 
    
    // While we are still "open" in this file and reading it,
    while (infile) 
    {
        //call the initialize stack method on the stack
        stack.initializeStack(); 
        // Set the boolean expr. to true 
        expressionOk = true;
        // We output the ch values to the file
        outfile << ch; 
        // Evaluate the postfix expression we wrote using this function
        evaluateExpression(infile, outfile, stack, ch, expressionOk); 
        //Print the result of the postfix calculation into the output file.
        printResult(outfile, stack, expressionOk); 
        //Begin processing the next expression in the file
        infile >> ch; 
    } //end while 

    infile.close(); // Close the text file we read from
    outfile.close(); // Close the text file we wrote from

    return 0; // end program safely

} //end main


// Evaluate the postfix expression using this function here.
//The function takes in the input and output file (to read and write into each respective one, a stack and a boolean
// to check if the expression is okay.)
void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{ 

    double num; //declare a double variable

    //While the characters read in are not equal to the "=" sign, then
    while (ch != '=') 
    {
        // Use the switch function on ch () and check what its equivalency is
        switch (ch) 
        {

        case '#':  // In the case when the char is a # sign,
            inpF >> num; // Read in the num variable & process it 
            outF << num << " ";  // Write the num and a space after it in the output file

            // If the stack is not full 
            if (!stack.isFullStack())  
                stack.push(num); // Then push the num value into the stack
            
            // If the stack is full
            else
            {
                // Print the following message telling the user that the stack is full and terminate the program.
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                //terminate the program
                exit(0);  
            }
            // Break out of the while loop
            break;

        // The default case of the switch statement is:    
        default: 
            // Call the evaluateOpr function with the following parameters:
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch

        //if the expression is in the correct format and no errors,
        if (isExpOk) 
        {
            inpF >> ch; // Read in the char value and process it
            outF << ch; // Write the char value in the output file

            if (ch != '#') // If the char value doesn't equal '#' then
                outF << " "; // In the output file write a blank space.
        }

        // If the expression is not in the correct format and has errors,
        else
            // Call the discardExp function outlined below
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression

// This is the evaluateOpr function which evaluates which operator is being used in the postfix program calculator
// The function writes to the output file, uses a stack of type double and takes in a character.
void evaluateOpr(ofstream& out, stackType<double>& stack, char& ch, bool& isExpOk) 
{
    // Declaration of the 2 operator variables
    double op1, op2; 

    // If the stack is empty,
    if (stack.isEmptyStack()) 
    {
        // Write this message to the output file
        out << " (Not enough operands)"; 
        // Set the isExpOk boolean value to false since not enough operands
        isExpOk = false; 
    }

    // If the stack has values in it, then do the following:
    else 
    {
        op2 = stack.top(); // Set operator 2 to the topmost value on the stack
        stack.pop(); // Delete the top most value that is on the stack now (since op2 already equals this value)

        if (stack.isEmptyStack()) // If the stack is empty,
        {
            // Write this message to the output file
            out << " (Not enough operands)";
            // Set the isExpOk boolean value to false since not enough operands
            isExpOk = false; 
        }

        // If the stack has remaining values in it, then do the following:
        else
        {
            op1 = stack.top(); // Set op1 to the topmost value in the stack
            stack.pop(); // now delete the topmost value in the stack

            switch (ch) // Use the switch statement on the character ch. This allows ch to be tested against the list
                        // of different case values that are listed below. 
            {

            // In the case when ch is a '+' sign, do this:
            case '+':  
                stack.push(op1 + op2); // add both values of op1 and op2 and push it to the stack
                break; // break out of the switch statement

            // In the case when ch is a '-' sign, do this:
            case '-': 
                stack.push(op1 - op2); // Delete the first (op1) value from op2, then push onto stack
                break; // break out of the switch statement

            // In the case when ch is a '*' sign, do this:
            case '*': 
                stack.push(op1 * op2); // Multiply op1 by op2 and push the value onto the stack
                break; // break out of the switch statement
            
            // In the case when ch is a '/' sign, do this:
            case '/':  
                if (op2 != 0) // if op2 does not equal 0, do this:
                    stack.push(op1 / op2); // Divide op1 by op2 and push the value on to the stack
                // If op2 does equal to 0, do this:
                else 
                {
                    out << " (Division by 0)"; // Write to the output file the following statement
                    isExpOk = false; // Set the isExpOk boolean to false
                }
                break; // Break out of the switch stament when the division part is complete

            // In the default case, do this:
            default:   
                out << " (Illegal operator)"; // Write the following statement into the output file
                isExpOk = false; // Set the isExpOk boolean to false (the expression is not okay)
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

// The following function is discardExp, when the expression is discarded if there are errors in it
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=') // while the character does not equal to an '=' sign,
    {
        in.get(ch); // In the infile, get the value of the character
        out << ch; // in the output file, write the character into the file 
    }
} //end discardExp

// This function is used to print the postfix calculation result after it has been calculated
void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk)
{
    double result; // Declare a double variable named result, which will compile our calculation result

    //if the expression is okay and has the proper format/calculated correctly, do this:
    if (isExpOk) 
    {
        // If the stack is not empty, 
        if (!stack.isEmptyStack()) 
        {
            result = stack.top(); // Set the result value to the value currently at the top of the stack
            stack.pop(); // De-allocate memory by removing the value from the top of the stack, and to allow
                        // other calculations to take place if desired
                        
            // If the stack is empty, then:
            if (stack.isEmptyStack()) 
                outF << result << endl; // Write into the output file the result and add a new line.
            else // If the stack does have values in it, then print the following message
                outF << " (Error: Too many operands)" << endl; // In the output file, write in the following line
        } //end if
        else //  If the stack is empty, print this:
            outF << " (Error in the expression)" << endl; // If stack is empty, write this line in the output file
    }
    else //If the expression is not okay & doesn't parse properly,
        outF << " (Error in the expression)" << endl; // Write this comment into the file and endline.

    outF << "_________________________________"  // Write a blank line into the outfile and skip two lines.
         << endl << endl;
} //end printResult