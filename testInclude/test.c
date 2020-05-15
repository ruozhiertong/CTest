//1.为避免头文件的重复包含，可以在头文件使用 #ifndef __TEST_H 等，避免这个头文件被重复包含。
//2.对于全局变量在头文件中定义，要格外注意 如果引用文件中也存在同名的变量，那么会导致覆盖 或者 出错【重复定义】。
#include "test.h"
//#include "test.h" //include 重复，如果头文件中没有处理重复，会报错的。 如果有处理，多次include也没关系,如stdio.h。

#include <stdio.h>
#include <stdio.h>


//重复定义。 全局存在同名，会报错。
//int TEST_VAR = 100;

int main()
{
	//全局与局部变量 定义同名，局部覆盖全局。
	int TEST_VAR = 100;

	printf("hello\n");
	printf("%d\n",TEST_VAR);
	return 0;
}