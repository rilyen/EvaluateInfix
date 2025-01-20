/* 
 * Stack.cpp
 *
 * Description: Implementation of a linked list-based Stack ADT class - SHSL list
 * Class Invariant: LIFO order
 *                  Top of Stack located at the back of SHSL list.
 *
 * Author:  
 * Date:    October 13, 2023
 */

#include "Stack.h"
#include <iostream>

using std::cout;
using std::endl;

// Constructor 
Stack::Stack() {
    // Initializes head as nullptr, indicating empty stack
    head = nullptr;
}

// Destructor
Stack::~Stack() {
    // Clean up any dynamically allocated resources, if any
    if (isEmpty()){
        return;
    } // Otherwise, clean up
    
    StackNode* current = head;
    while(current->next != nullptr){
        StackNode* next = current->next;
        delete current;
        current = next;
    }
    delete current;
    return; // End Program
}

// Desc: Returns true if the stack is empty otherwise false
bool Stack::isEmpty() const{
    if (head == nullptr){
        return true;
    }
    return false;
}

// Desc: Adds a new element to the top of the stack (back of LL)
bool Stack::push(int num){
    StackNode* newNode = new StackNode;
    if (newNode == nullptr){
        return false; // Memory Allocation Error
    }
    
    newNode->data = num; // Setting the data of the newNode
    newNode->next = nullptr;

    // Special Case: Stack is empty, assign newNode as head
    if (isEmpty()){
        head = newNode;
        return true; 
    } else {
    // General Case: Traverse LL to find last node
        StackNode* current = head;
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = newNode; // Set newNode to end of LL
    }

    return true;
}

// Desc: Removes the top element of the stack
//       Returns true if removal is successful otherwise false
// PRECONDITION: The stack is NOT empty
bool Stack::pop(){
    if(isEmpty()){
        return false; // Stack is empty --> Cannot pop
    }
    
    // "current" find the top and deletes/pops it
    // "previous" will be the new head
    StackNode* current = head;
    StackNode* previous = nullptr;
    while (current->next != nullptr){
        previous = current;
        current = current->next;
    }
    
    if(previous == nullptr){ // There's only 1 element in Stack
        delete head;
        head = nullptr; 
    } else {                // ≥2 element in the stack
        delete current;
        previous->next = nullptr;
    }
    return true;
}

// Desc: Returns the top of the stack
// PRE-CONDITION: The Stack is not empty
// post-condition: The Stack is unchanged
// Exceptions: I don't actually throw an exception, just print error 
int Stack::peek() const{
    if (isEmpty()){
        cout << "ERROR: peek() called with empty stack." << endl;
        return -999999;
    }
    StackNode* current = head;
    while (current->next != nullptr){
        current = current->next;
    }
    return current->data;
} 
