
///
/// @file AVL.h
/// @brief AVL tree class definition.
///
/// This file contains the definition of the AVL Tree class.
///
/// @author Chan Kok Wai ( Student Number: 33924804 )
/// @version 1.0.0
///
#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "Tree.h"

/**
* @brief Represents the AVL Class
*/
template<class T>
class AVL: public Tree<T>
{
public:

    /**
    * @brief Default constructor for the AVL tree.
    *
    * Constructs an AVL tree with no nodes.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    */
    AVL();

    /**
    * @brief Destructor for the AVL tree.
    *
    * Destroys the AVL tree by recursively deleting all nodes.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    */
    ~AVL();

    /**
    * @brief Insert a node with the given object into the AVL tree.
    *
    * This function inserts a new node containing the specified object into the AVL tree
    * while maintaining the AVL tree property.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    * @param object The object to be inserted into the AVL tree.
    * @return true if the insertion is successful, false if the object already exists in the tree.
    */
    bool InsertNode( const T &object ) override;

    /**
    * @brief Delete a node with the given object from the AVL tree.
    *
    * This function deletes a node containing the specified object from the AVL tree
    * while maintaining the AVL tree property.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    * @param object The object to be deleted from the AVL tree.
    * @return true if the deletion is successful, false if the object is not found in the tree.
    */
    bool DeleteNode( const T &object ) override;

private:

    /**
    * @brief Get the balance factor of a given AVL tree node.
    *
    * This function calculates the balance factor of the specified AVL tree node.
    * The balance factor is the difference between the heights of the left and right
    * subtrees of the node. It indicates whether the subtree rooted at this node is
    * balanced, left-heavy, or right-heavy.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    * @param ptr A pointer to the node for which the balance factor is calculated.
    * @return The balance factor of the node. It is calculated as the difference
    *         between the height of the left subtree and the height of the right
    *         subtree. If the node is null, -1 is returned.
    */
    int GetBalanceFactor( Node<T> *ptr );

    /**
    * @brief Perform a right rotation on the given AVL tree node.
    *
    * This function performs a right rotation on the specified AVL tree node.
    * Right rotation is a type of rotation operation in AVL trees used to
    * restore the balance of the tree. It involves rotating the node and its
    * left child in a clockwise direction.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    * @param rst A pointer to the node to be rotated.
    * @return A pointer to the root of the subtree resulting from the rotation.
    */
    Node<T> *RightRotate( Node<T> *rst );

    /**
    * @brief Perform a left rotation on the given AVL tree node.
    *
    * This function performs a left rotation on the specified AVL tree node.
    * Left rotation is a type of rotation operation in AVL trees used to
    * restore the balance of the tree. It involves rotating the node and its
    * right child in an anti-clockwise direction.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    * @param lst A pointer to the node to be rotated.
    * @return A pointer to the root of the subtree resulting from the rotation.
    */
    Node<T> *LeftRotate( Node<T> *lst );

    /**
    * @brief Insert a new node with the given object into the AVL tree.
    *
    * This function inserts a new node containing the specified object into the AVL tree
    * while maintaining the AVL tree property. If the object is already present in the tree,
    * the insertion fails, and false is returned.
    *
    * @tparam T The data type of the elements stored in the AVL tree.
    * @param current A reference to the pointer to the current node being processed. Initially, it should be a reference to the root node of the tree.
    * @param object The object to be inserted into the AVL tree.
    * @return true if the insertion is successful, false if the object already exists in the tree.
    */
    bool Insert( Node<T> *&current, const T &object ) override;

    /**
     * @brief Delete a node with the given object from the AVL tree.
     *
     * This function deletes a node containing the specified object from the AVL tree
     * while maintaining the AVL tree property. If the object is not found in the tree,
     * the deletion fails, and false is returned.
     *
     * @tparam T The data type of the elements stored in the AVL tree.
     * @param current A reference to the pointer to the current node being processed. Initially, it should be a reference to the root node of the tree.
     * @param object The object to be deleted from the AVL tree.
     * @return true if the deletion is successful, false if the object is not found in the tree.
     */
    bool Delete( Node<T> *&current, const T &object ) override;

};

// +++ PRIVATE +++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++
template<class T>
int AVL<T>::GetBalanceFactor( Node<T> *ptr )
{
    if( ptr == nullptr )
    {
        return -1;
    }
    else
    {
        return ( this->GetHeight(ptr->m_left) - this->GetHeight(ptr->m_right) );
    }
}

template<class T>
Node<T> *AVL<T>::RightRotate(Node<T> *rst)
{
    Node<T> *lst = rst->m_left;
    Node<T> *otherTree = lst->m_right;

    lst->m_right = rst;
    rst->m_left = otherTree;

    return lst;
}

template<class T>
Node<T> *AVL<T>::LeftRotate( Node<T> *lst )
{
    Node<T> *rst = lst->m_right;
    Node<T> *otherTree = rst->m_left;

    rst->m_left = lst;
    lst->m_right = otherTree;

    return rst;
}

template<class T>
bool AVL<T>::Insert(Node<T> *&current, const T &object)
{
    if (current == nullptr)
    {
        current = new Node<T>;
        current->m_object = object;
        current->m_left = nullptr;
        current->m_right = nullptr;
        return true;
    }
    else if (object < current->m_object)
    {
        bool inserted = Insert(current->m_left, object);
        if (!inserted)
            return false; // Insertion failed due to duplicate value
    }
    else if (object > current->m_object)
    {
        bool inserted = Insert(current->m_right, object);
        if (!inserted)
            return false; // Insertion failed due to duplicate value
    }
    else
    {
        return false; // Duplicate value, insertion failed
    }

    // Calculate balance factor and perform rotations if needed
    int balanceFactor = GetBalanceFactor(current);

    if (balanceFactor > 1 && object < current->m_left->m_object)
    {
        current = RightRotate(current);   // Left-left rotate
    }
    else if (balanceFactor < -1 && object > current->m_right->m_object)
    {
        current = LeftRotate(current);    // Right-right rotate
    }
    else if (balanceFactor > 1 && object > current->m_left->m_object)
    {
        // Left-right case
        current->m_left = LeftRotate(current->m_left);
        current = RightRotate(current);
    }
    else if (balanceFactor < -1 && object < current->m_right->m_object)
    {
        // Right Left case
        current->m_right = RightRotate(current->m_right);
        current = LeftRotate(current);
    }

    return true;
}

template<class T>
bool AVL<T>::Delete( Node<T> *&current, const T &object )
{
    if( current == nullptr )
    {
        return false; // Node not found, deletion failed
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
        bool deleted = false;
        if( current->m_left == nullptr )
        {
            Node<T> *temp = current->m_right;
            delete current;
            current = temp;
            deleted = true;
        }
        else if( current->m_right == nullptr )
        {
            Node<T> *temp = current->m_left;
            delete current;
            current = temp;
            deleted = true;
        }
        else
        {
            // Find inorder successor
            Node<T> *temp = current->m_right;
            while( temp->m_left != nullptr )
            {
                temp = temp->m_left;
            }
            current->m_object = temp->m_object;
            // Delete the successor
            deleted = Delete(current->m_right, temp->m_object);
        }

        if(deleted)
        {
            // Calculate balance factor and perform rotations if needed
            int balanceFactor = GetBalanceFactor(current);

            // Left Left Imbalance/Case or Right rotation
            if ( balanceFactor == 2 && GetBalanceFactor( current->m_left ) >= 0 )
            {
                current = RightRotate(current);
            }
            // Left Right Imbalance/Case or LR rotation
            else if ( balanceFactor == 2 && GetBalanceFactor( current->m_left ) == -1 )
            {
                current->m_left = LeftRotate(current->m_left);
                current = RightRotate(current);
            }
            // Right Right Imbalance/Case or Left rotation
            else if ( balanceFactor == -2 && GetBalanceFactor( current->m_right ) <= 0 )
            {
                current = LeftRotate(current);
            }
            // Right Left Imbalance/Case or RL rotation
            else if ( balanceFactor == -2 && GetBalanceFactor( current->m_right ) == 1 )
            {
                current->m_right = RightRotate(current->m_right);
                current = LeftRotate(current);
            }
        }

        return deleted; // Return whether deletion was successful
    }
}


// ++++++++++ PUBLIC METHOD ++++++++++++++++++++
// +++++++++++++++++++++++++++++++++++++++++

template<class T>
AVL<T>::AVL(): Tree<T>() {}

template<class T>
AVL<T>::~AVL()
{
    this->Destroy( this->m_root );
}

template<class T>
bool AVL<T>::InsertNode(const T &object)
{
    return Insert( this->m_root, object );
}

template<class T>
bool AVL<T>::DeleteNode( const T &object )
{
    return Delete( this->m_root, object );
}

#endif // AVL_H_INCLUDED
