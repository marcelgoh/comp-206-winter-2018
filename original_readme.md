# Assignment3

This is the source code repository that will be used as a starting point for Assignment 3. You should edit this file (README.md) in order to write your responses for Question 2.

# Question 2: Code Reading

## 1) Function-Call Structure of Program
* main() calls load\_one\_preference(), which calls LOAD\_FIELD() to load the PREFERENCE\_INFO struct with data.
* LOAD\_FIELD() is defined to be input\_fcn\_array, which points to input\_string(), input\_int(), input\_double(), or input\_animal(), depending on the field\_number. If in DEBUG mode, main() then prints the preferences of the target user with print\_preference().
* (print\_preference() calls PRINT\_FIELD(), which, similar to LOAD\_FIELD(), can point to any of the following: output\_string(), output\_int(), output\_double(), or output\_animal().)
* main() then loops through loading the rest of the data, using compute\_difference\_numeric() and compute\_difference\_alphabetic() to calculate the differences in preferences. If in DEBUG mode, print\_preference() will print the best match after the loop.
* main() then prints the top movie pick for the user.
## 2) Considering the LOAD\_FIELD() Function
LOAD\_FIELD() looks like a single function that can handle all sorts of different data but it actually isn't. Instead, the program uses \#define to disguise an array of function pointers as one LOAD\_FIELD() function. When LOAD\_FIELD() is called, its third argument, field\_number, is the index in the array of the actual function that will be called.
## 3) Considering the field\_offsets Array
A struct's total size in bytes is the sum of the sizes of all the basic data types that constitute it. Unlike an array of just one type, it's often unclear how many bytes we have to offset to get to a certain index. The offsetof() function takes in a struct and a field and returns the offset in bytes that we have to move to access the field within the struct. The field\_offsets array simply stores the offsets of each field in the PREFERENCE\_INFO struct in an easy-to-access integer array.
