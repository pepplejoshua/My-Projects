#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template <class K, class V>
class BSTree {
public:
    BSTree();
    ~BSTree();
    
    V& operator[](const K &key);
    K& index(const int i);
    void traverse(void (*f)(const K& key, V& value));
    V& find(const K &key);
    V& insert(const K &key, const V &val);
    int size() const;
    
private:
    class Node {
    public:
        K key;
        V value;
        Node *left, *right;
        Node(const K &k, const V &v) : key(k), value(v), left{NULL}, right{NULL} {}
    };
    
    Node *root;
    
    
    int count;
    
    void deleteTree(Node *&root);
    
    void traverse(Node *root, void (*f)(const K &key, V &value));
    
    Node *find(Node *root, const K &key);
    
    Node *insert(Node *&root, const K &key, const V &value);
    
    Node *inorder(Node *, int);
};

template <class K, class V>
class Map {
public:
    Map();
    ~Map();
    V& operator[](const K &key);
    V& at(const K &key);
    K& index(const int i);
    V& find(const K &key);
    V& insert(const K &key, const V &value);
    
    void traverse(void (*f)(const K& key, V& value));
    
    int size() const;
private:
    BSTree<K, V> *tree;
    // V& *find(Node *root, const K &key);
    
    // V& *insert(Node *&root, const K &key, const V &value = 0);
};


template <class K, class V>
BSTree<K, V>::BSTree()
{
    root = NULL;
    count = 0;
}

template <class K, class V>
BSTree<K, V>::~BSTree()
{
    deleteTree(root);
}

// returns a reference to the string vector of the node containing the
// given key.  If it is not found, a new node with an empty vector is
// created and a reference to the new value is returned
template <class K, class V>
V& BSTree<K, V>::operator[](const K &key)
{
    Node *n;
    
    n = find(root, key);
    if (n) {
        return n->value;
    } else {
        return insert(key, root->value);
    }
}

// calls the supplied function on the data in the nodes in alphabetical
// order
template <class K, class V>
void BSTree<K, V>::traverse(void (*f)(const K &key, V& value))
{
    traverse(root, f);
}

// helper function to delete the whole tree
template <class K, class V>
void BSTree<K, V>::deleteTree(Node *&root)
{
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = NULL;
    }
}

template <class K, class V>
// helper function to recursively move through the tree
void BSTree<K, V>::traverse(Node *root, void (*f)(const K &key,
                                                  V& value))
{
    if (root) {
        traverse(root->left, f);
        f(root->key, root->value);
        traverse(root->right, f);
    }
}

template <class K, class V>
V& BSTree<K, V>::insert(const K &key, const V &val)
{
    Node *result = insert(root, key, val);
    return result->value;
}

// helper function to search for a node with a key
template <class K, class V>
typename BSTree<K, V>::Node *BSTree<K, V>::find(Node *root, const K &key)
{
    if (!root) return NULL;
    if (root->key == key)
        return root;
    else if (root->key > key)
        return find(root->left, key);
    else
        return find(root->right, key);
}

// helper function to insert a new node with a key, returns a pointer
// to the node inserted.
template <class K, class V>
typename BSTree<K, V>::Node *BSTree<K, V>::insert(Node *&root, const K &key, const V &value)
{
    if (!root) {
        root = new Node(key, value);
        count++;
        return root;
    } else if (root->key >= key) {
        return insert(root->left, key, value);
    } else {
        return insert(root->right, key, value);
    }
}

template <class K, class V>
int BSTree<K, V>::size() const
{
    return count;
}

template <class K, class V>
typename BSTree<K, V>::Node *BSTree<K, V>::inorder(Node *node, int i)
{
    stack<Node *> s;
    Node *curr = node;
    vector<Node *> store;
    while(curr || !s.empty())
    {
        while(curr)
        {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        store.push_back(curr);
        
        curr = curr->right;
    }
    
    Node *result = store[i];
    return result;
}

template <class K, class V>
K& BSTree<K, V>::index(const int i)
{
    Node *item = NULL;
    item = inorder(root, i);
    
    if (item)
    {
        return item->key;
    }
    else
        return root->key;
}

template <class K, class V>
V& BSTree<K, V>::find(const K &key)
{
    Node *result = find(root, key);
    return result->value;
}

template <class K, class V>
Map<K, V>::Map()
{
    tree = new BSTree<K, V>();
}

template <class K, class V>
Map<K, V>::~Map()
{
    //delete tree;
    //tree = NULL;
}

template <class K, class V>
V& Map<K, V>::operator[](const K &key)
{
    
    return tree->operator[](key);
}

template <class K, class V>
V& Map<K, V>::at(const K &key)
{
    return tree->operator[](key);
}

template <class K, class V>
void Map<K, V>::traverse(void (*f)(const K& key, V& value))
{
    tree->traverse(f);
}

template <class K, class V>
int Map<K, V>::size() const
{
    return tree->size();
}

template <class K, class V>
K& Map<K, V>::index(const int i)
{
    return tree->index(i);
}

template <class K, class V>
V& Map<K, V>::find(const K &key)
{
    return tree->find(key);
}

template <class K, class V>
V& Map<K, V>::insert(const K &key, const V &value)
{
    return tree->insert(key, value);
}
