#include <iostream>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <stdexcept>
#include <fstream>

void mysetcolor(const int& colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

//void LogError(const string& errorMessage) {
//	ofstream errorLogFile("errorlog.txt", ios::app);
//	if (errorLogFile.is_open()) {
//		errorLogFile << "Error: " << errorMessage << endl;
//		errorLogFile.close();
//	}
//	else {
//		cout << "Error: Unable to open errorlog.txt for writing." << endl;
//	}
//}

using namespace std;

class Meal {
	string name;
	double price;
	double rating;
public:
	Meal() : name(""), price(0.0), rating(0.0) {};

	Meal(const string& name, double price, double rating)
		:name(name), price(price), rating(rating) {};

	void SetName(const string& name) {
		this->name = name;
	}

	void SetPrice(double price) {
		this->price = price;
	}

	void SetRating(double rating) {
		this->rating;
	}

	void UpdateRating(double newRating) {
		rating = max(1.0, min(5.0, newRating));
	}

	string GetName()const {
		return name;
	}

	double GetPrice()const {
		return price;
	}

	double GetRating()const {
		return rating;
	}
};


class Ingridients {
	string name;
	double price;
	int quantity;
public:
	Ingridients() :name(""), price(0.0), quantity(0) {};

	Ingridients(const string& name, double price, int quantity)
		:name(name), price(price), quantity(quantity) {};

	void SetQuantity(int quantity) {
		this->quantity = quantity;
	}

	string GetName()const {
		return name;
	}

	double GetPrice()const {
		return price;
	}

	int GetQuantity()const {
		return quantity;
	}
};


class Table {
	string table_no;
	Meal** order;
	string messageToKitchen;
	int orderCapacity;
	int orderCount;
public:
	Table() : table_no(""), messageToKitchen(""), orderCapacity(30), orderCount(0) {
		order = new Meal * [orderCapacity];
		for (size_t i = 0; i < orderCapacity; i++)
		{
			order[i] = nullptr;
		}
	}

	void PlaceOrder(const Meal* meal) {
		if (orderCount < orderCapacity) {
			order[orderCount] = const_cast<Meal*>(meal);
			orderCount++;
		}
		else {
			cout << "Order capacity is Full. Cannot add more meals to the order" << endl;
		}
	}

	void DisplayOrder()const {
		cout << "Table " << table_no << " Order : " << endl;
		for (size_t i = 0; i < orderCount; i++)
		{
			if (order[i] != nullptr) {
				cout << order[i]->GetName() << " - $" << order[i]->GetPrice() << endl;
			}
		}
	}

	double CalculateTotal()const {
		double total = 0.0;
		for (size_t i = 0; i < orderCount; i++)
		{
			if (order[i] != nullptr) {
				total += order[i]->GetPrice();
			}
		}
		return total;
	}

	void SetTableNo(const string& table_no) {
		this->table_no = table_no;
	}

	void SetMessageToKitchen(const string& messageToKitchen) {
		this->messageToKitchen = messageToKitchen;
	}

	void SetOrderCapacity(int orderCapacity) {
		this->orderCapacity = orderCapacity;
	}

	void SetOrderCount(int orderCount) {
		this->orderCount = orderCount;
	}

	string GetTableNo()const {
		return table_no;
	}

	string GetMessageToKitchen()const {
		return messageToKitchen;
	}

	int GetOrderCapacity()const {
		return orderCapacity;
	}

	int GetOrderCount()const {
		return orderCount;
	}

	~Table() {
		for (size_t i = 0; i < orderCount; i++)
		{
			delete order[i];
		}
		delete[]order;
	}
};


const int MAX_INGRIDIENTS = 50;
class Stock {
	Ingridients ingridients[MAX_INGRIDIENTS];
	int ingridientCount;
public:
	Stock() : ingridientCount(0) {};

	Stock(int ingridientCount) {
		SetIngridientCount(ingridientCount);
	}

	void SetIngridientCount(int ingridientCount) {
		if (ingridientCount >= 0 && ingridientCount <= MAX_INGRIDIENTS) {
			this->ingridientCount = ingridientCount;
		}
		else {
			cout << "Invalid ingridient count.Setting to 0" << endl;
			this->ingridientCount = 0;
		}
	}

	int GetIngridientCount() const {
		return ingridientCount;
	}

	void AllViewIngredients() const {
		mysetcolor(3.0);
		cout << "\t= > = > Current Stock < = < =" << endl;
		mysetcolor(7.0);
		for (size_t i = 0; i < ingridientCount; i++)
		{
			cout << ingridients[i].GetName() << " - price $ " << ingridients[i].GetPrice() << " - quantity " << ingridients[i].GetQuantity() << endl;
		}

	}

	void AddNewIngredient(const string& name, double price, int quantity) {
		if (ingridientCount < MAX_INGRIDIENTS) {
			Ingridients newIngredient(name, price, quantity);
			ingridients[ingridientCount] = newIngredient;
			ingridientCount++;
			cout << "Added new ingredient : " << name << endl;
		}
		else {
			cout << "Stock is full.Cannot add more ingredients" << endl;
		}

	}

	void DeleteIngredient(const string& name) {
		int index = -1;
		for (size_t i = 0; i < ingridientCount; i++) {
			if (ingridients[i].GetName() == name) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			for (size_t i = index; i < ingridientCount - 1; i++) {
				ingridients[i] = ingridients[i + 1];
			}
			ingridientCount--;
			cout << "Deleted ingredient : " << name << endl;
		}
		else {
			cout << "Ingredient '" << name << "' not fount in the stock" << endl;
		}

	}

	void IncreaseIngredient(const string& name, int quantity) {
		for (size_t i = 0; i < ingridientCount; i++)
		{
			if (ingridients[i].GetName() == name) {
				ingridients[i].SetQuantity(ingridients[i].GetQuantity() + quantity);
				cout << "Increased " << name << " by " << quantity << " units" << endl;
				return;
			}
		}
		cout << "Ingredient '" << name << "' not found in the stock" << endl;

	}

	void DecreaseIngredient(const string& name, int quantity) {
		for (size_t i = 0; i < ingridientCount; i++)
		{
			if (ingridients[i].GetName() == name) {
				if (ingridients[i].GetQuantity() >= quantity) {
					ingridients[i].SetQuantity(ingridients[i].GetQuantity() - quantity);
					cout << "Decreased " << name << " by " << quantity << " units " << endl;
					return;
				}
			}
		}
		cout << "Ingredient '" << name << "' not found in the stock" << endl;

	}
};


class Kitchen {
	Meal restaurantMenu[100];
	int numMeals = 0;

	Table allOrders[100];
	int numOrders = 0;
public:
	Kitchen() {};

	void SetNumMeals(int numMeals) {
		this->numMeals = numMeals;
	}

	int GetNumMeals()const {
		return numMeals;
	}

	void SetNumOrders(int numOrders) {
		this->numOrders = numOrders;
	}

	int GetNumOrders()const {
		return numOrders;
	}

	const Meal* GetRestaurantMenu() const {
		return restaurantMenu;
	}

	void AllViewOrder() {
		cout << "All Orders : " << endl;
		for (size_t i = 0; i < numOrders; i++)
		{
			allOrders[i].DisplayOrder();
		}
	}

	void ViewAllOrders() {
		AllViewOrder();
		mysetcolor(3.0);
		cout << "\t= > = > All Orders < = < =" << endl;
		mysetcolor(7.0);
		for (size_t i = 0; i < numOrders; i++) {
			cout << "Order for Table " << allOrders[i].GetTableNo() << endl;
			allOrders[i].DisplayOrder();
			cout << "Message to Kitchen: " << allOrders[i].GetMessageToKitchen() << endl;
			cout << "Total: $" << allOrders[i].CalculateTotal() << endl;
			cout << "------------------------" << endl;
		}
	}

	void AdminManageOrders() {
		int orderIndex;
		while (true) {
			ViewAllOrders();
			cout << "Enter the index of the order you want to manage (0 to go back): ";
			cin >> orderIndex;
			if (orderIndex == 0) {
				break;
			}
			else if (orderIndex >= 1 && orderIndex <= numOrders) {
				cout << "Do you want to accept this order? (yes/no): ";
				string response;
				cin >> response;
				bool acceptOrder = (response == "yes");

				string reason;
				if (!acceptOrder) {
					cout << "Enter the reason for rejecting the order: ";
					cin.ignore();
					getline(cin, reason);
				}

				allOrders[orderIndex - 1].SetMessageToKitchen("Admin's decision: " + (acceptOrder ? "Accepted" : "Rejected - " + reason));
				cout << "Order status updated." << endl;
			}
			else {
				cout << "Invalid index. Please enter a valid index." << endl;
			}
		}
	}

	void AcceptOrCancelOrder(Table* table, bool accept, const string& reason) {
		if (accept) {
			table->SetMessageToKitchen("Order accepted");
		}
		else {
			table->SetMessageToKitchen("Order cancelled.Reason : " + reason);
		}
	}

	void AllViewRestaurant() {
		mysetcolor(3.0);
		cout << "\t= > = > Restaurant Menu < = < =" << endl;
		mysetcolor(7.0);
		for (size_t i = 0; i < numMeals; i++)
		{
			cout << restaurantMenu[i].GetName() << " - price $" << restaurantMenu[i].GetPrice() << " - rating " << restaurantMenu[i].GetRating() << endl;
		}
	}

	void AddNewMeal(const string& name, double price, double rating) {
		if (numMeals < 100) {
			Meal newMeal(name, price, rating);
			restaurantMenu[numMeals] = newMeal;
			numMeals++;
			cout << "Added new meal : " << name << endl;
		}
		else {
			cout << "Menu is full.Cannot add more meals" << endl;
		}
	}

	void DeleteMeal(const string& name) {
		int index = -1;
		for (size_t i = 0; i < numMeals; i++)
		{
			if (restaurantMenu[i].GetName() == name) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			for (size_t i = index; i < numMeals - 1; i++)
			{
				restaurantMenu[i] = restaurantMenu[i + 1];
			}
			numMeals--;
			cout << "Deleted meal : " << name << endl;
		}
		else {
			cout << "Meal '" << name << "' not found in the menu" << endl;
		}
	}

	void UpdateMeal(const string& name, double price, double rating) {
		for (size_t i = 0; i < numMeals; i++)
		{
			if (restaurantMenu[i].GetName() == name) {
				restaurantMenu[i].SetPrice(price);
				restaurantMenu[i].SetRating(rating);
				cout << "Updated meal : " << name << endl;
				return;
			}
		}
		cout << "Meal '" << name << "' not found in the menu" << endl;
	}

	void ViewStock(Stock* stock) {
		try {
			stock->AllViewIngredients();
		}
		catch (const std::exception& e) {
			cout << "Exception caught: " << e.what() << std::endl;
		}
	}
};


class Client {
	string table_no;
	const Meal* menu;
	int numMeals;
public:
	Client() : menu(nullptr), numMeals(0) {};
	Client(const string& table_no, const Meal* menu, int numMeals)
		: table_no(table_no), menu(menu), numMeals(numMeals) {};

	void SetTableNo(const string& table_no) {
		this->table_no = table_no;
	}

	string GetTableNo()const {
		return table_no;
	}

	void ViewAllIngredients(const Stock* stock) {
		stock->AllViewIngredients();
	}

	void ViewAllMeals(const Meal* menu, int numMeals) {
		mysetcolor(3.0);
		cout << "\t\t= > = > Restaurant Menu < = < =" << endl;
		mysetcolor(7.0);
		for (size_t i = 0; i < numMeals; i++)
		{
			cout << menu[i].GetName() << " - $" << menu[i].GetPrice() << endl;
		}
	}

	void ViewMealDetails(const Meal* menu, int numMeals, const string& mealName) {
		cout << "Meal Details for '" << mealName << "':" << endl;
		for (size_t i = 0; i < numMeals; i++) {
			if (menu[i].GetName() == mealName) {
				cout << "Meal Name: " << menu[i].GetName() << endl;
				cout << "Price: $" << menu[i].GetPrice() << endl;
				cout << "Rating: " << menu[i].GetRating() << endl;
				return;
			}
		}
		cout << "Meal '" << mealName << "' not found in the menu" << endl;
	}

	void PlaceOrder(Kitchen* kitchen, Table* table, const Meal* menu, int numMeals,
		const string& mealName, double newPrice, double newRating) {

		bool found = false;
		for (size_t i = 0; i < numMeals; i++) {
			if (menu[i].GetName() == mealName) {
				found = true;
				cout << "Meal Name: " << menu[i].GetName() << endl;
				cout << "Price: $" << menu[i].GetPrice() << endl;
				cout << "Rating: " << menu[i].GetRating() << endl;
				double price = menu[i].GetPrice();
				cout << "Enter the amount to pay: ";
				double amountPaid;
				cin >> amountPaid;
				if (amountPaid >= price) {
					table->PlaceOrder(&menu[i]);
					cout << "Order placed for " << mealName << endl;
					double change = amountPaid - price;
					cout << "Change: $" << change << endl;
				}
				else {
					throw runtime_error("Insufficient amount to place the order.");
				}
				break;
			}
		}

		if (!found) {
			throw runtime_error("Meal '" + mealName + "' not found in the menu. Cannot place order.");
		}
	}


	void SearchMealByName(const Meal* menu, int numMeals, const string& mealName) {
		cout << "Search Result" << endl;
		for (size_t i = 0; i < numMeals; i++) {
			if (menu[i].GetName() == mealName) {
				cout << menu[i].GetName() << " - $" << menu[i].GetPrice() << " - Rating " << menu[i].GetRating() << endl;
				return;
			}
		}
		cout << "Meal '" << mealName << "' not found in the menu" << endl;
	}

	void InformKitchen(Kitchen* kitchen, Table* table, bool acceptOrder, const string& reason) {
		if (acceptOrder) {
			kitchen->AcceptOrCancelOrder(table, true, "");
			cout << "Order accepted" << endl;
		}
		else {
			kitchen->AcceptOrCancelOrder(table, false, reason);
			cout << "Order cancelled.Reason : " << reason << endl;
		}

	}
};


class Admin {
	string username;
	string password;
public:
	Admin() {};

	Admin(const string& username, const string& password)
		: username(username), password(password) {};

	void SetUsername(const string& username) {
		this->username = username;
	}

	void SetPassword(const string& password) {
		this->password = password;
	}

	string GetUsername() const {
		return username;
	}

	string GetPassword() const {
		return password;
	}

	bool Login(const string& enteredUsername, const string& enteredPassword) {
		return (enteredUsername == username && enteredPassword == password);
	}

	void ViewRestaurantMenu(const Meal* menu, int numMeals) {
		mysetcolor(3.0);
		cout << "\tRestaurant Menu" << endl;
		mysetcolor(7.0);
		for (size_t i = 0; i < numMeals; i++) {
			cout << menu[i].GetName() << " - $" << menu[i].GetPrice() << endl;
		}
	}

	void ShowMenu() {
		cout << "\t\t= > = > Welcome To Admin < = < =" << username << "!" << endl;
		cout << "1. Kitchen" << endl;
		cout << "2. Stock" << endl;
		cout << "3. Back" << endl;
		cout << "Select an option : " << endl;
	}
};


class Restaurant {
	string name;
	string address;
	string city;
	double budget;
	Admin admin;

public:
	Restaurant() : budget(0.0) {};

	Restaurant(const string& name, const string& address, const string& city,
		double budget, const Admin& admin)
		: name(name), address(address), city(city), budget(budget), admin(admin) {};

	void SetName(const string& name) {
		this->name = name;
	}

	string GetName() const {
		return name;
	}

	void SetAddress(const string& address) {
		this->address = address;
	}

	string GetAddress() const {
		return address;
	}

	void SetCity(const string& city) {
		this->city = city;
	}

	string GetCity() const {
		return city;
	}

	void SetBudget(double budget) {
		this->budget = budget;
	}

	double GetBudget() const {
		return budget;
	}

	void SetAdmin(const Admin& admin) {
		this->admin = admin;
	}

	Admin GetAdmin() const {
		return admin;
	}

	void UpdateBudget(double amount) {
		budget += amount;
	}

	bool HasSufficientBudget(double amount) const {
		return budget >= amount;
	}

	void DeductOrderCost(double amount) {
		if (HasSufficientBudget(amount)) {
			budget -= amount;
		}
		else {
			throw runtime_error("Insufficient budget to deduct order cost.");
		}
	}
};

void DisplayAdminMenu() {
	mysetcolor(3.0);
	cout << "\t\t= > = > Welcome Admin < = < =" << endl;
	mysetcolor(7.0);
	cout << "\tKitchen [1] \t\t\t  Stock [2] " << endl;
	cout << "\t\t\t  Back  [3]" << endl;
}

void DisplayKitchenMenyu() {
	mysetcolor(3.0);
	cout << "\t= > = > Kitchen Menu < = < =" << endl;
	mysetcolor(7.0);
	cout << "View Restaurant Menu    [1] " << endl;
	cout << "Add New Meal            [2] " << endl;
	cout << "Delete Meal             [3] " << endl;
	cout << "Update Meal             [4] " << endl;
	cout << "View All Orders         [5] " << endl;
	cout << "Back                    [6] " << endl;
}

void DisplayStockMenyu() {
	mysetcolor(3.0);
	cout << "\t= > = > Stock Menu < = < =" << endl;
	mysetcolor(7.0);
	cout << "View All Ingredients [1] " << endl;
	cout << "Add New Ingredient   [2] " << endl;
	cout << "Delete Ingredient    [3] " << endl;
	cout << "Increase Ingredient  [4] " << endl;
	cout << "Decrease Ingredient  [5] " << endl;
	cout << "Back                 [6] " << endl;
}

void DisplayClientMenu() {
	mysetcolor(3.0);
	cout << "\t\t= > = > Welcome Client < = < =" << endl;
	mysetcolor(7.0);
	cout << "View Menu           [1] " << endl;
	cout << "View Meal Details   [2] " << endl;
	cout << "Place Order         [3] " << endl;
	cout << "Search Meal by Name [4] " << endl;
	cout << "Inform Kitchen      [5] " << endl;
	cout << "View Ingredients    [6] " << endl;
	cout << "Back                [7] " << endl;
}

void DisplayAdminAndClientMenu() {
	cout << "\tAdmin   [1]\t\t\t\t Client  [2]" << endl;
	cout << "\t\t\t\tExit  [3]" << endl;
}

void main() {



	Admin admin("ali", "1234");
	Restaurant restaurant("HardRock Restaurant", "Targovu street", "Baku City", 1000000, admin);

	Kitchen kitchen;
	Stock stock;
	Table table;
	Meal meal;

	kitchen.AddNewMeal("Burger", 5, 8);
	kitchen.AddNewMeal("Lahmacun", 3, 9);
	kitchen.AddNewMeal("Steak", 14, 10);
	kitchen.AddNewMeal("Mangal", 7, 9);
	kitchen.AddNewMeal("Sezar", 13, 10);
	system("cls");

	stock.AddNewIngredient("tomato", 1, 5);
	stock.AddNewIngredient("ketcup", 2, 3);
	stock.AddNewIngredient("moyanez", 1.5, 6);
	stock.AddNewIngredient("patote", 1.2, 7);
	stock.AddNewIngredient("lettuce", 2.5, 4);
	system("cls");

	try
	{
		while (true) {
			mysetcolor(3.0);
			cout << "  #    #      ##      #####    #####    #####    ####   #####   #    #\n";
			cout << "  #    #     #  #     #    #   #    #   #    #  #    #  #       #   # \n";
			cout << "  ######    ######    #####    #    #   #####   #    #  #       ####  \n";
			cout << "  #    #   #      #   #  #     #    #   #  #    #    #  #       #   # \n";
			cout << "  #    #  #        #  #    #   #####    #    #   ####   #####   #    #\n";
			cout << endl;
			cout << "\t\t\tWelcome To Restaurant" << endl;
			mysetcolor(7.0);
			DisplayAdminAndClientMenu();
			cout << "Select in option : ";
			int option;
			cin >> option;
			if (option == 1) {
				string username, password;
				cout << "Enter Admin Username : ";
				cin >> username;
				cout << "Enter Admin Password : ";
				cin >> password;
				cout << "Entry is checked...." << endl;
				Sleep(1500);
				system("cls");
				if (admin.Login(username, password)) {
					int adminOption;
					while (true) {
						DisplayAdminMenu();
						cout << "Select in admin option : ";
						cin >> adminOption;
						system("cls");
						if (adminOption == 1) {
							int kitchenOption;
							while (true) {
								DisplayKitchenMenyu();
								cin >> kitchenOption;

								if (kitchenOption == 1) {
									kitchen.AllViewRestaurant();
									system("cls");
									kitchen.AllViewRestaurant();

								}
								else if (kitchenOption == 2) {
									string name;
									double price, rating;
									cout << "Enter meal name : ";
									cin >> name;
									cout << "Enter meal price : ";
									cin >> price;
									cout << "Enter meal rating : ";
									cin >> rating;
									kitchen.AddNewMeal(name, price, rating);
									Sleep(1700);
									system("cls");
								}
								else if (kitchenOption == 3) {
									string name;
									cout << "Enter meal name to delete : ";
									cin >> name;
									kitchen.DeleteMeal(name);
									Sleep(1700);
									system("cls");
								}
								else if (kitchenOption == 4) {
									string name;
									double price, rating;
									cout << "Enter meal name to update : ";
									cin >> name;
									cout << "Enter new price : ";
									cin >> price;
									cout << "Enter new rating : ";
									cin >> rating;
									kitchen.UpdateMeal(name, price, rating);
									Sleep(1700);
									system("cls");
								}
								else if (kitchenOption == 5) {
									kitchen.AllViewOrder();
								}
								else if (kitchenOption == 6) {
									system("cls");
									break;
								}
							}
						}
						else if (adminOption == 2) {
							int stockOption;
							while (true) {
								DisplayStockMenyu();
								cin >> stockOption;
								if (stockOption == 1) {
									stock.AllViewIngredients();
									system("cls");
									stock.AllViewIngredients();
								}
								else if (stockOption == 2) {
									string name;
									double price;
									int quantity;
									cout << "Enter ingredient name : ";
									cin >> name;
									cout << "Enter ingredient price : ";
									cin >> price;
									cout << "Enter ingredient quantity : ";
									cin >> quantity;
									stock.AddNewIngredient(name, price, quantity);
									Sleep(1700);
									system("cls");
								}
								else if (stockOption == 3) {
									string name;
									cout << "Enter ingredient name to delete : ";
									cin >> name;
									stock.DeleteIngredient(name);
									Sleep(1700);
									system("cls");
								}
								else if (stockOption == 4) {
									string name;
									int quantity;
									cout << "Enter ingredient name to increase quantity: ";
									cin >> name;
									cout << "Enter quantity to increase: ";
									cin >> quantity;
									stock.IncreaseIngredient(name, quantity);
									Sleep(1700);
									system("cls");
								}
								else if (stockOption == 5) {
									string name;
									int quantity;
									cout << "Enter ingredient name to decrease quantity : ";
									cin >> name;
									cout << "Enter quantity to decrease : ";
									cin >> quantity;
									stock.DecreaseIngredient(name, quantity);
									Sleep(1700);
									system("cls");
								}
								else if (stockOption == 6) {
									system("cls");
									break;
								}
							}
						}
						else if (adminOption == 3) {
							break;
						}
					}
				}
			}
			else if (option == 2) {
				string tableNo;
				const Meal* menu = kitchen.GetRestaurantMenu();
				int numMeals = kitchen.GetNumMeals();
				system("cls");
				mysetcolor(3.0);
				cout << "\t\t= > = > Welcome Client < = < =" << endl;
				mysetcolor(7.0);
				cout << "Enter your table number : ";
				cin >> tableNo;
				Client client(tableNo, menu, numMeals);
				system("cls");
				int clientOption;
				while (true) {
					DisplayClientMenu();
					cout << "Select an option: ";
					cin >> clientOption;
					if (clientOption == 1) {
						system("cls");
						client.ViewAllMeals(menu, numMeals);
					}
					else if (clientOption == 2) {
						system("cls");
						client.ViewAllMeals(menu, numMeals);
						string mealName;
						cout << endl;
						cout << "Enter the name of the meal : ";
						cin.ignore();
						getline(cin, mealName);
						client.ViewMealDetails(menu, numMeals, mealName);
						Sleep(2000);
						system("cls");
					}
					else if (clientOption == 3) {
						string mealName;
						cout << "Enter the name of the meal you want to order : ";
						cin.ignore();
						getline(cin, mealName);

						double newPrice, newRating;
						cout << "Enter the new price for the meal : ";
						cin >> newPrice;
						cout << "Enter the new rating for the meal : ";
						cin >> newRating;

						client.PlaceOrder(&kitchen, &table, menu, numMeals, mealName, newPrice, newRating);
					}
					else if (clientOption == 4) {
						string searchMealName;
						cout << "Enter the name of the meal you want to search : ";
						cin.ignore();
						getline(cin, searchMealName);
						client.SearchMealByName(menu, numMeals, searchMealName);
						Sleep(1800);
						system("cls");
					}
					else if (clientOption == 5) {
						string kitchenMessage;
						bool acceptOrder;

						cout << "Do you want to accept the order? (yes/no) : ";
						string acceptAnswer;
						cin >> acceptAnswer;

						if (acceptAnswer == "yes") {
							acceptOrder = true;
							cout << "Enter any additional message for the kitchen : ";
							cin.ignore();
							getline(cin, kitchenMessage);
						}
						else {
							acceptOrder = false;
							cout << "Enter the reason for canceling the order : ";
							cin.ignore();
							getline(cin, kitchenMessage);
						}

						client.InformKitchen(&kitchen, &table, acceptOrder, kitchenMessage);
					}
					else if (clientOption == 6) {
						system("cls");
						stock.AllViewIngredients();
					}
					else if (clientOption == 7) {
						system("cls");
						break;
					}
					else {
						cout << "Invalid option. Please select a valid option" << std::endl;
					}
				}
			}
			else if (option == 3) {
				system("cls");
				mysetcolor(4.0);
				cout << "Exiting program....!";
				mysetcolor(7.0);
				break;

			}
			else {
				mysetcolor(4.0);
				cout << "Invalid admin credentials." << endl;
				mysetcolor(7.0);
				break;
			}
		}
	}
	catch (const exception& e) {
		cout << "Exception caught: " << e.what() << endl;
	}
}


