#include <iostream>
#include <cstdlib>
#include <string>

#include "rbtree.h"
#include "stocksystem.h"

using namespace std;

// forward declarations

void PrintMenu();
void RBTreeTest();

// program entry point
int main() {
    RBTreeTest();
    
    int choice = 0;
    string inputchoice;
    int asku;
    string inputasku;
    string adesc;
    double aprice;
    string inputaprice;
    int amount;
    string inputamt;
    string ctlg = "";
    
    StockSystem mystore;
    
    while (choice != 8)
    {
        PrintMenu();
        // get the menu choice from standard input
        getline(cin, inputchoice);
        choice = atoi(inputchoice.c_str());
        
        switch (choice)
        {
            case 1: // Print balance
                cout << "Funds: $" << mystore.GetBalance() << endl << endl;
                break;
            case 2: // Print catalogue
                ctlg = mystore.GetCatalogue();
                cout << ctlg << endl;
                break;
            case 3: // Add SKU
                cout << "Enter a numeric SKU (will be converted to 5 digits): ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter item description: ";
                getline(cin, adesc);
                cout << "Enter a retail price: $";
                getline(cin, inputaprice);
                aprice = atof(inputaprice.c_str());
                if (mystore.StockNewItem(StockItem(asku, adesc, aprice)))
                    cout << "Successfully added item to catalogue." << endl;
                else
                    cout << "Item not added to catalogue." << endl;
                break;
            case 4: // Edit item description
                cout << "Enter a numeric SKU to edit: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter item description: ";
                getline(cin, adesc);
                if (mystore.EditStockItemDescription(asku, adesc))
                    cout << "Item successfully updated." << endl;
                else
                    cout << "Item not updated." << endl;
                break;
            case 5: // Edit item price
                cout << "Enter a numeric SKU to edit: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter a retail price: $";
                getline(cin, inputaprice);
                aprice = atof(inputaprice.c_str());
                if (mystore.EditStockItemPrice(asku, aprice))
                    cout << "Item successfully updated." << endl;
                else
                    cout << "Item not updated." << endl;
                break;
            case 6: // Restock an item
                cout << "Enter a numeric SKU to purchase: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter a quantity to purchase: ";
                getline(cin, inputamt);
                amount = atoi(inputamt.c_str());
                cout << "Enter the per-unit purchase price: $";
                getline(cin, inputaprice);
                aprice = atof(inputaprice.c_str());
                if (mystore.Restock(asku, amount, aprice))
                    cout << "Item successfully restocked." << endl;
                else
                    cout << "Item not restocked." << endl;
                break;
            case 7: // Sell an item
                cout << "Enter the SKU of item to sell: ";
                getline(cin, inputasku);
                asku = atoi(inputasku.c_str());
                cout << "Enter a quantity to sell: ";
                getline(cin, inputamt);
                amount = atoi(inputamt.c_str());
                if (mystore.Sell(asku, amount))
                    cout << "Transaction complete. Have a nice day." << endl;
                else
                    cout << "Item is out of stock. Sorry!" << endl;
                break;
            case 8: // Quit
                    // no need to do anything, will cause while loop to break
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
    
    return 0;
}

void PrintMenu()
{
    cout << "****************************************************\n"
    << "* Please select an option:                         *\n"
    << "* 1. Print balance             6. Restock an item  *\n"
    << "* 2. Print catalogue           7. Sell an item     *\n"
    << "* 3. Add a new SKU                                 *\n"
    << "* 4. Edit item description                         *\n"
    << "* 5. Edit item price           8. Quit             *\n"
    << "****************************************************\n" << endl;
    cout << "Enter your choice: ";
}

void RBTreeTest()
{
    
    // INSERTION TESTS
    
    cout << " " << endl;
    cout << "########## Insertion Tests ##########" << endl;
    cout << " " << endl;
    
    // case 1: figure 11.22 frm textbook
    
    RBTree<int> treeCase1;
    treeCase1.Insert(20);
    treeCase1.Insert(10);
    treeCase1.Insert(30);
    treeCase1.Insert(35);
    
    cout << "1. Insertion Test- treeCase1 contains " << treeCase1.Size() << " entries." << endl; // expected output: 4
    cout << "1. Insertion Test- treeCase1 height: " << treeCase1.Height() << endl; // expected output: 2 + 1 null node
    
    int sz1 = treeCase1.Size();
    int* contents1 = treeCase1.DumpPreOrder(sz1);
    cout << "1. Insertion Test- treeCase1 PreOrder Traversal: " << endl; // expected output: 2, 10, 30, 35*
    cout << " " << endl;
    for (int i = 0; i < sz1; i++) {
        cout << contents1[i] << endl;
    }
    cout << " " << endl;
    
    
    // case 2: figure 11.23 frm textbook
    
    RBTree<int> treeCase2;
    treeCase2.Insert(20);
    treeCase2.Insert(30);
    treeCase2.Insert(35);
    
    cout << "2. Insertion Test- treeCase2 contains " << treeCase2.Size() << " entries." << endl; // expected output: 3
    cout << "2. Insertion Test- treeCase2 height: " << treeCase2.Height() << endl; // expected output: 1 + 1 null node
    
    int sz2 = treeCase2.Size();
    int* contents2 = treeCase2.DumpPreOrder(sz2);
    cout << "2. Insertion Test- treeCase2 PreOrder Traversal: " << endl; // expected output: 30, 20*, 35*
    cout << " " << endl;
    for (int i = 0; i < sz2; i++) {
        cout << contents2[i] << endl;
    }
    cout << " " << endl;
    
    // case 3: figure 11.25 frm textbook
    
    RBTree<int> treeCase3;
    treeCase3.Insert(20);
    treeCase3.Insert(30);
    treeCase3.Insert(25);
    
    cout << "3. Insertion Test- treeCase3 contains " << treeCase3.Size() << " entries." << endl; // output: 3
    cout << "3. Insertion Test- treeCase3 height: " << treeCase3.Height() << endl; // output: 2 + null node
    
    int sz3 = treeCase3.Size();
    int* contents3 = treeCase3.DumpPreOrder(sz3);
    cout << "3. Insertion Test- treeCase3 PreOrder Traversal: " << endl; // expected output: 25, 20*, 30*
    cout << " " << endl;
    for (int i = 0; i < sz3; i++) {
        cout << contents3[i] << endl;
    }
    cout << " " << endl;
    
    // case 4: figure 11.30 frm textbook
    
    RBTree<int> treeCase4;
    treeCase4.Insert(11);
    treeCase4.Insert(2);
    treeCase4.Insert(14);
    treeCase4.Insert(1);
    treeCase4.Insert(7);
    treeCase4.Insert(5);
    treeCase4.Insert(8);
    treeCase4.Insert(4);
    
    cout << "4. Insertion Test- treeCase4 contains " << treeCase4.Size() << " entries." << endl; // output: 8
    cout << "4. Insertion Test- treeCase4 height: " << treeCase4.Height() << endl; // output: 3 + null node
    
    int sz4 = treeCase4.Size();
    int* contents4 = treeCase4.DumpPreOrder(sz4);
    cout << "4. Insertion Test- treeCase4 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 11*, 8, 14
    cout << " " << endl;
    for (int i = 0; i < sz4; i++) {
        cout << contents4[i] << endl;
    }
    cout << " " << endl;
    
    // case 5: insert 1 node, then insert duplicate node
    
    RBTree<int> treeCase5;
    treeCase5.Insert(11); // insert 1 node
    
    cout << "5. Insertion Test- treeCase5 contains " << treeCase5.Size() << " entries." << endl; // output: 1
    cout << "5. Insertion Test- treeCase5 height: " << treeCase5.Height() << endl; // output: 0
    
    treeCase5.Insert(11); // insert duplicate node
    
    cout << "5. Insertion Test after dup- treeCase5 contains " << treeCase5.Size() << " entries." << endl; // output: 1
    cout << "5. Insertion Test after dup- treeCase5 height: " << treeCase5.Height() << endl; // output: 0 + 1 null node
    cout << " " << endl;
    
    
    // DEEP COPY / COPYTREE TESTS
    
    cout << " " << endl;
    cout << "########## Deep Copy / CopyTree Tests ##########" << endl;
    cout << " " << endl;

    
    // case 1: copy empty tree
    
    RBTree<int> cTree1;
    RBTree<int>copyTree1(cTree1);
    
    cout << "1. Deep Copy Test- copyTree1 contains " << copyTree1.Size() << " entries." << endl; // output: 0
    cout << "1. Deep Copy Test- copyTree1 height: " << copyTree1.Height() << endl; // output: 0
    
    int csz1 = cTree1.Size();
    int* copyContents11 = cTree1.DumpPreOrder(csz1);
    cout << "1. Deep Copy Test- treeCase4 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 11*, 8, 14
    for (int i = 0; i < csz1; i++) {
        cout << copyContents11[i] << endl;
    }
    cout << " " << endl;
    
    // case 2: copy tree with 1 node
    
    RBTree<int> cTree2;
    cTree2.Insert(11);
    RBTree<int>copyTree2(cTree2);
    
    cout << "2. Deep Copy Test- copyTree2 contains " << copyTree2.Size() << " entries." << endl; // output: 1
    cout << "2. Deep Copy Test- copyTree2 height: " << copyTree2.Height() << endl; // output: 1
    cout << " " << endl;
    
    // case 3: copy tree with 8 nodes
    
    RBTree<int> cTree4;
    cTree4.Insert(11);
    cTree4.Insert(2);
    cTree4.Insert(14);
    cTree4.Insert(1);
    cTree4.Insert(7);
    cTree4.Insert(5);
    cTree4.Insert(8);
    cTree4.Insert(4);
    RBTree<int>copyTree4(cTree4);
    
    cout << "3. Deep Copy Test- copyTree3 contains " << copyTree4.Size() << " entries." << endl; // output: 8
    cout << "3. Deep Copy Test- copyTree3 height: " << copyTree4.Height() << endl; // output: 4
    
    int csz4 = copyTree4.Size();
    int* copyContents = copyTree4.DumpPreOrder(csz4);
    cout << "3. Deep Copy Test- treeCase4 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 11*, 8, 14
    cout << " " << endl;
    for (int i = 0; i < sz4; i++) {
        cout << copyContents[i] << endl;
    }
    cout << " " << endl;
    
    // case 4: operator on empty list
    
    copyTree2 = cTree1;
    
    cout << "4. Operator Test- copyTree2 contains " << copyTree2.Size() << " entries." << endl; // output: 0
    cout << "4. Operator Test- copyTree2 height: " << copyTree2.Height() << endl; // output:
    
    cout << "4. Operator Test- cTree1 contains " << cTree1.Size() << " entries." << endl; // output: 0
    cout << "4. Operator Test- cTree1 height: " << cTree1.Height() << endl; // output: 0
    cout << " " << endl;
    
    // case 5: operator on non-empty list
    
    RBTree<int> cTree5;
    cTree5.Insert(99);
    cTree5.Insert(97);
    cTree5.Insert(56);
    
    cTree5 = cTree4;
    
    // print cTree5
    cout << "5. Operator Test- BEFORE cTree5 contains " << cTree5.Size() << " entries." << endl; // output: 8
    cout << "5. Operator Test- BEFORE cTree5 height: " << cTree5.Height() << endl; // output: 4
    
    int csz5 = cTree5.Size();
    int* copyContents5 = cTree5.DumpPreOrder(csz5);
    cout << "5. Operator Test- BEFORE cTree5 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 11*, 8, 14
    cout << " " << endl;
    for (int i = 0; i < csz5; i++) {
        cout << copyContents5[i] << endl;
    }
    cout << " " << endl;
    
    cTree5.Insert(99);
    
    // print cTree4
    cout << "5. Operator Test- cTree4 contains " << cTree4.Size() << " entries." << endl; // output: 8
    cout << "5. Operator Test- cTree4 height: " << cTree4.Height() << endl; // output: 4
    
    int n = cTree4.Size();
    int* nDump = cTree4.DumpPreOrder(n);
    cout << "5. Operator Test- BEFORE cTree4 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 11*, 8, 14
    cout << " " << endl;
    for (int i = 0; i < n; i++) {
        cout << nDump[i] << endl;
    }
    cout << " " << endl;
    
    cout << "5. Operator Test- AFTER cTree5 contains " << cTree5.Size() << " entries." << endl; // output: 9
    cout << "5. Operator Test- AFTER cTree5 height: " << cTree5.Height() << endl; // output: 4
    
    csz5 = cTree5.Size();
    copyContents5 = cTree5.DumpPreOrder(csz5);
    cout << "5. Operator Test- AFTER cTree5 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 11*, 8*, 14, 99*
    cout << " " << endl;
    for (int i = 0; i < csz5; i++) {
        cout << copyContents5[i] << endl;
    }
    cout << " " << endl;
    
    // case 6: a = a
    
    // NEED A TEST HERE!!!

    /*
    
    // REMOVE(ITEM) TESTS
    
    cout << " " << endl;
    cout << "########## Remove(Item) Tests ##########" << endl;
    cout << " " << endl;
    
    // case 1: remove 1 node from left subtree
    
    RBTree<int> removeTree1;
    removeTree1.Insert(11);
    removeTree1.Insert(2);
    removeTree1.Insert(14);
    removeTree1.Insert(1);
    removeTree1.Insert(7);
    removeTree1.Insert(5);
    removeTree1.Insert(8);
    removeTree1.Insert(4);
    
    removeTree1.Remove(5);
    
    cout << "1. Remove(Item) Test- removeTree1 contains " << removeTree1.Size() << " entries." << endl; // output: 7
    cout << "1. Remove(Item) Test- removeTree1 height: " << removeTree1.Height() << endl; // output: 3
    
    int rsz1 = removeTree1.Size();
    int* rContents1 = removeTree1.DumpPreOrder(rsz1);
    cout << "1. Remove(Item) Test- removeTree1 PreOrder Traversal: " << endl; // expected output: 7, 4*, 1, 5, 11*, 8, 14
    cout << " " << endl;
    for (int i = 0; i < rsz1; i++) {
        cout << rContents1[i] << endl;
    }
    cout << " " << endl;
    
    // case 2: remove 1 node in right subtree
    
    RBTree<int> removeTree2;
    removeTree2.Insert(11);
    removeTree2.Insert(2);
    removeTree2.Insert(14);
    removeTree2.Insert(1);
    removeTree2.Insert(7);
    removeTree2.Insert(5);
    removeTree2.Insert(8);
    removeTree2.Insert(4);
    
    removeTree2.Remove(11);
    
    cout << "2. Remove(Item) Test- removeTree2 contains " << removeTree2.Size() << " entries." << endl; // output: 7
    cout << "2. Remove(Item) Test- removeTree2 height: " << removeTree2.Height() << endl; // output: 4
    
    int rsz2 = removeTree2.Size();
    int* rContents2 = removeTree2.DumpPreOrder(rsz2);
    cout << "2. Remove(Item) Test- removeTree2 PreOrder Traversal: " << endl; // expected output: 7, 2*, 1, 5, 4*, 8, 14*
    cout << " " << endl;
    for (int i = 0; i < rsz2; i++) {
        cout << rContents2[i] << endl;
    }
    cout << " " << endl;
    
    // case 3: remove root
    
    RBTree<int> removeTree3;
    removeTree3.Insert(11);
    
    removeTree3.Remove(11);
    
    cout << "3. Remove(Item) Test- removeTree3 contains " << removeTree3.Size() << " entries." << endl; // output: 0
    cout << "3. Remove(Item) Test- removeTree3 height: " << removeTree3.Height() << endl; // output: 0
    
    int rsz3 = removeTree3.Size();
    int* rContents3 = removeTree3.DumpPreOrder(rsz3);
    cout << "3. Remove(Item) Test- removeTree3 PreOrder Traversal: " << endl; // expected output:
    cout << " " << endl;
    for (int i = 0; i < rsz3; i++) {
        cout << rContents3[i] << endl;
    }
    cout << " " << endl;
    
    // case 4: remove item not contained in tree
    
    RBTree<int> removeTree4;
    
    removeTree4.Remove(100);
    
    cout << "4. Remove(Item) Test- removeTree4 contains " << removeTree4.Size() << " entries." << endl; // output: 0
    cout << "4. Remove(Item) Test- removeTree4 height: " << removeTree4.Height() << endl; // output: 0
    cout << " " << endl;
    
    // REMOVEALL TESTS
    
    cout << " " << endl;
    cout << "########## RemoveAll Tests ##########" << endl;
    cout << " " << endl;
    
    // case 1: remove empty tree
    
    removeTree3.RemoveAll();
    
    cout << "1. RemoveAll Test- removeTree3 contains " << removeTree3.Size() << " entries." << endl; // output: 0
    cout << "1. RemoveAll Test- removeTree3 height: " << removeTree3.Height() << endl; // output: 0
    
    rsz3 = removeTree3.Size();
    rContents3 = removeTree3.DumpPreOrder(rsz3);
    cout << "1. RemoveAll Test- removeTree3 PreOrder Traversal: " << endl; // expected output: NO LIST
    for (int i = 0; i < rsz3; i++) {
        cout << rContents3[i] << endl;
    }
    cout << " " << endl;
    
    // case 2: remove root
    
    removeTree3.Insert(999); //removeTree3 was empty before inserting 999
    
    removeTree3.RemoveAll();
    
    cout << "2. RemoveAll Test- removeTree3 contains " << removeTree3.Size() << " entries." << endl; // output: 0
    cout << "2. RemoveAll Test- removeTree3 height: " << removeTree3.Height() << endl; // output: 0
    cout << " " << endl;
    
    rsz3 = removeTree3.Size();
    rContents3 = removeTree3.DumpPreOrder(rsz3);
    cout << "2. RemoveAll Test- removeTree3 PreOrder Traversal: " << endl; // expected output:
    for (int i = 0; i < rsz3; i++) {
        cout << rContents3[i] << endl;
    }
    cout << " " << endl;
    
    // case 3: remove tree with many nodes
    
    removeTree2.RemoveAll();  // removeTree2 originally has 7 items in it
    
    cout << "3. RemoveAll Test- removeTree2 contains " << removeTree2.Size() << " entries." << endl; // output: 0
    cout << "3. RemoveAll Test- removeTree2 height: " << removeTree2.Height() << endl; // output: 0
    
    rsz2 = removeTree2.Size();
    rContents2 = removeTree2.DumpPreOrder(rsz2);
    cout << "3. Remove(Item) Test- removeTree2 PreOrder Traversal: " << endl; // expected output: empty
    cout << " " << endl;
    for (int i = 0; i < rsz2; i++) {
        cout << rContents2[i] << endl;
    }
    cout << " " << endl;
    
    cout << " " << endl;
    cout << "$$$$$$$" << endl;
    cout << " " << endl;
*/

    
    
    RBTree<int> tree1;
    
    tree1.Insert(1);
    tree1.Insert(3);
    tree1.Insert(2); // should cause 2 rotations to occur
    tree1.Insert(4);
    tree1.Remove(4);
    
    cout << "Tree contains " << tree1.Size() << " entries." << endl;
    cout << "Tree height: " << tree1.Height() << endl;
    
    RBTree<int> tree2(tree1);
    
    tree1.RemoveAll();
    
    RBTree<int> tree3;
    tree3.Insert(5);
    tree3 = tree2;
    
    cout << "Tree contains " << tree3.Size() << " entries." << endl;
    cout << "Tree height: " << tree3.Height() << endl;


}
