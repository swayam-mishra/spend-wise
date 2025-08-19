-- Create the database if it doesn't exist
CREATE DATABASE IF NOT EXISTS spend_wise;

-- Use the newly created database
USE spend_wise;

-- Drop existing tables to ensure a clean setup
DROP TABLE IF EXISTS transactions;
DROP TABLE IF EXISTS users;


CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE transactions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    amount DECIMAL(10, 2) NOT NULL, 
    category VARCHAR(100) NOT NULL,
    type ENUM('income', 'expense') NOT NULL,
    transaction_date DATE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);