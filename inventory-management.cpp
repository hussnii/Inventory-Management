#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// --------- Inventory Item as Doubly Linked List Node ----------
struct Item {
    int id;
    string name;
    string category;
    int quantity;
    float price;
    Item* prev;
    Item* next;
};

Item* head = nullptr;

// --------- Stack for Undo Feature ---------
struct Operation {
    string type; // "add", "delete", "update"
    Item data;   // snapshot of item before operation (for undo)
};

stack<Operation> undoStack;

// --------- Queue for Order Processing ---------
struct Order {
    int itemId;
    int orderQuantity;
};

queue<Order> orderQueue;

// --------- Function Prototypes ----------
void addItem();
void displayItems();
void searchItem();
void deleteItem();
void updateItem();
void sortItems();
Item* findItemById(int id);
void showExplanation();
void undoLastOperation();
void enqueueOrder();
void processNextOrder();
void displayOrders();
void addItemNodeAtEnd(Item* newItem);
void deleteItemNode(Item* node);
int main() {
    showExplanation();
    int choice;
    do {
        cout << "\n========= Inventory Management System =========\n";
        cout << "1. Add Item\n";
        cout << "2. Display All Items\n";
        cout << "3. Search Item by ID\n";
        cout << "4. Delete Item by ID\n";
        cout << "5. Update Item by ID\n";
        cout << "6. Sort Items by Price\n";
        cout << "7. Undo Last Operation\n";
        cout << "8. Add Order Request\n";
        cout << "9. Process Next Order\n";
        cout << "10. Display Pending Orders\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: deleteItem(); break;
            case 5: updateItem(); break;
            case 6: sortItems(); break;
            case 7: undoLastOperation(); break;
            case 8: enqueueOrder(); break;
            case 9: processNextOrder(); break;
            case 10: displayOrders(); break;
            case 11: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 11);

    return 0;
}

// Explanation and Group Members
void showExplanation() {
    cout << "========== PROJECT EXPLANATION ==========\n";
    cout << "Mini Project: Inventory Management System using C++\n\n";
    cout << "Data Structures Used:\n";
    cout << "- Doubly Linked List: For inventory records (easy insertion, deletion, traversal).\n";
    cout << "- Stack: To implement Undo feature (undo last add/delete/update).\n";
    cout << "- Queue: To manage incoming order requests and process them FIFO.\n\n";

    cout << "Algorithms Used:\n";
    cout << "- Linear Search: To find items by ID.\n";
    cout << "- Bubble Sort: To sort inventory by price.\n";
    cout << "- Stack LIFO: Undo last operation.\n";
    cout << "- Queue FIFO: Order request processing.\n\n";

    cout << "Each inventory item contains: ID, Name, Category, Quantity, Price.\n";
    cout << "Features: Add, Search, Delete, Update, Display, Sort, Undo, Add Orders, Process Orders.\n";
    cout << "===========================================\n\n";
}
// Add item node at end helper for doubly linked list
void addItemNodeAtEnd(Item* newItem) {
    if (!head) {
        head = newItem;
        newItem->prev = newItem->next = nullptr;
    } else {
        Item* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newItem;
        newItem->prev = temp;
        newItem->next = nullptr;
    }
}

void addItem() {
    Item* newItem = new Item;
    cout << "\nEnter Item Details:\n";
    cout << "ID: "; cin >> newItem->id;
    cin.ignore();
    cout << "Name: "; getline(cin, newItem->name);
    cout << "Category: "; getline(cin, newItem->category);
    cout << "Quantity: "; cin >> newItem->quantity;
    cout << "Price: "; cin >> newItem->price;

    // Save undo info: type = "add", data = newItem itself (for undo, delete)
    Operation op;
    op.type = "add";
    op.data = *newItem;
    undoStack.push(op);

    addItemNodeAtEnd(newItem);
    cout << "Item added successfully!\n";
}

void displayItems() {
    if (!head) {
        cout << "Inventory is empty!\n";
        return;
    }

    cout << "\nCurrent Inventory:\n";
    cout << left << setw(5) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Category"
         << setw(10) << "Qty"
         << setw(10) << "Price\n";
    cout << "----------------------------------------------------------\n";

    Item* temp = head;
    while (temp) {
        cout << left << setw(5) << temp->id
             << setw(20) << temp->name
             << setw(15) << temp->category
             << setw(10) << temp->quantity
             << setw(10) << fixed << setprecision(2) << temp->price << "\n";
        temp = temp->next;
    }
}

Item* findItemById(int id) {
    Item* temp = head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}
void searchItem() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    Item* item = findItemById(id);
    if (!item) {
        cout << "Item not found!\n";
        return;
    }

    cout << "\nItem Details:\n";
    cout << "ID: " << item->id << "\n";
    cout << "Name: " << item->name << "\n";
    cout << "Category: " << item->category << "\n";
    cout << "Quantity: " << item->quantity << "\n";
    cout << "Price: " << fixed << setprecision(2) << item->price << "\n";
}

// Delete node helper for doubly linked list
void deleteItemNode(Item* node) {
    if (!node) return;

    if (node == head) {
        head = node->next;
        if (head) head->prev = nullptr;
    } else {
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
    }
    delete node;
}

void deleteItem() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    Item* item = findItemById(id);
    if (!item) {
        cout << "Item not found!\n";
        return;
    }

    // Save undo info: type = "delete", data = deleted item (for undo, re-add)
    Operation op;
    op.type = "delete";
    op.data = *item;
    undoStack.push(op);

    deleteItemNode(item);
    cout << "Item deleted successfully.\n";
}

void updateItem() {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;

    Item* item = findItemById(id);
    if (!item) {
        cout << "Item not found!\n";
        return;
    }

    // Save undo info: type = "update", data = old item before update
    Operation op;
    op.type = "update";
    op.data = *item;
    undoStack.push(op);

    cin.ignore();
    cout << "Enter new details:\n";
    cout << "Name: "; getline(cin, item->name);
    cout << "Category: "; getline(cin, item->category);
    cout << "Quantity: "; cin >> item->quantity;
    cout << "Price: "; cin >> item->price;

    cout << "Item updated successfully.\n";
}

void sortItems() {
    if (!head || !head->next) {
        cout << "Not enough items to sort.\n";
        return;
    }
    bool swapped;
    do {
        swapped = false;
        Item* curr = head;
        while (curr->next) {
            if (curr->price > curr->next->price) {
                // Swap all fields except pointers
                swap(curr->id, curr->next->id);
                swap(curr->name, curr->next->name);
                swap(curr->category, curr->next->category);
                swap(curr->quantity, curr->next->quantity);
                swap(curr->price, curr->next->price);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);

    cout << "Items sorted by price successfully!\n";
}

// Undo last operation (add/delete/update)
void undoLastOperation() {
    if (undoStack.empty()) {
        cout << "No operations to undo.\n";
        return;
    }

    Operation lastOp = undoStack.top();
    undoStack.pop();

    if (lastOp.type == "add") {
        // Undo add => delete the item with that id
        Item* item = findItemById(lastOp.data.id);
        if (item) {
            deleteItemNode(item);
            cout << "Undo successful: Last added item deleted.\n";
        } else {
            cout << "Undo failed: Item not found.\n";
        }
    } else if (lastOp.type == "delete") {
        // Undo delete => re-add the deleted item at end
        Item* restored = new Item(lastOp.data);
        restored->prev = restored->next = nullptr;
        addItemNodeAtEnd(restored);
        cout << "Undo successful: Last deleted item restored.\n";
    } else if (lastOp.type == "update") {
        // Undo update => revert the item to old data
        Item* item = findItemById(lastOp.data.id);
        if (item) {
            *item = lastOp.data;
            item->prev = item->next = nullptr; // We fix pointers below:
            // Reconnect pointers manually
            // Actually, since pointers are lost in op.data copy, we only revert fields:
            // So fix pointers to preserve linked list structure:
            // We'll revert only fields except prev and next:
            // So redo field assignment excluding prev and next:
            // (Re-assign fields manually)
            item->id = lastOp.data.id;
            item->name = lastOp.data.name;
            item->category = lastOp.data.category;
            item->quantity = lastOp.data.quantity;
            item->price = lastOp.data.price;
            cout << "Undo successful: Last updated item reverted.\n";
        } else {
            cout << "Undo failed: Item not found.\n";
        }
    } else {
        cout << "Unknown operation type in undo stack.\n";
    }
}

// Add order request to queue
void enqueueOrder() {
    Order ord;
    cout << "Enter Item ID for order: ";
    cin >> ord.itemId;
    cout << "Enter Order Quantity: ";
    cin >> ord.orderQuantity;

    // Check if item exists
    if (!findItemById(ord.itemId)) {
        cout << "Item not found in inventory! Cannot add order.\n";
        return;
    }

    orderQueue.push(ord);
    cout << "Order added to the queue successfully.\n";
}

// Process next order in queue
void processNextOrder() {
    if (orderQueue.empty()) {
        cout << "No pending orders to process.\n";
        return;
    }

    Order ord = orderQueue.front();
    orderQueue.pop();

    Item* item = findItemById(ord.itemId);
    if (!item) {
        cout << "Order processing failed: Item no longer exists.\n";
        return;
    }

    if (item->quantity >= ord.orderQuantity) {
        item->quantity -= ord.orderQuantity;
        cout << "Order processed successfully! " << ord.orderQuantity << " units of Item ID "
             << ord.itemId << " dispatched.\n";
    } else {
        cout << "Order cannot be fulfilled: Not enough stock.\n";
        // Optionally requeue or discard order here
    }
}

// Display pending orders in queue
void displayOrders() {
    if (orderQueue.empty()) {
        cout << "No pending orders.\n";
        return;
    }
    cout << "\nPending Orders:\n";
    cout << left << setw(10) << "Item ID" << setw(15) << "Quantity\n";
    cout << "------------------------\n";

    // We need to print queue contents without modifying it
    // So copy queue to temp
    queue<Order> tempQ = orderQueue;
    while (!tempQ.empty()) {
        Order ord = tempQ.front();
        tempQ.pop();
        cout << left << setw(10) << ord.itemId << setw(15) << ord.orderQuantity << "\n";
    }
}
