-- ***************************************************************
-- Optional: Drop the database if it exists (use with caution)
-- ***************************************************************
DROP DATABASE IF EXISTS shipping_db;

-- ***************************************************************
-- 1. Create and Use the Database
-- ***************************************************************
CREATE DATABASE shipping_db;
USE shipping_db;

-- ***************************************************************
-- 2. Create Tables
-- ***************************************************************

-- Users Table (For Login)
CREATE TABLE Users (
    userID INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) UNIQUE,
    password VARCHAR(50),
    role ENUM('Admin', 'User')
);

-- Customers Table
CREATE TABLE Customers (
    customerID INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    contact VARCHAR(20),
    address VARCHAR(255)
);

-- Inventory Table
CREATE TABLE Inventory (
    itemID INT AUTO_INCREMENT PRIMARY KEY,
    itemName VARCHAR(100),
    quantity INT,
    weight DOUBLE,
    destination VARCHAR(100)
);

-- Orders Table
CREATE TABLE Orders (
    orderID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT,
    itemID INT,
    quantity INT,
    amountDue DOUBLE,
    status VARCHAR(50),
    FOREIGN KEY (customerID) REFERENCES Customers(customerID),
    FOREIGN KEY (itemID) REFERENCES Inventory(itemID)
);

-- Wishlist Table
CREATE TABLE Wishlist (
    wishlistID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT,
    itemID INT,
    dateAdded TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customerID) REFERENCES Customers(customerID),
    FOREIGN KEY (itemID) REFERENCES Inventory(itemID)
);

-- Support Tickets Table
CREATE TABLE SupportTickets (
    ticketID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT,
    issueDescription TEXT,
    status ENUM('Open', 'In Progress', 'Resolved', 'Closed') DEFAULT 'Open',
    dateCreated TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customerID) REFERENCES Customers(customerID)
);

-- Audit Log Table
CREATE TABLE AuditLog (
    logID INT AUTO_INCREMENT PRIMARY KEY,
    userID INT,
    actionDescription TEXT,
    actionDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (userID) REFERENCES Users(userID)
);

-- Payment Preferences Table
CREATE TABLE PaymentPreferences (
    preferenceID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT,
    paymentMethod VARCHAR(50),
    cardNumber VARCHAR(20),
    expiryDate DATE,
    FOREIGN KEY (customerID) REFERENCES Customers(customerID)
);

-- Notifications Table
CREATE TABLE Notifications (
    notificationID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT,
    message TEXT,
    dateSent TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    isRead BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (customerID) REFERENCES Customers(customerID)
);

-- Reviews Table
CREATE TABLE Reviews (
    reviewID INT AUTO_INCREMENT PRIMARY KEY,
    customerID INT,
    itemID INT,
    rating INT CHECK (rating >= 1 AND rating <= 5),
    reviewText TEXT,
    reviewDate TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customerID) REFERENCES Customers(customerID),
    FOREIGN KEY (itemID) REFERENCES Inventory(itemID)
);

-- ***************************************************************
-- 3. Insert Sample Data
-- ***************************************************************

-- Insert Sample Users
INSERT INTO Users (username, password, role) VALUES
('admin', 'admin123', 'Admin'),
('user1', 'user123', 'User');

-- Insert Sample Customers
INSERT INTO Customers (name, contact, address) VALUES
('Dhruv Patel', '+1 1234567890', '123 Main St, Chicago, America'),
('Ramkrishan', '+1 9876543210', '456 Elm St, Toronto, Canada'),
('Riyaz', '+92 43234523', 'Lahore, Pakistan'),
('HM Sultan', '+968 44332211', 'Muscat International Airport, P.O. Box 1707, P.C. 111, CPO, Muscat, As Seeb, Masqat'),
('Justin', '+55 812-446-2211', '22 S Washington St, Brazil, IN 47834'),
('Lora', '+1 812-446-2222', '1001 Desiree Blvd, Montreal, Quebec H4A 3J 1, Canada'),
('Burj Khalifa', '+971 4 888 8888', 'Sheikh Mohammed Bin Rashid Blvd, 800 BURJ Dubai'),
('Sheikh Hasina', '+971 4 888 7777', 'Mohammed Bin Rashid Blvd, 113444 دبي, UAE'),
('Abhishek Bachan', '+46-8-585 900 00', 'Landsvägen 40, Sundbyberg'),
('MD Sala', '+507 456784', 'Panama');

-- Insert Sample Inventory Data
INSERT INTO Inventory (itemName, quantity, weight, destination) VALUES
('Laptop', 10, 2.5, 'USA'),
('Mobile Phone', 50, 0.2, 'India'),
('Tablet', 20, 1.5, 'UK'),
('Printer', 15, 7.5, 'Germany'),
('Headphones', 100, 0.3, 'France'),
('Camera', 25, 3.0, 'Japan'),
('Smartwatch', 50, 0.5, 'China'),
('Gaming Console', 5, 8.0, 'Canada'),
('Monitor', 8, 10.0, 'Italy'),
('Keyboard', 30, 1.0, 'Australia');

-- Insert Sample Orders Data
INSERT INTO Orders (customerID, itemID, quantity, amountDue, status) VALUES
(1, 1, 2, 5000.0, 'Pending'),
(2, 2, 5, 1000.0, 'Shipped'),
(3, 3, 3, 1500.0, 'Delivered'),
(4, 4, 1, 200.0, 'Processing'),
(5, 5, 20, 3000.0, 'Pending'),
(6, 6, 10, 5000.0, 'Cancelled'),
(7, 7, 7, 250.0, 'Shipped'),
(8, 8, 3, 1200.0, 'Processing'),
(9, 9, 1, 100.0, 'Delivered'),
(10, 10, 4, 400.0, 'Pending');

-- Insert Sample Wishlist Data
INSERT INTO Wishlist (customerID, itemID) VALUES
(1, 3),
(2, 4),
(3, 5),
(4, 6),
(5, 7);

-- Insert Sample Support Tickets Data
INSERT INTO SupportTickets (customerID, issueDescription, status) VALUES
(1, 'Order not received', 'Open'),
(2, 'Payment issue', 'In Progress'),
(3, 'Wrong item delivered', 'Resolved'),
(4, 'Need invoice copy', 'Closed'),
(5, 'Item damaged', 'Open');

-- Insert Sample Audit Log Data
INSERT INTO AuditLog (userID, actionDescription) VALUES
(1, 'Added new inventory item'),
(2, 'Updated order status'),
(1, 'Deleted customer record'),
(2, 'Generated financial report'),
(1, 'Logged in');

-- Insert Sample Payment Preferences Data
INSERT INTO PaymentPreferences (customerID, paymentMethod, cardNumber, expiryDate) VALUES
(1, 'Credit Card', '1234567812345678', '2026-12-31'),
(2, 'Debit Card', '8765432187654321', '2025-11-30'),
(3, 'PayPal', 'paypal@example.com', NULL),
(4, 'Credit Card', '1111222233334444', '2024-10-31'),
(5, 'Debit Card', '4444333322221111', '2023-09-30');

-- Insert Sample Notifications Data
INSERT INTO Notifications (customerID, message) VALUES
(1, 'Your order has been shipped'),
(2, 'Your payment was successful'),
(3, 'Your review was posted'),
(4, 'Your support ticket was resolved'),
(5, 'Your order was delayed');

-- Insert Sample Reviews Data
INSERT INTO Reviews (customerID, itemID, rating, reviewText) VALUES
(1, 1, 5, 'Excellent product'),
(2, 2, 4, 'Good quality'),
(3, 3, 3, 'Average performance'),
(4, 4, 2, 'Not satisfied'),
(5, 5, 1, 'Poor quality');
