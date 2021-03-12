/*
 * 使用智能指针实现动态链表
 * 无需手动释放空间
 */

#include <cassert>
#include <iostream>
#include <memory>
using namespace std;

struct LinkedListNode {
    int val;
    shared_ptr<LinkedListNode> next;
    LinkedListNode() = default;
    LinkedListNode(int v) : val(v) {}
};

// 创建一个长度为n的链表
auto create(int n) {
    auto head = make_shared<LinkedListNode>();
    auto end = head;
    int val;
    puts("请输入要添加的元素，以空格分隔");
    for (int i = 0; i < n; i++) {
        cin >> val;
        auto node = make_shared<LinkedListNode>(val);
        end->next = node;
        end = node;
    }
    end->next = nullptr;
    return head;
}

// 在第n个元素后插入一个新结点
void insert(shared_ptr<LinkedListNode> head) {
    int n, val;
    puts("请输入要插入的位置和元素");
    cin >> n >> val;
    int i = 0;
    auto t = head;
    while (i < n && t != nullptr) {
        t = t->next;
        i++;
    }
    if (t != nullptr) {
        auto node = make_shared<LinkedListNode>(val);
        node->next = t->next;
        t->next = node;
    } else {
        puts("结点不存在");
    }
}

// 删除链表的第n个元素
void del(shared_ptr<LinkedListNode> head) {
    int n;
    puts("请输入要删除结点的位置");
    cin >> n;
    auto cur = head, pre = cur;
    int i = 0;
    while (i < n && cur) {
        pre = cur;
        cur = cur->next;
        i++;
    }
    if (cur != nullptr) {
        pre->next = cur->next;
    } else {
        puts("结点不存在");
    }
}

void print(shared_ptr<LinkedListNode> head) {
    while (head->next) {
        head = head->next;
        cout << head->val << " ";
    }
    cout << endl;
}

int main() {
    int n;
    puts("请输入要创建链表的长度");
    cin >> n;
    auto h = create(n);
    int opt;
    while (true) {
        puts("输入1插入结点\n输入2删除结点\n输入3打印链表\n输入0退出");
        cin >> opt;
        switch (opt) {
            case 1:
                insert(h);
                continue;
            case 2:
                del(h);
                continue;
            case 3:
                print(h);
                continue;
            default:
                return 0;
        }
    }
    print(h);
    return 0;
}