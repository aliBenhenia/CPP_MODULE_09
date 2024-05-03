# CPP_MODULE_09 

Algorithm to evaluate a reverse polish notation using a stack :
Create a stack of type Stack<Integer> to store the operands.
Scan the string s from left to right and perform below for every element that is scanned.
If the element scanned is an operand, push the element to the stack.
If the element scanned is an operator, pop two elements from the stack and evaluate the expression using the operator and popped elements and push the result back to the stack.
When the scanning of entire string is complete, the element left in the stack is the result.