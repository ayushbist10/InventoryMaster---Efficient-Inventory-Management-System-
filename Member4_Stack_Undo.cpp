// MEMBER 2: Stack and undo feature (LIFO)
#include "inventory.h"

Action stackData[LIMIT];
int top = -1;

void pushAction(int id, int oldQty) {
    if (top < LIMIT - 1) {
        top++;
        stackData[top].productId = id;
        stackData[top].oldQuantity = oldQty;
    }
}

bool popAction(Action &a) {
    if (top == -1) return false;
    a = stackData[top];
    top--;
    return true;
}

void changeStock() {
    int id, amount;
    cout << "Enter product ID: ";
    cin >> id;

    int index = findProduct(id);
    if (index == -1) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter amount to add (positive) or sell (negative): ";
    cin >> amount;

    if (products[index].quantity + amount < 0) {
        cout << "Not enough stock.\n";
        return;
    }

    pushAction(id, products[index].quantity);
    products[index].quantity += amount;
    saveProducts();
    addHistory("Stock changed for product ID " + to_string(id));
    cout << "Stock updated.\n";
}

void undoLastChange() {
    Action a;
    if (!popAction(a)) {
        cout << "Nothing to undo.\n";
        return;
    }

    int index = findProduct(a.productId);
    if (index != -1) {
        products[index].quantity = a.oldQuantity;
        saveProducts();
        addHistory("Undo stock change for product ID " + to_string(a.productId));
        cout << "Last stock change undone.\n";
    }
}
