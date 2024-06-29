

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    void addRecursive(Node* current, int value) {
        if (value < current->data) {
            if (current->left == nullptr) {
                current->left = new Node(value);
            } else {
                addRecursive(current->left, value);
            }
        } else {
            if (current->right == nullptr) {
                current->right = new Node(value);
            } else {
                addRecursive(current->right, value);
            }
        }
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* removeRecursive(Node* current, int value) {
        if (current == nullptr) {
            return current;
        }

        if (value < current->data) {
            current->left = removeRecursive(current->left, value);
        } else if (value > current->data) {
            current->right = removeRecursive(current->right, value);
        } else {
            if (current->left == nullptr) {
                Node* temp = current->right;
                delete current;
                return temp;
            } else if (current->right == nullptr) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            Node* temp = findMin(current->right);
            current->data = temp->data;
            current->right = removeRecursive(current->right, temp->data);
        }
        return current;
    }

    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void add(int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            addRecursive(root, value);
        }
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }

    void preorderTraversal() {
        cout << "Preorder Traversal: ";
        preorderRecursive(root);
        cout << endl;
    }

    void inorderTraversal() {
        cout << "Inorder Traversal: ";
        inorderRecursive(root);
        cout << endl;
    }

    void postorderTraversal() {
        cout << "Postorder Traversal: ";
        postorderRecursive(root);
        cout << endl;
    }

    void preorderRecursive(Node* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }

    void postorderRecursive(Node* node) {
        if (node != nullptr) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            cout << node->data << " ";
        }
    }
};

int main() {
    BinaryTree tree;

    tree.add(5);
    tree.add(3);
    tree.add(7);
    tree.add(2);
    tree.add(4);

    tree.inorderTraversal();

    tree.remove(3);

    tree.preorderTraversal();
    tree.postorderTraversal();

    return 0;
}