#include <cstdio>
#include <cassert>

const int M = 1000000; // 栈的最大容量

typedef struct {
	int element[M];
	int top;

	// 初始化栈
	void init() {
		top = -1;
	}

	// 入栈
	void push(int e) {
		assert(top - 1 < 100000);
		element[++top] = e;
	}

	// 得到栈顶元素
	int peek() {
		assert(top != -1);
		return element[top];
	}

	// 弹出栈顶元素
	void pop() {
		assert(top != -1);
		top--;
	}

	// 返回栈中元素个数
	int size() {
		return top + 1;
	}
} Stack;

int get() {
	int n;
	scanf("%d", &n);
	return n;
}

int main() {
	puts("******模拟堆栈程序******");
	Stack stk;
	stk.init();
	while (true) {
		printf("元素的个数为%d, 显示如下:\n", stk.size());
		for (int i = 0; i < stk.size(); i++)
			printf("%d ", stk.element[i]);
		puts("\n请选择栈操作：\n入栈请输入1\n出栈请输入2\n返回栈顶元素请输入3\n退出请输入0");
		int opt;
		scanf("%d", &opt);
		switch (opt) {
		case 0: return 0;
		case 1: puts("请输入要入栈的元素");
			stk.push(get());
			continue;
		case 2: stk.pop(); continue;
		case 3: printf("栈顶元素为%d\n", stk.peek());
			continue;
		}
	}
	return 0;
}