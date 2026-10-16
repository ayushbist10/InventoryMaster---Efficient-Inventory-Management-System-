// MEMBER 3: Queue (FIFO) and linked-list transaction history
#include "inventory.h"

Request queueData[LIMIT];
int frontIndex = 0;
int rearIndex = -1;

Transaction* historyHead = NULL;

void addRequest(int id, int amount) {
    if (rearIndex >= LIMIT - 1) {
        cout << "Queue is full.\n";
        return;
    }
    if (amount <= 0) {
        cout << "Amount must be positive.\n";
        return;
    }

    rearIndex++;
    queueData[rearIndex].productId = id;
    queueData[rearIndex].amount = amount;
    cout << "Request added to queue.\n";
}

void processRequest() {
    if (frontIndex > rearIndex) {
        cout << "No pending requests.\n";
        return;
    }

    Request r = queueData[frontIndex];
    frontIndex++;

    int index = findProduct(r.productId);
    if (index == -1) {
        cout << "Product not found.\n";
    } else if (products[index].quantity < r.amount) {
        cout << "Not enough stock.\n";
    } else {
        pushAction(r.productId, products[index].quantity);
        products[index].quantity -= r.amount;
        saveProducts();
        addHistory("Queue request processed for product ID " + to_string(r.productId));
        cout << "Request completed.\n";
    }
}

void addHistory(string message) {
    Transaction* newNode = new Transaction;
    newNode->message = message;
    newNode->next = NULL;

    if (historyHead == NULL) {
        historyHead = newNode;
    } else {
        Transaction* temp = historyHead;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }

    ofstream file("transactions.txt", ios::app);
    file << message << endl;
    file.close();
}

void showHistory() {
    Transaction* temp = historyHead;
    if (temp == NULL) cout << "No transactions this session.\n";

    while (temp != NULL) {
        cout << temp->message << endl;
        temp = temp->next;
    }
}
