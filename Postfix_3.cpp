#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    char data;
    Node *left, *right;

    Node(char val) {
        data = val;
        left = right = NULL;
    }
};

class ExpressionTree {
public:
    Node *root;

    ExpressionTree() {
        root = NULL;
    }

    // Check if a character is an operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
    }

    // Build tree from postfix expression
    Node* constructFromPostfix(string postfix) {
        stack<Node*> st;
        // Traverse from left to right for postfix
        for (int i = 0; i < postfix.size(); i++) {
            char c = postfix[i];
            Node* newNode = new Node(c);

            if (isOperator(c)) {
                // Pop two operands
                newNode->right = st.top(); st.pop();
                newNode->left = st.top(); st.pop();
            }
            st.push(newNode);
        }
        return st.top();
    }

    void createExpressionTree() {
        string postfix;
        cout << "\nEnter Postfix Expression: ";
        cin >> postfix;
        root = constructFromPostfix(postfix);
        cout << "\nExpression Tree Created!\n";
    }

    // Recursive Traversals
    void recursiveInorder(Node* root) {
        if (root != NULL) {
            recursiveInorder(root->left);
            cout << root->data << " ";
            recursiveInorder(root->right);
        }
    }

    void recursivePreorder(Node* root) {
        if (root != NULL) {
            cout << root->data << " ";
            recursivePreorder(root->left);
            recursivePreorder(root->right);
        }
    }

    void recursivePostorder(Node* root) {
        if (root != NULL) {
            recursivePostorder(root->left);
            recursivePostorder(root->right);
            cout << root->data << " ";
        }
    }

    // Non-recursive Traversals
    void nonRecursiveInorder() {
        stack<Node*> s;
        Node* curr = root;
        while (curr != NULL || !s.empty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top(); s.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
    }

    void nonRecursivePreorder() {
        if (root == NULL) return;
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* temp = s.top(); s.pop();
            cout << temp->data << " ";
            if (temp->right) s.push(temp->right);
            if (temp->left) s.push(temp->left);
        }
    }

    void nonRecursivePostorder() {
        if (root == NULL) return;
        stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* temp = s1.top(); s1.pop();
            s2.push(temp);
            if (temp->left) s1.push(temp->left);
            if (temp->right) s1.push(temp->right);
        }
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
    }
};

int main() {
    ExpressionTree et;
    int choice;

    do {
        cout << "\n\n*** Expression Tree Menu ***";
        cout << "\n1. Create Expression Tree (Postfix Expression)";
        cout << "\n2. Recursive Inorder";
        cout << "\n3. Recursive Preorder";
        cout << "\n4. Recursive Postorder";
        cout << "\n5. Non-Recursive Inorder";
        cout << "\n6. Non-Recursive Preorder";
        cout << "\n7. Non-Recursive Postorder";
        cout << "\n8. Exit";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: et.createExpressionTree(); break;
            case 2: cout << "\nInorder (Recursive): "; et.recursiveInorder(et.root); break;
            case 3: cout << "\nPreorder (Recursive): "; et.recursivePreorder(et.root); break;
            case 4: cout << "\nPostorder (Recursive): "; et.recursivePostorder(et.root); break;
            case 5: cout << "\nInorder (Non-Recursive): "; et.nonRecursiveInorder(); break;
            case 6: cout << "\nPreorder (Non-Recursive): "; et.nonRecursivePreorder(); break;
            case 7: cout << "\nPostorder (Non-Recursive): "; et.nonRecursivePostorder(); break;
            case 8: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid Choice!";
        }
    } while (choice != 8);

    return 0;
}







