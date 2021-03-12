#include <stdio.h>
#include <stdlib.h>

typedef struct value {
	int v;
	struct value *next;
} LinkList;


// 创建一个长度为n的链表
LinkList *create(int n) {
	LinkList *head, *node, *end;
	// 头结点
	head = (LinkList*)malloc(sizeof(LinkList));
	end = head;
	for (int i = 0; i < n; i++) {
		node = (LinkList*)malloc(sizeof(LinkList)); // 动态申请空间
		scanf("%d", &node->v);
		end->next = node;
		end = node;
	}
	end->next = NULL;
	return head;
}

// 修改链表的第n个元素
void change(LinkList *list, int n) {
	LinkList *t = list;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}
	if (t != NULL) {
		puts("输入要修改的值");
		scanf("%d", &t->v);
	} else {
		puts("结点不存在");
	}
}

// 删除链表的第n个元素
void delet(LinkList *list, int n) {
	LinkList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		in = t;
		t = t->next;
		i++;
	}
	if (t != NULL) {
		in->next = t ->next;
		free(t); // 使用free释放内存
	} else {
		puts("结点不存在");
	}
}

// 在第n个元素后插入一个新结点
void insert(LinkList *list, int n, int value) {
	LinkList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	} if (t != NULL) {
		in = (LinkList*)malloc(sizeof(LinkList)); // 动态申请空间
		in->v = value;
		in->next = t->next;
		t->next = in;
	} else {
		puts("结点不存在");
	}
}


// 输出链表
void show(LinkList *h) {
	while (h->next != NULL) {
		h = h->next;
		printf("%d\n", h->v);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	LinkList *h = create(n);
	show(h);
	insert(h, 3, 9);
	show(h);
	delet(h, 4);
	show(h);
	return 0;
}