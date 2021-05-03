#include <binary-search-tree.hpp>

#include <iostream>

void BinarySearchTree::delete_postorder_(node *delete_node) 
{
    if (!delete_node)
    {
        return;
    }
  
    delete_postorder_(delete_node->left);
    delete_postorder_(delete_node->right);
    delete delete_node;
}

BinarySearchTree::~BinarySearchTree()
{
    delete_postorder_(root_);
    size_ = 0;
    root_ = nullptr;
}

int BinarySearchTree::add(const int key, std::string&& value)
{
    auto parent = root_;
    auto node = root_;
    while (node)
    {
        parent = node;
        if (node->key < key)
        {
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            return -1;
        }
    }

    auto new_node = new BinarySearchTree::node();

    new_node->key = key;
    new_node->value = value;
    new_node->left = nullptr;
    new_node->right = nullptr;

    if (parent)
    {
        if (parent->key < key)
        {
            parent->right = new_node;
        }
        else
        {
            parent->left = new_node;
        }
    }
    else
    {
        root_ = new_node;
    }

    ++size_;
    return 0;
}

int BinarySearchTree::remove(const int key)
{
    if (empty()) {
        return -1;
    }

    BinarySearchTree::node *parent{nullptr};

    auto node = root_;
    while (node && node->key != key)
    {
        parent = node;
        if (node->key < key)
        {   
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
    }

    if (!node)
    {
        return -1;
    }
    
    delete_node_(parent, node);

    delete node;
    
    --size_;
    return 0;
}

const std::string_view BinarySearchTree::lookup(const int key) const
{
    if (empty())
    {
        return {};
    }

    auto node = root_;
    while (node)
    {
        if (node->key < key)
        {
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            return node->value;
        }
    }

    return {};
}

const std::string_view BinarySearchTree::min() const
{
    if (empty())
    {
        return {};
    }

    auto node = root_;
    while (node->left)
    {
        node = node->left;
    }
    return node->value;
}

const std::string_view BinarySearchTree::max() const
{
    if (empty())
    {
        return {};
    }

    auto node = root_;
    while (node->right)
    {
        node = node->right;
    }
    return node->value;
}

std::size_t BinarySearchTree::size() const
{
    return size_;
}

bool BinarySearchTree::empty() const
{
    return size_ ? false : true;
}

void BinarySearchTree::print_postorder() const
{
    print_postorder_(root_);
}

void BinarySearchTree::print_inorder() const
{
    print_inorder_(root_);
}

void BinarySearchTree::print_preorder() const
{
    print_preorder_(root_);
}

void BinarySearchTree::replace_node_(node* parent, node* node1, node* child)
{
    if (!parent || !node1)
    {
        return;
    }

    if (node1->key < parent->key)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
}

void BinarySearchTree::delete_node_(node *parent, node *tree_node)
{
    if (!tree_node)
    {
        return;
    }

    // Case 1: node->left is null and node->right is null
    // Case 2: node->left is null or node->right is null
    // Case 3: node->left is not null and node->right is not null

    if (!tree_node->left) // Case 1 or 2
    {
        replace_node_(parent, tree_node, tree_node->right);
        if (!parent)
        {
            root_ = tree_node->right; // Remove tree root
        }
    }
    else if (!tree_node->right) // Case 2
    {
        replace_node_(parent, tree_node, tree_node->left);
        if (!parent)
        {
            root_ = tree_node->left; // Remove tree root
        }
    }
    else // Case 3
    {
        auto min = tree_node->right;
        auto min_parent = min;
        while (min->left)
        {
            min_parent = min;
            min = min->left;
        }

        replace_node_(parent, tree_node, min);
        if (!parent)
        {
            root_ = min; // Remove tree root
        }

        if (tree_node->right != min) // Case 3.1
        {
            min_parent->left = min->right;
            min->left = tree_node->left;
            min->right = tree_node->right;
        }
        else // Case 3.2
        {
            min->left = tree_node->left;
        }
    }

    return;
}

void BinarySearchTree::print_preorder_(node* tree_node) const
{
    if (!tree_node)
    {
        return;
    }

    std::cout << tree_node->value << std::endl;
    print_preorder_(tree_node->left);
    print_preorder_(tree_node->right);
}

void BinarySearchTree::print_inorder_(node *tree_node) const
{
    if (!tree_node)
    {
        return;
    }
  
    print_inorder_(tree_node->left);
    std::cout << tree_node->value << std::endl;
    print_inorder_(tree_node->right);
}

void BinarySearchTree::print_postorder_(node *tree_node) const
{
    if (!tree_node)
    {
        return;
    }
  
    print_postorder_(tree_node->left);
    print_postorder_(tree_node->right);
    std::cout << tree_node->value << std::endl;
}
