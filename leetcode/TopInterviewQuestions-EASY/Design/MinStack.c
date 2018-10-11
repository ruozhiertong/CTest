/*
Min Stack
  Go to Discuss
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.

*/

typedef struct {
	int *arr;
	int maxSize;
	int size; //top

	int minValue;

} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {

	MinStack *ms = (MinStack*)malloc(sizeof(MinStack));
	ms->arr = (int *)malloc(sizeof(int)*maxSize);
	ms->maxSize = maxSize;
	ms->size = 0;
	return ms;
}

void minStackPush(MinStack* obj, int x) 
{
	if(obj->size == obj->maxSize)
		return;

	obj->arr[obj->size++] = x;

	if(obj->size == 1)
		obj->minValue = x;
	else
	{
		if(obj->minValue > x)
			obj->minValue = x;
	}
}

void minStackPop(MinStack* obj) {
	if(obj->size == 0)
		return;

	int removeX = obj->arr[obj->size -1];
	obj->size--;
	if(removeX == obj->minValue)
	{
		obj->minValue = minStackMin(obj);
	}
}

int minStackTop(MinStack* obj) {
	if(obj->size == 0)
		return -1;

	return obj->arr[obj->size -1];
    
}

int minStackGetMin(MinStack* obj) {

	if(obj->size == 0)
		return -1;

	return obj->minValue;
    
}

int minStackMin(MinStack *obj){
	if(obj->size == 0)
		return -1;

	int min = obj->arr[0];

	for(int i = 1; i < obj->size; i++)
	{
		if(obj->arr[i] < min)
			min = obj->arr[i];
	}
	return min;
}

void minStackFree(MinStack* obj) {
	if(obj == NULL)
		return;

	free(obj->arr);

	free(obj);
    
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */