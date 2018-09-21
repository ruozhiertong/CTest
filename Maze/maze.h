/**

参考：
https://zhuanlan.zhihu.com/p/37061369
https://zhuanlan.zhihu.com/p/27381213


*/



#define COL	41//11//41
#define ROW	21// 7//21
#define NODEMAXNUM	1000 //90//

typedef struct Node {
	int x;
	int y; //坐标
	int type; // 0 墙 1 路.
	int visited; //0 未访问过， 1 访问过。   //使用过. 0 未入队。 1 在队中。 2 出队了，使用过
}Node;


//循环队列
typedef struct Queue{
	int size;
	Node * nodeArr; //数组形式存储队列。
	int front;//指向刚放置到队列中的位置。队列内。
	int rear; //指向未使用过的位置。队列内。初始化-1
	//front rear指向队列外，或者队列内的，或者一个队列内一个队列外，不同的指向，对于出队入队是有区别的。
	/*
       ---------------
		   1 5 4 3
       ---------------
	       ^     ^ 
	  front rear 都指向队列内的。 入队rear++; nodeArr[rear];	出队nodeArr[front]; front++;

	   ---------------
		   1 5 4 3
       ---------------
	      ^       ^ 
 	  front rear 都指向队列外的。入队nodeArr[rear];rear++; 	出队front++;nodeArr[front];

	*/  
}Queue;

typedef struct Stack{
	int size; //只使用top也能知道size。
	Node *nodeArr; //数组形式存储。 栈。
	int top;
}Stack;


//################Queue operation####################
void initQueue(Queue * queue);
int isEmptyQueue(Queue * queue);
int isFullQueue(Queue * queue);
int getQueueLen(Queue *queue);
//入队。从队尾入队。
int EnQueue(Queue* queue, Node node);
//出队。从队首出队。 像排队一样。
int DeQueue(Queue* queue, Node* node);
//随机出队。
int RandDeQueue(Queue* queue, Node* node);
//################End Queue operation####################



//################Stack operation####################
void initStack(Stack *stack);
int isEmptyStack(Stack * stack);
int isFullStack(Stack * stack);
int getStackLen(Stack *stack);
//入栈。
int pushStack(Stack* stack, Node node);
//出栈
int popStack(Stack* stack, Node* node);
int peekStack(Stack * stack, Node *node);
//################End Stack operation####################


void gotoxy(int x, int y);
void showCursor(int show);



void initMaze();

void creatMaze();

int isValidNode(Node node);

void clearVisit();

void printMaze();

void printVisited();

void printPath();

void printBFSPath();

void BFS(Node node);
void DFS(Node node);
int DFS2(Node node);





Node g_Maze[ROW][COL]; // 0 为墙。 只对第一个元素初始化。其余的是默认初始化值的。要想全部赋值初始化就要全部元素进行赋值。

//int visit[ROW][COL] = {0};

//迷宫出入口
Node inNode;
Node outNode;

Node parenNode[ROW][COL] = {{0,-1,-1, 0}}; //只对第一个元素初始化，其余的默认初始化。//用于在BFS中保存父节点。
Node visitNode[COL*ROW]; //保存DFS访问过的路径。
int step = 0;



