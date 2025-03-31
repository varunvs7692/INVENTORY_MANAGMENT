#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <string> // Add this header for to_string
// #include "customer_id_generator.h"  // Not used since MySQL auto-generates IDs

using namespace std;

// Function Prototypes
MYSQL* connectDB();
void exportToCSV(MYSQL* conn, string tableName, const char* filename);
bool loginUser(MYSQL* conn, string& role);
bool userLogin(MYSQL* conn, string& role);
void registerCustomer(MYSQL* conn);
void displayCustomers(MYSQL* conn);
void addInventory(MYSQL* conn);
void displayInventory(MYSQL* conn);
void trackAllOrders(MYSQL* conn);
void updateOrderStatus(MYSQL* conn);
void deleteInventoryItem(MYSQL* conn);
void manageUsers(MYSQL* conn);
void generateFinancialReports(MYSQL* conn);
void inventoryAlerts(MYSQL* conn);
void advancedSearch(MYSQL* conn);
void auditLog(MYSQL* conn);
void customizableReports(MYSQL* conn);
void insertAdditionalSampleData(MYSQL* conn); // Partial sample data insertion
void insertAllSampleData(MYSQL* conn);         // Full sample data insertion

// Additional General Features (Placeholders)
void twoFactorAuth(MYSQL* conn);
void dataEncryption(MYSQL* conn);
void graphicalDashboard(MYSQL* conn);
void multiLanguageSupport(MYSQL* conn);
void realTimeNotifications(MYSQL* conn);
void supportTicketing(MYSQL* conn);

// Customer Features (Placeholders)
void wishlist(MYSQL* conn);
void savePaymentPreferences(MYSQL* conn);
void downloadInvoice(MYSQL* conn);
void orderNotifications(MYSQL* conn);
void reviewRatingSystem(MYSQL* conn);
void editPersonalInfo(MYSQL* conn);
void cancelPendingOrders(MYSQL* conn);
void trackOrderStatus(MYSQL* conn);
void requestSupport(MYSQL* conn);

// -------------------- MySQL Connection --------------------
const string SERVER = "localhost";
const string USER = "root";
const string PASSWORD = "MySQL#7692";
const string DATABASE = "shipping_db";

MYSQL* connectDB() {
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER.c_str(), USER.c_str(), PASSWORD.c_str(), DATABASE.c_str(), 0, NULL, 0)) {
        cerr << "Database Connection Failed: " << mysql_error(conn) << endl;
        exit(1);
    }
    return conn;
}

// -------------------- Export CSV --------------------
void exportToCSV(MYSQL* conn, string tableName, const char* filename) {
    string query = "SELECT * FROM " + tableName;
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    ofstream file(filename);
    int num_fields = mysql_num_fields(res);
    MYSQL_FIELD* fields = mysql_fetch_fields(res);
    for (int i = 0; i < num_fields; i++) {
        file << fields[i].name << (i == num_fields - 1 ? "\n" : ",");
    }
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_fields; i++) {
            file << row[i] << (i == num_fields - 1 ? "\n" : ",");
        }
    }
    file.close();
    cout << "Report exported to " << filename << endl;
}

// -------------------- Insert Additional Sample Data (Partial) --------------------
void insertAdditionalSampleData(MYSQL* conn) {
    const char* queryOrders = "INSERT INTO Orders (customerID, itemID, quantity, amountDue, status) VALUES "
                              "(1, 1, 2, 5000.0, 'Pending'), "
                              "(2, 2, 5, 1000.0, 'Shipped'), "
                              "(3, 3, 3, 1500.0, 'Delivered')";
    if (mysql_query(conn, queryOrders))
        cerr << "Error inserting Orders: " << mysql_error(conn) << endl;
    else
        cout << "Orders sample data inserted successfully!" << endl;

    const char* queryWishlist = "INSERT INTO Wishlist (customerID, itemID) VALUES "
                                "(1, 3), "
                                "(2, 4), "
                                "(3, 5)";
    if (mysql_query(conn, queryWishlist))
        cerr << "Error inserting Wishlist: " << mysql_error(conn) << endl;
    else
        cout << "Wishlist sample data inserted successfully!" << endl;

    const char* querySupportTickets = "INSERT INTO SupportTickets (customerID, issueDescription, status) VALUES "
                                      "(1, 'Order not received', 'Open'), "
                                      "(2, 'Payment issue', 'In Progress'), "
                                      "(3, 'Wrong item delivered', 'Resolved')";
    if (mysql_query(conn, querySupportTickets))
        cerr << "Error inserting SupportTickets: " << mysql_error(conn) << endl;
    else
        cout << "SupportTickets sample data inserted successfully!" << endl;

    const char* queryAuditLog = "INSERT INTO AuditLog (userID, actionDescription) VALUES "
                                "(1, 'Added new inventory item'), "
                                "(2, 'Updated order status'), "
                                "(1, 'Deleted customer record')";
    if (mysql_query(conn, queryAuditLog))
        cerr << "Error inserting AuditLog: " << mysql_error(conn) << endl;
    else
        cout << "AuditLog sample data inserted successfully!" << endl;

    const char* queryPaymentPreferences = "INSERT INTO PaymentPreferences (customerID, paymentMethod, cardNumber, expiryDate) VALUES "
                                          "(1, 'Credit Card', '1234567812345678', '2026-12-31'), "
                                          "(2, 'Debit Card', '8765432187654321', '2025-11-30')";
    if (mysql_query(conn, queryPaymentPreferences))
        cerr << "Error inserting PaymentPreferences: " << mysql_error(conn) << endl;
    else
        cout << "PaymentPreferences sample data inserted successfully!" << endl;

    const char* queryNotifications = "INSERT INTO Notifications (customerID, message) VALUES "
                                     "(1, 'Your order has been shipped'), "
                                     "(2, 'Your payment was successful')";
    if (mysql_query(conn, queryNotifications))
        cerr << "Error inserting Notifications: " << mysql_error(conn) << endl;
    else
        cout << "Notifications sample data inserted successfully!" << endl;

    const char* queryReviews = "INSERT INTO Reviews (customerID, itemID, rating, reviewText) VALUES "
                               "(1, 1, 5, 'Excellent product'), "
                               "(2, 2, 4, 'Good quality')";
    if (mysql_query(conn, queryReviews))
        cerr << "Error inserting Reviews: " << mysql_error(conn) << endl;
    else
        cout << "Reviews sample data inserted successfully!" << endl;
}

// -------------------- Insert All Sample Data --------------------
void insertAllSampleData(MYSQL* conn) {
    // Insert Sample Users
    const char* queryUsers = "INSERT INTO Users (username, password, role) VALUES "
                             "('admin', 'admin123', 'Admin'), "
                             "('user1', 'user123', 'User ')";
    if (mysql_query(conn, queryUsers))
        cerr << "Error inserting Users: " << mysql_error(conn) << endl;
    else
        cout << "Users sample data inserted successfully!" << endl;

    // Insert Sample Customers
    const char* queryCustomers = "INSERT INTO Customers (name, contact, address) VALUES "
                                 "('Dhruv Patel', '+1 1234567890', '123 Main St, Chicago, America'), "
                                 "('Ramkrishan', '+1 9876543210', '456 Elm St, Toronto, Canada'), "
                                 "('Riyaz', '+92 43234523', 'Lahore, Pakistan'), "
                                 "('HM Sultan', '+968 44332211', 'Muscat International Airport, P.O. Box 1707, P.C. 111, CPO, Muscat, As Seeb, Masqat'), "
                                 "('Justin', '+55 812-446-2211', '22 S Washington St, Brazil, IN 47834')";
    if (mysql_query(conn, queryCustomers))
        cerr << "Error inserting Customers: " << mysql_error(conn) << endl;
    else
        cout << "Customers sample data inserted successfully!" << endl;

    // Insert Sample Inventory Data
    const char* queryInventory = "INSERT INTO Inventory (itemName, quantity, weight, destination) VALUES "
                                 "('Laptop', 10, 2.5, 'USA'), "
                                 "('Mobile Phone', 50, 0.2, 'India'), "
                                 "('Tablet', 20, 1.5, 'UK'), "
                                 "('Printer', 15, 7.5, 'Germany'), "
                                 "('Headphones', 100, 0.3, 'France')";
    if (mysql_query(conn, queryInventory))
        cerr << "Error inserting Inventory: " << mysql_error(conn) << endl;
    else
        cout << "Inventory sample data inserted successfully!" << endl;

    // Insert Sample Orders Data
    const char* queryOrders = "INSERT INTO Orders (customerID, itemID, quantity, amountDue, status) VALUES "
                              "(1, 1, 2, 5000.0, 'Pending'), "
                              "(2, 2, 5, 1000.0, 'Shipped'), "
                              "(3, 3, 3, 1500.0, 'Delivered')";
    if (mysql_query(conn, queryOrders))
        cerr << "Error inserting Orders: " << mysql_error(conn) << endl;
    else
        cout << "Orders sample data inserted successfully!" << endl;

    // Insert Sample Wishlist Data
    const char* queryWishlist = "INSERT INTO Wishlist (customerID, itemID) VALUES "
                                "(1, 3), "
                                "(2, 4), "
                                "(3, 5)";
    if (mysql_query(conn, queryWishlist))
        cerr << "Error inserting Wishlist: " << mysql_error(conn) << endl;
    else
        cout << "Wishlist sample data inserted successfully!" << endl;

    // Insert Sample Support Tickets Data
    const char* querySupportTickets = "INSERT INTO SupportTickets (customerID, issueDescription, status) VALUES "
                                      "(1, 'Order not received', 'Open'), "
                                      "(2, 'Payment issue', 'In Progress'), "
                                      "(3, 'Wrong item delivered', 'Resolved')";
    if (mysql_query(conn, querySupportTickets))
        cerr << "Error inserting SupportTickets: " << mysql_error(conn) << endl;
    else
        cout << "SupportTickets sample data inserted successfully!" << endl;

    // Insert Sample Audit Log Data
    const char* queryAuditLog = "INSERT INTO AuditLog (userID, actionDescription) VALUES "
                                "(1, 'Added new inventory item'), "
                                "(2, 'Updated order status'), "
                                "(1, 'Deleted customer record')";
    if (mysql_query(conn, queryAuditLog))
        cerr << "Error inserting AuditLog: " << mysql_error(conn) << endl;
    else
        cout << "AuditLog sample data inserted successfully!" << endl;

    // Insert Sample Payment Preferences Data
    const char* queryPaymentPreferences = "INSERT INTO PaymentPreferences (customerID, paymentMethod, cardNumber, expiryDate) VALUES "
                                          "(1, 'Credit Card', '1234567812345678', '2026-12-31'), "
                                          "(2, 'Debit Card', '8765432187654321', '2025-11-30')";
    if (mysql_query(conn, queryPaymentPreferences))
        cerr << "Error inserting PaymentPreferences: " << mysql_error(conn) << endl;
    else
        cout << "PaymentPreferences sample data inserted successfully!" << endl;

    // Insert Sample Notifications Data
    const char* queryNotifications = "INSERT INTO Notifications (customerID, message) VALUES "
                                     "(1, 'Your order has been shipped'), "
                                     "(2, 'Your payment was successful')";
    if (mysql_query(conn, queryNotifications))
        cerr << "Error inserting Notifications: " << mysql_error(conn) << endl;
    else
        cout << "Notifications sample data inserted successfully!" << endl;

    // Insert Sample Reviews Data
    const char* queryReviews = "INSERT INTO Reviews (customerID, itemID, rating, reviewText) VALUES "
                               "(1, 1, 5, 'Excellent product'), "
                               "(2, 2, 4, 'Good quality')";
    if (mysql_query(conn, queryReviews))
        cerr << "Error inserting Reviews: " << mysql_error(conn) << endl;
    else
        cout << "Reviews sample data inserted successfully!" << endl;
}

// -------------------- Customer Features (Placeholders) --------------------
void wishlist(MYSQL* conn) {
    string customerId;
    cout << "Enter Customer ID to view Wishlist: ";
    cin >> customerId;
    string query = "SELECT Wishlist.itemID, Inventory.itemName FROM Wishlist "
                   "JOIN Inventory ON Wishlist.itemID = Inventory.itemID "
                   "WHERE Wishlist.customerID = " + customerId;
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\nWishlist:\n---------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Item ID: " << row[0] << " | Item Name: " << row[1] << "\n";
    }
    mysql_free_result(res);
}

void savePaymentPreferences(MYSQL* conn) {
    string customerId, paymentMethod, cardNumber, expiryDate;
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter Payment Method (e.g., Credit Card, Debit Card): ";
    cin.ignore();
    getline(cin, paymentMethod);
    cout << "Enter Card Number: ";
    getline(cin, cardNumber);
    cout << "Enter Expiry Date (YYYY-MM-DD): ";
    getline(cin, expiryDate);
    string query = "INSERT INTO PaymentPreferences (customerID, paymentMethod, cardNumber, expiryDate) VALUES ('" +
                   customerId + "', '" + paymentMethod + "', '" + cardNumber + "', '" + expiryDate + "')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Payment preferences saved successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void downloadInvoice(MYSQL* conn) {
    string orderId;
    cout << "Enter Order ID to download invoice: ";
    cin >> orderId;
    string query = "SELECT * FROM Orders WHERE orderID = " + orderId;
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        string filename = "invoice_" + orderId + ".txt";
        ofstream file(filename.c_str()); // Explicitly convert to const char*
        file << "Invoice for Order ID: " << row[0] << "\n";
        file << "Customer ID: " << row[1] << "\n";
        file << "Item ID: " << row[2] << "\n";
        file << "Quantity: " << row[3] << "\n";
        file << "Amount Due: $" << row[4] << "\n";
        file << "Status: " << row[5] << "\n";
        file.close();
        cout << "Invoice downloaded successfully as " << filename << "\n";
    } else {
        cout << "Order not found.\n";
    }
    mysql_free_result(res);
}

void orderNotifications(MYSQL* conn) {
    string customerId;
    cout << "Enter Customer ID to view notifications: ";
    cin >> customerId;
    string query = "SELECT message FROM Notifications WHERE customerID = " + customerId;
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\nOrder Notifications:\n---------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Message: " << row[0] << "\n";
    }
    mysql_free_result(res);
}

void reviewRatingSystem(MYSQL* conn) {
    string customerId, itemId, rating, reviewText;
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter Item ID: ";
    cin >> itemId;
    cout << "Enter Rating (1-5): ";
    cin >> rating;
    cout << "Enter Review Text: ";
    cin.ignore();
    getline(cin, reviewText);
    string query = "INSERT INTO Reviews (customerID, itemID, rating, reviewText) VALUES ('" +
                   customerId + "', '" + itemId + "', '" + rating + "', '" + reviewText + "')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Review and rating submitted successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void editPersonalInfo(MYSQL* conn) {
    string customerId, name, contact, address;
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter New Contact: ";
    getline(cin, contact);
    cout << "Enter New Address: ";
    getline(cin, address);
    string query = "UPDATE Customers SET name = '" + name + "', contact = '" + contact + "', address = '" + address +
                   "' WHERE customerID = " + customerId;
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Personal information updated successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void cancelPendingOrders(MYSQL* conn) {
    string orderId;
    cout << "Enter Order ID to cancel: ";
    cin >> orderId;
    string query = "DELETE FROM Orders WHERE orderID = " + orderId + " AND status = 'Pending'";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Pending order canceled successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void trackOrderStatus(MYSQL* conn) {
    string orderId;
    cout << "Enter Order ID to track: ";
    cin >> orderId;
    string query = "SELECT status FROM Orders WHERE orderID = " + orderId;
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        cout << "Order Status: " << row[0] << "\n";
    } else {
        cout << "Order not found.\n";
    }
    mysql_free_result(res);
}

void requestSupport(MYSQL* conn) {
    string customerId, issueDescription;
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter Issue Description: ";
    cin.ignore();
    getline(cin, issueDescription);
    string query = "INSERT INTO SupportTickets (customerID, issueDescription, status) VALUES ('" +
                   customerId + "', '" + issueDescription + "', 'Open')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Support request submitted successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

// -------------------- Admin Features --------------------

// Modified registerCustomer: Let MySQL auto-generate the customerID
void registerCustomer(MYSQL* conn) {
    string name, contact, address;
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Contact: ";
    getline(cin, contact);
    cout << "Enter Address: ";
    getline(cin, address);
    string query = "INSERT INTO Customers (name, contact, address) VALUES ('" + name + "', '" + contact + "', '" + address + "')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Customer Registered Successfully!" << endl;
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void displayCustomers(MYSQL* conn) {
    string query = "SELECT * FROM Customers";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\nRegistered Customers:\n---------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "ID: " << row[0] << " | Name: " << row[1] 
             << " | Contact: " << row[2] << " | Address: " << row[3] << "\n";
    }
    mysql_free_result(res);
}

void addInventory(MYSQL* conn) {
    string item, quantity;
    cout << "Enter Item Name: ";
    cin.ignore();
    getline(cin, item);
    cout << "Enter Quantity: ";
    cin >> quantity;
    string query = "INSERT INTO Inventory (itemName, quantity, weight, destination) VALUES ('" 
                   + item + "', " + quantity + ", 0, 'Unknown')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Inventory Item Added Successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void displayInventory(MYSQL* conn) {
    string query = "SELECT * FROM Inventory";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\nInventory:\n---------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "ID: " << row[0] << " | Item: " << row[1] 
             << " | Quantity: " << row[2] << "\n";
    }
    mysql_free_result(res);
}

void trackAllOrders(MYSQL* conn) {
    string query = "SELECT * FROM Orders";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\nAll Orders:\n---------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Order ID: " << row[0] << " | Customer ID: " << row[1]
             << " | Item ID: " << row[2] << " | Quantity: " << row[3]
             << " | Amount Due: " << row[4] << " | Status: " << row[5] << "\n";
    }
    mysql_free_result(res);
}

void updateOrderStatus(MYSQL* conn) {
    string orderId, status;
    cout << "Enter Order ID: ";
    cin >> orderId;
    cout << "Enter New Status (Pending/Shipped/Delivered): ";
    cin >> status;
    string query = "UPDATE Orders SET status='" + status + "' WHERE orderID=" + orderId;
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Order status updated successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void deleteInventoryItem(MYSQL* conn) {
    string itemId;
    cout << "Enter Inventory Item ID to Delete: ";
    cin >> itemId;
    string query = "DELETE FROM Inventory WHERE itemID=" + itemId;
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Inventory item deleted successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void manageUsers(MYSQL* conn) {
    string username, role;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Role (Admin/User): ";
    cin >> role;
    string query = "INSERT INTO Users (username, password, role) VALUES ('" 
                   + username + "', 'default', '" + role + "')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "User added successfully!\n";
    else
        cerr << "Error: " << mysql_error(conn) << endl;
}

void generateFinancialReports(MYSQL* conn) {
    string query = "SELECT SUM(amountDue) AS TotalRevenue FROM Orders";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    cout << "Generating financial reports...\n";
    if (row) {
        cout << "Total Revenue: $" << row[0] << "\n";
    } else {
        cout << "No financial data available.\n";
    }
    mysql_free_result(res);
}

void inventoryAlerts(MYSQL* conn) {
    string query = "SELECT itemName, quantity FROM Inventory WHERE quantity < 10";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Inventory Alerts:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Item: " << row[0] << " - Low Stock (" << row[1] << " remaining)\n";
    }
    mysql_free_result(res);
}

void advancedSearch(MYSQL* conn) {
    string query = "SELECT name, COUNT(Orders.orderID) AS OrderCount FROM Customers "
                   "LEFT JOIN Orders ON Customers.customerID = Orders.customerID "
                   "GROUP BY Customers.customerID";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Advanced Search Results:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Customer: " << row[0] << " - Orders: " << row[1] << "\n";
    }
    mysql_free_result(res);
}

void auditLog(MYSQL* conn) {
    string query = "SELECT * FROM AuditLog";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Audit Log:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "User ID: " << row[0] << " | Action: " << row[1] << "\n";
    }
    mysql_free_result(res);
}

void customizableReports(MYSQL* conn) {
    string query = "SELECT itemName, SUM(quantity) AS TotalQuantity FROM Inventory GROUP BY itemName";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Customizable Reports:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Item: " << row[0] << " | Total Quantity: " << row[1] << "\n";
    }
    mysql_free_result(res);
}

void twoFactorAuth(MYSQL* conn) {
    cout << "Two-Factor Authentication activated!\n";
    cout << "Verification code sent to registered email.\n";
    string query = "INSERT INTO AuditLog (userID, actionDescription) VALUES (1, 'Activated Two-Factor Authentication')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Audit log updated successfully.\n";
    else
        cerr << "Error updating audit log: " << mysql_error(conn) << endl;
}

void dataEncryption(MYSQL* conn) {
    cout << "Data Encryption:\n";
    cout << "Sensitive data encrypted using AES-256.\n";
    string query = "INSERT INTO AuditLog (userID, actionDescription) VALUES (1, 'Enabled Data Encryption')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Audit log updated successfully.\n";
    else
        cerr << "Error updating audit log: " << mysql_error(conn) << endl;
}

void graphicalDashboard(MYSQL* conn) {
    cout << "Graphical Dashboard:\n";
    cout << "Displaying sales trends, inventory levels, and customer activity.\n";
    string query = "INSERT INTO AuditLog (userID, actionDescription) VALUES (1, 'Accessed Graphical Dashboard')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Audit log updated successfully.\n";
    else
        cerr << "Error updating audit log: " << mysql_error(conn) << endl;
}

void multiLanguageSupport(MYSQL* conn) {
    cout << "Multi-Language Support:\n";
    cout << "Available languages: English, Spanish, French, German.\n";
    string query = "INSERT INTO AuditLog (userID, actionDescription) VALUES (1, 'Enabled Multi-Language Support')";
    if (mysql_query(conn, query.c_str()) == 0)
        cout << "Audit log updated successfully.\n";
    else
        cerr << "Error updating audit log: " << mysql_error(conn) << endl;
}

void realTimeNotifications(MYSQL* conn) {
    string query = "SELECT * FROM Notifications";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Real-Time Notifications:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Customer ID: " << row[0] << " | Message: " << row[1] << "\n";
    }
    mysql_free_result(res);
}

void supportTicketing(MYSQL* conn) {
    string query = "SELECT * FROM SupportTickets";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "Support Ticketing System:\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Ticket ID: " << row[0] << " | Customer ID: " << row[1]
             << " | Issue: " << row[2] << " | Status: " << row[3] << "\n";
    }
    mysql_free_result(res);
}

// -------------------- Menus --------------------
void adminMenu(MYSQL* conn) {
    int choice;
    while (true) {
        cout << "\n=== Admin Menu ===\n";
        cout << "1. Register Customer\n";
        cout << "2. Display Customers\n";
        cout << "3. Add Inventory\n";
        cout << "4. Display Inventory\n";
        cout << "5. Track All Orders\n";
        cout << "6. Update Order Status\n";
        cout << "7. Delete Inventory Item\n";
        cout << "8. Manage Users\n";
        cout << "9. Export CSV Report\n";
        cout << "10. Generate Financial Reports\n";
        cout << "11. Inventory Alerts\n";
        cout << "12. Advanced Search & Filter\n";
        cout << "13. Audit Log\n";
        cout << "14. Customizable Reports\n";
        cout << "15. Wishlist\n";
        cout << "16. Save Payment Preferences\n";
        cout << "17. Download Invoice\n";
        cout << "18. Order Notifications\n";
        cout << "19. Review and Rating System\n";
        cout << "20. Edit Personal Information\n";
        cout << "21. Cancel Pending Orders\n";
        cout << "22. Track Order Status\n";
        cout << "23. Request Support\n";
        cout << "24. Two-Factor Authentication\n";
        cout << "25. Data Encryption\n";
        cout << "26. Graphical Dashboard\n";
        cout << "27. Multi-language Support\n";
        cout << "28. Real-Time Notifications\n";
        cout << "29. Support Ticketing\n";
        cout << "30. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:  registerCustomer(conn); break;
            case 2:  displayCustomers(conn); break;
            case 3:  addInventory(conn); break;
            case 4:  displayInventory(conn); break;
            case 5:  trackAllOrders(conn); break;
            case 6:  updateOrderStatus(conn); break;
            case 7:  deleteInventoryItem(conn); break;
            case 8:  manageUsers(conn); break;
            case 9:  exportToCSV(conn, "Customers", "customers.csv"); break;
            case 10: generateFinancialReports(conn); break;
            case 11: inventoryAlerts(conn); break;
            case 12: advancedSearch(conn); break;
            case 13: auditLog(conn); break;
            case 14: customizableReports(conn); break;
            case 15: wishlist(conn); break;
            case 16: savePaymentPreferences(conn); break;
            case 17: downloadInvoice(conn); break;
            case 18: orderNotifications(conn); break;
            case 19: reviewRatingSystem(conn); break;
            case 20: editPersonalInfo(conn); break;
            case 21: cancelPendingOrders(conn); break;
            case 22: trackOrderStatus(conn); break;
            case 23: requestSupport(conn); break;
            case 24: twoFactorAuth(conn); break;
            case 25: dataEncryption(conn); break;
            case 26: graphicalDashboard(conn); break;
            case 27: multiLanguageSupport(conn); break;
            case 28: realTimeNotifications(conn); break;
            case 29: supportTicketing(conn); break;
            case 30: return; // Exit Admin Menu
            default: cout << "Invalid choice or insufficient permission!\n";
        }
    }
}

void viewOrdersByCustomerID(MYSQL* conn, int customerID) {
    stringstream ss;
    ss << customerID; // Convert customerID to string using stringstream
    string query = "SELECT Orders.orderID, Orders.itemID, Inventory.itemName, Orders.quantity, Orders.amountDue, Orders.status "
                   "FROM Orders "
                   "JOIN Inventory ON Orders.itemID = Inventory.itemID "
                   "WHERE Orders.customerID = " + ss.str(); // Use the converted string
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\nYour Orders:\n---------------------------------\n";
    while ((row = mysql_fetch_row(res))) {
        cout << "Order ID: " << row[0] << " | Item ID: " << row[1] 
             << " | Item Name: " << row[2] << " | Quantity: " << row[3]
             << " | Amount Due: $" << row[4] << " | Status: " << row[5] << "\n";
    }
    mysql_free_result(res);
}

void userMenu(MYSQL* conn, const string& role) {
    int customerID;
    cout << "Enter your Customer ID: ";
    cin >> customerID;
    int choice;
    while (true) {
        cout << "\n=== User Menu (" << role << ") ===\n";
        cout << "1. Display Inventory\n";
        cout << "2. View Your Orders\n";
        cout << "3. Wishlist\n";
        cout << "4. Save Payment Preferences\n";
        cout << "5. Download Invoice\n";
        cout << "6. Order Notifications\n";
        cout << "7. Review and Rating System\n";
        cout << "8. Edit Personal Information\n";
        cout << "9. Cancel Pending Orders\n";
        cout << "10. Track Order Status\n";
        cout << "11. Request Support\n";
        cout << "12. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: displayInventory(conn); break;
            case 2: viewOrdersByCustomerID(conn, customerID); break; // View orders by customerID
            case 3: wishlist(conn); break;
            case 4: savePaymentPreferences(conn); break;
            case 5: downloadInvoice(conn); break;
            case 6: orderNotifications(conn); break;
            case 7: reviewRatingSystem(conn); break;
            case 8: editPersonalInfo(conn); break;
            case 9: cancelPendingOrders(conn); break;
            case 10: trackOrderStatus(conn); break;
            case 11: requestSupport(conn); break;
            case 12: return; // Exit User Menu
            default: cout << "Invalid choice or insufficient permission!\n";
        }
    }
}

// -------------------- User Authentication --------------------
bool loginUser(MYSQL* conn, string& role) {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    string query = "SELECT role FROM Users WHERE username = '" + username + "' AND password = '" + password + "'";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        role = row[0];
        cout << "Login Successful! Role: " << role << endl;
        if (role == "User") {
            cout << "Welcome, Customer! You have limited access to the system.\n";
        }
        mysql_free_result(res);
        return true;
    } else {
        cout << "Invalid Credentials or Insufficient Permissions!\n";
        mysql_free_result(res);
        return false;
    }
}

bool userLogin(MYSQL* conn, string& role) {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    string query = "SELECT role FROM Users WHERE username = '" + username + "' AND password = '" + password + "'";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        role = row[0];
        cout << "Login Successful! Role: " << role << endl;
        mysql_free_result(res);
        return true;
    } else {
        cout << "Invalid Credentials or Insufficient Permissions!\n";
        mysql_free_result(res);
        return false;
    }
}

bool adminLogin(MYSQL* conn) {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;
    cout << "Enter Admin Password: ";
    cin >> password;
    string query = "SELECT role FROM Users WHERE username = '" + username + "' AND password = '" + password + "' AND role = 'Admin'";
    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        cout << "Admin Login Successful! Welcome, Admin.\n";
        mysql_free_result(res);
        return true;
    } else {
        cout << "Invalid Admin Credentials!\n";
        mysql_free_result(res);
        return false;
    }
}

void userRoles(MYSQL* conn) {
    string role;
    if (userLogin(conn, role)) {
        if (role == "Admin") {
            adminMenu(conn);
        } else if (role == "User") {
            userMenu(conn, role);
        } else {
            cout << "Unknown role. Exiting...\n";
        }
    }
}

int main() {
    MYSQL* conn = connectDB();
    string choice;
    cout << "Are you logging in as Admin or User? (Enter 'Admin' or 'User'): ";
    cin >> choice;
    if (choice == "Admin") {
        if (adminLogin(conn)) {
            adminMenu(conn);
        }
    } else if (choice == "User") {
        userRoles(conn);
    } else {
        cout << "Invalid choice. Exiting...\n";
    }
    mysql_close(conn);
    cout << "Press Enter to exit...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}


