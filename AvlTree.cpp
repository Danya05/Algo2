//

#include <iostream>

#include <cstdlib>

#include <cmath>

#include <utility>

#include <random>

class Treap {
  struct Node {
    Node(long long x, long long y)
        : x(x), y(y), left(nullptr), right(nullptr) {}

    long long x;
    long long y;
    long long depth{0};
    long long count{1};
    Node* left;
    Node* right;
  };

 public:
  Treap() : root_(nullptr) {}

  ~Treap() { Clear(root_); }

  long long GetCount(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->count;
  }

  void UpdateCount(Node* node) {
    node->count = GetCount(node->left) + GetCount(node->right) + 1;
  }

  bool Search(long long value) {
    return Search(nullptr, root_, value).second != nullptr;
  }

  void Insert(long long value) {
    if (Search(value)) {
      return;
    }
    /*std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> ran(1,pow(10, 9));
    int y = (int)ran(rng);*/
    int y = random();
    Node* node = new Node(value, y);
    std::pair<Node*, Node*> a;
    a = Split(root_, value);
    Node* left = a.first;
    Node* right = a.second;
    root_ = Merge(Merge(left, node), right);
  }

  void Erase(long long value) {
    if (!Search(value)) {
      return;
    }
    std::pair<Node*, Node*> a = Split(root_, value);
    Node* left_with_value = a.first;
    Node* right = a.second;
    std::pair<Node*, Node*> b = Split(left_with_value, value - 1);
    Node* left = b.first;
    Node* value_tree = b.second;
    delete value_tree;
    root_ = Merge(left, right);
  }

  long long FindMin(long long value) { return FindMin(root_, value); }

  long long FindMax(long long value) { return FindMax(root_, value); }

  long long KStatic(long long value) { return KStatic(root_, value); }

 private:
  long long FindMax(Node* node, long long value) {
    std::pair<Node*, Node*> a;
    a = Split1(node, value);
    Node* node1 = a.first;
    if (node1 == nullptr) {
      return -1;
    }
    while (node1->right != nullptr) {
      node1 = node1->right;
    }
    long long x = node1->x;
    *node = *Merge(a.first, a.second);
    return x;
  }

  long long FindMin(Node* node, long long value) {
    std::pair<Node*, Node*> a;
    a = Split(node, value);
    Node* node1 = a.second;
    if (node1 == nullptr) {
      return -1;
    }
    while (node1->left != nullptr) {
      node1 = node1->left;
    }
    long long x = node1->x;
    *node = *Merge(a.first, a.second);
    return x;
  }

  std::pair<Node*, Node*> Search(Node* parent, Node* node, long long value) {
    if (node == nullptr) {
      return {parent, node};
    }
    if (value == node->x) {
      return {parent, node};
    }
    if (value < node->x) {
      return Search(node, node->left, value);
    }
    return Search(node, node->right, value);
  }

  std::pair<Node*, Node*> Split1(Node* node, long long key) {
    std::pair<Node*, Node*> a;
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key <= node->x) {
      a = Split(node->left, key);
      Node* left = a.first;
      Node* right = a.second;
      node->left = right;
      CalcHeight(left);
      CalcHeight(node);
      return {left, node};
    }
    a = Split(node->right, key);
    Node* left = a.first;
    Node* right = a.second;
    node->right = left;
    CalcHeight(right);
    CalcHeight(node);
    return {node, right};
  }

  std::pair<Node*, Node*> Split(Node* node, long long key) {
    std::pair<Node*, Node*> a;
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key < node->x) {
      a = Split(node->left, key);
      Node* left = a.first;
      Node* right = a.second;
      node->left = right;
      CalcHeight(left);
      CalcHeight(node);
      UpdateCount(node);
      return {left, node};
    }
    a = Split(node->right, key);
    Node* left = a.first;
    Node* right = a.second;
    node->right = left;
    CalcHeight(right);
    CalcHeight(node);
    UpdateCount(node);
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
      CalcHeight(left);
      UpdateCount(left);
      return left;
    }
    right->left = Merge(left, right->left);
    CalcHeight(right);
    UpdateCount(right);
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

  static long long Height(Node* node) {
    return node == nullptr ? 0 : static_cast<long long>(node->depth);
  }

  static long long BalanceFactor(Node* node) {
    return node == nullptr ? 0 : Height(node->right) - Height(node->left);
  }

  static void CalcHeight(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->depth = std::max(Height(node->left), Height(node->right)) + 1;
  }

  long long KStatic(Node* node, long long value) {
    if (node == nullptr) {
      return -1;
    }
    if (value == GetCount(node->left)) {
      return node->x;
    }
    if (value == GetCount(node->left)) {
      return KStatic(node->left, value);
    }
    return KStatic(node->right, value - GetCount(node->left) - 1);
  }

  Node* root_;
};
