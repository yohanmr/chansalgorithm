#ifndef CUSTOMSTACK_H
#define CUSTOMSTACK_H

#include <iostream>
using namespace std;

#define SIZE 10000

template <class T>
class customStack
{
    private:
        T *arr;
        int top;
        int belowTop;
        int capacity;


    public:
        customStack(int size = SIZE);
        
        void push(T);
        T getTopElement();
        T getElementBelowTop();
        void pop();

        // only for points
        vector<T> getPoints();

};

/*
Constructor to initialize stack
*/
template <class T>
customStack<T>::customStack(int size)
{
	arr = new T[size];
	capacity = size;
	top = -1;
    belowTop = top-1;
}

/*
function to add an element x in the stack
*/
template <class T>
void customStack<T>::push(T t)
{
	if (top == (capacity - 1))
	{
		cout << "STack overflow, program terminated\n";
		exit(EXIT_FAILURE);
	}

	arr[++top] = t;
    ++belowTop;
}

/*
function to pop top element from the stack
*/
template <class T>
void customStack<T>::pop()
{
	// check for stack underflow
	if (top == -1)
	{
		cout << "stack UnderFlow, program terminated\n";
		exit(EXIT_FAILURE);
	}

	// decrease stack size by 1 and (optionally) return the popped element
	top--;
    belowTop--;
}

/*
function to return top element from the stack
*/
template <class T>
T customStack<T>::getTopElement()
{
	// check for stack underflow
    if (top <= -1)
	{
		cout << "stack is empty, program terminated\n";
		exit(EXIT_FAILURE);
	}

	// decrease stack size by 1 and (optionally) return the popped element
	return arr[top];
}

/*
function to return 2nd element from the stack
*/
template <class T>
T customStack<T>::getElementBelowTop()
{
	// check for stack underflow
	if (belowTop <= -1)
	{
		cout << "stack is empty or contains only one element, program terminated\n";
		exit(EXIT_FAILURE);
	}

	// decrease stack size by 1 and (optionally) return the popped element
	return arr[belowTop];
}

/*
function to print all the elements the stack
*/
template <class T>
vector<T> customStack<T>::getPoints()
{
    vector<T> points;
    for(int i = 0; i <= top; i++)
    {
//        cout<< arr[i].x << " " << arr[i].y << endl;
        points.push_back(arr[i]);
    }
    return points;

}

#endif
