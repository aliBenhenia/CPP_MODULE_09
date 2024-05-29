# CPP_MODULE_09 

https://www.tldraw.com/s/v2_c_m01d2wU0mdmJlMoP1WNcX?v=-366,-1520,1781,2417&p=page

Algorithm to evaluate a reverse polish notation using a stack :
Create a stack of type Stack<Integer> to store the operands.
Scan the string s from left to right and perform below for every element that is scanned.
If the element scanned is an operand, push the element to the stack.
If the element scanned is an operator, pop two elements from the stack and evaluate the expression using the operator and popped elements and push the result back to the stack.
When the scanning of entire string is complete, the element left in the stack is the result.
https://www.youtube.com/watch?v=xhFKZyy722M

alg :
Input Parsing (parseNumbers):
This function takes command line arguments and processes each one using processNumber, which validates and converts the string to an integer, then stores it in the numbers vector if valid.
Splitting Pairs (splitPairs):
The numbers are paired up sequentially. If the total count of numbers is odd, the last number is stored separately in lastNumber and removed from the main list.
Each pair is then stored in a vector of pairs named PairNumbers.
Sorting Pairs (MergeSortPair and Merge):
A merge sort algorithm is applied specifically to the pairs. The MergeSortPair function recursively splits the list of pairs into smaller segments and then merges them back together in sorted order using the Merge function. The sorting criteria is based on the first element of the pairs.
Chain Creation (fillMainChainAndPend):
After sorting, the pairs are used to fill two sequences: mainChain and pendChain. The mainChain is intended to be the primary sequence, while pendChain holds potential elements to be merged into the mainChain.
Jacob Sequence and Combination (createComb):
A Jacob sequence is generated, which is a specific sequence of numbers based on a recursive formula. This sequence is then used to create a combination list that dictates how elements from pendChain should be merged into mainChain.
Result Sorting (sortingResult):
Using the combination list, elements from pendChain are inserted into mainChain at positions determined by a binary search (std::lower_bound), ensuring that mainChain remains sorted.
Final Adjustments and Output (start and printNumbers):
The start function orchestrates the entire process: parsing input, splitting pairs, sorting, and merging. If there's an odd number out (lastNumber), it's inserted into the sorted mainChain at the correct position.
Finally, printNumbers outputs the sorted mainChain.
This algorithm is a combination of sorting (using merge sort for pairs), and a custom sequence generation and insertion strategy (using the Jacob sequence and binary search insertion). The overall goal seems to be to achieve a highly specific order of numbers, potentially for a specialized application.