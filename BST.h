
///
/// @file BST.h
/// @brief BST tree class definition.
///
/// This file contains the definition of the BST Tree class.
///
/// @author Chan Kok Wai ( Student Number: 33924804 )
/// @version 1.0.0
///
#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "Tree.h"

/**
* @brief Represents the BST Class
*/
template<class T>
class BST: public Tree<T>
{
public:

    /**
    * @brief Default constructor for the binary search tree (BST).
    *
    * Constructs a binary search tree with no nodes.
    *
    * @tparam T The data type of the elements stored in the BST.
    */
    BST();

    /**
    * @brief Destructor for the binary search tree (BST).
    *
    * Destroys the binary search tree by recursively deleting all nodes.
    *
    * @tparam T The data type of the elements stored in the BST.
    */
    ~BST();

    /**
    * @brief Insert a node with the given object into the binary search tree (BST).
    *
    * This function inserts a new node containing the specified object into the binary search tree (BST).
    *
    * @tparam T The data type of the elements stored in the BST.
    * @param object The object to be inserted into the BST.
    * @return true if the insertion is successful, false if the object already exists in the tree.
    */
    bool InsertNode( const T &object ) override;

    /**
    * @brief Delete a node with the given object from the binary search tree (BST).
    *
    * This function deletes a node containing the specified object from the binary search tree (BST).
    *
    * @tparam T The data type of the elements stored in the BST.
    * @param object The object to be deleted from the BST.
    * @return true if the deletion is successful, false if the object is not found in the tree.
    */
    bool DeleteNode( const T &object ) override;

private:

    /**
    * @brief Insert a node with the given object into the binary search tree (BST).
    *
    * This private function inserts a new node containing the specified object into the binary search tree (BST).
    *
    * @tparam T The data type of the elements stored in the BST.
    * @param current A reference to the pointer to the current node being processed. Initially, it should be a reference to the root node of the tree.
    * @param object The object to be inserted into the BST.
    * @return true if the insertion is successful, false if the object already exists in the tree.
    */
    bool Insert( Node<T> *&current, const T &object ) override;

    /**
    * @brief Delete a node with the given object from the binary search tree (BST).
    *
    * This private function deletes a node containing the specified object from the binary search tree (BST).
    *
    * @tparam T The data type of the elements stored in the BST.
    * @param current A reference to the pointer to the current node being processed. Initially, it should be a reference to the root node of the tree.
    * @param object The object to be deleted from the BST.
    * @return true if the deletion is successful, false if the object is not found in the tree.
    */
    bool Delete( Node<T> *&current, const T &object ) override;
};

// +++++++ PUBLIC METHOD ++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++
template<class T>
BST<T>::BST(): Tree<T>() {}

template<class T>
BST<T>::~BST()
{
    this->Destroy( this->m_root );
}

template<class T>
bool BST<T>::InsertNode( const T &object )
{
    return Insert( this->m_root, object );
}

template<class T>
bool BST<T>::DeleteNode( const T &object )
{
    return Delete( this->m_root, object );
}

//++++++++ PRIVATE ++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++

template<class T>
bool BST<T>::Insert( Node<T> *&current, const T &object )
{
    if( current == nullptr )
    {
        current = new Node<T>;
        current->m_object = object;
        current->m_left = nullptr;
        current->m_right = nullptr;
        return true;
    }
    else if( object < current->m_object )
    {
        return ( Insert( current->m_left, object ) );
    }
    else if( object > current->m_object )
    {
        return ( Insert( current->m_right, object ) );
    }
    else
    {
        return false;
    }
}

template<class T>
bool BST<T>::Delete( Node<T> *&current, const T &object )
{
    if( current == nullptr )
    {
        return false;
    }
    else if( object < current->m_object )
    {
        return Delete( current->m_left, object );
    }
    else if( object > current->m_object )
    {
        return Delete(current->m_right, object );
    }
    else
    {
        if( current->m_left == nullptr )
        {
            Node<T> *temp = current->m_right;
            delete current;
            current = temp;
        }
        else if( current->m_right == nullptr )
        {
            Node<T> *temp = current->m_left;
            delete current;
            current = temp;
        }
        else
        {
            if( this->GetHeight(current->m_left) >= this->GetHeight(current->m_right) )
            {
                Node<T> *temp = current->m_left;
                while( temp->m_right != nullptr )
                {
                    temp = current->m_right;
                }
                current->m_object = temp->m_object;
                return Delete( current->m_left, temp->m_object );
            }
            else
            {
                Node<T> *temp = current->m_right;
                while( temp->m_left != nullptr )
                {
                    temp = current->m_left;
                }
                current->m_object = temp->m_object;
                return Delete( current->m_right, temp->m_object );
            }
        }
        return true;
    }
}

#endif // BST_H_INCLUDED
