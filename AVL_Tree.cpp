#include <iostream>
#include <vector>

class AVLTree {
 public:
  struct Node {
    Node* left{nullptr};
    Node* right{nullptr};
    std::pair<long long, std::string> value;
    unsigned char height{0};
  };

  AVLTree() : root_(nullptr) {}

  void Insert(long long value, std::string st) {
    root_ = Insert(root_, value, st);
  }

  ~AVLTree() {
    Clear();
    delete root_;
  }

  void Clear() {
    if (root_ != nullptr) {
      Clear(root_);
    }
    root_ = nullptr;
  }

  bool Find(long long value) { return Find(root_, value); }

  void Erase(long long value) { root_ = Erase(root_, value); }

  std::string Search(long long value) { return Search(root_, value); }

 private:
  std::string Search(Node* node, long long value) {
    if (node == nullptr) {
      return "";
    }
    if (node->value.first == value) {
      return node->value.second;
    }
    if (value < node->value.first) {
      return Search(node->left, value);
    }
    return Search(node->right, value);
  }

  static Node* Erase(Node* node, long long value) {
    if (node == nullptr) {
      return node;
    }
    if (node->value.first == value) {
      if (node->right == nullptr) {
        Node* temp = node->left;
        delete node;
        return FixBalance(temp);
      }
      Node* right_min = FindMin(node->right);
      node->right = UnlinkMin(node->right);
      right_min->left = node->left;
      right_min->right = node->right;
      delete node;
      return FixBalance(right_min);
    }
    if (value < node->value.first) {
      node->left = Erase(node->left, value);
    } else {
      node->right = Erase(node->right, value);
    }
    return FixBalance(node);
  }

  static Node* FindMin(Node* node) {
    if (node->left == nullptr) {
      return node;
    }
    return FindMin(node->left);
  }

  static Node* UnlinkMin(Node* node) {
    if (node->left == nullptr) {
      return node->right;
    }
    node->left = UnlinkMin(node->left);
    return FixBalance(node);
  }

  static bool Find(Node* node, long long value) {
    if (node == nullptr) {
      return false;
    }
    if (node->value.first == value) {
      return true;
    }
    if (value < node->value.first) {
      return Find(node->left, value);
    }
    return Find(node->right, value);
  }

  static void Clear(Node* node) {
    if (node->left != nullptr) {
      Clear(node->left);
    }
    if (node->right != nullptr) {
      Clear(node->right);
    }
    delete node;
  }

  static Node* Insert(Node* node, long long value, std::string st) {
    if (node == nullptr) {
      Node* new_node = new Node;
      new_node->value.first = value;
      new_node->value.second = st;
      return new_node;
    }
    if (value <= node->value.first) {
      node->left = Insert(node->left, value, st);
    } else {
      node->right = Insert(node->right, value, st);
    }
    return FixBalance(node);
  }

  static int Height(Node* node) {
    return node == nullptr ? 0 : static_cast<int>(node->height);
  }

  static int BalanceFactor(Node* node) {
    return node == nullptr ? 0 : Height(node->right) - Height(node->left);
  }

  static void CalcHeight(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->height = std::max(Height(node->left), Height(node->right)) + 1;
  }

  static Node* RightRotate(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    CalcHeight(p);
    CalcHeight(q);
    return q;
  }

  static Node* LeftRotate(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    CalcHeight(q);
    CalcHeight(p);
    return p;
  }

  static Node* FixBalance(Node* node) {
    CalcHeight(node);
    if (BalanceFactor(node) == 2) {
      if (BalanceFactor(node->right) == -1) {
        node->right = RightRotate(node->right);
      }
      return LeftRotate(node);
    }
    if (BalanceFactor(node) == -2) {
      if (BalanceFactor(node->left) == 1) {
        node->left = LeftRotate(node->left);
      }
      return RightRotate(node);
    }
    return node;
  }

  Node* root_{nullptr};
};

long long Stol(std::string st) {
  long long res_st = 1;
  for (char i : st) {
    res_st *= (long long)char(i);
    res_st -= (long long)char(i) - 2;
  }
  return res_st;
}
