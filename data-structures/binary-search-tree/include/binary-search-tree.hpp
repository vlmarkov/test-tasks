#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_

#include <string>
#include <memory>
#include <string_view>


class BinarySearchTree
{
private:
    struct node
    {
        int key{0};
        std::string value;
        node* left{nullptr};
        node* right{nullptr};
    };

    size_t size_{0};
    node* root_{nullptr};

    void replace_node_(node* parent, node* tree_node, node* child);
    void delete_node_(node *parent, node* node);
    void delete_postorder_(node *delete_node);

    void print_postorder_(node* node) const;
    void print_inorder_(node* node) const;
    void print_preorder_(node* node) const;

public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    int add(const int key, std::string&& value);
    int remove(const int key);

    const std::string_view lookup(const int key) const;
    const std::string_view min() const;
    const std::string_view max() const;
    std::size_t size() const;
    bool empty() const;
    void print_postorder() const;
    void print_inorder() const;
    void print_preorder() const;
};
 
#endif /* _BINARY_SEARCH_TREE_HPP_ */
