#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "maze.h"

void initQueue(Queue * queue)
{
	queue->nodeArr = (Node*)malloc(NODEMAXNUM * sizeof(Node));
	queue->size = 0;
	queue->front = 0;
	queue->rear = -1;
}

int isEmptyQueue(Queue * queue)
{
	//利用front 和rear 判断真是蛋疼。因为对于循环队列(数组实现)来讲，空和满的条件都是相等。(不是数组形式的就不会是循环队列了)(如果不是循环队列也不会有这样的问题) 
	//无法判断空和满，也无法从front 和 rear得到长度。 不过通过初始化 front rear 指向的位置来解决。也不行。 
	//如果只通过front和rear进行处理循环队列，不管怎么处理(不管front rear指向哪种形式的位置)都是有问题的，无法完全判断队空和队满，除非添加一些指示标志。
	//直接新增一个成员size就清爽很多。
	// if(queue->front == queue->rear) //如果front指向刚放到的位置，rear指向未使用的位置，这个==不能判断是否是空，也有可能只有一个元素时也是==。
	// 	return 1;
	// else
	// 	return 0;

	if(queue->size == 0)
		return 1;
	else
		return 0;
}

int isFullQueue(Queue * queue)
{

	// if((queue->rear + 1)%NODEMAXNUM == queue->front) //如果front 和rear都是指向队内，这个==是无法判断的，可能是队满，也有可能是队空，
	// 	return 1;
	// else
	// 	return 0;

	if(queue->size ==  NODEMAXNUM)
		return 1;
	else
		return 0;

}

int getQueueLen(Queue *queue)
{
	// int len;
	// if(front > rear)
	// {
	// 	len = front - rear;
	// } else if(front < rear)
	// {
	// 	len = NODEMAXNUM - (rear - front);
	// }
	// else //对于循环队列，相等时不知空还是满。
	// {

	// }

	// return len;

	return queue->size;
}

//入队。从队尾入队。
int EnQueue(Queue* queue, Node node)
{
	if(isFullQueue(queue))
	{
		printf("Queue is full\n");
		return -1;
	}
	//因为有isFull 和isEmpty的判断，使得入队和出队不用担心front和rear的问题。
	queue->rear++;
	if(queue->rear == NODEMAXNUM)
		queue->rear = 0;
	queue->nodeArr[queue->rear] = node;
	
	queue->size = queue->size + 1;
    return 0;
}
//出队。从队首出队。 像排队一样。
int DeQueue(Queue* queue, Node* node)
{
	if(isEmptyQueue(queue))
	{
		printf("Queue is empty\n");
		return -1;
	}

	*node = queue->nodeArr[queue->front];
	queue->front = (queue->front + 1) % NODEMAXNUM;
	queue->size = queue->size - 1;
    return 0;
}

//随机出队。
int RandDeQueue(Queue* queue, Node* node)
{
	if(isEmptyQueue(queue))
	{
		printf("Queue is empty\n");
		return -1;
	}
	int randIdx = (rand()%(queue->size)) + queue->front;
	*node = queue->nodeArr[randIdx];
	queue->nodeArr[randIdx] = queue->nodeArr[queue->front];
	queue->front = (queue->front + 1) % NODEMAXNUM;
	queue->size = queue->size - 1;
    return 0;
}


void initStack(Stack *stack)
{
	stack->nodeArr = (Node*)malloc(NODEMAXNUM * sizeof(Node));
	stack->size = 0;
	stack->top = -1; //指向最后元素的位置。
}

int isEmptyStack(Stack * stack)
{
	if(stack->size == 0)
		return 1;
	else
		return 0;
}

int isFullStack(Stack * stack)
{
	if(stack->size ==  NODEMAXNUM)
		return 1;
	else
		return 0;

}

int getStackLen(Stack *stack)
{
	return stack->size;
}

//入栈。
int pushStack(Stack* stack, Node node)
{
	if(isFullStack(stack))
	{
		printf("stack is full\n");
		return -1;
	}
	stack->nodeArr[++stack->top] = node;
	stack->size++;
    return 0;
}
//出栈
int popStack(Stack* stack, Node* node)
{
	if(isEmptyStack(stack))
	{
		printf("Stack is empty\n");
		return -1;
	}
	if(node != NULL) //空指针。 无法给空指针指向的地址赋值。
		*node = stack->nodeArr[stack->top--];
	else
		stack->top--;
	stack->size--;
    return 0;
}
int peekStack(Stack * stack, Node *node)
{
	if(isEmptyStack(stack))
	{
		printf("Stack is empty\n");
		return -1;
	}
	*node = stack->nodeArr[stack->top];
    return 0;
}

void gotoxy(int x, int y)
{
	#if (defined _WIN32) || (defined WIN32)
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD pos;
		pos.X = x;
		pos.Y = y;
		SetConsoleCursorPosition(handle, pos);
	#else
			printf("\033[%d;%dH",y, x);
	#endif
}
void showCursor(int show)
{
	#if (defined _WIN32) || (defined WIN32)
		if(show)
			CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
		else
			CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	#else
		if(show)
			printf("\033[?25h");
		else
			printf("\033[?25l");
	#endif
}

void clearVisit()
{
	
	for(int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			g_Maze[i][j].visited = 0;
		}
	}
	//二维数组。
	//memset(visit , 0 , sizeof(int)*COL*ROW);
}

void printMaze()
{
	gotoxy(0,0);
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j< COL; j++)
		{
			if(g_Maze[i][j].type == 1 || g_Maze[i][j].type == 2)
			{
				printf("\033[31m"); //设置字体颜色。
				printf("%-2d", g_Maze[i][j].type);
				printf("\033[m"); //重置。
			}
			else if(g_Maze[i][j].type == 3 || g_Maze[i][j].type == 4 || g_Maze[i][j].type == 5)
			{
				printf("\033[41m"); //设置字体颜色。
				printf("%-2d", g_Maze[i][j].type);
				printf("\033[m"); //重置。
			}
			else printf("%-2d", g_Maze[i][j].type);
		}
		printf("\n");
	}
}

void printVisited()
{
	system("clear");
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL ; j++)
		{
			if(g_Maze[i][j].visited == 1)
				g_Maze[i][j].type = 3;

		}
	}

	printMaze();

	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL ; j++)
		{
			if(g_Maze[i][j].visited == 1)
				g_Maze[i][j].type = 1;

		}
	}
	usleep(1000*100);
}

void printPath()
{
	//printf("step:%d %d %d\n",step, visitNode[0].x, visitNode[0].y);
	system("clear");
	for(int i = 0; i < step; i++)
	{
		g_Maze[visitNode[i].x][visitNode[i].y].type = 4;
	}

	printMaze();

	for(int i = 0; i < step; i++)
	{
		g_Maze[visitNode[i].x][visitNode[i].y].type = 1;
	}
	usleep(1000*100);

}

void printBFSPath()
{
	system("clear");
	
	Node node = outNode;
	while(!(parenNode[node.x][node.y].x == -1 && parenNode[node.x][node.y].y == -1))
	{
		g_Maze[node.x][node.y].type = 5;
		node = parenNode[node.x][node.y];
	}
	g_Maze[node.x][node.y].type = 5;

	printMaze();
}

int isValidNode(Node nextNode)
{
	if(nextNode.x < 0 || nextNode.x > ROW -1 || nextNode.y < 0 || nextNode.y > COL -1)
		return 0;

	if(g_Maze[nextNode.x][nextNode.y].visited == 1)
		return 0;

	if(g_Maze[nextNode.x][nextNode.y].type == 0)
		return 0;

	return 1;

}

//初始化基础地图。路和墙间隔分布。
void initMaze()
{
	for(int i = 0; i < ROW ; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			g_Maze[i][j].x = i;
			g_Maze[i][j].y = j;
			g_Maze[i][j].visited = 0;
			//边界都为墙
			if(i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
				g_Maze[i][j].type = 0;
			else
			{
				if(i % 2 == 1 && j % 2 == 1)
					g_Maze[i][j].type = 1;
				else
					g_Maze[i][j].type = 0;
			}
		}
	}

}


//0.迷宫要 奇*奇 的矩阵(实际也不定，主要是为了避免两列或两行都是墙)。最外一层是墙。
//  迷宫随机生成可以是广度，也可以是深度。 但是 如果是广度的，如果是规律入队，要注意随机出队(或者随机入队，然后先进先出出队)。 深度的要随机入栈(先进后出)。
//1.如何确保生成迷宫一定可用。因为这样路的位置都是互相联通的。所以确保可用。
//2.如何确定出口，入口。 入口可以从开始生成的点设置。 出口呢？出口也只要在靠近边缘的处的1的墙开洞就行(出入口都可以这么设置)。 
void creatMaze()
{
	Queue queue;

	initQueue(&queue);

	//选择一个靠近边缘的1作为起点
	Node startNode;
	startNode.x = 1;
	startNode.y = 2*(rand()%(COL/2)) + 1; // 随机某一列。

	//设置迷宫入口。
	inNode.x = startNode.x - 1;
	inNode.y = startNode.y;
	g_Maze[inNode.x][inNode.y].type = 1; //设置成路。 入口。

	//设置迷宫出口。
	outNode.x = ROW - 1;
	outNode.y =  2*(rand()%(COL/2)) + 1;
	g_Maze[outNode.x][outNode.y].type = 1; //设置成路。

	EnQueue(&queue, startNode);
	g_Maze[startNode.x][startNode.y].visited = 1;

	Node nextNode;
	//填充地图。 使用的是广度优先搜索型(非递归)。 
	while(isEmptyQueue(&queue) == 0)
	{
		//要随机的进行出队。 而不是按照队列先进先出的方式。
		if(RandDeQueue(&queue, &startNode) == -1)
			return;
		for(int i = 0; i < 4; i++) //四个方向. 右上左下
		{
			switch(i)
			{
				case 0:
					nextNode.x = startNode.x;
					nextNode.y = startNode.y + 2;
				break;
				case 1:
					nextNode.x = startNode.x - 2;
					nextNode.y = startNode.y;
				break;
				case 2:
					nextNode.x = startNode.x;
					nextNode.y = startNode.y - 2;
				break;
				case 3:
					nextNode.x = startNode.x + 2;
					nextNode.y = startNode.y;
				break;
			}

			if(nextNode.x <= 0 || nextNode.x >= ROW -1 || nextNode.y <= 0 || nextNode.y >= COL -1)
				continue;
			if(g_Maze[nextNode.x][nextNode.y].visited == 1)//已经在队列中或者访问过的就不必再入队。
				continue;
			Node midNode;
			midNode.x = (startNode.x + nextNode.x) /2;
			midNode.y = (startNode.y + nextNode.y) /2;
			g_Maze[midNode.x][midNode.y].visited = 1;
			g_Maze[midNode.x][midNode.y].type = 2;
			if(EnQueue(&queue, nextNode) == -1)
					return;
			g_Maze[nextNode.x][nextNode.y].visited = 1;

		}
		printMaze();
		usleep(1000*100);
	}
}

//广度优先遍历。（非递归）（利用队列）。
//难点：如何记录路径。 ==》解决。保存其 在遍历时 的前驱/父节点(遍历时其在遍历时的前驱节点是唯一的)，从而记录整个路径。
void BFS(Node node)
{
	Queue queue;
	initQueue(&queue);

	EnQueue(&queue, node);
	g_Maze[node.x][node.y].visited = 1;
	printVisited();

	Node nextNode , firstNode;
	while(isEmptyQueue(&queue) != 1)
	{
		DeQueue(&queue, &firstNode);

		if(firstNode.x == outNode.x && firstNode.y == outNode.y)
		{
			printf("BFS寻路成功\n");
			system("clear");
			//printBFSPath();
			break;
		}

		for(int i = 0; i < 4; i++)
		{
			switch(i)
			{
				case 0:
				nextNode.x = firstNode.x;
				nextNode.y = firstNode.y + 1;
				break;
				case 1:
				nextNode.x = firstNode.x - 1;
				nextNode.y = firstNode.y;
				break;
				case 2:
				nextNode.x = firstNode.x;
				nextNode.y = firstNode.y - 1;
				break;
				case 3:
				nextNode.x = firstNode.x + 1;
				nextNode.y = firstNode.y;
				break;
			}
			if(!isValidNode(nextNode))
				continue;
			parenNode[nextNode.x][nextNode.y] = firstNode;
			EnQueue(&queue, nextNode);
			g_Maze[nextNode.x][nextNode.y].visited = 1;
			printVisited();
		}
	}
}

//深度优先遍历。（非递归）(利用栈)
void DFS(Node node)
{
	Stack stack;
	initStack(&stack);

	pushStack(&stack, node);
	g_Maze[node.x][node.y].visited = 1;

	printVisited();

	Node topNode;

	while(isEmptyStack(&stack) != 1)
	{
		peekStack(&stack, &topNode);

		//回退时，重新添加已添加过的节点。
		if(visitNode[step-1].x == topNode.x && visitNode[step-1].y == topNode.y)
		{
			popStack(&stack, NULL);
			step--;
			//printPath();
			continue;
		}

		//避免已经添加过的节点再添加。 上面的if判断处理过了,这里也可以不必再判断。
		if(!(visitNode[step-1].x == topNode.x && visitNode[step-1].y == topNode.y))
			visitNode[step++] = topNode;
		
		//printPath();

		if(topNode.x == outNode.x && topNode.y == outNode.y)
		{
			printf("DFS寻路成功\n");
			system("clear");
			//printPath();
			break;
		}

		Node nextNode;
		int flag = 0;
		for(int i = 0; i < 4; i++)
		{
			switch(i)
			{
				case 0:
				nextNode.x = topNode.x;
				nextNode.y = topNode.y + 1;
				break;
				case 1:
				nextNode.x = topNode.x - 1;
				nextNode.y = topNode.y;
				break;
				case 2:
				nextNode.x = topNode.x;
				nextNode.y = topNode.y - 1;
				break;
				case 3:
				nextNode.x = topNode.x + 1;
				nextNode.y = topNode.y;
				break;
			}
			if(nextNode.x < 0 || nextNode.x > ROW -1 || nextNode.y < 0 || nextNode.y > COL -1)
				continue;

			if(g_Maze[nextNode.x][nextNode.y].visited == 1)
				continue;

			if(g_Maze[nextNode.x][nextNode.y].type == 0)
				continue;

			pushStack(&stack, nextNode);
			g_Maze[nextNode.x][nextNode.y].visited = 1;
			printVisited();
			flag = 1;
		}
		if(flag == 0)//没有周围的节点。 回溯。
		{
			popStack(&stack, NULL);
			step--;
			//printPath();
		}
	}
}
//深度优先遍历。(递归)
//0成功，-1失败
int DFS2(Node node)
{
	visitNode[step++] = node;
	g_Maze[node.x][node.y].visited = 1;
	printPath();
	//printf("node:x %d, y %d\n", node.x, node.y);

	if(node.x == outNode.x && node.y == outNode.y)
	{
		printf("DFS2寻路成功\n");
		system("clear");
		//printPath();
		return 0;
	}


	Node nextNode;
	int flag = 0;
	for(int i = 0; i < 4; i++)
	{
		switch(i)
		{
			case 0:
			nextNode.x = node.x;
			nextNode.y = node.y + 1;
			break;
			case 1:
			nextNode.x = node.x - 1;
			nextNode.y = node.y;
			break;
			case 2:
			nextNode.x = node.x;
			nextNode.y = node.y - 1;
			break;
			case 3:
			nextNode.x = node.x + 1;
			nextNode.y = node.y;
			break;
		}
		if(!isValidNode(nextNode))
			continue;

		if(DFS2(nextNode) != 0) //不成功
		{
			step--; //回退
			printPath();

		}
		else
		{
			flag = 1;
			break;
		}
	}

	if(flag == 1)
		return 0;
	else
		return -1;
}


int main()
{
	//初始化。
	Node node;
	node.x = -1;
	node.y = -1;
	//memset 一般用于 清空的初始化，不用于赋值的初始化。
	//memset(parenNode , node , sizeof(Node)*COL*ROW);
	//乖乖的循环初始化。
	for(int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			parenNode[i][j] = node; //可以直接赋值。 不行的话，直接用memcpy。
		}
	}

	
	 showCursor(0);
	 system("clear");
	 srand((int)time(NULL));
	 initMaze();
	 creatMaze();
	 

	 clearVisit();
	 DFS(inNode);
	 printPath();

	 clearVisit();
	 DFS2(inNode);
	 printPath();

	 clearVisit();
	 BFS(inNode);
	 printBFSPath();

	 //恢复光标
	 showCursor(1);


	/*
	for(int i = 0; i< HEIGHT; i++)
	{
		for (int j = 0; j< WIDTH; j++)
		{
			if(pow((i*i + j*j -1) , 3) - i*i*j*j*j == 0)
				printf("☐");
			else
				printf("■");
			fflush(stdout); //刷新stdout缓冲区，强制输出到stdout
			usleep(100*1000); //usleep 微秒
		}
		printf("\n");
	}
	*/

	return 0;
}