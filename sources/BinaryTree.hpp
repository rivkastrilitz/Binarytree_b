#pragma once
#include <string> 
#include <map>    
#include <iostream>
#include <vector>    
#include <exception> 
#include <queue>     
namespace ariel
{
    const std::string NOT_FOUND = " correct value to set  son --not found";
    template <typename T>
    class BinaryTree
    {

    public:
        struct T_Node
        {
        
            T val;
            T_Node *left;
            T_Node *right;

        
            T_Node(const T &value) : val(value), right(nullptr), left(nullptr) {}
         
            void add_left_child(const T &p)
            {

                if (left != nullptr)
                {
                    this->left->val=p;
                   
                }
                else
                {
                    T_Node *node= new T_Node(p);
                    left = node;
                }
            }
            void add_right_child(const T &p)
            {

                if (right != nullptr)
                {
                    this->right->val=p;
                    
                }
                else
                {
                   T_Node *node = new T_Node(p);
                    right = node; 
                }
            }
              
        };


        class iterator_pre_order
        {
        private:
            T_Node *curr;
            std::queue<T_Node *> qu;

            void tree_to_qu(T_Node *v)
            {
                if (v != nullptr)
                {
                    qu.push(v);
                    tree_to_qu(v->left);
                    tree_to_qu(v->right);
                }
            }

        public:
            iterator_pre_order(T_Node *v)
            {
                curr = nullptr;
                tree_to_qu(v);

                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
            }
            //prefix
            iterator_pre_order &operator++()
            {
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
                else
                {
                    curr = nullptr;
                }
                return *this;
            }
            //postfix
            iterator_pre_order operator++(int)
            {
                iterator_pre_order temp = *this;
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
                else
                {
                    curr = nullptr;
                }
                return temp;
            }

            T &operator*() const
            {
                return curr->val;
            }

            bool operator!=(const iterator_pre_order &other) const
            {
                return curr != other.curr;
            }

            bool operator==(const iterator_pre_order &other) const
            {
                return curr == other.curr;
            }

            const T *operator->() const
            {
                return &(*curr);
            }
        };

        class iterator_in_order
        {
        private:
            T_Node *curr;
            std::queue<T_Node *> qu;
            void tree_to_qu(T_Node *v)
            {
                if (v != nullptr)
                {
                    tree_to_qu(v->left);
                    qu.push(v);
                    tree_to_qu(v->right);
                }
            }

        public:
            iterator_in_order(T_Node *v)
            {
                curr = nullptr;
                tree_to_qu(v);
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
            }
            iterator_in_order &operator++()
            {
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
                else
                {
                    curr = nullptr;
                }
                return *this;
            }
            iterator_in_order operator++(int)
            {
                iterator_in_order temp = *this;
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
                else
                {
                    curr = nullptr;
                }
                return temp;
            }
            T &operator*() const
            {
                return curr->val;
            }
            bool operator!=(const iterator_in_order &other) const
            {
                return (curr != other.curr);
            }
            bool operator==(const iterator_in_order &other) const
            {
                return curr == other.curr;
            }
            const T *operator->() const
            {
                return &(curr->val);
            }
        };

        class iterator_post_order
        {
        private:
            T_Node *curr;
            std::queue<T_Node *> qu;
            void tree_to_qu(T_Node *v)
            {
                if (v == nullptr)
                {
                    return;
                }
                tree_to_qu(v->left);
                tree_to_qu(v->right);
                qu.push(v);
            }

        public:
            iterator_post_order(T_Node *v)
            {
                curr = nullptr;
                tree_to_qu(v);
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
            }
            iterator_post_order &operator++()
            {
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
                else
                {
                    curr = nullptr;
                }
                return *this;
            }
            iterator_post_order operator++(int)
            {
                iterator_post_order temp = *this;
                if (!qu.empty())
                {
                    curr = qu.front();
                    qu.pop();
                }
                else
                {
                    curr = nullptr;
                }
                return temp;
            }
            T &operator*()
            {
                return curr->val;
            }
            bool operator!=(const iterator_post_order &other) const
            {
               
                return curr != other.curr;
            }
            bool operator==(const iterator_post_order &other) const
            {
                return curr == other.curr;
            }
            const T *operator->()
            {
                return &(curr->val);
            }
        };
        BinaryTree()
        {
            root = nullptr;
            exeist = 0;
        }
        BinaryTree(BinaryTree & other)
        {
            if (!root)
            {
                delete root;
            }
            root = other.get_root();
            exeist = 0;
        }
        BinaryTree(BinaryTree &&btree) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = btree.get_root();
            btree.set_root(nullptr);
            exeist = 0;
        }
        ~BinaryTree()
        {
            if (root != nullptr)
            {
                delete root;
            }
        }
        BinaryTree &operator=(BinaryTree other)
        {
            if (root == other.get_root())
            {
                return *this;
            }
            if (other.get_root() == nullptr)
            {
                root = nullptr;
            }
            else
            {
                if (root != nullptr)
                {
                    delete root;
                }
                root = new T_Node(*other.get_root());
            }

            exeist = 0;
            return *this;
        }
        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            if (root)
            {
                delete root;
            }
            root = other.get_root();
            other.set_root(nullptr);
            exeist = 0;
            return *this;
        }
        BinaryTree &add_root(T value)
        {
            if (root != nullptr)
            {
                root->val=value;
                
            }
            else
            {
                T_Node *t_Node = new T_Node(value);
                root = t_Node;
               
            }

            return *this;
        }
        BinaryTree &add_left(T current, T left_son)
        {
            exeist = 0;
            if (!add_son(1, current, left_son, root))
            {

                throw std::invalid_argument(NOT_FOUND);
            }

            return *this;
        }
        void set_root(T_Node *root_n)
        {
            this->root = root_n;
        }
        BinaryTree &add_right(T current, T right_son)
        {

            exeist = 0;
            if (!add_son(0, current, right_son, root))
            {

                throw std::invalid_argument(NOT_FOUND);
            }

            return *this;
        }
      
        iterator_pre_order begin_preorder()
        {
            return iterator_pre_order{root};
        }
        iterator_pre_order end_preorder()
        {
            return iterator_pre_order{nullptr};
        }
        iterator_in_order begin_inorder()
        {
            return iterator_in_order{root};
        }
        iterator_in_order end_inorder()
        {
            return iterator_in_order{nullptr};
        }
        iterator_post_order begin_postorder()
        {
            return iterator_post_order{root};
        }
        iterator_post_order end_postorder()
        {
            return iterator_post_order{nullptr};
        }

        iterator_in_order begin()
        {
            return begin_inorder();
        }
        iterator_in_order end()
        {
            return end_inorder();
        }
        friend std::ostream &operator<<(std::ostream &out, BinaryTree<T> &BT)
        {   
            
            for(auto it=iterator_in_order(BT.get_root).bgin();it!=iterator_in_order(BT.get_root).end();++it){
                out<<(*it)<<" ";
            }
            
            return out;
        }
        T_Node *get_root() const
        {
            return this->root;
        }

    private:
        T_Node *root;
        int  exeist;
        bool add_son(int son, T val_exist, T val_n, T_Node *current)
        {
            if (exeist || current == nullptr)
            {
                return false;
            }
            if (current->val == val_exist || add_son(son, val_exist, val_n, current->left) || add_son(son, val_exist, val_n, current->right))
            {
                if (current->val == val_exist)
                {
                    exeist = 1;
                    //son =1 to left and 0 to right 
                    if (son == 1)
                    {
                        current->add_left_child(val_n);
                    }
                    else
                    {
                        current->add_right_child(val_n);
                    }
                }
                return true;
            }
            return false;
        }
    };
}