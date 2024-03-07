#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include "Tree.h"

template<class T>
class BST: public Tree<T>
{
public:
    BST();
    ~BST();

    bool InsertNode( const T &object ) override;
    bool DeleteNode( const T &object ) override;

private:
    bool Insert( Node<T> *&current, const T &object ) override;
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
