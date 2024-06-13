#include <bits/stdc++.h>
#include <fstream>
#include "header.h"
using namespace std;

set<string> fooditem;

class MenuItem
{
protected:
    int item_id;
    string name;

public:
    MenuItem(int id, const string &itemName) : item_id(id), name(itemName) { fooditem.insert(itemName); }

    int getID() const
    {
        return item_id;
    }

    string getName() const
    {
        return name;
    }

    virtual ~MenuItem() {}
};

class Food : public MenuItem
{
public:
    Food(int id, const string &foodName) : MenuItem(id, foodName) {}
};

class Drink : public MenuItem
{
public:
    Drink(int id, const string &drinkName) : MenuItem(id, drinkName) {}
};

class Restaurant
{
private:
    int restaurant_id;
    string restaurant_name;
    string address;
    vector<pair<MenuItem *, double>> menu;
    double rating;

public:
    Restaurant(int id, const string &restaurantName, const string &addr, double r) : restaurant_id(id), restaurant_name(restaurantName), address(addr), rating(r) {}

    void addMenuItem(MenuItem *item, double price)
    {
        menu.push_back(make_pair(item, price));
    }

    void setRating(double r)
    {
        rating = r;
    }

    double getRating() const
    {
        return rating;
    }

    vector<pair<MenuItem *, double>> getMenu() const
    {
        return menu;
    }

    string getRestaurantName() const
    {
        return restaurant_name;
    }

    string getAddress() const
    {
        return address;
    }
};

class Cart
{
private:
    vector<pair<Restaurant, pair<Food *, int>>> items;
    float totalFare;
    int deliveryFee;

public:
    Cart() : totalFare(0.0) {}
    float gettotalfare() const
    {
        return totalFare + deliveryFee;
    }

    void addItem(const Restaurant &restaurant, Food *food, int quantity, double price)
    {
        bool found = false;

        for (auto &item : items)
        {
            if (item.second.first == food && item.first.getRestaurantName() == restaurant.getRestaurantName())
            {
                item.second.second += quantity;
                totalFare += price;
                found = true;
                break;
            }
        }

        if (!found)
        {
            items.push_back(make_pair(restaurant, make_pair(food, quantity)));
            totalFare += price;
        }
    }

    void removeItem(const string &itemName, int quantity)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (it->second.first->getName() == itemName)
            {
                if (quantity > it->second.second)
                {
                    cout << "Error: Quantity to remove exceeds available quantity." << endl;
                    return;
                }
                double price = quantity * getPriceForItem(*it);
                it->second.second -= quantity;
                if (it->second.second == 0)
                {
                    items.erase(it);
                }

                totalFare -= price;
                return;
            }
        }
        cout << "Error: Item not found in the cart." << endl;
    }

    double getPriceForItem(const pair<Restaurant, pair<Food *, int>> &item) const
    {
        for (const auto &menuItem : item.first.getMenu())
        {
            if (menuItem.first->getName() == item.second.first->getName())
            {
                return menuItem.second;
            }
        }
        return 0.0;
    }

    void calculateDeliveryFee()
    {

        int group1Fee = 5;
        int group2Fee = 10;
        int group3Fee = 15;

        if (totalFare < 30)
        {
            deliveryFee = group3Fee;
        }
        else if (totalFare < 50)
        {
            deliveryFee = group2Fee;
        }
        else
        {
            deliveryFee = group1Fee;
        }
    }

   void displayCart()
{
    ofstream file("user_data.txt", ios::app); // Open the file in append mode
    vector<pair<string, int>> v;
    if (items.empty())
    {
        cout << "Cart is empty." << endl;
    }
    else
    {
        cout << "Items in Cart:" << endl;
        for (const auto &item : items)
        {
            cout << "Restaurant: " << item.first.getRestaurantName() << endl;
            cout << "Food: " << item.second.first->getName() << endl;
            cout << "Quantity: " << item.second.second << endl;
            double price = getPriceForItem(item);
            cout << "Price: $" << price << endl;
            v.push_back({item.first.getRestaurantName(), static_cast<int>(price)});
            // Write item details to the file
            if (file.is_open())
            {
                file << "Restaurant: " << item.first.getRestaurantName() << endl;
                file << "Food: " << item.second.first->getName() << endl;
                file << "Quantity: " << item.second.second << endl;
                file << "Price: $" << price << endl << endl;
            }
            else
            {
                cout << "Error: Unable to open user_data.txt for writing." << endl;
                return;
            }
        }
        cout << "Total Food Fare: $" << totalFare << endl;
        calculateDeliveryFee();
        cout << "Delivery Fee: $" << deliveryFee << endl;
        double totalAmount = totalFare + deliveryFee;
        cout << "Total Amount to Pay: $" << totalAmount << endl;
    }
    file.close(); // Close the file after writing all items
}


    void removeItemsFromCart()
    {
        if (items.empty())
        {
            cout << "Cart is empty." << endl;
            return;
        }

        cout << "Items in Cart:" << endl;
        int index = 1;
        for (const auto &item : items)
        {
            cout << index++ << ". "
                 << "Restaurant: " << item.first.getRestaurantName() << ", Food: " << item.second.first->getName() << ", Quantity: " << item.second.second << endl;
        }

        int choice;
        cout << "Enter the index of the item you want to remove: ";
        cin >> choice;
        int n = items.size();
        if (choice >= 1 && choice <= n)
        {
            string itemName = items[choice - 1].second.first->getName();
            int quantity;
            cout << "Enter the quantity to remove: ";
            cin >> quantity;
            removeItem(itemName, quantity);
            cout << "Item(s) removed from the cart." << endl;
        }
        else
        {
            cout << "Invalid choice. Please enter a valid index." << endl;
        }

        displayCart();
    }
};

class PaymentMethod
{
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~PaymentMethod() {}
};

class PaytmPayment : public PaymentMethod
{
public:
    bool processPayment(double amount) override
    {
        std::cout << "Processing Paytm payment of Rs." << amount << std::endl;
        wait(3);
        return true;
    }

private:
    void wait(int seconds)
    {
#ifdef _WIN32
        Sleep(seconds * 1000);
#else
        sleep(seconds);
#endif
    }
};

class BharatPePayment : public PaymentMethod
{
public:
    bool processPayment(double amount) override
    {
        std::cout << "Processing Bharat Pe payment of Rs." << amount << std::endl;
        wait(4);
        return true;
    }

    bool verifyUPI(const std::string &upiID, const std::string &pin)
    {

        return !upiID.empty() && !pin.empty();
    }

private:
    void wait(int seconds)
    {
#ifdef _WIN32
        Sleep(seconds * 1000);
#else
        sleep(seconds);
#endif
    }
};

class Review
{
private:
    string userName;
    string foodName;
    string comment;
    string additionalComments;
    float overallRating;
    float foodQualityRating;
    float deliveryTimeRating;
    float packagingRating;
    float restaurantRating;
    float deliveryExecutiveRating;

public:
    Review(const string &user, const string &food)
        : userName(user), foodName(food), overallRating(0), foodQualityRating(0),
          deliveryTimeRating(0), packagingRating(0), restaurantRating(0),
          deliveryExecutiveRating(0), additionalComments("") {}

    void setOverallRating(int rating) { overallRating = rating; }
    void setFoodQualityRating(int rating) { foodQualityRating = rating; }
    void setDeliveryTimeRating(int rating) { deliveryTimeRating = rating; }
    void setPackagingRating(int rating) { packagingRating = rating; }
    void setRestaurantRating(int rating) { restaurantRating = rating; }
    void setDeliveryExecutiveRating(int rating) { deliveryExecutiveRating = rating; }
    void setAdditionalComments(const string &comments) { additionalComments = comments; }

    void display() const
    {
        cout << "========================================" << endl;
        cout << "           User Review Details          " << endl;
        cout << "========================================" << endl;
        cout << "User: " << userName << endl;
        cout << "Food Ordered: " << foodName << endl;
        cout << "----------------------------------------" << endl;
        cout << "Overall Rating:           ";
        cout << overallRating << endl;
        cout << "Food Quality Rating:      ";
        cout << foodQualityRating << endl;
        cout << "Delivery Time Rating:     ";
        cout << deliveryTimeRating << endl;
        cout << "Packaging Rating:         ";
        cout << packagingRating << endl;
        cout << "Restaurant Rating:        ";
        cout << restaurantRating << endl;
        ;
        cout << "Delivery Executive Rating:";
        cout << deliveryExecutiveRating << endl;
        cout << "Additional Comments: " << additionalComments << endl;
        cout << "========================================" << endl;
    }

    void printStars(float rating) const
    {
        int stars = static_cast<int>(rating);
        for (int i = 0; i < stars; ++i)
        {
            cout << "⭐ ";
        }
        cout << endl;
    }
};

int main()
{

    cout << "....................Welcome to TALAP......................." << endl;
    Sleep(3500);
    cout << "!!Your only source of tasty and divine food !!" << endl;

    FoodApp app;
    int ch;

    do
    {
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "3. Display Registered Usernames\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            bool checker;
            checker = app.login();
            if (checker == true)
            {
                ch = 4;
                break;
            }
            ch = 1;
            break;
        case 2:
            app.signUp();
            break;
        case 3:
            app.displayUsernames();
            break;
        case 4:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (ch != 4);

    Restaurant restaurant1(1, "Spicyleaf Family Dhaba", "Opp, Janapriya Apartments Rd,Kurnool, Andhra Pradesh 518002", 4.5);
    Restaurant restaurant2(2, "Madhulok restaurant and bar", "NH40, Kurnool, Andhra Pradesh 518002", 4.2);
    Restaurant restaurant3(3, "KGF-Kurnool Grand Food", "NH 44, Kurnool, Dinnedevarapadu, Andhra Pradesh 518002", 4.7);
    Restaurant restaurant4(4, "Rajavilas Restaurant", "R2HQ+G4Q, Raj Vihar Road, Kurnool, Andhra Pradesh 518001", 4.3);

    restaurant1.addMenuItem(new Food(1, "Biryani"), 10.99);
    restaurant1.addMenuItem(new Food(2, "Butter Chicken"), 12.99);
    restaurant1.addMenuItem(new Food(3, "Tandoori Chicken"), 14.99);

    restaurant2.addMenuItem(new Food(4, "Biryani"), 8.99);
    restaurant2.addMenuItem(new Food(5, "Palak Paneer"), 9.99);
    restaurant2.addMenuItem(new Food(6, "Chicken Tikka Masala"), 13.99);

    restaurant3.addMenuItem(new Food(7, "Chole Bhature"), 7.99);
    restaurant3.addMenuItem(new Food(8, "Rogan Josh"), 11.99);
    restaurant3.addMenuItem(new Food(9, "Masala Dosa"), 8.99);

    restaurant4.addMenuItem(new Food(10, "Idli Sambar"), 6.99);
    restaurant4.addMenuItem(new Food(11, "Vada Pav"), 5.99);
    restaurant4.addMenuItem(new Food(12, "Cold Drink"), 9.99);

    Cart cart;

    char choice = 'y';
    do
    {
        cout << "Choose a food item:" << endl;
        int index = 1;
        for (const auto &food : fooditem)
        {
            cout << "------------------------------------------------------------------" << endl;
            cout << index << ". " << food << endl;
            index++;
        }
        cout << endl;

        cout << "Enter 0 to search for a food item and show available food items in restaurants." << endl;
        int foodChoice;
        string search;
        cout << "Enter your choice (1-" << fooditem.size() << "): ";
        cin >> foodChoice;
        cout << endl;

        if (foodChoice == 0)
        {
            cout << "Enter the name of the food item you want to search: ";
            cin.ignore();
            getline(cin, search);
            cout << endl;
        }
        else
        {
            auto it = fooditem.begin();
            advance(it, foodChoice - 1);
            search = *it;
        }

        cout << "Available in the following restaurants:" << endl;
        cout << endl;
        vector<Restaurant> choices;
        for (const auto &restaurant : {restaurant1, restaurant2, restaurant3, restaurant4})
        {
            for (const auto &item : restaurant.getMenu())
            {
                if (item.first->getName() == search)
                {
                    cout << "Restaurant Name: " << restaurant.getRestaurantName() << endl;
                    cout << "Address: " << restaurant.getAddress() << endl;
                    choices.push_back(restaurant);
                    cout << "Item Name: " << item.first->getName() << endl;
                    cout << "Price: $" << item.second << endl;
                    cout << "Rating: " << restaurant.getRating() << endl;
                    cout << endl;
                }
            }
        }
        cout << endl;

        if (choices.size() == 1)
        {
            int quantity;
            cout << "Adding to cart automatically since there is only one restaurant offering this item." << endl;
            cout << "Restaurant Name: " << choices[0].getRestaurantName() << endl;
            cout << "Enter the Quantity:";
            cin >> quantity;
            double price = quantity * choices[0].getMenu()[0].second;
            cart.addItem(choices[0], dynamic_cast<Food *>(choices[0].getMenu()[0].first), quantity, price);
        }
        else
        {
            cout << "Choose the restaurant you want:";
            int choose;
            cin >> choose;
            int n = choices.size();
            if (choose <= n)
            {
                int quantity;
                cout << choices[choose - 1].getRestaurantName() << endl;
                cout << "Enter the Quantity:";
                cin >> quantity;
                double price = quantity * choices[choose - 1].getMenu()[0].second;
                cart.addItem(choices[choose - 1], dynamic_cast<Food *>(choices[choose - 1].getMenu()[0].first), quantity, price);
            }
        }

        cout << "Do you want to add more items to the cart? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "Cart Contents:" << endl;
    cart.displayCart();

    char removeChoice;
    do
    {
        cout << "Do you want to remove any items from the cart? (y/n): ";
        cin >> removeChoice;
        if (removeChoice == 'y' || removeChoice == 'Y')
        {
            cart.removeItemsFromCart();
        }
    } while (removeChoice == 'y' || removeChoice == 'Y');
    cart.displayCart();

    map<int, string> paymentOptions = {
        {0, "COD"},
        {1, "BharatPe"},
        {2, "Paytm"}};

    cout << "List of available payment options:\n";
    for (const auto &option : paymentOptions)
    {
        cout << option.first << ". " << option.second << std::endl;
    }
    cout << "Amount to pay:" << cart.gettotalfare() << endl;

    cout << "Select a payment method: ";
    int choi;
    cin >> choi;

    std::unique_ptr<PaymentMethod> paymentMethod;

    switch (choi)
    {
    case 0:
        cout << "CASH ON DELIVERY" << endl;
        break;
    case 1:
    {
        std::string upiID, pin;
        std::cout << "Enter your BharatPe UPI ID: ";
        std::cin >> upiID;
        if (upiID.find('@') != std::string::npos) {
        std::cout << "UPI ID is valid.\n";
    } else {
        std::cout << "Invalid UPI ID. It must contain the '@' symbol.\n";
    }
        std::cout << "Enter your BharatPe PIN: ";
        std::cin >> pin;
         if (pin.length() != 4)
        {
            cout << "invalid pin entry" << endl;
        }

        BharatPePayment bpPayment;
        if (bpPayment.verifyUPI(upiID, pin))
        {
            paymentMethod = std::make_unique<BharatPePayment>();
        }
        else
        {
            std::cout << "Invalid UPI ID or PIN. Payment method selection failed.\n";
            return 1;
        }
        break;
    }
    case 2:
    {
        std::string upiID, pin;
        std::cout << "Enter your Paytm UPI ID: ";
        std::cin >> upiID;
         if (upiID.find('@') != std::string::npos) {
        std::cout << "UPI ID is valid.\n";
    } else {
        std::cout << "Invalid UPI ID. It must contain the '@' symbol.\n";
        std::cout << "Enter your Paytm PIN: ";
        std::cin >> pin;
        if (pin.length() != 4)
        {
            cout << "invalid pin entry" << endl;
        }

        if (!upiID.empty() && !pin.empty())
        {
            paymentMethod = std::make_unique<PaytmPayment>();
        }
        else
        {
            std::cout << "Invalid UPI ID or PIN. Payment method selection failed.\n";
            return 1;
        }
        break;
    }
    }
    default:
    {
        std::cout << "Invalid choice. Exiting...\n";
        return 1;
    }
    bool success;
    if (paymentMethod)
    {
        double amount;
        std::cout << "Enter the amount: ";
        std::cin >> amount;
        if (amount < cart.gettotalfare())
        {
            cout << "wrong amount pay again or cancel" << endl;
            cin >> amount;
            if (amount < cart.gettotalfare())
            {
                cout << "order cancelled automatically!!" << endl;
                return 0;
            }
        }
        std::cout << "Processing payment. Please wait...\n";
        success = paymentMethod->processPayment(amount);
        std::cout << "Payment successful.\n";
    }
    if (success || choice == 0)
    {

        std::cout << "Your order is being checked..." << std::endl;
        Sleep(5000);
        std::cout << "Order verified." << std::endl;
        Sleep(5000);

        std::cout << "Ingredients at their best quality..." << std::endl;
        Sleep(5000);

        std::cout << "Your food is being packed..." << std::endl;
        Sleep(5000);

        std::cout << "Order picked up." << std::endl;
        Sleep(5000);

        std::cout << "Delivery boy: Rohit" << std::endl;
        std::cout << "Phone number: 8923651742" << std::endl;
        std::cout << "Rating: 4.6" << std::endl;
        std::cout << "Experience of: 100+ deliveries" << std::endl;

        Sleep(5000);
        std::cout << "Thank you for ordering!!" << endl;
    }
    if (choi == 0)
    {
        float amount;
        std::cout << "Enter the amount: ";
        std::cin >> amount;
        if (amount < cart.gettotalfare())
        {
            cout << "wrong amount pay again or cancel" << endl;
            cin >> amount;
            if (amount < cart.gettotalfare())
            {
                cout << "order cancelled automatically!!" << endl;
                return 0;
            }
        }
        std::cout << "Payment successful.\n";
    }

    string userName, foodName, additionalComments;
    float overallRating, foodQualityRating, deliveryTimeRating, packagingRating,
        restaurantRating, deliveryExecutiveRating;

    cout << endl;

    cout << "For your ordered food: ";
    getline(cin, foodName);
    Review userReview(userName, foodName);
    cout << endl;

    cout << "Enter your overall rating (1 to 5 stars): ";
    cin >> overallRating;
    if (overallRating > 5)
    {
        cout << "INVALID RATING" << endl;
    }
    else
    {
        userReview.setOverallRating(overallRating);
    }
    cout << endl;
    cout << "Enter your food quality rating (1 to 5 stars): ";
    cin >> foodQualityRating;
    if (foodQualityRating > 5)
    {
        cout << "INVALID RATING" << endl;
    }
    else
    {
        userReview.setFoodQualityRating(foodQualityRating);
    }
    cout << endl;
    cout << "Enter your delivery time rating (1 to 5 stars): ";
    cin >> deliveryTimeRating;

    if (deliveryTimeRating > 5)
    {
        cout << "INVALID RATING" << endl;
    }
    else
    {
        userReview.setDeliveryTimeRating(deliveryTimeRating);
    }
    cout << endl;
    cout << "Enter your packaging rating (1 to 5 stars): ";
    cin >> packagingRating;
    if (packagingRating > 5)
    {
        cout << "INVALID RATING" << endl;
    }
    else
    {
        userReview.setPackagingRating(packagingRating);
    }
    cout << endl;
    cout << "Enter your restaurant rating (1 to 5 stars): ";
    cin >> restaurantRating;

    if (restaurantRating > 5)
    {
        cout << "INVALID RATING" << endl;
    }
    else
    {
        userReview.setRestaurantRating(restaurantRating);
    }
    cout << endl;
    cout << "Enter your delivery executive rating (1 to 5 stars): ";
    cin >> deliveryExecutiveRating;
    if (deliveryExecutiveRating > 5)
    {
        cout << "INVALID RATING" << endl;
    }
    else
    {
        userReview.setDeliveryExecutiveRating(deliveryExecutiveRating);
    }

    cout << "Enter any additional comments (optional): ";
    cin.ignore();
    getline(cin, additionalComments);
    if (sizeof(additionalComments) <= 5)
    {
        cout << "INVALID comment" << endl;
    }
    else
    {
        userReview.setAdditionalComments(additionalComments);
    }
    cout << endl;
    cout << "\nThank you for your review!\n\n";
    userReview.display();

    return 0;
}
}
