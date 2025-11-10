#include <iostream>
#include <cstring>
using namespace std;

class AVLnode {
public:
    char keyword[20], meaning[100];
    int ht;
    AVLnode *left, *right;
};

class AVLtree {
public:
    AVLnode *root;
    AVLtree() { root = NULL; }

    int height(AVLnode *T);
    int BF(AVLnode *T);

    AVLnode* rotate_left(AVLnode *x);
    AVLnode* rotate_right(AVLnode *x);
    AVLnode* LL(AVLnode *T);
    AVLnode* RR(AVLnode *T);
    AVLnode* LR(AVLnode *T);
    AVLnode* RL(AVLnode *T);

    AVLnode* insert(AVLnode *root, char key[20], char mean[100]);
    AVLnode* deleteNode(AVLnode *root, char key[20]);
    AVLnode* find(AVLnode *root, char key[20], int &comparisons);
    AVLnode* update(AVLnode *root, char key[20], char mean[100]);

    void inorderAsc(AVLnode *root);
    void inorderDesc(AVLnode *root);
};

int AVLtree::height(AVLnode *T) {
    if (T == NULL) return -1;
    int lh = height(T->left);
    int rh = height(T->right);
    return (lh > rh ? lh : rh) + 1;
}

int AVLtree::BF(AVLnode *T) {
    if (T == NULL) return 0;
    return height(T->left) - height(T->right);
}

AVLnode* AVLtree::rotate_left(AVLnode *x) {
    AVLnode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

AVLnode* AVLtree::rotate_right(AVLnode *x) {
    AVLnode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

AVLnode* AVLtree::LL(AVLnode *T) { return rotate_right(T); }
AVLnode* AVLtree::RR(AVLnode *T) { return rotate_left(T); }
AVLnode* AVLtree::LR(AVLnode *T) {
    T->left = rotate_left(T->left);
    return rotate_right(T);
}
AVLnode* AVLtree::RL(AVLnode *T) {
    T->right = rotate_right(T->right);
    return rotate_left(T);
}

AVLnode* AVLtree::insert(AVLnode *root, char key[20], char mean[100]) {
    if (root == NULL) {
        AVLnode *temp = new AVLnode;
        strcpy(temp->keyword, key);
        strcpy(temp->meaning, mean);
        temp->left = temp->right = NULL;
        temp->ht = 0;
        return temp;
    }

    if (strcmp(key, root->keyword) < 0) {
        root->left = insert(root->left, key, mean);
        if (BF(root) == 2) {
            if (strcmp(key, root->left->keyword) < 0)
                root = LL(root);
            else
                root = LR(root);
        }
    } else if (strcmp(key, root->keyword) > 0) {
        root->right = insert(root->right, key, mean);
        if (BF(root) == -2) {
            if (strcmp(key, root->right->keyword) > 0)
                root = RR(root);
            else
                root = RL(root);
        }
    } else {
        cout << "\nDuplicate Key not allowed!\n";
    }

    root->ht = height(root);
    return root;
}

AVLnode* AVLtree::find(AVLnode *root, char key[20], int &comparisons) {
    if (root == NULL) return NULL;
    comparisons++;
    if (strcmp(key, root->keyword) == 0) return root;
    else if (strcmp(key, root->keyword) < 0) return find(root->left, key, comparisons);
    else return find(root->right, key, comparisons);
}

void AVLtree::inorderAsc(AVLnode *root) {
    if (root != NULL) {
        inorderAsc(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inorderAsc(root->right);
    }
}
void AVLtree::inorderDesc(AVLnode *root) {
    if (root != NULL) {
        inorderDesc(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        inorderDesc(root->left);
    }
}

AVLnode* AVLtree::deleteNode(AVLnode *root, char key[20]) {
    if (root == NULL) return NULL;

    if (strcmp(key, root->keyword) < 0)
        root->left = deleteNode(root->left, key);
    else if (strcmp(key, root->keyword) > 0)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLnode *temp = root->left ? root->left : root->right;
            if (temp == NULL) { temp = root; root = NULL; }
            else *root = *temp;
            delete temp;
        } else {
            AVLnode *succ = root->right;
            while (succ->left != NULL) succ = succ->left;
            strcpy(root->keyword, succ->keyword);
            strcpy(root->meaning, succ->meaning);
            root->right = deleteNode(root->right, succ->keyword);
        }
    }

    if (root == NULL) return root;

    root->ht = height(root);
    if (BF(root) == 2) {
        if (BF(root->left) >= 0) root = LL(root);
        else root = LR(root);
    }
    else if (BF(root) == -2) {
        if (BF(root->right) <= 0) root = RR(root);
        else root = RL(root);
    }

    return root;
}

AVLnode* AVLtree::update(AVLnode *root, char key[20], char mean[100]) {
    if (root == NULL) return NULL;

    if (strcmp(key, root->keyword) == 0) {
        cout << "Updating the meaning of " << key << endl;
        strcpy(root->meaning, mean);
        cout << "Updated meaning of " << key << " is " << mean << endl;
    } else if (strcmp(key, root->keyword) < 0) {
        root->left = update(root->left, key, mean);
    } else {
        root->right = update(root->right, key, mean);
    }
    return root;
}

int main() {
    AVLtree dict;
    int ch;
    char key[20], mean[100];
    do {
        cout << "\n*** Dictionary Using AVL ***";
        cout << "\n1. Insert";
        cout << "\n2. Find";
        cout << "\n3. Delete";
        cout << "\n4. Update";
        cout << "\n5. Display Ascending";
        cout << "\n6. Display Descending";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "Enter keyword: "; cin >> key;
            cout << "Enter meaning: "; cin.ignore(); cin.getline(mean, 100);
            dict.root = dict.insert(dict.root, key, mean);
            break;
        case 2: {
            cout << "Enter keyword to find: "; cin >> key;
            int comp = 0;
            AVLnode *res = dict.find(dict.root, key, comp);
            if (res != NULL)
                cout << "Found! Meaning = " << res->meaning << "\nComparisons = " << comp << endl;
            else
                cout << "Not Found! Comparisons = " << comp << endl;
            break;
        }
        case 3:
            cout << "Enter keyword to delete: "; cin >> key;
            dict.root = dict.deleteNode(dict.root, key);
            cout << "Deleted (if existed).\n";
            break;
        case 4:
            cout << "Enter keyword to Update: "; cin >> key;
            cout << "Enter new meaning: "; cin.ignore(); cin.getline(mean, 100);
            dict.root = dict.update(dict.root, key, mean);
            break;
        case 5:
            cout << "\nDictionary in Ascending Order:\n";
            dict.inorderAsc(dict.root);
            break;
        case 6:
            cout << "\nDictionary in Descending Order:\n";
            dict.inorderDesc(dict.root);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (ch != 7);

    return 0;
}


/*
*** Dictionary Using AVL ***
1. Insert
2. Find
3. Delete
4. Update
5. Display Ascending
6. Display Descending
7. Exit
Enter choice: 1
Enter keyword: cat
Enter meaning: a animal

*** Dictionary Using AVL ***
1. Insert
2. Find
3. Delete
4. Update
5. Display Ascending
6. Display Descending
7. Exit
Enter choice: 1
Enter keyword: dog
Enter meaning: a animal

*** Dictionary Using AVL ***
1. Insert
2. Find
3. Delete
4. Update
5. Display Ascending
6. Display Descending
7. Exit
Enter choice: 5

Dictionary in Ascending Order:
cat : a animal
dog : a animal

*** Dictionary Using AVL ***
1. Insert
2. Find
3. Delete
4. Update
5. Display Ascending
6. Display Descending
7. Exit
Enter choice: 2
Enter keyword to find: cat
Found! Meaning = a animal
Comparisons = 1

*** Dictionary Using AVL ***
1. Insert
2. Find
3. Delete
4. Update
5. Display Ascending
6. Display Descending
7. Exit
Enter choice: */

