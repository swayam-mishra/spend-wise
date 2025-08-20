# Spend Wise: AI-Powered Financial CLI

![Tech Stack](https://img.shields.io/badge/Tech-C%2B%2B%2C%20Python%2C%20MySQL-blueviolet)

Spend Wise is a command-line interface (CLI) application designed for personal finance management. It provides a robust C++ backend for core transaction handling and leverages a Python analytics engine to offer intelligent insights, including future expense prediction and AI-generated financial tips.

## Visual Demo

*(Once your project is running, take screenshots and replace these placeholders. This is crucial for making a great first impression!)*

**C++ Application Interface:**
![C++ CLI Screenshot](https://placehold.co/600x300/2d3748/ffffff?text=C%2B%2B%20App%20Screenshot%0A(Menu%2C%20Reports%2C%20etc.))

**Python Expense Prediction Chart:**
![Python Matplotlib Chart](https://placehold.co/600x400/2d3748/ffffff?text=Python%20Expense%20Prediction%20Chart)

---

## Core Features

* **Transaction Management:** Add, view, and manage income and expense transactions.
* **Monthly Financial Reports:** Generate detailed monthly summaries of total income, expenses, and net savings.
* **Predictive Analytics:** Utilizes a Machine Learning model to forecast next month's spending based on historical data.
* **AI-Powered Insights:** Integrates with a Generative AI model to provide personalized financial tips based on your spending habits.
* **Secure & Robust:** Employs modern C++ practices and secure database operations to ensure data integrity.

---

## Tech Stack

| Category              | Technology                                       |
| --------------------- | ------------------------------------------------ |
| **Core Logic** | C++ (Modern C++17)                               |
| **Database** | MySQL                                            |
| **Analytics & ML** | Python 3, Pandas, Scikit-learn, Matplotlib       |
| **Generative AI** | Hugging Face Inference API                       |
| **Build & Environment** | g++ / MSVC, Git & GitHub                         |

---

## Architecture & Design Decisions

This project was built with a strong emphasis on the skills required for modern software development.

### 1. Object-Oriented Design (OOD) & SOLID Principles

The C++ core is designed with a clear separation of concerns, adhering to the **Single Responsibility Principle (SRP)**:
* **`User` & `Transaction` Classes:** These classes act as simple data models, responsible only for holding their respective data.
* **`DatabaseManager` Class:** This class is solely responsible for all database communication (connecting, querying, disconnecting). It abstracts away the SQL logic from the main application flow.
* **`main.cpp`:** Serves as the "View" and "Controller," handling user interaction and orchestrating calls to the `DatabaseManager`.

### 2. Database Design & Security

The database schema was designed to be efficient and maintain relational integrity.
* **Data Modeling (ERD):** The relationship is straightforward: a `user` can have many `transactions`.

    ```plaintext
    +-------------+       +------------------+
    |    users    |       |   transactions   |
    +-------------+       +------------------+
    | id (PK)     |-------| id (PK)          |
    | name        |       | user_id (FK)     |
    | created_at  |       | amount           |
    +-------------+       | category         |
                          | type             |
                          | transaction_date |
                          +------------------+
    ```
* **Implementation (DDL):** The schema uses appropriate data types (`DECIMAL` for currency, `ENUM` for transaction types) and a `FOREIGN KEY` constraint with `ON DELETE CASCADE` to ensure data integrity.
* **Security:** All SQL queries are executed using **Prepared Statements**. This is a critical security measure that prevents SQL injection vulnerabilities by separating the SQL logic from the user-provided data.

### 3. Machine Learning Model

* **Model Choice:** **Linear Regression** was chosen as the initial model to establish a baseline for predicting future spending. Its simplicity and interpretability make it ideal for identifying a linear trend in spending over time.
* **Data Processing:** The **Pandas** library is used to fetch data from the MySQL database and aggregate it into a monthly time series, which serves as the input for the model.

### 4. Generative AI Integration

* **Personalization:** The Generative AI feature is designed to be genuinely useful. Instead of generating generic advice, the application first analyzes the user's top spending categories for the month.
* **Dynamic Prompt Engineering:** This analysis is used to programmatically build a specific, context-rich prompt for the AI model (e.g., a Hugging Face model via its API). This results in personalized, actionable tips relevant to the user's actual spending habits.

---

## Setup and Installation

### Prerequisites

* A C++ compiler (g++ on Linux/WSL, or MSVC on Windows)
* MySQL Server
* MySQL Connector/C++ (Version 8.0 is recommended for broad compatibility)
* Python 3 and Pip

### 1. C++ Application (Phase 1)

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/swayam-mishra/spend-wise.git](https://github.com/swayam-mishra/spend-wise.git)
    cd spend-wise
    ```

2.  **Set up the Database:**
    * Connect to your local MySQL server.
    * Execute the `sql/schema.sql` script to create the `finance_tracker` database and its tables.
    ```bash
    mysql -u your_user -p < sql/schema.sql
    ```

3.  **Configure Credentials:**
    * Rename `config.ini.example` to `config.ini`.
    * Edit `config.ini` and fill in your MySQL `host`, `user`, and `password`.

4.  **Compile the Code:**
    * Navigate to the `build/` directory.
    * Use the appropriate compile command for your environment (see project documentation for specific commands for MinGW, Linux, or MSVC).
    * *Example for Linux/WSL:*
        ```bash
        g++ ../src/*.cpp -o main -lmysqlcppconn
        ```

5.  **Run the Application:**
    ```bash
    ./main
    ```

### 2. Python Analytics (Phase 2)

1.  **Navigate to the analytics directory:**
    ```bash
    cd analytics/
    ```

2.  **Install Python dependencies:**
    ```bash
    pip install -r requirements.txt
    ```

3.  **Run the analyzer:**
    ```bash
    python expense_analyzer.py
    ```

## Usage

Once the C++ application is running, you will be presented with a menu:

1.  **Add Transaction:** Follow the prompts to enter the details of a new income or expense.
2.  **View All Transactions:** Displays a formatted table of all your transactions.
3.  **Generate Monthly Report:** Enter a month and year to see a summary of your finances for that period.
4.  **Exit:** Closes the application.
