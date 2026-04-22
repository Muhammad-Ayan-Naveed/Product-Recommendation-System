#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Stack {
private:
    string arr[20];
    int currentSize;

public:
    Stack() {
        currentSize = 0;
    }

    
        bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == 20;
    }

    void push(string value) {
        if (isFull()) {
            cout << "Stack is Full" << endl;
        }
        else {
            arr[currentSize] = value;
            currentSize++;
        }
    }

    string pop() {
        if (isEmpty()) {
            cout << "Stack is Empty; returning NULL" << endl;
            return "";
        }
        else {
            currentSize--;
            return arr[currentSize];
        }
    }
    

};

class User {
public:
    int UserID;
};

class Product {
public:
    int ProductID;
    string name;
    string category;
};

class UserHistory {
public:
    int purchasedProducts[20];
    int searchedProducts[20];
    string searchedCategories[20];

    
        int purchaseCount;
    int searchProductCount;
    int searchCount;

    UserHistory() {
        purchaseCount = 0;
        searchProductCount = 0;
        searchCount = 0;
    }

    void addPurchase(int productID) {
        if (purchaseCount < 20) {
            purchasedProducts[purchaseCount] = productID;
            purchaseCount++;
        }
    }

    void addSearchedProduct(int productID) {
        if (searchProductCount < 20) {
            searchedProducts[searchProductCount] = productID;
            searchProductCount++;
        }
    }

    void addSearchCategory(string category) {
        if (searchCount < 20) {
            searchedCategories[searchCount] = category;
            searchCount++;
        }
    }
    

};

// Each DecisionTree uses a different strategy (weight bias) to evaluate user preferences.
// Tree 0: Purchase-biased  -> counts purchases twice, searches once
// Tree 1: Search-biased    -> counts searches twice, purchases once
// Tree 2: Balanced         -> counts purchases and searches equally
class DecisionTree {
public:
    int treeID; // 0 = purchase-biased, 1 = search-biased, 2 = balanced

    
        DecisionTree() {
        treeID = 0;
    }

    string evaluate(UserHistory history, Product products[], int productSize) {
        int audio = 0;
        int accessories = 0;
        int electronics = 0;

        // Weight multipliers differ per tree to create genuine diversity
        int purchaseWeight, searchWeight;

        if (treeID == 0) {
            // Tree 0: Trusts purchase history more (user committed to buying)
            purchaseWeight = 2;
            searchWeight = 1;
        }
        else if (treeID == 1) {
            // Tree 1: Trusts search history more (reflects current interest)
            purchaseWeight = 1;
            searchWeight = 2;
        }
        else {
            // Tree 2: Balanced — treats both signals equally
            purchaseWeight = 1;
            searchWeight = 1;
        }

        // Score categories based on search history
        for (int i = 0; i < history.searchCount; i++) {
            string cat = history.searchedCategories[i];
            if (cat == "Audio")            audio += searchWeight;
            else if (cat == "Accessories") accessories += searchWeight;
            else if (cat == "Electronics") electronics += searchWeight;
        }

        // Score categories based on purchase history
        for (int i = 0; i < history.purchaseCount; i++) {
            int pid = history.purchasedProducts[i];
            string cat = "";

            for (int j = 0; j < productSize; j++) {
                if (products[j].ProductID == pid) {
                    cat = products[j].category;
                    break;
                }
            }

            if (cat == "Audio")            audio += purchaseWeight;
            else if (cat == "Accessories") accessories += purchaseWeight;
            else if (cat == "Electronics") electronics += purchaseWeight;
        }

        // Return the highest-scoring category
        if (audio >= accessories && audio >= electronics)           return "Audio";
        else if (accessories >= audio && accessories >= electronics) return "Accessories";
        else                                                         return "Electronics";
    }
    

};

class RandomForest {
public:
    DecisionTree trees[3];

    
        RandomForest() {
        // Assign each tree a different strategy ID
        trees[0].treeID = 0; // Purchase-biased
        trees[1].treeID = 1; // Search-biased
        trees[2].treeID = 2; // Balanced
    }

    // Each tree votes independently; majority wins
    string predict(UserHistory history, Product products[], int productSize) {
        int audio = 0;
        int accessories = 0;
        int electronics = 0;

        for (int i = 0; i < 3; i++) {
            string result = trees[i].evaluate(history, products, productSize);

            cout << "Tree " << i << " (";
            if (i == 0) cout << "Purchase-biased";
            else if (i == 1) cout << "Search-biased";
            else cout << "Balanced";
            cout << ") voted: " << result << endl;

            if (result == "Audio")            audio++;
            else if (result == "Accessories") accessories++;
            else                              electronics++;
        }

        // Majority vote decides final category
        if (audio >= accessories && audio >= electronics)           return "Audio";
        else if (accessories >= audio && accessories >= electronics) return "Accessories";
        else                                                         return "Electronics";
    }
    

};

class RecommendationEngine {
public:
    RandomForest forest;
    Stack s;

    
        void generateRecommendation(User user, UserHistory history, Product products[], int productSize) {
        string category = forest.predict(history, products, productSize);

        cout << "\nMajority voted category: " << category << endl;

        // Push all matching products onto the stack
        for (int i = 0; i < productSize; i++) {
            if (products[i].category == category) {
                s.push(products[i].name);
            }
        }

        cout << "\nRecommended Products for User " << user.UserID << ":\n";

        // Pop top 3 recommendations
        for (int i = 0; i < 3 && !s.isEmpty(); i++) {
            cout << i + 1 << ". " << s.pop() << endl;
        }
    }
    

};

int main() {
    // Expanded product catalog: 15 products across 3 categories
    Product products[15] = {
    {1,  "Wireless Headphones","Audio"},
    {2,  "Bluetooth Speaker",      "Audio"},
    {3,  "Noise Cancelling Earbuds","Audio"},
    {4,  "Studio Monitor Speaker", "Audio"},
    {5,  "Portable DAC Amplifier", "Audio"},
    {6,  "Laptop Stand",           "Accessories"},
    {7,  "Mobile Charger",         "Accessories"},
    {8,  "USB - C Hub",              "Accessories"},
    {9,  "Mechanical Keyboard",    "Accessories"},
    {10, "Ergonomic Mouse",        "Accessories"},
    {11, "Smart Watch",            "Electronics"},
    {12, "Tablet",                 "Electronics"},
    {13, "Action Camera",          "Electronics"},
    {14, "Smart Home Hub",         "Electronics"},
    {15, "E - Reader",               "Electronics"}
    };

    
        User user;
    cout << "Enter User ID: ";
    cin >> user.UserID;

    UserHistory history;

    ifstream file("history.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open history.txt\n";
        return 1;
    }

    int fileUserID;
    int ProductID;
    string Category;
    string Action;
    bool foundUser = false;

    while (file >> fileUserID >> Category >> ProductID >> Action) {
        if (fileUserID == user.UserID) {
            foundUser = true;

            if (Action == "Search") {
                history.addSearchCategory(Category);
                history.addSearchedProduct(ProductID);
            }
            else if (Action == "Purchase") {
                history.addPurchase(ProductID);
            }
        }
    }

    file.close();

    if (!foundUser) {
        cout << "User not found in history.\n";
        return 0;
    }

    cout << "\n--- Decision Tree Voting ---\n";
    RecommendationEngine engine;
    engine.generateRecommendation(user, history, products, 15);

    return 0;
    

}