#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int LIMIT = 100;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

struct Action {
    int productId;
    int oldQuantity;
};

struct Request {
    int productId;
    int amount;
};

struct Transaction {
    string message;
    Transaction* next;
};

extern Product products[LIMIT];
extern int productCount;

extern Action stackData[LIMIT];
extern int top;

extern Request queueData[LIMIT];
extern int frontIndex;
extern int rearIndex;

extern Transaction* historyHead;

int findProduct(int id);
void showProducts();
void addProduct();
void changeStock();

void pushAction(int id, int oldQty);
bool popAction(Action &a);
void undoLastChange();

void addRequest(int id, int amount);
void processRequest();

void addHistory(string message);
void showHistory();

void saveProducts();
void loadProducts();

void bubbleSortById();
int binarySearchById(int id);
void searchProduct();

#endif
