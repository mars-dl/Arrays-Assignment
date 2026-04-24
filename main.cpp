#include <iostream>
#include <limits>
#include <vector>
using namespace std;
//Ethan Ma
//Array Assignment, 4/24/26

class seat{
    int row{};
    char let{};
    string name = "";
    bool isAvailable = true;

    public:
    //initial constructor
    seat() = default;
    //loaded constructor
    seat (int row, char let) {
        this->row = row;
        this->let = let;
        isAvailable = true;
    }
    void display() {
        cout << row << let << " - ";
        if (isAvailable) {
            cout << "available" << endl;
        }
        else {
            cout << "is occupied by " << name << endl;
        }
    }
    bool checkAvailable() {
        return isAvailable;
    }
    void book(string x) {
        name = x;
        isAvailable = false;
    }
    void cancel() {
        name = "";
        isAvailable = true;
    }
    bool checkWindow() {
        if (let == 'A' || let == 'D') {
            return true;
        }
        return false;
    }

};

seat seats[4][6] = {};

void initializeSeats() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (i == 0){ seats[i][j] = seat(j+1, 'A'); }
            if (i == 1){ seats[i][j] = seat(j+1, 'B'); }
            if (i == 2){ seats[i][j] = seat(j+1, 'C'); }
            if (i == 3){ seats[i][j] = seat(j+1, 'D'); }
        }
    }
}

double calcOccupancy() {
    double occupancy = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (!seats[i][j].checkAvailable()) {
                occupancy++;
            }
        }
    }
    return (occupancy/24)*100;
}

void findWindowSeats() {
    for (int i = 0; i < 6; i++) {
        if (seats[0][i].checkAvailable()) {
            seats[0][i].display();
        }
        if (seats[3][i].checkAvailable()) {
            seats[3][i].display();
        }
    }
}

void getRowSeats(int i) {
    seats[0][i].display();
    seats[1][i].display();
    seats[2][i].display();
    seats[3][i].display();
}

int intInput() {
    int input;
    while (!(cin >> input)) {
        cout << "Invalid input, please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

int main() {
    initializeSeats();
    int choice;
    string name;
    int num;
    char let;
    vector<string> passwords;
    cout << "Welcome to Airplane Seat Booker"
            "\nMENU"
            "\n1 to display all seats"
            "\n2 to book a seat"
            "\n3 to cancel a seat(requires password)"
            "\n4 to see window seats"
            "\n5 to see a selected row"
            "\n6 to see admin menu(requires password)"
            "\n7 to quit" << endl;
    choice = intInput();
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7) {
        cout << "Invalid input, please try again." << endl;
        choice = intInput();
    }
    while (choice != 7) {
        if (choice == 1) {
            cout << "\nCurrent Seats:" << endl;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 6; j++) {
                    seats[i][j].display();
                }
            }
        }
        else if (choice == 2) {
            cout << "\nEnter your name:";
            cin.ignore();
            getline(cin, name);
            //A = 65, B = 66, C = 67, D = 68
            cout << "Enter the number of the seat (1-6):";
            num = intInput();
            while (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6) {
                cout << "Invalid input, please try again." << endl;
                num = intInput();
            }
            cout << "Enter the letter of the seat (A, B, C, D):";
            cin >> let;
            let = toupper(let);
            while (let != 'A' && let != 'B' && let != 'C' && let != 'D') {
                cout << "Invalid input, please try again." << endl;
                cin >> let;
                let = toupper(let);
            }
            if (seats[(int)let-65][num-1].checkAvailable()) {
                seats[(int)let-65][num-1].book(name);
                cout << "You have been booked, thank you!"
                        "\nEnter a password (use it if you want to cancel your seat):";
                cin.ignore();
                string password;
                getline(cin, password);
                passwords.push_back(password);
            }
            else {
                cout << "Sorry, that seat is occupied." << endl;
            }
        }
        else if (choice == 3) {
            cout << "\nEnter the number of the seat to cancel (1-6):";
            num = intInput();
            while (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6) {
                cout << "Invalid input, please try again." << endl;
                num = intInput();
            }
            cout << "Enter the letter of the seat to cancel (A, B, C, D):";
            cin >> let;
            let = toupper(let);
            while (let != 'A' && let != 'B' && let != 'C' && let != 'D') {
                cout << "Invalid input, please try again." << endl;
                cin >> let;
                let = toupper(let);
            }
            if (!seats[(int)let-65][num-1].checkAvailable()) {
                cout << "Enter password to cancel:" << endl;
                cin.ignore();
                string password;
                getline(cin, password);
                for (string s : passwords) {
                    if (s==password) {
                        seats[(int)let-65][num-1].cancel();
                        break;
                    }
                }
            }
            else {
                cout << "That seat is currently empty" << endl;
            }
        }
        else if (choice == 4) {
            //find seats with letter A or D
            findWindowSeats();
        }
        else if (choice == 5) {
            //find number row
            cout << "Enter the seat's number row (1-6):";
            num = intInput();
            while (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6) {
                cout << "Invalid input, please try again." << endl;
                num = intInput();
            }
            getRowSeats(num-1);
        }
        else if (choice == 6) {
            cout << "\nEnter the administrator's password:" << endl;
            cin.ignore();
            string password;
            cin >> password;
            if (password == "admin") {
                while (choice == 6) {
                    cout << "\nADMIN MENU"
                            "\n1 to cancel a seat"
                            "\n2 to see occupancy"
                            "\n3 to reset system"
                            "\n4 to return to exit" << endl;
                    int adchoice = intInput();
                    while (adchoice != 1 && adchoice != 2 && adchoice != 3 && adchoice != 4) {
                        cout << "Invalid input, please try again." << endl;
                        choice = intInput();
                    }
                    if (adchoice == 1) {
                        cout << "\nEnter the number of the seat to cancel (1-6):";
                        num = intInput();
                        while (num != 1 && num != 2 && num != 3 && num != 4 && num != 5 && num != 6) {
                            cout << "Invalid input, please try again." << endl;
                            num = intInput();
                        }
                        cout << "Enter the letter of the seat to cancel (A, B, C, D):";
                        cin >> let;
                        let = toupper(let);
                        while (let != 'A' && let != 'B' && let != 'C' && let != 'D') {
                            cout << "Invalid input, please try again." << endl;
                            cin >> let;
                            let = toupper(let);
                        }
                        if (!seats[(int)let-65][num-1].checkAvailable()) {
                            seats[(int)let-65][num-1].cancel();
                        }
                        else {
                            cout << "That seat is currently empty" << endl;
                        }
                    }
                    else if (adchoice == 2) {
                        cout << "\nThe current occupancy is " << calcOccupancy() << "%" << endl;
                    }
                    else if (adchoice == 3) {
                        cout << "\nResetting system"<< endl;
                        initializeSeats();
                    }
                    else if (adchoice == 4) {
                        break;
                    }
                }
            }
        }
        cout <<
            "\nMENU"
            "\n1 to display all seats"
            "\n2 to book a seat"
            "\n3 to cancel a seat(requires password)"
            "\n4 to see window seats"
            "\n5 to see a selected row"
            "\n6 to see admin menu(requires password)"
            "\n7 to quit" << endl;
        choice = intInput();
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7) {
            cout << "Invalid input, please try again." << endl;
            choice = intInput();
        }
    }
}