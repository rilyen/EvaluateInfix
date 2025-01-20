/* 
 * Eval.cpp
 *
 * Description: Evaluation of infix expressions using two Stacks.
 *
 * Author:  April Nguyen    301314527
 *          Anthony Nguyen  301545011
 * Date:    October 13, 2023
 */

#include <iostream>
#include "Scanner.h"
#include "Stack.h"  // GENERIC STACK

using std::cout;
using std::endl;
using std::cin;
using std::to_string;

int runop(Token op1, Token op2, Token operand);
bool isArithmetic(Token operand);
bool plusorminus(Token operand);
bool astorslash(Token operand);
void popperformpush(Stack<Token> * numstack, Stack<Token> * opstack);

int main () {
    Scanner S(cin);
    Token t;

    Stack<Token> numstack, opstack;  // 2x Stacks of type Token
    
    t = S.getnext();
    // while T is not EOF or the operator stack is non empty
    while(t.tt != eof || !opstack.isEmpty()) {
        // if T is a number
        if (t.tt == integer) {
            // push T to the number stack; get the next token
            numstack.push(t);
            t = S.getnext();
        }
        // else if T is a left parenthesis
        else if(t.tt == lptok) {
            // push T to the operator stack; get the next token
            opstack.push(t);
            t = S.getnext();
        }
        // else if T is a right parenthesis
        else if (t.tt == rptok) {
            // if the top of the operator stck is a left parenthesis
            if (opstack.peek().tt == lptok) {
                // pop it from the operator stack; get the next token
                opstack.pop();
                t = S.getnext();
            }
            // else
            else {
                // pop the top two numbers and the top operator
                // perform the operation
                // push the result to the number stack;
                popperformpush(&numstack, &opstack);
            }
        }
        // else if T is +, -, or EOF
        else if (plusorminus(t) || t.tt == eof) {
            // if the operator stack is nonempty and the top is one of +,-,*,/:
            Token top;
            if (!opstack.isEmpty()) {
                top = opstack.peek();
            }
            if (!opstack.isEmpty() && (plusorminus(top) || astorslash(top))) {
                // pop the top two numbers and the top operator
                // perform the operation
                // push the result to the number stack
                popperformpush(&numstack, &opstack);
            }
            else {
                // else push T to the operator stack
                // get the next token
                opstack.push(t);
                t = S.getnext();
            }
        }
        // else if T is * or /
        else if (astorslash(t)) {
            // if the operator stack is nonempty
            Token top;
            if (!opstack.isEmpty()) {
                top = opstack.peek();
            }
            if (!opstack.isEmpty() && astorslash(top)) {
                // pop the top two numbers and the top operator
                // perform the operation
                // push the result to the number stack;
                popperformpush(&numstack, &opstack);
            }
            else {
                opstack.push(t);
                t = S.getnext();
            }
        }
    }
    cout << numstack.pop().val << endl;
    return 0;
}

// perform the operation op1 operand op2
// return the result
int runop(Token op1, Token op2, Token operand) {
    int result;
    switch(operand.tt) {
        case pltok:
            result = op1.val + op2.val;
            break;
        case mitok:
            result = op1.val - op2.val;
            break;
        case asttok:
            result = op1.val * op2.val;
            break;
        case slashtok:
            result = op1.val / op2.val;
            break;
        default:
            cout << "ERROR: Invalid operation" << endl;
            break;
    }
    return result;
}

// return true if one of +,-
// false otherwise
bool plusorminus(Token operand) {
    if (operand.tt == pltok || operand.tt == mitok) {
            return true;
    }
    else {
        return false;
    }
}

// return true if one of *,/
// false otherwise
bool astorslash(Token operand) {
    if (operand.tt == asttok || operand.tt == slashtok) {
        return true;
    }
    else {
        return false;
    }
}

// pop the top two numbers and the top operator
// perform the operation
// push the result to the number stack;
void popperformpush(Stack<Token> * numstack, Stack<Token> * opstack) {
    Token op2 = numstack->pop();
    Token op1 = numstack->pop();
    Token operand = opstack->pop();
    int result = runop(op1, op2, operand);
    // create token from operation result and push to numstack
    Token token = Token();
    token.tt = integer;
    token.text = to_string(result);
    token.val = result;
    numstack->push(token);
}