/*

Valid Parentheses
  Go to Discuss
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true

*/


//easy,直接用一个栈就搞定了。

typedef struct Stack
{
	char *arr;
	int maxSize;
	int size;
}Stack;


int initStack(Stack ** s)
{
	*s = (Stack*)malloc(sizeof(Stack));
	(*s)->maxSize = 1024;
	(*s)->arr = (char*)malloc(sizeof(char) * ((*s)->maxSize));
	(*s)->size = 0;
	return 1;
}

char popStack(Stack *s)
{
	if(s->size == 0)
		return '\0';

	char ch = s->arr[--s->size];
	return ch;
}

int pushStack(Stack * s, char ch)
{
	if(s->size == s->maxSize)
	{
		s->maxSize *= 2;
		s->arr = (int*)realloc(s->arr, sizeof(int) * s->maxSize);
	}
	s->arr[s->size++] = ch;

	return 1;
}

int isEmpty(Stack * s)
{
	if(s->size == 0)
		return 1;
	else
		return 0;
}

int destroyStack(Stack * s)
{
	if(s == NULL)
		return 0;

	if(s->arr)
		free(s->arr);

	free(s);

	return 1;
}

bool isValid(char* s) {

	char * p = s;

	Stack *st;
	initStack(&st);
	char top;

	while(*p != '\0')
	{
		switch(*p)
		{
			case '(':
			case '[':
			case '{':
				pushStack(st, *p);
				break;
			case ')':
				top = popStack(st);
				if(top != '(')
					return 0;
				break;
			case ']':
				top = popStack(st);
				if(top != '[')
					return 0;
				break;
			case '}':
				top = popStack(st);
				if(top != '{')
					return 0;
				break;
		}
		p++;
	}
	int empty = isEmpty(st);
	destroyStack(st);
	return empty;
    
}