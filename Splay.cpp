#include <iostream>
#include <functional>
#include <utility>

class SplayTree {
 private:

  class Node {
   public:
    Node(const long long& key, Node* left, Node* right, Node* parent, std::string value)
        : key(key), left(left), right(right), parent(parent), value(value) {}
    long long key;
    Node* left;
    Node* right;
    Node* parent;
    std::string value;
  };

 public:

  SplayTree() {
    root = nullptr;
  }

  ~SplayTree() {
    Clear(root);
  }

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  void postOrder(Node* v, const std::function<void(Node*)>& callback) {
    if (v == nullptr) {
      return;
    }
    postOrder(v->left, callback);
    postOrder(v->right, callback);
    callback(v);
  }

  std::pair<Node*, Node*> split(Node* v, long long key) {
    if (v == nullptr) {
      return std::make_pair(nullptr, nullptr);
    }
    Node* left;
    Node* right;
    if (v->key > key) {
      std::pair<Node*, Node*> t = split(v->left, key);
      v->left = t.second;
      if (t.second != nullptr) {
        p(t.second) = v;
      }
      left = t.first;
      right = v;
    } else {
      std::pair<Node*, Node*> t = split(v->right, key);
      v->right = t.first;
      if (t.first != nullptr) {
        p(t.first) = v;
      }
      right = t.second;
      left = v;
    }
    return std::make_pair(left, right);
  }

  Node* merge(Node* l, Node* r) {
    if (l == nullptr) {
      return r;
    }
    if (r == nullptr) {
      return l;
    }
    Node* m = max(l);
    splay(m);
    m->right = r;
    p(r) = m;
    return m;
  }

  void add(long long x, std::string value) {
    add(root, x, value);
  }

  void remove(long long key) {
    Node* v = find(root, key);
    splay(v);
    if (v->left != nullptr) {
      v->left->parent = nullptr;
    }
    if (v->right != nullptr) {
      v->right->parent = nullptr;
    }
    Node* tree = merge(v->left, v->right);
    delete v;
    root = tree;
    tree->parent = nullptr;
  }

  std::string& operator [] (long long key) {
    Node* v = find(root, key);
    splay(v);
    root = v;
    return v->value;
  }

  bool Find(long long value) {
    return find(root, value) != nullptr;
  }

  std::string Find2(long long value) {
    return find(root, value)->value;
  }
 private:

  void add(Node*, long long key, const std::string& value) {
    auto trees = split(root, key);
    root = merge(merge(trees.first, new Node(key, nullptr, nullptr, nullptr, value)), trees.second);
  }

  Node* max(Node* v) {
    if (v->right == nullptr) {
      return v;
    } else {
      return max(v->right);
    }
  }

  Node* find(Node* v, long long key) {
    if (v == nullptr) {
      return nullptr;
    }
    if (v->key == key) {
      return v;
    }
    if (v->key > key) {
      return find(v->left, key);
    } else {
      return find(v->right, key);
    }
  }

  Node*& p(Node* v) {
    return v->parent;
  }

  Node*& g(Node* v) {
    return p(p(v));
  }

  void rotateLeft(Node* v) {
    Node* p = this->p(v);
    Node* r = v->right;
    if (p != nullptr) {
      (p->left == v ? p->left : p->right) = r;
    }
    Node* tmp = r->left;
    r->left = v;
    v->right = tmp;
    this->p(v) = r;
    this->p(r) = p;
    if (v->right != nullptr) {
      this->p(v->right) = v;
    }
  }

  void rotateRight(Node* v) {
    Node* p = this->p(v);
    Node* l = v->left;
    if (p != nullptr) {
      (p->right == v ? p->right : p->left) = l;
    }
    Node* tmp = l->right;
    l->right = v;
    v->left = tmp;
    this->p(v) = l;
    this->p(l) = p;
    if (v->left != nullptr) {
      this->p(v->left) = v;
    }
  }

  void splay(Node* v) {
    while (p(v) != nullptr) {
      if (v == p(v)->left) {
        if (g(v) == nullptr) {
          rotateRight(p(v));          // zig
        } else if (p(v) == g(v)->left) {
          rotateRight(g(v));          // zig-zig
          rotateRight(p(v));
        } else {
          rotateRight(p(v));          // zig-zag
          rotateLeft(p(v));
        }
      } else {
        if (g(v) == nullptr) {
          rotateLeft(p(v));           // zig
        } else if (p(v) == g(v)->right) {
          rotateLeft(g(v));           // zig-zig
          rotateLeft(p(v));
        } else {
          rotateLeft(p(v));           // zig-zag
          rotateRight(p(v));
        }
      }
    }
  }

  Node* root;

};

long long Stol(std::string st) {
  long long res_st = 1;
  for (char i : st) {
    res_st *= (long long)char(i);
    res_st -= (long long)char(i) - 2;
  }
  return res_st;
}
