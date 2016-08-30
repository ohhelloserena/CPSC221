#ifdef _RBTREE_H_
using namespace std;
#include <algorithm>

// default constructor
template <typename T>
RBTree<T>::RBTree() {
    root = NULL;
    size = 0;
}

// copy constructor, performs deep copy of parameter
template <typename T>
RBTree<T>::RBTree(const RBTree<T>& rbtree) {
    root = CopyTree(rbtree.root, NULL);
    size = rbtree.Size();
    
}

// destructor
// Must deallocate memory associated with all nodes in tree
template <typename T>
RBTree<T>::~RBTree() {
    RemoveAll();
    size = 0;
    root = NULL;
}


// overloaded assignment operator
template <typename T>
RBTree<T>& RBTree<T> :: operator=(const RBTree<T>& rbtree) {
    if (this != &rbtree) {
        RemoveAll();
        root = CopyTree(rbtree.root, NULL);
        size = rbtree.Size();
    }
    return *this;
}



// recursive helper function for deep copy
// creates a new node based on sourcenode's contents, links back to parentnode,
//   and recurses to create left and right children
template <typename T>
Node<T>* RBTree<T>::CopyTree(Node<T>* sourcenode, Node<T>* parentnode) {
    if (sourcenode == NULL) {
        return NULL;
    } else {
        Node<T>* newNode= new Node<T>(sourcenode->data);
        newNode->is_black = sourcenode->is_black;
        
        if (parentnode != NULL) {
            newNode->p = parentnode;
        }
        
        newNode->left = CopyTree(sourcenode->left, newNode);
        newNode->right = CopyTree(sourcenode->right, newNode);
        return newNode;
    }
}

// recursive helper function for tree deletion
// deallocates nodes in post-order
template <typename T>
void RBTree<T>::RemoveAll(Node<T>* node) {
    if (node != NULL) {
        RemoveAll(node->left);
        RemoveAll(node->right);
        delete node;
        node = NULL;
        root = NULL;
        size--;
    }
}

    /*
    if (node == NULL) {
        return;
    } else {
        RemoveAll(node->left);

        RemoveAll(node->right);

        size--;
        delete(node);
        node = NULL;
    }
     */



// Tree fix, performed after removal of a black node
// Note that the parameter x may be NULL
template <typename T>
void RBTree<T>::RBRemoveFixUp(Node<T>* x, Node<T>* xparent, bool xisleftchild) {
    
    Node<T>* y;
    
    while (x != root && x->is_black == true) {
        if (xisleftchild == true) {   // x is left child
            y = xparent->right;     // x's sibling
            if(y->is_black == false) {
                y->is_black = true;
                xparent->is_black = false;
                RotateLeft(xparent);
                y = xparent->right;
            }
            if ((y->left == NULL && y->right == NULL) || ((y->left->is_black == true) && (y->right->is_black = true))) {
                y->is_black = false;
                x = xparent;        // and into while again...Check this: not sure if this would happen as coded here.
            } else {
                if (y->right->is_black == true) {
                    y->left->is_black = true;
                    y->is_black = false;
                    RotateRight(y);
                    y = xparent->right;
                }
                y->is_black = xparent->is_black;
                xparent->is_black = true;
                y->right->is_black = true;
                RotateLeft(xparent);
                x = root;
            }
        } else {
            //if (xisleftchild == false) { // x is right child
            y = xparent->left;     // x's sibling
            if(y->is_black == false) {
                y->is_black = true;
                xparent->is_black = false;
                RotateRight(xparent);
                y = xparent->left;
            }
            if ((y->right->is_black == true) && (y->left->is_black == true)) {
                y->is_black = false;
                x = xparent;
            } else {
                if (y->left->is_black == true) {
                    y->right->is_black = true;
                    y->is_black = false;
                    RotateLeft(y);
                    y = xparent->left;
                }
                y->is_black = xparent->is_black;
                xparent->is_black = true;
                y->left->is_black = true;
                RotateRight(xparent);
                x = root;
            }
        }
    }
    x->is_black = true;
}





// Calculates the height of the tree
// Requires a traversal of the tree, O(n)
// Height of node = length of longest path from v to leaf
template <typename T>
int RBTree<T>::ComputeHeight(Node<T>* node) const {
    if (node == NULL) {
        return 0;
    }
    
    if (node->left == NULL && node->right == NULL) {
        return 1;
    }
    
    int left = ComputeHeight(node->left);
    int right = ComputeHeight(node->right);
    
    return 1 + std::max(left, right);
}


// Accessor functions

// Calls BSTInsert and then performs any necessary tree fixing.
// If item already exists, do not insert and return false.
// Otherwise, insert, increment size, and return true.
template <typename T>
bool RBTree<T>::Insert(T item) {
    if (Contains(item)) { // item already exists
        return false;
    } else {
        Node<T>* x = BSTInsert(item);
        x->is_black = false;
        while (x != root && x->p->is_black == false) {
            if (x->p == x->p->p->left) {                            // left child case
                Node<T>* y = x->p->p->right;                      // uncle of newNode
                if (y != NULL && y->is_black == false) {       // if uncle is red
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                } else {                                                      // if uncle is black
                    if (x == x->p->right) {
                        x = x->p;
                        RotateLeft(x);
                    }
                    x->p->is_black = true;
                    x->p->p->is_black = false;
                    RotateRight(x->p->p);
                }
            } else {                                                            // right child case
                Node<T>* y = x->p->p->left;
                if (y != NULL && y->is_black == false) {
                    x->p->is_black = true;
                    y->is_black = true;
                    x->p->p->is_black = false;
                    x = x->p->p;
                } else {
                    if (x == x->p->left) {
                        x = x->p;
                        RotateRight(x);
                    }
                    x->p->is_black = true;
                    x->p->p->is_black = false;
                    RotateLeft(x->p->p);
                }
            }
        }
        root->is_black = true;
        size++;
        return true;
    }
}



// Removal of an item from the tree.
// Must deallocate deleted node after RBDeleteFixUp returns
template <typename T>
bool RBTree<T>::Remove(T item) {
    Node<T>* y; // predecessor
    Node<T>* x; // y's child
    bool xisleftchild;
    
    if (Contains(item)) {
        Node<T>* z = Find(item); // node to be removed
        
        //
        
        // if z is a leaf
        if (z->left == NULL && z->right == NULL) {
            if (z->p != NULL) {
                if (z->p->left == z) {
                    z->p->left = NULL;
                    delete(z);
                    size--;
                    return true;
                } else {
                    z->p->right = NULL;
                    delete(z);
                    size--;
                    return true;
                }
                
            } else {
                z = NULL;
                root = NULL;
                delete(z);
                size--;
                return true;
            }
        }
        
        
        // if z has 1 child
        if (z->left == NULL)  {
            y = z;
        } else {
            // if z has 2 children
            y = Predecessor(z);
        }
        
        
        
        if (y->left != NULL) {
            x = y->left;
            xisleftchild = false;
        } else {
            x = y->right;
            xisleftchild = true;
        }
        
        if (x != NULL) {
            x->p = y->p;
        }

        if (y->p == NULL) {
            root = x;
        } else {
            // attach x to y's parent
            if (y == y->p->left) {
                y->p->left = x;
                //xisleftchild = true;
                
            } else {
                y->p->right = x;
                //xisleftchild = false;
            }
        }
        

        if (y != z) {
            z->data = y->data;
        }
        
        if (y->is_black == true) {
            RBRemoveFixUp(y, z, xisleftchild);
        }
        
        delete y;
        y = NULL;
        size--;
        return true;
    } else {
        return false;
    }
}



// deletes all nodes in the tree. Calls recursive helper function.
template <typename T>
void RBTree<T>::RemoveAll() {
    RemoveAll(root);
}


// returns the number of items in the tree
template <typename T>
int RBTree<T>::Size() const {
    return size;
}

// returns the height of the tree, from root to deepest null child. Calls recursive helper function.
// Note that an empty tree should have a height of 0, and a tree with only one node will have a height of 1.
template <typename T>
int RBTree<T>::Height() const {
    return ComputeHeight(root);
}

#endif
