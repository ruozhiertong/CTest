#include <stdio.h>
#include <dirent.h>

int height = 0;
int dirNum = 0;
int fileNum = 0;

void printTreeSpace(int treeH, int hasNextDent)
{
	int i = 0;
	for(i = 0; i< treeH - 2; i++)
	{
		printf("|\t");
	}
	if(treeH - 1 > 0)
	{
		if(hasNextDent == 1)
		{
			printf("|\t");
		}
		else
		{
			printf("\t");
		}

	}

}

void printTreeDot()
{
    printf("|-------");
}


/*

	基本功能实现。 和tree命令差不多。
	不过，还有一个小问题：
|-------speedtest
|	|-------myhttptest
|	|	|-------_2X68P~X.C
|	|	|-------Makefile
|	|	|-------src
|	|	|	|-------http-client.b1
|	|	|	|-------http-client.b2
|	|	|	|-------http-client.c
|	|	|	|-------Makefile
|	|	|	|-------myhttptest.b2
|	|	|	|-------myhttptest.c
|	|-------speedtest.c
|	|-------speedtest.h
|	|-------speedtest1.c
|	|-------Speedtest2.c
在打印多层时，如myhttptest，在src后没有myhttptest下的子项目，那么就不应该打印|。 正确应该如下：
|-------speedtest
|	|-------myhttptest
|	|	|-------_2X68P~X.C
|	|	|-------Makefile
|	|	|-------src
|	|		|-------http-client.b1
|	|		|-------http-client.b2
|	|		|-------http-client.c
|	|		|-------Makefile
|	|		|-------myhttptest.b2
|	|		|-------myhttptest.c
|	|-------speedtest.c
|	|-------speedtest.h
|	|-------speedtest1.c
|	|-------Speedtest2.c


做了改进，判断是否还有下个条目。根据这个来是否打印最后的|。

不过还是存在一些问题：如：
|-------HuffmanCode
|	|-------a.c
|	|-------a.out
|	|-------huffmancode.c
|	|-------test
|			|-------1txt
|			|-------2.txt
|			|-------test_test
|	|				|-------1
|	|				|-------2.txt

在打印1.txt和2.txt时，将父节点的父节点的|打印出来。正确的应该是：
|-------HuffmanCode
|	|-------a.c
|	|-------a.out
|	|-------huffmancode.c
|	|-------test
|			|-------1txt
|			|-------2.txt
|			|-------test_test
|					|-------1
|					|-------2.txt

最终解决办法：printDirVisual2 用栈来保存回溯点。判断回溯点是否有下一个孩子，从而保证输出|。
栈保存的回溯点就是每层的一个点，回溯点个数就是层高的个数。
也是一种深度优先搜索。

*/


void printDirVisual(char * dirName, int hasNextDent)
{
	if(dirName == NULL)
		return;

	DIR * dir = opendir(dirName);
	struct dirent dentry;
	struct dirent * nextDentry;
	

	if(height == 0)
	{
		printf("%-8s\n", dirName);
	}

	height++; //注意
	nextDentry = readdir(dir);
	//多叉树的遍历（也是先序/先根遍历.递归）。
	while(nextDentry!= NULL)
    {
    	memcpy(&dentry,nextDentry, sizeof(struct dirent));

    	nextDentry = readdir(dir);

    	if(dentry.d_name[0] == '.') //隐藏文件不处理。
    	{
    		continue;
    	}
    	if(strcmp(dentry.d_name, ".") == 0 || strcmp(dentry.d_name, "..") == 0)
    	{
    		continue;
    	}

    	printTreeSpace(height , hasNextDent);
    	printTreeDot();
    	printf("%-8s\n", dentry.d_name);

    	if(dentry.d_type == DT_DIR)
    	{
    		dirNum++;
    		char childDir[128];
    		strcpy(childDir,dirName);
    		strcat(childDir,"/");
    		strcat(childDir, dentry.d_name);
    		if(nextDentry == NULL)
    			printDirVisual(childDir, 0);
    		else
    			printDirVisual(childDir, 1);
    	}
    	else
    	{
    		fileNum++;
    	}
    }
    height--; //注意
    close(dir);

}


int dirHeight = 0; //树的深度
int parentHasOtherChild[128];//数组，栈的形式。保存回溯点位置是否还有其他孩子，如果还有打印| ,没有打印空格。
int size = 0; //parentHasOtherChild数组的大小。



void printDirVisual2(char * dirName, int hasNextDent)
{
	if(dirName == NULL)
		return;

	DIR * dir = opendir(dirName);
	struct dirent dentry;
	struct dirent * nextDentry;

	if(dirHeight == 0)
	{
		printf("%-8s\n", dirName);
	}

	
	dirHeight++; //注意
	nextDentry = readdir(dir);
	//多叉树的遍历（也是先序/先根遍历）。
	while(nextDentry!= NULL)
    {
    	memcpy(&dentry,nextDentry, sizeof(struct dirent));

    	nextDentry = readdir(dir);

    	if(dentry.d_name[0] == '.') //隐藏文件不处理。
    	{
    		continue;
    	}
    	if(strcmp(dentry.d_name, ".") == 0 || strcmp(dentry.d_name, "..") == 0)
    	{
    		continue;
    	}

    	for(int i =1; i <= dirHeight; i++)
    	{
    		if(i == dirHeight)
    		{
    			printf("%-8s", "+-------");
    		}
    		else
    		{
    			if(parentHasOtherChild[i - 1] == 1)
    				printf("%-8s", "|");
    			else
    				printf("%-8s", " ");
    		}
    	}

    	printf("%-8s\n", dentry.d_name);

    	

    	if(dentry.d_type == DT_DIR)
    	{
    		dirNum++;
    		char childDir[128];
    		strcpy(childDir,dirName);
    		strcat(childDir,"/");
    		strcat(childDir, dentry.d_name);

    		if(nextDentry == NULL)
    			parentHasOtherChild[size++] = 0;
    		else
    			parentHasOtherChild[size++] = 1;

    		printDirVisual2(childDir, 0);
    		//回溯
    		parentHasOtherChild[--size] = 0;

    	}
    	else
    	{
    		fileNum++;
    	}
    }
    dirHeight--; //注意
    close(dir);

}


int main(int argc, char *argv[])
{
	if(argc > 2)
	{
		printf("usage : tree dirName\n");
		return -1;
	}

	char * dirName;

	if(argc == 1)
	{
		dirName =".";
	}
	else
	{
		dirName = argv[1];
	}	

	printDirVisual(dirName, 1);
	printf("%d\n",height);
	printf("%-4d directories, %-4d files\n", dirNum, fileNum);

    dirNum = 0;
    fileNum = 0;
	printDirVisual2(dirName, 1);

    printf("%d\n",dirHeight);
    printf("%-4d directories, %-4d files\n", dirNum, fileNum);


	return 0;
}