// MEMBER 4: File handling, searching, sorting, and main menu
#include "inventory.h"

void saveProducts() {
    ofstream file("inventory.txt");
    for (int i = 0; i < productCount; i++) {
        file << products[i].id << " " << products[i].name << " "
             << products[i].quantity << " " << products[i].price << endl;
    }
    file.close();
}

void loadProducts() {
    ifstream file("inventory.txt");
    while (productCount < LIMIT &&
           file >> products[productCount].id
                >> products[productCount].name
                >> products[productCount].quantity
                >> products[productCount].price) {
        productCount++;
    }
    file.close();
}

void bubbleSortById() {
    for (int i = 0; i < productCount - 1; i++) {
        for (int j = 0; j < productCount - i - 1; j++) {
            if (products[j].id > products[j + 1].id) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
    cout << "Products sorted by ID.\n";
}

int binarySearchById(int id) {
    int low = 0, high = productCount - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (products[mid].id == id) return mid;
        if (products[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void searchProduct() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    int index = findProduct(id); // Linear search
    if (index == -1) cout << "Product not found by linear search.\n";
    else cout << "Linear search found: " << products[index].name << endl;

    bubbleSortById(); // Binary search needs sorted data
    index = binarySearchById(id);
    if (index == -1) cout << "Product not found by binary search.\n";
    else cout << "Binary search found: " << products[index].name << endl;
}

int main() {
    loadProducts();

    int choice;
    do {
        cout << "\n===== INVENTORY MANAGEMENT =====\n";
        cout << "1. Add product\n";
        cout << "2. Show products\n";
        cout << "3. Add stock / sell stock\n";
        cout << "4. Undo last stock change\n";
        cout << "5. Add pending request\n";
        cout << "6. Process next request\n";
        cout << "7. Search product\n";
        cout << "8. Sort products by ID\n";
        cout << "9. Show transaction history\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) addProduct();
        else if (choice == 2) showProducts();
        else if (choice == 3) changeStock();
        else if (choice == 4) undoLastChange();
        else if (choice == 5) {
            int id, amount;
            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter amount requested: ";
            cin >> amount;
            addRequest(id, amount);
        }
        else if (choice == 6) processRequest();
        else if (choice == 7) searchProduct();
        else if (choice == 8) {
            bubbleSortById();
            showProducts();
        }
        else if (choice == 9) showHistory();
        else if (choice == 0) cout << "Goodbye!\n";
        else cout << "Invalid choice.\n";
    } while (choice != 0);

    while (historyHead != NULL) {
        Transaction* temp = historyHead;
        historyHead = historyHead->next;
        delete temp;
    }
    return 0;
}
