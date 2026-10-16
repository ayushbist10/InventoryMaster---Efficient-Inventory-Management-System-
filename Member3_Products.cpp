// MEMBER 1: Product details, adding, displaying, and finding products
#include "inventory.h"

Product products[LIMIT];
int productCount = 0;

int findProduct(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) return i;
    }
    return -1;
}

void showProducts() {
    if (productCount == 0) {
        cout << "No products available.\n";
        return;
    }

    cout << "\nID\tName\tQuantity\tPrice\n";
    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << "\t" << products[i].name << "\t"
             << products[i].quantity << "\t\t" << products[i].price << endl;
    }
}

void addProduct() {
    if (productCount == LIMIT) {
        cout << "Inventory is full.\n";
        return;
    }

    Product p;
    cout << "Enter ID: ";
    cin >> p.id;

    if (findProduct(p.id) != -1) {
        cout << "That ID already exists.\n";
        return;
    }

    cout << "Enter one-word product name: ";
    cin >> p.name;
    cout << "Enter quantity: ";
    cin >> p.quantity;
    cout << "Enter price: ";
    cin >> p.price;

    if (p.quantity < 0 || p.price < 0) {
        cout << "Quantity and price cannot be negative.\n";
        return;
    }

    products[productCount] = p;
    productCount++;
    saveProducts();
    addHistory("Added product ID " + to_string(p.id));
    cout << "Product added.\n";
}
