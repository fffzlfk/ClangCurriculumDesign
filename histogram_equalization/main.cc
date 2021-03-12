#include <iostream>
#include <memory>

struct Node {
    int val;
    std::shared_ptr<Node> left, right;
    Node(int _v) : val(_v) {}
};

std::shared_ptr<Node> create() {
    int cur;
    std::cin >> cur;
    if (!cur) return nullptr;
    auto root = std::make_shared<Node>(cur);
    root->left = create();
    root->right = create();
    return root;
}

void dfs(std::shared_ptr<Node> root) {
    if (!root) return;
    std::cout << root->val << " ";
    dfs(root->left);
    dfs(root->right);
}

int main() {
    auto root = create();
    dfs(root);
    return 0;
}