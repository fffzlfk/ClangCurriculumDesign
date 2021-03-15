#include <iostream>
#include <memory>
#include <vector>

struct Node {
    int val;
    std::shared_ptr<Node> left, right;
    Node(int _v) : val(_v) {}
};

std::shared_ptr<Node> create(std::vector<int>::iterator &begin,
                             const std::vector<int>::iterator end) {
    if (begin >= end || *begin == -1) return nullptr;
    auto root = std::make_shared<Node>(*begin);
    root->left = create(++begin, end);
    root->right = create(++begin, end);
    return root;
}

void dfs(std::shared_ptr<Node> root) {
    if (!root) return;
    std::cout << root->val << " ";
    dfs(root->left);
    dfs(root->right);
}

int main() {
    std::vector<int> v{1, 2, 4, -1, -1, -1, 3};
    auto it = v.begin();
    auto root = create(it, v.end());
    dfs(root);
    return 0;
}