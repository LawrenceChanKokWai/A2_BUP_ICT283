#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include<iostream>

/**
* @brief Node structure for an template Binary Search Tree (BST).
*/
template<class T>
struct Node
{
    T m_object;     /**< Data of the template node. */
    Node *m_left;   /**< Pointer to the left child. */
    Node *m_right;  /**< Pointer to the right child. */
};

template<class T>
class Tree
{
public:
    typedef void( *PFnTraversal )( const T & );

    /**
    * @name Constructor & Destructor
    * @{
    */

    /**
    * @brief Constructor used for creating an empty template BST.
    */
    Tree();

    /**
    * @brief Destructor used for releasing allocate memory.
    */
    ~Tree();
    /** @} */

    /**
    * @name Copy Constructor & Overload Equals Assignment Operator
    * @{
    */

    /**
    * @brief Copy constructor used for creating a new BST from another BST.
    * @param[in] otherTree Reference to the BST to be copied.
    */
    Tree( const Tree &otherTree );

    /**
    * @brief Equals assignment operator used for assigning the contents from another BST.
    * @param[in] otherTree Reference to another BST on the right-hand side of the assignment.
    * @return Reference to the modified BST.
    */
    Tree &operator = ( const Tree &otherTree );
    /** @} */

    /**
    * @name Assessors
    * @{
    */

    /**
    * @brief Checks if the BST is empty.
    * @return True if BST is empty else False.
    */
    bool IsEmpty() const;

    Node<T> *GetRoot() const;

    /**
    * @brief Get the height of the BST.
    * @return Height of the BST.
    */
    int GetTreeHeight() const;

    /**
    * @brief Get the number of nodes in the BST.
    * @return Number of nodes in the BST.
    */
    int GetTreeNodes() const;

    /**
    * @brief Get the number of leaf nodes in the BST.
    * @return Number of leaf nodes in the BST.
    */
    int GetTreeLeaves() const;

    /**
    * @name Modifiers
    * @{
    */

    /**
    * @brief Insert a new node with the specified object into the BST.
    * @param[in] object The object to be inserted into the BST.
    * @return True if the insertion is successful, false if the object already exists in the BST.
    */
    virtual bool InsertNode( const T &object ) = 0;

    /**
    * @brief Search for a node with the specified object in the BST.
    * @param[in] object The object to be searched in the BST.
    * @return True if the object is found, false otherwise.
    */
    bool SearchNode( const T &object );

    /**
    * @brief Delete a node with the specified object in the BST.
    * @param[in] object The object to be deleted in the BST.
    * @return True if the object is deleted, false otherwise.
    */
    virtual bool DeleteNode( const T &object ) = 0;
    /** @} */

    /**
    * @name Operations
    * @{
    */

    /**
    * @brief Perform a pre-order traversal of the BST and print the node values.
    */
    void PreOrderTraversal( PFnTraversal traversal ) const;

    /**
    * @brief Perform a in-order traversal of the BST and print the node values.
    */
    void InOrderTraversal( PFnTraversal traversal ) const;

    /**
    * @brief Perform a post-order traversal of the BST and print the node values.
    */
    void PostOrderTraversal( PFnTraversal traversal ) const;
    /** @} */



protected:
    Node<T> *m_root;    /**< Pointer to the root of the BST */

    /**
    * @brief Recursively destroy the BST starting from the given node.
    * @param[in] ptr Pointer to the root node of the subtree to be destroyed.
    */
    void Destroy( Node<T> *&ptr );

    /**
    * @brief Method used to copy the contents of one subtree to another.
    * @param[in] copiedTreeRoot Reference to the root of the copied subtree.
    * @param[in] otherTreeRoot Pointer to the root of the subtree to be copied.
    */
    void CopyTree( Node<T> *&copiedTreeRoot, Node<T> *otherTreeRoot );

    /**
    * @brief Method used to get the maximum of two integers.
    * @param[in] x First integer representing the left subtree.
    * @param[in] y Second integer representing the right subtree.
    * @return Maximum of x or y.
    */
    int GetMaxTreeSubHeight( int left, int right ) const;

    /**
    * @brief Method used to get the height of a subtree at the given node.
    * @param[in] ptr Pointer to the root of the subtree.
    * @return Height of the subtree.
    */
    int GetHeight( Node<T> *ptr ) const;

    /**
    * @brief Method used to get the total number of nodes in a subtree at the given node.
    * @param[in] ptr Pointer to the root of the subtree.
    * @return Number of nodes in the subtree.
    */
    int GetNodes( Node<T> *ptr ) const;

    /**
    * @brief Method used to get the number of leaf nodes in a subtree at the given node.
    * @param[in] ptr Pointer to the root of the subtree.
    * @return Number of leaf nodes in the subtree.
    */
    int GetLeaves( Node<T> *ptr ) const;

    /**
    * @brief Method used to insert a new node with the specified object into a subtree.
    * @param[in] current Pointer to the root of the current subtree.
    * @param[in] object The object to be inserted.
    * @return True if the insertion is successful, false if the object already exists in the subtree.
    */
    virtual bool Insert( Node<T> *&current, const T &object ) = 0;

    /**
    * @brief Method used to search for a node with the specified object in a subtree.
    * @param[in] current Pointer to the root of the current subtree.
    * @param[in] object The object to be searched.
    * @return True if the object is found, false otherwise.
    */
    bool Search( Node<T> *&current, const T &object );

    /**
    * @brief Method used to delete a node with the specified object in a BST tree.
    * @param[in] current Pointer to the root of the current node.
    * @param[in] object The object to be deleted.
    * @return True if the object is deleted, false otherwise.
    */
    virtual bool Delete( Node<T> *&current, const T &object ) = 0;

    /**
    * @brief Method used to perform a pre-order traversal of a subtree and print the node values.
    * @param[in] ptr Pointer to the root of the subtree.
    */
    void PreOrder( PFnTraversal traversal, Node<T> *ptr ) const;

    /**
    * @brief Method used to perform an in-order traversal of a subtree and print the node values.
    * @param[in] ptr Pointer to the root of the subtree.
    */
    void InOrder( PFnTraversal traversal, Node<T> *ptr ) const;

    /**
    * @brief Method used to perform a post-order traversal of a subtree and print the node values.
    * @param[in] ptr Pointer to the root of the subtree.
    */
    void PostOrder( PFnTraversal traversal, Node<T> *ptr ) const;

};

template<class T>
void Tree<T>::Destroy( Node<T> *&ptr )
{
    if( ptr != nullptr )
    {
        Destroy( ptr->m_left );
        Destroy( ptr->m_right );
        delete ptr;
        ptr = nullptr;
    }
}

template<class T>
Tree<T>::Tree()
{
    m_root = nullptr;
}

template<class T>
Tree<T>::~Tree()
{
    Destroy( m_root );
}

template<class T>
bool Tree<T>::IsEmpty() const
{
    return ( m_root == nullptr );
}

template<class T>
Node<T> *Tree<T>::GetRoot() const
{
    return m_root;
}

template<class T>
int Tree<T>::GetMaxTreeSubHeight( int left, int right ) const
{
    if( left >= right )
    {
        return left;
    }
    else
    {
        return right;
    }
}

template<class T>
int Tree<T>::GetHeight( Node<T> *ptr ) const
{
    if( ptr == nullptr )
    {
        return 0;
    }
    else
    {
        return (1 + GetMaxTreeSubHeight( GetHeight( ptr->m_left ), GetHeight( ptr->m_right ) ) );
    }
}

template<class T>
int Tree<T>::GetTreeHeight() const
{
    return GetHeight( m_root );
}

template<class T>
int Tree<T>::GetNodes( Node<T> *ptr ) const
{
    if( ptr == nullptr )
    {
        return 0;
    }
    else
    {
        return ( 1+ GetNodes( ptr->m_left ) + GetNodes( ptr->m_right ) );
    }
}

template<class T>
int Tree<T>::GetTreeNodes() const
{
    return GetNodes( m_root );
}

template<class T>
int Tree<T>::GetLeaves( Node<T> *ptr ) const
{
    if( ptr == nullptr )
    {
        return 0;
    }
    if( ptr->m_left == nullptr && ptr->m_right == nullptr )
    {
        return 1;
    }
    return ( GetLeaves( ptr->m_left ) + GetLeaves( ptr->m_right ) );
}

template<class T>
int Tree<T>::GetTreeLeaves() const
{
    return GetLeaves( m_root );
}

template<class T>
void Tree<T>::CopyTree( Node<T> *&copiedTreeRoot, Node<T> *otherTreeRoot )
{
    if( otherTreeRoot == nullptr )
    {
        copiedTreeRoot = nullptr;
    }
    else
    {
        copiedTreeRoot = new Node<T>;
        copiedTreeRoot->m_object = otherTreeRoot->m_object;
        CopyTree( copiedTreeRoot->m_left, otherTreeRoot->m_left );
        CopyTree( copiedTreeRoot->m_right, otherTreeRoot->m_right );
    }
}

template<class T>
Tree<T>::Tree( const Tree &otherTree )
{
    if( otherTree.m_root == nullptr )
    {
        m_root = nullptr;
    }
    else
    {
        CopyTree( m_root, otherTree.m_root );
    }
}

template<class T>
Tree<T> &Tree<T>::operator = ( const Tree &otherTree )
{
    if( this != &otherTree )
    {
        if( m_root != nullptr )
        {
            Destroy( m_root );
        }
        if( otherTree.m_root == nullptr )
        {
            m_root = nullptr;
        }
        CopyTree( m_root, otherTree.m_root );
    }
    return *this;
}

template<class T>
bool Tree<T>::Search( Node<T> *&current, const T &object )
{
    if( current == nullptr )
    {
        return false;
    }
    else if( object == current->m_object )
    {
        return true;
    }
    else if( object < current->m_object )
    {
        return Search( current->m_left, object );
    }
    else
    {
        return Search( current->m_right, object );
    }
}

template<class T>
bool Tree<T>::SearchNode( const T &object )
{
    return Search( m_root, object );
}

template<class T>
void Tree<T>::InOrder( PFnTraversal traversal, Node<T> *ptr ) const
{
    if( ptr != nullptr )
    {
        InOrder( traversal, ptr->m_left );
        ( traversal )( ptr->m_object );
        InOrder( traversal, ptr->m_right );
    }
}

template<class T>
void Tree<T>::InOrderTraversal( PFnTraversal traversal ) const
{
    return InOrder( traversal, m_root );
}

template<class T>
void Tree<T>::PreOrder( PFnTraversal traversal, Node<T> *ptr ) const
{
    if( ptr != nullptr )
    {
        ( traversal )( ptr->m_object );
        PreOrder( traversal, ptr->m_left );
        PreOrder( traversal, ptr->m_right );
    }
}

template<class T>
void Tree<T>::PreOrderTraversal( PFnTraversal traversal ) const
{
    return PreOrder( traversal, m_root );
}

template<class T>
void Tree<T>::PostOrder( PFnTraversal traversal, Node<T> *ptr ) const
{
    if( ptr != nullptr )
    {
        PostOrder( traversal, ptr->m_left );
        PostOrder( traversal, ptr->m_right );
        ( traversal )( ptr->m_object );
    }
}

template<class T>
void Tree<T>::PostOrderTraversal( PFnTraversal traversal ) const
{
    return PostOrder( traversal, m_root );
}


#endif // TREE_H_INCLUDED
