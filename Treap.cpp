#include <iostream>

#include <cstdlib>

#include <utility>

class Treap {
  struct Node {
    Node(int x, int y) : x(x), y(y), left(nullptr), right(nullptr) {}

    int x;
    int y;
    Node* left;
    Node* right;
  };

 public:
  Treap() : root_(nullptr) {}

  ~Treap() { Clear(root_); }

  bool Search(int value) {
    return Search(nullptr, root_, value).second != nullptr;
  }

  void Insert(int value) {
    if (Search(value)) {
      return;
    }
    int y = (int)random();
    Node* node = new Node(value, y);
    std::pair<Node*, Node*> a;
    a = Split(root_, value);
    Node* left = a.first;
    Node* right = a.second;
    root_ = Merge(Merge(left, node), right);
  }

  int FindMin(int value) { return FindMin(root_, value); }

 private:
  int FindMin(Node* node, int value) {
    std::pair<Node*, Node*> a;
    a = Split(node, value);
    Node* node1 = a.second;
    if (node1 == nullptr) {
      return -1;
    }
    while (node1->left != nullptr) {
      node1 = node1->left;
    }
    int x = node1->x;
    *node = *Merge(a.first, a.second);
    return x;
  }

  std::pair<Node*, Node*> Search(Node* parent, Node* node, int value) {
    if (node == nullptr) {
      return {parent, node};
    }
    if (value == node->x) {
      return {parent, node};
    }
    if (value <= node->x) {
      return Search(node, node->left, value);
    }
    return Search(node, node->right, value);
  }

  std::pair<Node*, Node*> Split(Node* node, int key) {
    std::pair<Node*, Node*> a;
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key <= node->x) {
      a = Split(node->left, key);
      Node* left = a.first;
      Node* right = a.second;
      node->left = right;
      return {left, node};
    }
    a = Split(node->right, key);
    Node* left = a.first;
    Node* right = a.second;
    node->right = left;
    return {node, right};
  }

  Node* Merge(Node* left, Node* right) {
    if (left == nullptr) {
      return right;
    }
    if (right == nullptr) {
      return left;
    }
    if (left->y > right->y) {
      left->right = Merge(left->right, right);
      return left;
    }
    right->left = Merge(left, right->left);
    return right;
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  Node* root_;
};
