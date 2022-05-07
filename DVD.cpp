#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <ctime>

using namespace std;

class MovieDvD
{
public:
    int id;
    string name;
    int base_period, base_price, extend_price;
    bool in_stock;
    float points;

    MovieDvD(int id, string name) {
        this->id = id;
        this->name = name;
        this->in_stock = true;
    }
};


class NewMovie : public MovieDvD
{
public:
    NewMovie(int id, string name): MovieDvD(id, name)
    {
        base_period = 1
        base_price = 3;
        extend_price = 2;
        points = 2.0;
    }
};

class OldMovie : public MovieDvD
{
public:
    OldMovie(int id, string name) : MovieDvD(id, name)
    {
        base_period = 3
        base_price = 2;
        extend_price = 1;
        points = 1.0;
    }
};

class ChildMovie : public MovieDvD
{
public:
    ChildMovie(int id, string name) : MovieDvD(id, name)
    {
        base_period = 5
        base_price = 2;
        extend_price = 1;
        points = 0.5;
    }
};

class Customer
{
public:
    int id;
    string name;
    int total_spent;
    float points;
    vector<RentRecord *> rent_history;

    Customer(int id, string name)
    {
        this->id = id;
        this->name = name;
        this->total_spent = 0;
        this->points = 0;
    }

    int addRecord(RentRecord *record)
    {
        this->total_spent += record->price;
        this->points += record->movie->points;
        this->rent_history.push_back(record);

        return 0;
    }
}

class RentRecord
{
public:
    string date;
    int rentDays;
    int price;
    Customer    *client;
    MovieDvD    *movie;
    bool isReturned;

    RentRecord(string date, int rentDays, Customer *client, MovieDvD *movie)
    {
        this->date = date;
        this->rentDays = rentDays;
        this->client = client;
        this->movie = movie;
        this->isReturned = false;

        this->price = movie->base_price;
        if (rentDays > movie->base_period)
        {
            this->price += (movie->extend_price) * (rentDays - movie->base_period);
        }

    }

    int returnMovie()
    {
        this->isReturned = true;

        return 0;
    }
};

class RentManager
{
public:
    int new_customer_id, new_movie_id;
    string date_today;
    set<Customer *> customers;
    set<MovieDvD *> movies;
    vector<RentRecord *> records;

    RentManager()
    {
        this->updateTime();
        this->new_customer_id = 0;
        this->new_movie_id = 0;
    }

    void updateTime()
    {
        time_t now = time(0);
        char *c = ctime(&now);
        string date(c);
        this->date_today = date;
    }

    int getNewClientID() {
        int id = this->new_customer_id++;
        return id;
    }

    int getNewMovieID() {
        int id = this->new_movie_id++;
        return id;
    }

    void addCustomer(Customer *customer)
    {
        this->customers.insert(customer);
    }

    void addMovie(MovieDvD *movie)
    {
        this->movies.insert(movie);
    }

    void addRecord(Customer *customer, MovieDvD *movie, int rentDays)
    {
        RentRecord *newRecord = new RentRecord(this->date_today, rentDays, customer, movie);
        this->records.push_back(newRecord);
        customer->addRecord(newRecord);
    }

    void print_statement(Customer *customer)
    {
        cout << "Customer : " << customer->name << endl;
        for (RentRecord *record : customer->rent_history)
        {
            cout << "\tdate: " << record->date;
            cout << "\trent days: " << record->rentDays;
            cout << "\tmovie: " << record->movie->name;
            cout << "\tprice: " << record->price;
            cout << "\tisReturned: " << record->isReturned << endl;
        }
    }
}

int main()
{
    RentManager rent_system;
    Customer *Alice1 = new Customer(rent_system.getNewClientID(), "Alice");
    Customer *Alice2 = new Customer(rent_system.getNewClientID(), "Alice");
    Customer *Bob = new Customer(rent_system.getNewClientID(), "Bob");
    Customer *Eve = new Customer(rent_system.getNewClientID(), "Eve");
    
    NewMovie *Doctor_Strange_2_copy_0 = new NewMovie(rent_system.getNewMovieID(), "Doctor Strange 2");
    NewMovie *Doctor_Strange_2_copy_1 = new NewMovie(rent_system.getNewMovieID(), "Doctor Strange 2");
    OldMovie *The_Kings_Man_copy_0 = new OldMovie(rent_system.getNewMovieID(), "The King's Man");
    OldMovie *The_Kings_Man_copy_1 = new OldMovie(rent_system.getNewMovieID(), "The King's Man");
    ChildMovie *Toy_Story_copy_0 = new ChildMovie(rent_system.getNewMovieID(), "Toy Story");
    ChildMovie *Toy_Story_copy_1 = new ChildMovie(rent_system.getNewMovieID(), "Toy Story");

    rent_system.addCustomer(Alice1);
    rent_system.addCustomer(Alice2);
    rent_system.addCustomer(Bob);
    rent_system.addCustomer(Eve);

    rent_system.addMovie(Doctor_Strange_2_copy_0);
    rent_system.addMovie(Doctor_Strange_2_copy_1);
    rent_system.addMovie(The_Kings_Man_copy_0);
    rent_system.addMovie(The_Kings_Man_copy_1);
    rent_system.addMovie(Toy_Story_copy_0);
    rent_system.addMovie(Toy_Story_copy_1);

    rent_system.addRecord(Alice1, Toy_Story_copy_0);
    rent_system.addRecord(Alice1, The_Kings_Man_copy_0);

    rent_system.addRecord(Alice2, Toy_Story_copy_1);
    rent_system.addRecord(Alice2, Doctor_Strange_2_copy_0);

    rent_system.addRecord(Bob, Doctor_Strange_2_copy_1);
    
    rent_system.addRecord(Eve, Toy_Story_copy_1);
    rent_system.addRecord(Eve, The_Kings_Man_copy_1);

    for (Customer *c: rent_system.customers)
    {
        rent_system.print_statement(c);
    }
}