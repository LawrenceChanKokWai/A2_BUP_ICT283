
/**
* @file BSTTest.cpp
* @brief BST Test execution file
*
* This file contains the execution unit test for BST Class.
*
* @author Chan Kok Wai ( Student Number: 33924804 )
* @version 1.0
*/
#include<iostream>

#include "BST.h"

using namespace std;

void Assert_Equals( bool condition, const string &message );

template<class T>
void TestInitialization( const BST<T> &bst );

template<class T>
void TestInsertionAndSearchOperation( BST<T> &bst );

template<class T>
void TestTraversalOrders( const BST<T> &bst );

template<class T>
void TestDeepCopyingOperations( BST<T> &bst );

template<class T>
void TestDeleteOperation( BST<T> &bst );

template<class T>
void Display( const T &node );

template<class T>
void Print(Node<T> * r, int space);

int main()
{
    BST<unsigned> bst;

    TestInitialization( bst );
    TestInsertionAndSearchOperation( bst );
    TestTraversalOrders( bst );
    TestDeepCopyingOperations( bst );
    TestDeleteOperation( bst );

    return 0;
}


void Assert_Equals( bool condition, const string &message )
{
    cout << (condition ? "\t-->[ PASS ] " : "\t-->[ FAIL ] ") << message << endl;
}

//++++ Test on initialization of intBST +++
template<class T>
void TestInitialization( const BST<T> &bst )
{
    cout << "Test on initialization of BST Tree" << endl;
    Assert_Equals( bst.GetTreeHeight() == 0, "Constructed initial tree height is zero" );
    Assert_Equals( bst.GetTreeNodes() == 0, "Constructed initial tree node is zero" );
    Assert_Equals( bst.GetTreeLeaves() == 0, "Constructed initial tree leaves is zero" );
    cout << endl;
}

//++++ Test node insertion +++
template<class T>
void TestInsertionAndSearchOperation( BST<T> &bst )
{
    cout << "Test on node insertion to BST Tree" << endl;
    Assert_Equals( bst.InsertNode(5), "Insertion of object 5");
    Assert_Equals( bst.GetTreeHeight() == 1, "Tree height after inserting a node" );
    Assert_Equals( bst.GetTreeNodes() == 1, "Tree node after inserting a node" );
    Assert_Equals( bst.GetTreeLeaves() == 1, "Tree leaves after inserting a node" );
    Assert_Equals( bst.InsertNode(6), "Insertion of object 6");
    Assert_Equals( bst.InsertNode(10), "Insertion of object 10");
    Assert_Equals( bst.InsertNode(10) == false, "Unable to perform insertion of duplicate object 10");
    Assert_Equals( bst.GetTreeHeight() == 3, "Tree height after inserting two more nodes" );
    Assert_Equals( bst.GetTreeNodes() == 3, "Tree node after inserting two more nodes" );
    Assert_Equals( bst.GetTreeLeaves() == 1, "Tree leaves after inserting two more nodes" );
    Assert_Equals( bst.SearchNode(5), "Search for a node that exist in the BinarySearchTree");
    Assert_Equals( bst.SearchNode(12) == false, "Search for a node that does not exist in the BinarySearchTree");

    Print( bst.GetRoot(), 5 );

    cout << endl;
}

//++++ Test traversal orders +++
template<class T>
void TestTraversalOrders( const BST<T> &bst )
{
    cout << "Test on Traversal Orders" << endl;
    cout << "\tActual Pre-Order Traversal: ";
    bst.PreOrderTraversal( Display );
    cout << " | Expected Pre-Order Traversal: 5 6 10" << endl;
    cout << "\tActual In-Order Traversal: ";
    bst.InOrderTraversal( Display );
    cout << " | Expected In-Order Traversal: 5 6 10" << endl;
    cout << "\tActual Post-Order Traversal: ";
    bst.PostOrderTraversal( Display );
    cout << " |Expected Post-Order Traversal: 10 6 5" << '\n' << endl;
}

//++++ Test Copy Constructor & Equals Assignment Operators +++
template<class T>
void TestDeepCopyingOperations( BST<T> &bst )
{
    BST<unsigned> copiedBST( bst );
    cout << "Test on copy constructor" << endl;
    Assert_Equals( copiedBST.GetTreeHeight() == bst.GetTreeHeight(), "Height of copied BST using copy constructor" );
    Assert_Equals( copiedBST.GetTreeNodes() == bst.GetTreeNodes(), "Number of nodes from copiedBST using copy constructor" );
    Assert_Equals( copiedBST.GetTreeLeaves() == bst.GetTreeLeaves(), "Number of leaves from copiedBST using copy constructor" );
    Assert_Equals( &copiedBST != &bst, "Both Addresses from copiedBST and otherBST differences using copy constructor");
    Print( copiedBST.GetRoot(), 5);
    cout << endl;

    cout << "Test on equal assignment operator" << endl;
    BST<unsigned> equalAssignmentBST( bst );
    Assert_Equals( equalAssignmentBST.GetTreeHeight() == 3, "Height of copied BST using copy constructor" );
    Assert_Equals( equalAssignmentBST.GetTreeNodes() == 3, "Number of nodes from copiedBST using copy constructor" );
    Assert_Equals( equalAssignmentBST.GetTreeLeaves() == 1, "Number of leaves from copiedBST using copy constructor" );
    Assert_Equals( &equalAssignmentBST != &bst, "Both Addresses from equalAssignmentBST and otherBST differences using copy constructor");
    cout << endl;
}


//++++ Test Deleting a node +++
template<class T>
void TestDeleteOperation( BST<T> &bst )
{
    bst.InsertNode( 15 );
    bst.InsertNode( 16 );
    bst.InsertNode( 17 );
    bst.InsertNode( 19 );

    cout << "--> Before Deletion: " << endl;
    cout << "Tree Height: " << bst.GetTreeHeight() << '\n'
         << "Tree Nodes: " << bst.GetTreeNodes() << '\n'
         << "Tree Leaves: " << bst.GetTreeLeaves() << '\n' << endl;
    Print( bst.GetRoot(), 5 );
    cout << endl;

    cout << "--> Test on deleting object operation" << endl;
    Assert_Equals( bst.DeleteNode(5), "Deletion of node object 5 (1 leave node without child)" );
    cout << "Tree Height: " << bst.GetTreeHeight() << '\n'
         << "Tree Nodes: " << bst.GetTreeNodes() << '\n'
         << "Tree Leaves: " << bst.GetTreeLeaves() << '\n' << endl;
    Print( bst.GetRoot(), 5 );
    cout << endl;

    cout << "--> Test on deleting object operation" << endl;
    Assert_Equals( bst.DeleteNode(17), "Deletion of node object 17 (1 node with left and right child)" );
    cout << "Tree Height: " << bst.GetTreeHeight() << '\n'
         << "Tree Nodes: " << bst.GetTreeNodes() << '\n'
         << "Tree Leaves: " << bst.GetTreeLeaves() << '\n' << endl;
    Print( bst.GetRoot(), 5 );
    cout << endl;

    cout << "--> Test on deleting object operation" << endl;
    Assert_Equals( bst.DeleteNode(15), "Deletion of node object 15 (root node)" );
    cout << "Tree Height: " << bst.GetTreeHeight() << '\n'
            << "Tree Nodes: " << bst.GetTreeNodes() << '\n'
            << "Tree Leaves: " << bst.GetTreeLeaves() << '\n' << endl;
    Print( bst.GetRoot(), 5 );
    cout << endl;
}

template<class T>
void Print(Node<T> * r, int space)
{
    const unsigned SPACE = 10;
    if (r == NULL) // Base case  1
        return;
    space += SPACE; // Increase distance between levels   2
    Print(r->m_right, space); // Process right child first 3
    cout << endl;
    for (int i = SPACE; i < space; i++) // 5
        cout << " "; // 5.1
    cout << r->m_object << "\n"; // 6
    Print(r->m_left, space); // Process left child  7
}

//++++ For displaying traversal operation +++
template<class T>
void Display( const T &node )
{
    cout << node << " ";
}
