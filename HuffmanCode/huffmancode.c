#include <stdio.h>
#include <stdlib.h>


/*
前缀码。即一个字符编码的前缀不可能是另一个字符的编码。
哈夫曼编码 也是一种前缀编码，最优前缀码(对带权重的的字符进行编码，使其总长度最小，即最优。)。

对于树(森林),叶子节点 《===》 没有子树。
           根节点   《===》 没有父节点。 (森林可以有多个根节点)

*/



int traceMap[10]  = {-1}; //10  为huffman树的最大深度
int traceNum = 0;
int treeHeight = 0; //树的深度



typedef struct Noe
{
    char text;  //字符
    int weight; //权重
    int used; //在构造的时，判断是否被使用过。
    struct Node *pParent;
    struct Node *pLchild;
    struct Node *pRchild;
    struct Node *pLeafNext; //叶子节点的下一个指针，指向下一个叶子节点。

    int hasDeal;
    
}Node;

//方法1：利用递归求树的高度。
int getTreeHeight(Node *rootNode)
{
    if(rootNode == NULL)
        return 0;
    if(rootNode->pLchild == NULL && rootNode->pRchild == NULL) //叶子节点
        return 1;
    int leftChildTreeHe = getTreeHeight(rootNode->pLchild);
    int rightChildTreeHe = getTreeHeight(rootNode->pRchild);

    return leftChildTreeHe > rightChildTreeHe? leftChildTreeHe + 1 : rightChildTreeHe + 1;
}
//方法2：从遍历中求得树的高度。 递归，非递归的 遍历都可以。
int traceHeight = 0; //记录此时trace到的高度。
int maxHeight = 0;   //树的高度。
void getHeightFromTrace(Node * rootNode)
{

    traceHeight++;
    if(rootNode == NULL)
        return ;

    if(rootNode->pLchild == NULL  && rootNode->pRchild == NULL)//叶子节点。
    {
        if(traceHeight > maxHeight)
            maxHeight = traceHeight;
        return;
    }

    getHeightFromTrace(rootNode->pLchild);
    traceHeight--; //回退
    getHeightFromTrace(rootNode->pRchild);
    traceHeight--;//回退

    //traceHeight--; //结束。
}

//方法3：利用层次遍历求高度。 层次遍历一般都是非递归的，好像对于递归的不好用。
int printTreeAndGetHeight(Node *rootNode)
{

    Node* arr[100]; //保存每层的node
    int size = 0; //每层的node数目

    arr[size++] = rootNode;
    int height =0;
    while(size != 0)
    {
        Node*temp[100];
        int tmpSize = 0;
        for(int i =0; i < size ;i++)
        {
            printf("%c %d\n",arr[i]->text,arr[i]->weight);
            if(arr[i]->pLchild != NULL)
                temp[tmpSize++] = arr[i]->pLchild;
            if(arr[i]->pRchild != NULL)
                temp[tmpSize++] = arr[i]->pRchild;
        }
        height++;
        size = tmpSize;
        //arr = temp; //Wrong, 数组名是一个常量，不能改变值。
        memcpy(arr,temp, tmpSize * sizeof(Node*));
    }
    return height;
}


void swapNode(Node* nodeA, Node* nodeB)
{
    //memcpy()

    int temp;
    Node * ptempNode;


    temp = nodeA->text;
    nodeA->text = nodeB->text;
    nodeB->text = temp;

    temp = nodeA->weight;
    nodeA->weight = nodeB->weight;
    nodeB->weight = temp;

    ptempNode = nodeA->pParent;
    nodeA->pParent = nodeB->pParent;
    nodeB->pParent = ptempNode;

    ptempNode = nodeA->pLchild;
    nodeA->pLchild = nodeB->pLchild;
    nodeB->pLchild = ptempNode;


    ptempNode = nodeA->pRchild;
    nodeA->pRchild = nodeB->pRchild;
    nodeB->pRchild = ptempNode;


}


void pick2MinNode(Node nodes[], int num, Node** pMinNode, Node** p2MinNode)
{
    int min = 999;

    Node *pTempMinNode;
    Node *p2TempMinNode;

    for (int i = 0; i < num; i++)
    {
        //先和自身比较。
        if (nodes[i].used == 0 && min > nodes[i].weight)
        {
            pTempMinNode = &nodes[i];
            min = pTempMinNode->weight;
        }
        Node *pParent = nodes[i].pParent;
        //明显nodes都是叶子节点。 且都比相应的父节点的权重小。
        while (pParent)
        {
            if (pParent->used == 0 && min  > pParent->weight)
            {
                pTempMinNode = pParent;
                min = pTempMinNode ->weight;
            }
            pParent = pParent->pParent;
        }
    }

    pTempMinNode->used = 1; //使用了

    min=999;
    //寻找排除掉最大的第二大值。

    for (int i = 0; i < num; i++)
    {
        //先和自身比较。
        if (nodes[i].used == 0 && min > nodes[i].weight)
        {
            p2TempMinNode = &nodes[i];
            min = p2TempMinNode->weight;
        }
        Node *pParent = nodes[i].pParent;
        while (pParent)
        {
            if (pParent->used == 0 && min  > pParent->weight)
            {
                p2TempMinNode = pParent;
                min = p2TempMinNode ->weight;
            }
            pParent = pParent->pParent;
        }
    }

    p2TempMinNode->used = 1; //使用了


    *pMinNode = pTempMinNode;
    *p2MinNode = p2TempMinNode;
}



//根据权重排序,选择排序
void selectSortNodes(Node nodes[], int num)
{
    int min;
    int minIndex;
    for(int i = 0; i < num; i++)
    {
        min = nodes[i].weight;
        minIndex = i;
        for (int j =i + 1; j< num; j++)
        {
            if (nodes[j].weight < min)
            {
                min = nodes[j].weight;
                minIndex = j;
            }
        }
        if (minIndex != i)
            swapNode(&nodes[i],&nodes[minIndex]);
        }
}

//print
void printNodes(Node nodes[], int num)
{
    for(int i = 0; i < num; i++)
    {
        printf("%c %d\n",nodes[i].text,nodes[i].weight);
    }
}

//前序遍历。递归方式。 好理解。 但是开销大。
void printHuffmanTree(Node* rootNode)
{
    if (rootNode == NULL)
        return;

    printf("%c %d\n",rootNode->text,rootNode->weight);

    printHuffmanTree(rootNode->pLchild);

    printHuffmanTree(rootNode->pRchild);
}
//前序遍历。非递归方式。 要用到栈。一般递归转非递归，都会用到栈。
typedef struct StackNode
{
    Node* data;
    struct StackNode * next;
    struct StackNode * pre;
}StackNode;
typedef struct MyStack
{
    StackNode* top;
}MyStack;

void initStack(MyStack *myStack)
{
    myStack->top = NULL;
}
Node* pop(MyStack *myStack)
{
    if(myStack->top == NULL)
        return NULL;
    StackNode *curNode = myStack->top;
    Node* node = curNode->data;
    myStack->top = myStack->top->pre;
    if(myStack->top != NULL)
        myStack->top->next = NULL;
    free(curNode);
    return node;
}

Node* peek(MyStack *myStack)
{
    if(myStack->top == NULL)
        return NULL;
    StackNode *curNode = myStack->top;
    Node* node = curNode->data;
    return node;
}
void push(MyStack *myStack, Node *node)
{
    
    StackNode *stNode = (StackNode*)malloc(sizeof(StackNode));
    stNode->data = node;
    stNode->next = NULL;
    stNode->pre = NULL;

    //node第一个元素
    if(myStack->top == NULL)
        myStack->top = stNode;
    else
    {
        myStack->top->next = stNode;
        stNode->pre = myStack->top;
        myStack->top = stNode;
    }
}
int isEmpty(MyStack * stack)
{
    if(stack->top == NULL)
        return 1;
    else
        return 0;
}

//前序遍历。 非递归遍历。
void printHuffmanTreePreOrder(Node* rootNode)
{
    MyStack stack;
    initStack(&stack);

    push(&stack,rootNode);
    Node* p = NULL;
    while (isEmpty(&stack) != 1) 
    {
        p = pop(&stack);
        if (p != NULL) {
            printf("%c %d\n",p->text,p->weight);
            if(p->pRchild != NULL)
                push(&stack, p->pRchild);
            if(p->pLchild != NULL)
                push(&stack, p->pLchild);
        }
    }
}


//前序遍历。 非递归遍历。带标志标记
void printHuffmanTreePreOrder2(Node* rootNode)
{
    MyStack stack;
    initStack(&stack);

    push(&stack,rootNode);
    Node* p = NULL;
    while (isEmpty(&stack) != 1) 
    {
        p = pop(&stack);

        if (p != NULL) 
        {
            if(p->hasDeal)
            {
                printf("%c %d\n",p->text,p->weight);
                p->hasDeal = 0; //恢复标志位，以便其他操作
                continue;
            }
        if(p->pLchild == NULL && p->pRchild == NULL)//叶子节点
        {
            printf("%c %d\n",p->text,p->weight);
            p->hasDeal = 0; //恢复标志位，以便其他操作
            continue;
        } 

        if(p->pRchild != NULL)
            push(&stack, p->pRchild);
        if(p->pLchild != NULL)
            push(&stack, p->pLchild);
        p->hasDeal = 1;
        push(&stack, p);
    }
}
}

//中序遍历。非递归遍历。
void printHuffmanTreeInOrder(Node* rootNode)
{
    MyStack stack;
    initStack(&stack);

    //push(&stack,rootNode);
    Node* p = rootNode;
    while (p != NULL || isEmpty(&stack) != 1) 
    {
        while(p != NULL)
        {
            push(&stack, p);
            p = p->pLchild;
        }

        p = pop(&stack);
        printf("%c %d\n",p->text,p->weight);
        if(p->pRchild != NULL)
            p = p->pRchild;
        else
            p = NULL;
    }
}



//中序遍历。非递归遍历。带标记位。
void printHuffmanTreeInOrder2(Node* rootNode)
{
    MyStack stack;
    initStack(&stack);

    push(&stack,rootNode);
    Node* p = NULL;
    while (isEmpty(&stack) != 1) 
    {
        p = pop(&stack);

        if(p != NULL)
        {
            if(p->hasDeal == 1) //需要额外的标志用来标志是否已经处理过。
            {
                //visit
                printf("%c %d\n",p->text,p->weight);
                p->hasDeal = 0; //恢复标志位，以便其他操作
                continue;
            }
            //if(p->pLchild == NULL && p->pRchild == NULL)

            if(p->pRchild != NULL)
            {
                push(&stack, p->pRchild);   
            }

            p->hasDeal = 1;
            push(&stack, p);

            if(p->pLchild != NULL)
            {
                push(&stack, p->pLchild);
            }
            /*
            //虽然这种判断更优化，但是理解上还是有统一。
            if(p->pLchild == NULL)
            {
                //visit
                printf("%c %d\n",p->text,p->weight);

            }
            else
            {
                p->hasDeal = 1;
                push(&stack, p);
                push(&stack, p->pLchild);
            }
            */
        }
    }
}

void printHuffmanTreePostOrder(Node* rootNode)
{
    MyStack stack;
    initStack(&stack);
    Node*p = rootNode;
    Node *last = NULL;
    while(p != NULL ||(isEmpty(&stack))!=1)
    {
        while(p != NULL)
        {
            push(&stack, p);
            p = p->pLchild;
        }

        p = peek(&stack);
        if(p->pRchild == last)
        {
            p = pop(&stack);
            printf("%c %d\n",p->text,p->weight);
            last = p;
            p = NULL;
            continue;
        }


        if(p->pRchild != NULL)
        {
            p = p->pRchild;
        }
        else
        {
            p = pop(&stack);
            printf("%c %d\n",p->text,p->weight);
            last = p;
            p = NULL;

        }
    }

}


//后序遍历。非递归遍历。带标记位。
void printHuffmanTreePostOrder2(Node* rootNode)
{
    MyStack stack;
    initStack(&stack);

    push(&stack,rootNode);
    Node* p = NULL;
    while (isEmpty(&stack) != 1) 
    {
        p = pop(&stack);

        if(p != NULL)
        {
            if(p->hasDeal == 1) //需要额外的标志用来标志是否已经处理过。
            {
                //visit
                printf("%c %d\n",p->text,p->weight);
                p->hasDeal = 0; //恢复标志位，以便其他操作
                continue;
            }

            if(p->pLchild == NULL && p->pRchild == NULL)
            {
                //visit
                printf("%c %d\n",p->text,p->weight);
                p->hasDeal = 0; //恢复标志位，以便其他操作
                continue;
            }

            p->hasDeal = 1;
            push(&stack, p);

            if(p->pRchild != NULL)
                push(&stack, p->pRchild);

            if(p->pLchild != NULL)
                push(&stack, p->pLchild);
            
        }
    }
}

//层次遍历。 利用层次遍历，可以求树的高度/深度， 树的宽度(哪层的节点最多)， 树的最小高度，和层相关(节点位于哪层，每层多少节点)。
void printHuffmanTreeTop2Bottom(Node *rootNode)
{
    Node* arr[100]; //用于存储节点
    int size = 0;
    arr[size++] = rootNode;
    for(int i = 0; i< size; i++)
    {
        if(arr[i]->pLchild != NULL)
            arr[size++] = arr[i]->pLchild;
        if(arr[i]->pRchild != NULL)
            arr[size++] = arr[i]->pRchild;
    }

    for(int i =0; i< size; i++)
    {
        printf("%c %d\n",arr[i]->text,arr[i]->weight);

    }

}

/* void printHuffmanTree2(Node* rootNode)
{
    if (rootNode == NULL)
        return;
    Node* pNode  = rootNode;
    Node* pParentNode = NULL;
    Node* pGrandNode = NULL;

    while(pNode)
    {
        printf("%c %d\n",pNode->text,pNode->weight);
        if(pNode->pLchild != NULL)
        {
            pGrandNode = pParent;
            pParent = pNode;
            pNode = pNode->pLchild;
        }
        else if(pNode->pRchild != NULL)
        {
            pNode = pNode->pRchild;
        }
        else
        {
            pNode = pParent;
        }


        if(pLNode->pLchild == NULL)
            pLNode
    }
    while(rootNode)
    {
        printf("%c %d\n",rootNode->text,rootNode->weight);
        Node* pLchild = rootNode->pLchild;
        while(pLchild)
        {
            printf("%c %d\n",pLchild->text,pLchild->weight);
            pLchild = pLchild->pLchild;
        }
        Node* pRchild = rootNode->pRchild;
        while(pRchild)
        {
            printf("%c %d\n",pRchild->text,pRchild->weight);
            pRchild = pRchild->pRchild;
        }

    }
}
*/

void printTreeSpace(int treeH)
{
    for(int i = 0; i< treeH; i++)
    {
        printf("|\t");
    }
}
void printTreeDot()
{
    printf("+-------");
}

//有一些不足。会打印多余的|。 递归。
void printHuffmanTreeVisual(Node* rootNode)
{
    if (rootNode == NULL)
        return;

    printTreeSpace(treeHeight - 1);
    if(treeHeight != 0)
        printTreeDot();
    //打印中间节点
    printf("%-4d\n",rootNode->weight);


   //打印左子树
    if(rootNode->pLchild == NULL)
        return;
    printTreeSpace(treeHeight);
    printf("|\n");
    fflush(stdout);
   
    treeHeight++;
    printHuffmanTreeVisual(rootNode->pLchild);
    treeHeight--; //回退

   //打印右子树
    if(rootNode->pRchild == NULL)
        return;
    printTreeSpace(treeHeight);
    printf("|\n");
    fflush(stdout);

    treeHeight++;
    printHuffmanTreeVisual(rootNode->pRchild);
    treeHeight--;
}


//用到栈保存 回溯点。 非递归 
void printHuffmanTreeVisual2(Node* rootNode)
{
    if (rootNode == NULL)
        return;

    Node *pNode = rootNode;
    Node *nodeArr[100]; // 数组形式的栈。 不仅用于保存回溯点(非递归)，还用来判断该回溯点是否是有效(即是否还有其他分支)。
    int size = 0;
    int height = 0;
    while(1)
    {
        if(pNode != NULL)
        {
            for(int i = 1; i <= height; i++)
            {
                if(i == height)
                {
                    printf("%-8s", "+-------");
                }
                else
                {
                    Node* parentNode = nodeArr[ i-1 ];
                    if(parentNode != NULL && parentNode->pRchild)
                        printf("%-8s","|");
                    else
                        printf("%-8s"," ");
                }
            }
            printf("%-8d\n", pNode->weight);
            if(pNode->pRchild != NULL)
                nodeArr[size++] = pNode; //有效回溯点
            else
                nodeArr[size++] = NULL;
            pNode = pNode->pLchild;
            height++;
        }
        else
        {
            if(size == 0)
                break;
            //回溯。
            pNode = nodeArr[size - 1]; //取栈顶
            if(pNode != NULL) //该回溯点有效。即还有其他分支。
            {
                pNode = pNode->pRchild;
                nodeArr[size - 1] = NULL; //同时该回溯点置为无效。
            }
            else
            {
                size--;
                height--;  // 实际上栈中保存到个数就是树的高度大小。
            }
            
        }

    }
}


//利用前序遍历。
//遍历一遍，从根到节点 轨迹， 就是其编码
void printTrace(Node* rootNode)
{
    if (rootNode == NULL)
        return;

    //如果trace到叶子节点。 输出traceMap。
    if (rootNode->pRchild == NULL && rootNode->pLchild == NULL)
    {
        printf("%c:\n",rootNode->text);//叶子节点就是带编码的字符。 此时的traceMap就是其二进制编码。
        for(int i = 0; i < traceNum ; i ++)
        {
            printf("%d ",traceMap[i]);
        }
        printf("\n");
    }

    traceMap[traceNum] = 0 ;//左子树
    traceNum += 1;
    printTrace(rootNode->pLchild);
    traceNum -=1; //回退

    traceMap[traceNum] = 1; //右子树
    traceNum +=1;
    printTrace(rootNode->pRchild);
    traceNum -=1; //回退

}



//text 10111101100。
//因为是前缀码，因此解码时不会因为前缀的问题，产生二义性，如不会因为0100看成01和00等。
void decodeHuffCode(Node* rootNode, char text[])
{

    int num = strlen(text);
    char byte;
    Node *pNode = rootNode;
    for (int i =  0; i < num;i++)
    {
        byte = text[i];

        //到达叶子节点
        if (pNode->pRchild == NULL && pNode->pRchild == NULL)
        {
            printf("%c\n",pNode->text);
            pNode = rootNode;
        }
        if (byte == '0') //左子树方向
        {
            pNode = pNode->pLchild;
        }
        else
        {
            pNode = pNode->pRchild;
        }
    }
    if (pNode->pRchild == NULL && pNode->pRchild == NULL)
    {
        printf("%c\n",pNode->text);
    }

}


int main()
{
    Node nodes[10];
    int num;
    Node * pHunffTree = NULL;

    printf("Input the num of nodes:\n");
    scanf("%d",&num);
    //输入的字符节点，都是作为叶子节点存在的。 叶子节点也可以以链表形式存在，new出来，而非数组形式。可以在叶子节点的链表做一个链接pLeafNext。 其实都统一做成链表形式更好，更统一，都是new出来，销毁的时候都一起free。pLeafNext 也能将叶子节点进行排序了。
    printf("Input character and its weight:\n");
    for (int i = 0; i < num; i++)
    {
        //消除上一次回车\n 对%c的影响。 上次scanf遇到空白字符后，停止scanf，下一次scanf的时候会从上次停止的地方进行scanf。 如果不是%c, 则会跳过空白字符，从第一个非空白字符开始读，因此不会被上一个scanf中的回车所影响。 而%c是对所有的字符进行读取。因此上次回车，会被读入。因为scanf实际是从缓冲区去处理的。因此每次scanf的时候是从上次停止的地方进行scanf，而不是从新的地方。所以在%c的时候，可能会读到上次scanf的停止地方(即空白符)。
        //scanf 和 printf 都有用到缓冲区。每次去printf 和scanf 都是从相应的缓冲区中去处理。
        getchar();
        scanf("%c %d",&nodes[i].text , &nodes[i].weight);
        nodes[i].pLchild = NULL;
        nodes[i].pRchild = NULL;
        nodes[i].pParent = NULL;
        nodes[i].used = 0;
    }

    
    //可以不必排序。
    //sort by weight

//    selectSortNodes(nodes, num);

    printNodes(nodes, num);


    //构造huffmanTree。对于非叶子节点都是malloc出来的。 销毁的时候对于非叶子节点要free。
    //构造huffman树时发现，huffman树其实就是也是类似一个大顶堆(只是不是一个完全二叉树)。
    //每次从排好的序中选取两个构造, 构造huffman树

    int time = num -1;
    Node * pNodeA;
    Node * pNodeB;
    Node *parentNode;

    //从叶子节点nodes 构造一颗二叉树。
    //进行num-1次选取
    while (time--)
    {
        parentNode = (Node*)malloc(sizeof(Node));

        //因为每次去最大的两个节点，因此可以不必原来的排序。
        pick2MinNode(nodes, num, &pNodeA, &pNodeB);

        parentNode->weight = pNodeA->weight + pNodeB->weight;
        parentNode->pLchild = pNodeA;
        pNodeA->pParent = parentNode;
        parentNode->pRchild = pNodeB;
        pNodeB->pParent = parentNode;
        parentNode->used = 0;
        parentNode->text = 'P';
        parentNode->pParent = NULL;

    }
    //最后一个生成的节点就是根节点。

    //print huffman tree
    //printHuffmanTree(parentNode);
    printf("printHuffmanTreeVisual\n");
    printHuffmanTreeVisual(parentNode);
    printf("end  printHuffmanTreeVisual\n");

    printf("printHuffmanTreeVisual2\n");
    printHuffmanTreeVisual2(parentNode);
    printf("end printHuffmanTreeVisual2\n");


    printf("printHuffmanTreePreOrder\n");
    printHuffmanTreePreOrder(parentNode);
    printf("end  printHuffmanTreePreOrder\n");

    printf("printHuffmanTreePreOrder2\n");
    printHuffmanTreePreOrder2(parentNode);
    printf("end  printHuffmanTreePreOrder2\n");

    printf("printHuffmanTreeInOrder\n");
    printHuffmanTreeInOrder(parentNode);
    printf("end  printHuffmanTreeInOrder\n");

    printf("printHuffmanTreeInOrder2\n");
    printHuffmanTreeInOrder2(parentNode);
    printf("end  printHuffmanTreeInOrder2\n");

    printf("printHuffmanTreePostOrder\n");
    printHuffmanTreePostOrder(parentNode);
    printf("end  printHuffmanTreePostOrder\n");

    printf("printHuffmanTreePostOrder2\n");
    printHuffmanTreePostOrder2(parentNode);
    printf("end  printHuffmanTreePostOrder2\n");


    printf("printHuffmanTreeTop2Bottom\n");
    printHuffmanTreeTop2Bottom(parentNode);
    printf("end  printHuffmanTreeTop2Bottom\n");

    printf("getTree and print top2Bottom\n");
    printf("height:%d\n", printTreeAndGetHeight(parentNode));
    printf("end getTree and print top2Bottom\n");



    printf("tree treeHeight: %d\n", getTreeHeight(parentNode));

    getHeightFromTrace(parentNode);

    printf("tree treeHeight: %d %d\n", maxHeight, traceHeight);

    printTrace(parentNode);


    char decodeData[100];

    scanf("%s",decodeData);

    decodeHuffCode(parentNode,decodeData);



    return 1;
}
