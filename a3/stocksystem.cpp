//#include "rbtree.h"
#include "stocksystem.h"
//#include "stockitem.h"
using namespace std;


// default constructor;
// begin with a balance of $100,000.00
StockSystem::StockSystem() {
    balance = 100000.00;
}

// returns the balance member
double StockSystem::GetBalance() {
    return balance;
}

// Add a new SKU to the system. Do not allow insertion of duplicate sku
bool StockSystem::StockNewItem(StockItem item) {
    if (!records.Contains(item)) {
        records.Insert(item);
        return true;
    } else {
        return false;
    }
}

// Locate the item with key itemsku and update its description field.
// Return false if itemsku is not found.
bool StockSystem::EditStockItemDescription(int itemsku, string desc) {
    StockItem* item = new StockItem(itemsku, "", 0.00);
    if (records.Contains(*item)) {
        (records.Retrieve(*item))->SetDescription(desc);   // (records.Retrieve(*item)) returns a pointer
        return true;
    } else {
        return false;
    }
}

// Locate the item with key itemsku and update its description field.
// ReStockSystem::turn false if itemsku is not found or retailprice is negative.
bool StockSystem::EditStockItemPrice(int itemsku, double retailprice) {
    StockItem* item = new StockItem(itemsku, "", 0.00);
    if (retailprice < 0) return false;
    if (!records.Contains(*item)) return false;
    else {
        (records.Retrieve(*item))->SetPrice(retailprice);
        return true;
    }
}

// Purchase quantity of item at unitprice each, to reach a maximum (post-purchase) on-hand stock quantity of 1000.
// Return false if balance is not sufficient to make the purchase,
//   or if SKU does not exist, or if quantity or unitprice are negative.
// Otherwise, return true and increase the item's on-hand stock by quantity,
//   and reduce balance by quantity*unitprice.
bool StockSystem::Restock(int itemsku, int quantity, double unitprice) {
    StockItem* item = new StockItem(itemsku, "", 0.00);
    if (balance < (quantity * unitprice)) return false;
    if (!records.Contains(*item)) return false;
    if (quantity < 0) return false;
    if (unitprice < 0.00) return false;

else {
        int currStock = (records.Retrieve(*item))->GetStock(); // current stock
        int diff = 1000 - currStock;
        if (quantity < diff) {
            (records.Retrieve(*item))->SetStock(currStock + quantity);
            balance = balance - (quantity * unitprice);
        } else {
            (records.Retrieve(*item))->SetStock(currStock + diff);
            balance = balance - (diff * unitprice);
        }
        return true;
        
    }
}

// Sell an item to a customer, if quantity of stock is available and SKU exists.
// Reduce stock by quantity, increase balance by quantity*price, and return true if stock available.
// If partial stock (less than quantity) available, sell the available stock and return true.
// If no stock, sku does not exist, or quantity is negative, return false.
bool StockSystem::Sell(int itemsku, int quantity) {
    StockItem* item = new StockItem(itemsku, "", 0.00);
    int currStock = records.Retrieve(*item)->GetStock();
    double price = records.Retrieve(*item)->GetPrice();
    
    if (currStock == 0) return false;
    if (!records.Contains(*item)) return false;
    if (quantity < 0) return false;
    else {
        if (currStock < quantity) {
            records.Retrieve(*item)->SetStock(0); // sell all current stock
            balance = balance + (currStock * price);
        } else {
            records.Retrieve(*item)->SetStock(currStock - quantity);
            balance = balance + (quantity * price);
        }
        return true;
    }
}

