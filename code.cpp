#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

const int MAX_PRODUCTS = 300;
const string FILENAME = "inventory.txt";
const string SALES_FILE = "sales_history.txt";

struct Product {
    int productId;
    string productName;
    string category;
    int quantity;
    double costPrice;
    double sellingPrice;
    int reorderLevel;
    string supplier;
    string lastRestocked;
};

struct Sale {
    int productId;
    string productName;
    int quantity;
    double totalAmount;
    string date;
};

// Function prototypes
void displayMenu();
void addProduct(Product products[], int &count);
void viewAllProducts(Product products[], int count);
void searchProduct(Product products[], int count);
void updateProduct(Product products[], int count);
void deleteProduct(Product products[], int &count);
void restockProduct(Product products[], int count);
void sellProduct(Product products[], int count);
void viewLowStockProducts(Product products[], int count);
void viewProductsByCategory(Product products[], int count);
void calculateInventoryValue(Product products[], int count);
void viewProfitAnalysis(Product products[], int count);
void sortProducts(Product products[], int count);
void viewSalesHistory();
void generateInventoryReport(Product products[], int count);
void saveToFile(Product products[], int count);
void loadFromFile(Product products[], int &count);
void saveSale(Sale sale);
string getCurrentDate();

int main() {
    Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    
    // Load existing data from file
    loadFromFile(products, productCount);
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                addProduct(products, productCount);
                break;
            case 2:
                viewAllProducts(products, productCount);
                break;
            case 3:
                searchProduct(products, productCount);
                break;
            case 4:
                updateProduct(products, productCount);
                break;
            case 5:
                deleteProduct(products, productCount);
                break;
            case 6:
                restockProduct(products, productCount);
                break;
            case 7:
                sellProduct(products, productCount);
                break;
            case 8:
                viewLowStockProducts(products, productCount);
                break;
            case 9:
                viewProductsByCategory(products, productCount);
                break;
            case 10:
                calculateInventoryValue(products, productCount);
                break;
            case 11:
                viewProfitAnalysis(products, productCount);
                break;
            case 12:
                sortProducts(products, productCount);
                break;
            case 13:
                viewSalesHistory();
                break;
            case 14:
                generateInventoryReport(products, productCount);
                break;
            case 15:
                saveToFile(products, productCount);
                cout << "Data saved successfully!" << endl;
                break;
            case 16:
                saveToFile(products, productCount);
                cout << "Exiting Inventory System. Data saved!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
        
        if(choice != 16) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while(choice != 16);
    
    return 0;
}

void displayMenu() {
    system("cls");
    cout << "\n================================================" << endl;
    cout << "       INVENTORY MANAGEMENT SYSTEM" << endl;
    cout << "================================================" << endl;
    cout << "1.  Add New Product" << endl;
    cout << "2.  View All Products" << endl;
    cout << "3.  Search Product" << endl;
    cout << "4.  Update Product Details" << endl;
    cout << "5.  Delete Product" << endl;
    cout << "6.  Restock Product" << endl;
    cout << "7.  Sell Product" << endl;
    cout << "8.  View Low Stock Alert" << endl;
    cout << "9.  View by Category" << endl;
    cout << "10. Calculate Inventory Value" << endl;
    cout << "11. Profit Analysis" << endl;
    cout << "12. Sort Products" << endl;
    cout << "13. View Sales History" << endl;
    cout << "14. Generate Inventory Report" << endl;
    cout << "15. Save Data" << endl;
    cout << "16. Exit" << endl;
    cout << "================================================" << endl;
}

void addProduct(Product products[], int &count) {
    if(count >= MAX_PRODUCTS) {
        cout << "Error: Maximum product limit reached!" << endl;
        return;
    }
    
    cout << "\n--- Add New Product ---" << endl;
    
    cout << "Enter Product ID: ";
    cin >> products[count].productId;
    cin.ignore();
    
    // Check for duplicate ID
    for(int i = 0; i < count; i++) {
        if(products[i].productId == products[count].productId) {
            cout << "Error: Product ID already exists!" << endl;
            return;
        }
    }
    
    cout << "Enter Product Name: ";
    getline(cin, products[count].productName);
    
    cout << "Enter Category (Electronics/Clothing/Food/Books/etc.): ";
    getline(cin, products[count].category);
    
    cout << "Enter Quantity: ";
    cin >> products[count].quantity;
    
    cout << "Enter Cost Price: Rs. ";
    cin >> products[count].costPrice;
    
    cout << "Enter Selling Price: Rs. ";
    cin >> products[count].sellingPrice;
    
    cout << "Enter Reorder Level (minimum quantity): ";
    cin >> products[count].reorderLevel;
    cin.ignore();
    
    cout << "Enter Supplier Name: ";
    getline(cin, products[count].supplier);
    
    products[count].lastRestocked = getCurrentDate();
    
    count++;
    cout << "\nProduct added successfully!" << endl;
}

void viewAllProducts(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    cout << "\n--- Inventory List (" << count << " products) ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(25) << "Product Name" 
         << setw(15) << "Category" 
         << setw(10) << "Qty"
         << setw(12) << "Cost"
         << setw(12) << "Sell Price" << endl;
    cout << string(82, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        cout << left << setw(8) << products[i].productId
             << setw(25) << products[i].productName
             << setw(15) << products[i].category
             << setw(10) << products[i].quantity
             << "Rs." << setw(8) << fixed << setprecision(2) << products[i].costPrice
             << "Rs." << setw(8) << fixed << setprecision(2) << products[i].sellingPrice << endl;
    }
}

void searchProduct(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    cout << "\n1. Search by Product ID" << endl;
    cout << "2. Search by Product Name" << endl;
    cout << "Enter choice: ";
    int searchChoice;
    cin >> searchChoice;
    cin.ignore();
    
    bool found = false;
    
    if(searchChoice == 1) {
        int searchId;
        cout << "Enter Product ID: ";
        cin >> searchId;
        
        for(int i = 0; i < count; i++) {
            if(products[i].productId == searchId) {
                cout << "\n--- Product Found ---" << endl;
                cout << "Product ID: " << products[i].productId << endl;
                cout << "Name: " << products[i].productName << endl;
                cout << "Category: " << products[i].category << endl;
                cout << "Quantity: " << products[i].quantity << endl;
                cout << "Cost Price: Rs. " << fixed << setprecision(2) << products[i].costPrice << endl;
                cout << "Selling Price: Rs. " << fixed << setprecision(2) << products[i].sellingPrice << endl;
                cout << "Reorder Level: " << products[i].reorderLevel << endl;
                cout << "Supplier: " << products[i].supplier << endl;
                cout << "Last Restocked: " << products[i].lastRestocked << endl;
                
                double profit = products[i].sellingPrice - products[i].costPrice;
                double profitMargin = (profit / products[i].costPrice) * 100;
                cout << "Profit per Unit: Rs. " << fixed << setprecision(2) << profit << endl;
                cout << "Profit Margin: " << fixed << setprecision(1) << profitMargin << "%" << endl;
                
                found = true;
                break;
            }
        }
    } else if(searchChoice == 2) {
        string searchName;
        cout << "Enter Product Name: ";
        getline(cin, searchName);
        
        cout << "\n--- Search Results ---" << endl;
        for(int i = 0; i < count; i++) {
            if(products[i].productName.find(searchName) != string::npos) {
                cout << "\nID: " << products[i].productId << endl;
                cout << "Name: " << products[i].productName << endl;
                cout << "Quantity: " << products[i].quantity << endl;
                cout << "Price: Rs. " << fixed << setprecision(2) << products[i].sellingPrice << endl;
                cout << string(40, '-') << endl;
                found = true;
            }
        }
    }
    
    if(!found) {
        cout << "\nProduct not found!" << endl;
    }
}

void updateProduct(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Product ID to update: ";
    cin >> id;
    cin.ignore();
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(products[i].productId == id) {
            cout << "\n--- Current Product Details ---" << endl;
            cout << "Name: " << products[i].productName << endl;
            cout << "Category: " << products[i].category << endl;
            cout << "Cost Price: Rs. " << products[i].costPrice << endl;
            cout << "Selling Price: Rs. " << products[i].sellingPrice << endl;
            
            cout << "\n--- Enter New Details ---" << endl;
            cout << "Enter Product Name: ";
            getline(cin, products[i].productName);
            
            cout << "Enter Category: ";
            getline(cin, products[i].category);
            
            cout << "Enter Cost Price: Rs. ";
            cin >> products[i].costPrice;
            
            cout << "Enter Selling Price: Rs. ";
            cin >> products[i].sellingPrice;
            
            cout << "Enter Reorder Level: ";
            cin >> products[i].reorderLevel;
            cin.ignore();
            
            cout << "Enter Supplier Name: ";
            getline(cin, products[i].supplier);
            
            cout << "\nProduct updated successfully!" << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nProduct with ID " << id << " not found!" << endl;
    }
}

void deleteProduct(Product products[], int &count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Product ID to delete: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(products[i].productId == id) {
            cout << "\nDeleting product: " << products[i].productName << endl;
            cout << "Are you sure? (y/n): ";
            char confirm;
            cin >> confirm;
            
            if(confirm == 'y' || confirm == 'Y') {
                for(int j = i; j < count - 1; j++) {
                    products[j] = products[j + 1];
                }
                count--;
                cout << "\nProduct deleted successfully!" << endl;
            }
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nProduct with ID " << id << " not found!" << endl;
    }
}

void restockProduct(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Product ID to restock: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(products[i].productId == id) {
            cout << "\nProduct: " << products[i].productName << endl;
            cout << "Current Quantity: " << products[i].quantity << endl;
            
            int addQty;
            cout << "Enter quantity to add: ";
            cin >> addQty;
            
            products[i].quantity += addQty;
            products[i].lastRestocked = getCurrentDate();
            
            cout << "\nRestocked successfully!" << endl;
            cout << "New Quantity: " << products[i].quantity << endl;
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nProduct with ID " << id << " not found!" << endl;
    }
}

void sellProduct(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    int id;
    cout << "\nEnter Product ID to sell: ";
    cin >> id;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(products[i].productId == id) {
            cout << "\nProduct: " << products[i].productName << endl;
            cout << "Available Quantity: " << products[i].quantity << endl;
            cout << "Price: Rs. " << fixed << setprecision(2) << products[i].sellingPrice << endl;
            
            int sellQty;
            cout << "Enter quantity to sell: ";
            cin >> sellQty;
            
            if(sellQty > products[i].quantity) {
                cout << "\nError: Insufficient stock!" << endl;
                return;
            }
            
            products[i].quantity -= sellQty;
            double totalAmount = sellQty * products[i].sellingPrice;
            
            // Save sale
            Sale sale;
            sale.productId = products[i].productId;
            sale.productName = products[i].productName;
            sale.quantity = sellQty;
            sale.totalAmount = totalAmount;
            sale.date = getCurrentDate();
            saveSale(sale);
            
            cout << "\n--- Sale Successful ---" << endl;
            cout << "Quantity Sold: " << sellQty << endl;
            cout << "Total Amount: Rs. " << fixed << setprecision(2) << totalAmount << endl;
            cout << "Remaining Stock: " << products[i].quantity << endl;
            
            if(products[i].quantity <= products[i].reorderLevel) {
                cout << "\n*** LOW STOCK ALERT! Please reorder. ***" << endl;
            }
            
            found = true;
            break;
        }
    }
    
    if(!found) {
        cout << "\nProduct with ID " << id << " not found!" << endl;
    }
}

void viewLowStockProducts(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    cout << "\n--- Low Stock Alert ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(25) << "Product Name" 
         << setw(10) << "Current"
         << setw(12) << "Reorder At"
         << setw(20) << "Supplier" << endl;
    cout << string(75, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(products[i].quantity <= products[i].reorderLevel) {
            cout << left << setw(8) << products[i].productId
                 << setw(25) << products[i].productName
                 << setw(10) << products[i].quantity
                 << setw(12) << products[i].reorderLevel
                 << setw(20) << products[i].supplier << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "All products are adequately stocked!" << endl;
    }
}

void viewProductsByCategory(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    string category;
    cout << "\nEnter Category: ";
    getline(cin, category);
    
    cout << "\n--- Products in Category: " << category << " ---" << endl;
    cout << left << setw(8) << "ID" 
         << setw(25) << "Product Name" 
         << setw(10) << "Qty"
         << setw(12) << "Price" << endl;
    cout << string(55, '-') << endl;
    
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(products[i].category == category) {
            cout << left << setw(8) << products[i].productId
                 << setw(25) << products[i].productName
                 << setw(10) << products[i].quantity
                 << "Rs." << fixed << setprecision(2) << products[i].sellingPrice << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No products found in this category!" << endl;
    }
}

void calculateInventoryValue(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    double totalCostValue = 0;
    double totalSellingValue = 0;
    
    for(int i = 0; i < count; i++) {
        totalCostValue += products[i].quantity * products[i].costPrice;
        totalSellingValue += products[i].quantity * products[i].sellingPrice;
    }
    
    double potentialProfit = totalSellingValue - totalCostValue;
    
    cout << "\n========================================" << endl;
    cout << "       INVENTORY VALUE ANALYSIS" << endl;
    cout << "========================================" << endl;
    cout << "Total Products: " << count << endl;
    cout << "Total Cost Value: Rs. " << fixed << setprecision(2) << totalCostValue << endl;
    cout << "Total Selling Value: Rs. " << fixed << setprecision(2) << totalSellingValue << endl;
    cout << "Potential Profit: Rs. " << fixed << setprecision(2) << potentialProfit << endl;
    cout << "========================================" << endl;
}

void viewProfitAnalysis(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    cout << "\n--- Profit Analysis ---" << endl;
    cout << left << setw(25) << "Product Name" 
         << setw(12) << "Cost"
         << setw(12) << "Sell Price"
         << setw(12) << "Profit"
         << setw(10) << "Margin %" << endl;
    cout << string(71, '-') << endl;
    
    for(int i = 0; i < count; i++) {
        double profit = products[i].sellingPrice - products[i].costPrice;
        double margin = (profit / products[i].costPrice) * 100;
        
        cout << left << setw(25) << products[i].productName
             << "Rs." << setw(8) << fixed << setprecision(2) << products[i].costPrice
             << "Rs." << setw(8) << fixed << setprecision(2) << products[i].sellingPrice
             << "Rs." << setw(8) << fixed << setprecision(2) << profit
             << setw(10) << fixed << setprecision(1) << margin << "%" << endl;
    }
}

void sortProducts(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    cout << "\n1. Sort by Name (A-Z)" << endl;
    cout << "2. Sort by Quantity (High to Low)" << endl;
    cout << "3. Sort by Price (Low to High)" << endl;
    cout << "Enter choice: ";
    int sortChoice;
    cin >> sortChoice;
    
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            bool swap = false;
            
            if(sortChoice == 1 && products[j].productName > products[j + 1].productName) {
                swap = true;
            } else if(sortChoice == 2 && products[j].quantity < products[j + 1].quantity) {
                swap = true;
            } else if(sortChoice == 3 && products[j].sellingPrice > products[j + 1].sellingPrice) {
                swap = true;
            }
            
            if(swap) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
    
    cout << "\nProducts sorted successfully!" << endl;
    viewAllProducts(products, count);
}

void viewSalesHistory() {
    ifstream inFile(SALES_FILE);
    
    if(!inFile) {
        cout << "\nNo sales history found!" << endl;
        return;
    }
    
    cout << "\n--- Sales History ---" << endl;
    cout << left << setw(8) << "ID"
         << setw(25) << "Product" 
         << setw(10) << "Qty"
         << setw(15) << "Amount"
         << setw(15) << "Date" << endl;
    cout << string(73, '-') << endl;
    
    string line;
    while(getline(inFile, line)) {
        cout << line << endl;
    }
    
    inFile.close();
}

void generateInventoryReport(Product products[], int count) {
    if(count == 0) {
        cout << "\nNo products in inventory!" << endl;
        return;
    }
    
    string filename = "inventory_report_" + getCurrentDate() + ".txt";
    ofstream outFile(filename);
    
    if(!outFile) {
        cout << "Error: Unable to create report file!" << endl;
        return;
    }
    
    outFile << "========================================" << endl;
    outFile << "       INVENTORY REPORT" << endl;
    outFile << "       Date: " << getCurrentDate() << endl;
    outFile << "========================================" << endl << endl;
    
    outFile << "Total Products: " << count << endl << endl;
    
    double totalValue = 0;
    
    for(int i = 0; i < count; i++) {
        outFile << "Product ID: " << products[i].productId << endl;
        outFile << "Name: " << products[i].productName << endl;
        outFile << "Category: " << products[i].category << endl;
        outFile << "Quantity: " << products[i].quantity << endl;
        outFile << "Cost Price: Rs. " << fixed << setprecision(2) << products[i].costPrice << endl;
        outFile << "Selling Price: Rs. " << fixed << setprecision(2) << products[i].sellingPrice << endl;
        outFile << "Total Value: Rs. " << fixed << setprecision(2) 
                << (products[i].quantity * products[i].costPrice) << endl;
        outFile << "----------------------------------------" << endl;
        
        totalValue += products[i].quantity * products[i].costPrice;
    }
    
    outFile << "\nTotal Inventory Value: Rs. " << fixed << setprecision(2) << totalValue << endl;
    outFile << "========================================" << endl;
    
    outFile.close();
    cout << "\nInventory report generated: " << filename << endl;
}

void saveToFile(Product products[], int count) {
    ofstream outFile(FILENAME);
    
    if(!outFile) {
        cout << "Error: Unable to open file for writing!" << endl;
        return;
    }
    
    outFile << count << endl;
    for(int i = 0; i < count; i++) {
        outFile << products[i].productId << endl;
        outFile << products[i].productName << endl;
        outFile << products[i].category << endl;
        outFile << products[i].quantity << endl;
        outFile << products[i].costPrice << endl;
        outFile << products[i].sellingPrice << endl;
        outFile << products[i].reorderLevel << endl;
        outFile << products[i].supplier << endl;
        outFile << products[i].lastRestocked << endl;
    }
    
    outFile.close();
}

void loadFromFile(Product products[], int &count) {
    ifstream inFile(FILENAME);
    
    if(!inFile) {
        count = 0;
        return;
    }
    
    inFile >> count;
    inFile.ignore();
    
    for(int i = 0; i < count; i++) {
        inFile >> products[i].productId;
        inFile.ignore();
        getline(inFile, products[i].productName);
        getline(inFile, products[i].category);
        inFile >> products[i].quantity;
        inFile >> products[i].costPrice;
        inFile >> products[i].sellingPrice;
        inFile >> products[i].reorderLevel;
        inFile.ignore();
        getline(inFile, products[i].supplier);
        getline(inFile, products[i].lastRestocked);
    }
    
    inFile.close();
}

void saveSale(Sale sale) {
    ofstream outFile(SALES_FILE, ios::app);
    
    if(!outFile) {
        return;
    }
    
    outFile << left << setw(8) << sale.productId
            << setw(25) << sale.productName
            << setw(10) << sale.quantity
            << "Rs." << setw(11) << fixed << setprecision(2) << sale.totalAmount
            << setw(15) << sale.date << endl;
    
    outFile.close();
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    string year = to_string(1900 + ltm->tm_year);
    string month = (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(1 + ltm->tm_mon);
    string day = (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday);
    
    return year + "-" + month + "-" + day;
}