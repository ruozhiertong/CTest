#include <stdio.h>
int gA = 10;

class TestClass
{
	//C++ 不像java那样，在类中的方法外 设置代码块。 只能在一般函数(和C一样) 和 类中方法中设置代码块。
	// {
	// 	int gA += 1;
	// 	printf("%d\n",gA );
	// }
	
};

//C中代码块只能放在方法中，而不能放在方法外。

static void test()
{

	int a = 0;
	{
		//代码块中的作用域和方法中的作用域不同，是单独的作用域。
		//而且代码块中的变量可以使用static进行修饰，使其成为全局的作用域，只被定义一次。
		//http://c.biancheng.net/view/1860.html
		//https://blog.csdn.net/keyeagle/article/details/6708077
		//java中 方法中的代码块本身不能被static修饰，而且代码块中的变量也无法被static修饰，方法中的变量也是无法被static修饰的。
		static int a = 10;
		a+=1;
		printf("%d\n", a);

	}

	printf("%d\n",a);
}


int main(){

	test();


	test();

	return 0;
}