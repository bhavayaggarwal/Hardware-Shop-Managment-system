#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Product {
public:
    Product(const string& name, double price, int quantity)
        : name(name), price(price), quantity(quantity) {}

    void display() const {
        cout << "Product: " << name << "\n";
        cout << "Price: Rs. " << price << "\n";
        cout << "Quantity: " << quantity << "\n";
    }

    string toString() const {
        return name + "," + to_string(price) + "," + to_string(quantity);
    }

    bool matchesName(const string& searchTerm) const {
        return name == searchTerm;
    }

    void reduceQuantity(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
        }
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

private:
    string name;
    double price;
    int quantity;
};

class HardwareShop {
public:
    void addProduct(const string& name, int price, int quantity) {
        products.push_back(Product(name, price, quantity));
        cout << "Product added.\n";
    }

    void displayProducts() const {
        cout << "Inventory:\n";
        for (const Product& product : products) {
            product.display();
            cout << "-------------\n";
        }
    }

    void searchProduct(const string& searchTerm) const {
        bool found = false;
        cout << "Search Results:\n";
        for (const Product& product : products) {
            if (product.matchesName(searchTerm)) {
                product.display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Product not found.\n";
        }
    }

    void sellProduct(const string& productName, int quantity) {
        for (Product& product : products) {
            if (product.getName() == productName) {
                if (product.getQuantity() >= quantity) {
                    product.reduceQuantity(quantity);
                    cout << "Sale completed.\n";
                } else {
                    cout << "Insufficient quantity in stock.\n";
                }
                return;
            }
        }
        cout << "Product not found.\n";
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const Product& product : products) {
                outFile << product.toString() << "\n";
            }
            outFile.close();
            cout << "Data saved to file.\n";
        } else {
            cout << "Error: Unable to save data to file.\n";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            products.clear();
            string line;
            while (getline(inFile, line)) {
                size_t comma1 = line.find(',');
                size_t comma2 = line.rfind(',');
                if (comma1 != string::npos && comma2 != string::npos) {
                    string name = line.substr(0, comma1);
                    double price = stod(line.substr(comma1 + 1, comma2 - comma1 - 1));
                    int quantity = stoi(line.substr(comma2 + 1));
                    products.push_back(Product(name, price, quantity));
                }
            }
            inFile.close();
            cout << "Data loaded from file.\n";
        } else {
            cout << "Error: Unable to load data from file.\n";
        }
    }

private:
    vector<Product> products;
};

int main() {
    HardwareShop shop;
    shop.loadFromFile("inventory.txt");

    int choice;
    string productName;
    int quantity;

    do {
        cout << "\nMenu:\n";
        cout << "1. Display Products\n";
        cout << "2. Search Product\n";
        cout << "3. Sell Product\n";
        cout << "4. Save Data to File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                shop.displayProducts();
                break;
            case 2:
                cout << "Enter product name to search: ";
                cin.ignore();
                getline(cin, productName);
                shop.searchProduct(productName);
                break;
            case 3:
                cout << "Enter product name to sell: ";
                cin.ignore();
                getline(cin, productName);
                cout << "Enter quantity to sell: ";
                cin >> quantity;
                shop.sellProduct(productName, quantity);
                break;
            case 4:
                shop.saveToFile("inventory.txt");
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
