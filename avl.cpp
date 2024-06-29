


#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y;
    }

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) {
            return rotateRight(node);
        }
        // Right Right Case
        if (balance < -1 && value > node->right->data) {
            return rotateLeft(node);
        }
        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* removeRecursive(Node* root, int value) {
        if (root == nullptr) {
            return root;
        }

        if (value < root->data) {
            root->left = removeRecursive(root->left, value);
        } else if (value > root->data) {
            root->right = removeRecursive(root->right, value);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = removeRecursive(root->right, temp->data);
            }
        }

        if (root == nullptr) {
            return root;
        }

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = balanceFactor(root);

        // Left Left Case
        if (balance > 1 && balanceFactor(root->left) >= 0) {
            return rotateRight(root);
        }

// Left Right Case
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        // Right Right Case
        if (balance < -1 && balanceFactor(root->right) <= 0) {
            return rotateLeft(root);
        }
        // Right Left Case
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }

    int minValue() {
        Node* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    int maxValue() {
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorderRecursive(root);
        cout << endl;
    }

    bool search(int value) {
      Node* current = root;
      while (current != nullptr) {
          if (value == current -> data)
              return true;
          else if (value < current -> data)
              current = current -> left;
          else
              current = current -> right;
      }
      return false;
    }
};

int main() {
    AVLTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);

    tree.inorderTraversal();

    tree.remove(3);

    tree.inorderTraversal();

    cout << "Min Value: " << tree.minValue() << endl;
    cout << "Max Value: " << tree.maxValue() << endl;

    cout << "Search for 4: " << (tree.search(4) ? "Found" : "Not Found") << endl;
    cout << "Search for 10: " << (tree.search(10) ? "Found" : "Not Found") << endl;

    return 0;
}