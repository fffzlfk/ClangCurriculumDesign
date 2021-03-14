/*
 * 使用智能指针实现动态链表
 * 无需手动释放空间
 */

#include <cassert>
#include <iostream>
#include <memory>
using namespace std;

template<typename T>
struct LinkedListNode {
    T val;
    shared_ptr<LinkedListNode> next;
    LinkedListNode() = default;
    LinkedListNode(T _val) : val(_val) {}
};

// 创建一个长度为n的链表
template<typename T>
auto createLinkedList(int N) {
    auto head = make_shared<LinkedListNode<T>>();
    auto end = head;
    T t;
    puts("请输入要添加的元素，以空格分隔");
    for (int i = 0; i < N; i++) {
        cin >> t;
        auto node = make_shared<LinkedListNode<T>>(t);
        end->next = node;
        end = node;
    }
    end->next = nullptr;
    return head;
}


// 在第n个元素后插入一个新结点
template<typename T>
void insertNode(shared_ptr<LinkedListNode<T>> head) {
    int n;
    T val;
    puts("请输入要插入的位置和元素");
    cin >> n >> val;
    int i = 0;
    auto t = head;
    while (i < n && t != nullptr) {
        t = t->next;
        i++;
    }
    if (t != nullptr) {
        auto node = make_shared<LinkedListNode<T>>(val);
        node->next = t->next;
        t->next = node;
    } else {
        puts("结点不存在");
    }
}

// 删除链表的第n个元素
template<typename T>
void delNode(shared_ptr<LinkedListNode<T>> head) {
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

// 输出链表
template<typename T>
void printLinkedList(shared_ptr<LinkedListNode<T>> head) {
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
    auto h = createLinkedList<int>(n);
    int opt;
    while (true) {
        puts("输入1插入结点\n输入2删除结点\n输入3打印链表\n输入0退出");
        cin >> opt;
        switch (opt) {
            case 1:
                insertNode(h);
                continue;
            case 2:
                delNode(h);
                continue;
            case 3:
                printLinkedList(h);
                continue;
            default:
                return 0;
        }
    }
    return 0;
}