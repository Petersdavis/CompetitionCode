#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
enum Tiles {


}

struct Customer{

}

void Customer::read(){

}


struct Game{
    vector<Customer> all_customer;
    vector<Customer> customer;


}

struct Grid{

}

struct Cell{

}



int main()
{

    Game game = new Game();


    int numAllCustomers;
    cin >> numAllCustomers; cin.ignore();
    for (int i = 0; i < numAllCustomers; i++) {
        Customer customer = new Customer();
        customer::read()
        game.all_customer.push_back(customer)
    }


    for (int i = 0; i < 7; i++) {
        string kitchenLine;
        getline(cin, kitchenLine);
    }

    // game loop
    while (1) {
        int turnsRemaining;
        cin >> turnsRemaining; cin.ignore();
        int playerX;
        int playerY;
        string playerItem;
        cin >> playerX >> playerY >> playerItem; cin.ignore();
        int partnerX;
        int partnerY;
        string partnerItem;
        cin >> partnerX >> partnerY >> partnerItem; cin.ignore();
        int numTablesWithItems; // the number of tables in the kitchen that currently hold an item
        cin >> numTablesWithItems; cin.ignore();
        for (int i = 0; i < numTablesWithItems; i++) {
            int tableX;
            int tableY;
            string item;
            cin >> tableX >> tableY >> item; cin.ignore();
        }
        string ovenContents; // ignore until wood 1 league
        int ovenTimer;
        cin >> ovenContents >> ovenTimer; cin.ignore();
        int numCustomers; // the number of customers currently waiting for food
        cin >> numCustomers; cin.ignore();
        for (int i = 0; i < numCustomers; i++) {
            string customerItem;
            int customerAward;
            cin >> customerItem >> customerAward; cin.ignore();
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;


        // MOVE x y
        // USE x y
        // WAIT
        cout << "WAIT" << endl;
    }
}