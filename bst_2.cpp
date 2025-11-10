#include<iostream>
#include<stack>
#include<string>
using namespace std;

class node {
public:
    int id; 
    string name;
    node *left, *right;
    node(int id,string name){
        this->id=id;
        this->name=name;
    }

};

class bstree {
public:
    node *root;

    bstree() {
        root = NULL;
    }

    void create();
    void insert();
    void min_node();
    void max_node();
    void recursive_inorder(node *);
    void recursive_preorder(node *);
    void recursive_postorder(node *);
    void non_inorder();
    void non_preorder();
    void non_postorder();
    void number_of_nodes_in_longest_path_from_root();
    void search();
    void print_in_asc();
    void print_in_desc();
};

void bstree::create() {
    cout << "\nCreating Root\n";
    int id;
    string name;
    cout<<"Enter the id:";
    cin>>id;
    cin.ignore();
    cout<<"Enter the name:";
    getline(cin,name);
     root=new node(id,name);
}

void bstree::insert() {
    

    if (root == NULL) {
        create();
        return;
    }
    int id;
    string name;
    cout<<"Enter the id:";
    cin>>id;
    cin.ignore();
    cout<<"Enter the name:";
    getline(cin,name);
    node* p=new node(id,name);

    

    node*temp = root;
    while (true) {
        if (p->id < temp->id) {
            if (temp->left == NULL) {
                temp->left = p;
                break;
            } else {
                temp = temp->left;
            }
        } else if (p->id > temp->id) {
            if (temp->right == NULL) {
                temp->right = p;
                break;
            } else {
                temp = temp->right;
            }
        } else {
            cout << "\nAlready Inserted Data";
            delete p;
            break;
        }
    }
}

void bstree::min_node() {
    if (root == NULL) {
        cout << "\nTree is empty.\n";
        return;
    }

    node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    cout << "\nMinimum node is: " << temp->id << temp->name<<endl;
}

void bstree::max_node() {
    if (root == NULL) {
        cout << "\nTree is empty.\n";
        return;
    }

    node *temp = root;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    cout << "\nMaximum node is: " << temp->id <<temp->name<< endl;
}

void bstree::recursive_inorder(node *root) {
    if (root != NULL) {
        recursive_inorder(root->left);
        cout << root->id <<root->name<< " ";
        recursive_inorder(root->right);
    }
}

void bstree::recursive_preorder(node *root) {
    if (root != NULL) {
        cout << root->id << root->name<<" ";
        recursive_preorder(root->left);
        recursive_preorder(root->right);
    }
}

void bstree::recursive_postorder(node *root) {
    if (root != NULL) {
        recursive_postorder(root->left);
        recursive_postorder(root->right);
        cout << root->id <<root->name<< " ";
    }
}

void bstree::non_inorder() {
    if (root == NULL) return;
    stack<node*> s;
    node *temp = root;

    while (!s.empty() || temp != NULL) {
        if (temp != NULL) {
            s.push(temp);
            temp = temp->left;
        } else {
            temp = s.top(); s.pop();
            cout << temp->id << temp->name<<" ";
            temp = temp->right;
        }
    }
}

void bstree::non_preorder() {
    if (root == NULL) return;
    stack<node*> s;
    s.push(root);

    while (!s.empty()) {
        node *temp = s.top(); s.pop();
       cout << temp->id << temp->name<<" ";
        if (temp->right) s.push(temp->right);
        if (temp->left) s.push(temp->left);
    }
}

void bstree::non_postorder() {
    if (root == NULL) return;
    stack<node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        node *temp = s1.top(); s1.pop();
        s2.push(temp);
        if (temp->left) s1.push(temp->left);
        if (temp->right) s1.push(temp->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->id << s2.top()->name<<" ";
        s2.pop();
    }
}

void bstree::number_of_nodes_in_longest_path_from_root() {
    node *temp = root;
    int count = 0;
    while (temp != NULL) {
        count++;
        if (temp->left != NULL)
            temp = temp->left;
        else
            temp = temp->right;
    }
    cout << "\nNumber of nodes in longest path from root: " << count << endl;
}

void bstree::search() {
    int key;
    cout << "\nEnter value to search: ";
    cin >> key;
    node *temp = root;
    while (temp != NULL) {
        if (key == temp->id) {
            cout << "\nValue found!";
            return;
        } else if (key < temp->id) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    cout << "\nValue not found.";
}

void bstree::print_in_asc() {
    recursive_inorder(root);
    cout << endl;
}

void bstree::print_in_desc() {
    if (root == NULL) return;
    stack<node*> s;
    node *temp = root;

    while (!s.empty() || temp != NULL) {
        if (temp != NULL) {
            s.push(temp);
            temp = temp->right;
        } else {
            temp = s.top(); s.pop();
            cout << temp->id<<temp->name<< " ";
            temp = temp->left;
        }
    }
}

int main() {
    bstree bst;
    int x;

    do {
        cout << "\n\n*** Select An Option ***";
        cout << "\n1. Create BST";
        cout << "\n2. Insert in BST";
        cout << "\n3. Find number of nodes in longest path from root";
        cout << "\n4. Minimum Node";
        cout << "\n5. Maximum Node";
        cout << "\n6. Search Node";
        cout << "\n7. Print in Ascending";
        cout << "\n8. Print in descending";
        cout << "\n9. Recursive InOrder";
        cout << "\n10. Recursive PreOrder";
        cout << "\n11. Recursive PostOrder";
        cout << "\n12. Non-Recursive InOrder";
        cout << "\n13. Non-Recursive PreOrder";
        cout << "\n14. Non-recursive PostOrder";
        cout << "\n15. Exit";
        cout << "\n\nEnter Choice: ";
        cin >> x;

        switch (x) {
            case 1: bst.create(); break;
            case 2: bst.insert(); break;
            case 3: bst.number_of_nodes_in_longest_path_from_root(); break;
            case 4: bst.min_node(); break;
            case 5: bst.max_node(); break;
            case 6: bst.search(); break;
            case 7: bst.print_in_asc(); break;
            case 8: bst.print_in_desc(); break;
            case 9: bst.recursive_inorder(bst.root); break;
            case 10: bst.recursive_preorder(bst.root); break;
            case 11: bst.recursive_postorder(bst.root); break;
            case 12: bst.non_inorder(); break;
            case 13: bst.non_preorder(); break;
            case 14: bst.non_postorder(); break;
            case 15: cout << "\nExiting Program...\n\n"; break;
            default: cout << "\nInvalid Choice!\n\n";
        }
    } while (x != 15);

    return 0;
}






/**** Select An Option *** output Example ****
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 1

Creating Root

Enter the data: 50


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 2

Enter the data: 30


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 2

Enter the data: 70


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 2

Enter the data: 20


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 2

Enter the data: 40


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 2

Enter the data: 60


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 2

Enter the data: 80


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 7
20 30 40 50 60 70 80 


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 3

Number of nodes in longest path from root: 3


*** Select An Option ***
1. Create BST
2. Insert in BST
3. Find number of nodes in longest path from root
4. Minimum Node
5. Maximum Node
6. Search Node
7. Print in Ascending
8. Print in descending
9. Recursive InOrder
10. Recursive PreOrder
11. Recursive PostOrder
12. Non-Recursive InOrder
13. Non-Recursive PreOrder
14. Non-recursive PostOrder
15. Exit

Enter Choice: 4

Minimum node is: 20

*/

/*| **Function**                                  | **Operation**          | **Time Complexity** | **Explanation**                                                                                      |
| --------------------------------------------- | ---------------------- | ------------------- | ---------------------------------------------------------------------------------------------------- |
| `create()`                                    | Create root node       | **O(1)**            | Just one node creation                                                                               |
| `insert()`                                    | Insert new node        | **O(h)**            | Traverses path from root to leaf; `h` = height of BST → **O(log n)** (balanced) or **O(n)** (skewed) |
| `min_node()`                                  | Find smallest value    | **O(h)**            | Traverses leftmost path                                                                              |
| `max_node()`                                  | Find largest value     | **O(h)**            | Traverses rightmost path                                                                             |
| `recursive_inorder()`                         | Inorder traversal      | **O(n)**            | Visits every node exactly once                                                                       |
| `recursive_preorder()`                        | Preorder traversal     | **O(n)**            | Visits every node exactly once                                                                       |
| `recursive_postorder()`                       | Postorder traversal    | **O(n)**            | Visits every node exactly once                                                                       |
| `non_inorder()`                               | Inorder (using stack)  | **O(n)**            | Every node pushed/popped once                                                                        |
| `non_preorder()`                              | Preorder (using stack) | **O(n)**            | Same — each node processed once                                                                      |
| `non_postorder()`                             | Postorder (two stacks) | **O(n)**            | Each node pushed/popped a constant number of times                                                   |
| `number_of_nodes_in_longest_path_from_root()` | Height path count      | **O(h)**            | Traverses one branch from root                                                                       |
| `search()`                                    | Search a key           | **O(h)**            | Worst-case height traversal                                                                          |
| `print_in_asc()`                              | Inorder print          | **O(n)**            | Prints all nodes (same as inorder)                                                                   |
| `print_in_desc()`                             | Reverse inorder        | **O(n)**            | Visits all nodes once                                                                                |
*/