Inventory Management System in C++

A console-based Inventory Management System developed using C++ and advanced Data Structures & Algorithms concepts.

This project manages inventory records efficiently using:

Doubly Linked List
Stack
Queue

It also supports features like undo operations, sorting, searching, and order processing.

📌 Features
✅ Inventory Management
Add new inventory items
Display all inventory records
Search items by ID
Update item information
Delete items from inventory
✅ Data Structure Features
🔹 Doubly Linked List

Used for:

Inventory item storage
Efficient insertion and deletion
Forward traversal

Each item contains:

ID
Name
Category
Quantity
Price
🔹 Stack (Undo Feature)

Used for:

Undoing the last operation

Supported undo actions:

Undo Add
Undo Delete
Undo Update

Implements:

LIFO (Last In First Out)
🔹 Queue (Order Processing)

Used for:

Managing customer orders

Features:

Add order requests
Process orders in FIFO order
Display pending orders

Implements:

FIFO (First In First Out)
🧠 Algorithms Used
🔍 Linear Search

Used to:

Search items by ID
🔄 Bubble Sort

Used to:

Sort inventory items by price
🛠️ Technologies Used
C++
Object-based Struct Design
Doubly Linked List
Stack STL
Queue STL
Functions
Sorting Algorithms
Searching Algorithms
📂 Project Structure
Inventory-Management-System/
│
├── main.cpp
└── README.md
▶️ How to Run the Program
🔹 Step 1: Compile the Program

Using g++ compiler:

g++ main.cpp -o inventory
🔹 Step 2: Run the Program
For Linux / Mac:
./inventory
For Windows:
inventory.exe
💻 Main Menu
========= Inventory Management System =========

1. Add Item
2. Display All Items
3. Search Item by ID
4. Delete Item by ID
5. Update Item by ID
6. Sort Items by Price
7. Undo Last Operation
8. Add Order Request
9. Process Next Order
10. Display Pending Orders
11. Exit
💡 Example Features
✅ Add Item

Stores new inventory items into the doubly linked list.

✅ Undo Feature

Reverts:

Last Added Item
Last Deleted Item
Last Updated Item
✅ Order Processing

Processes orders using queue scheduling.

If stock is available:

Quantity decreases automatically

If stock is insufficient:

Order is rejected
🎯 Learning Objectives

This project helps in understanding:

Linked List operations
Stack implementation
Queue implementation
Memory management
Sorting algorithms
Searching algorithms
Menu-driven systems
Real-world DSA applications
🚀 Future Improvements

Possible future enhancements:

GUI version using Qt or JavaFX
File handling for permanent storage
Database integration (MySQL)
Login authentication system
Admin/User roles
Product analytics dashboard
Low-stock notifications

Hussniya Mohammed Yebrie
3rd Year Software Engineering Student
Bahir Dar University
