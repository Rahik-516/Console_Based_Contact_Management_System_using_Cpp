#include <iostream>
#include <fstream>
#include <string>
#include<conio.h>

using namespace std;

class Contact {
private:
    friend void menu(Contact c1);
    string first_name, last_name, address;
    long long phone_number;

public:
    void create_Contact() {
        cout << "Enter your first name: ";
        cin >> first_name;
        cout << "Enter your last name: ";
        cin >> last_name;
        cout << "Enter phone number: ";
        cin >> phone_number;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
    }

    void show_Contact(){
        cout << "Name: " << first_name << " " << last_name << endl;
        cout << "Phone: " << phone_number << endl;
        cout << "Address: " << address << endl;
    }

    void write_onFile(){
        char ch;
        ofstream f1("contact_management_system.txt", ios::app);
        if (!f1.is_open()) {
            cout << "Error opening the file." << endl;
            return;
        }
        do {
            create_Contact();
            f1 << first_name << " " << last_name << " " << phone_number << " " << address << endl;
            cout << "Do you have next data? (y/n): ";
            cin >> ch;
        } while (ch == 'y');

        cout << "Contact has been Successfully Created..." << endl;
        f1.close();
    }

    void read_FromFile() {
        ifstream f2("contact_management_system.txt");
        if (!f2.is_open()) {
            cout << "Error opening the file." << endl;
            return;
        }

        cout << "===========================================\n";
        cout << "LIST OF CONTACT\n";
        cout << "===========================================\n";

        while (f2 >> first_name >> last_name >> phone_number) {
            getline(f2, address);
            show_Contact();
            cout << "==========================================\n";
        }
        f2.close();
    }

    void search_onFile() {
        ifstream f3("contact_management_system.txt");
        long long phone;
        cout << "Enter phone number: ";
        cin >> phone;

        if (!f3.is_open()) {
            cout << "Error opening the file." << endl;
            return;
        }

        bool contactFound = false;
        while (f3 >> first_name >> last_name >> phone_number) {
            getline(f3, address);
            if (phone == phone_number) {
                show_Contact();
                contactFound = true;
            }
        }

        f3.close();

        if (!contactFound) {
            cout << "\nNo record found!" << endl;
        }
    }

    void delete_FromFile() {
        long long phone;
        int flag = 0;
        ifstream f5("contact_management_system.txt");
        ofstream f4("temp.txt");

        if (!f5.is_open() || !f4.is_open()) {
            cout << "Error opening files." << endl;
            return;
        }

        cout << "Enter phone number to delete: ";
        cin >> phone;

        while (f5 >> first_name >> last_name >> phone_number) {
            getline(f5, address);
            if (phone_number != phone) {
                f4 << first_name << " " << last_name << " " << phone_number << " " << address << endl;
            } else {
                flag = 1;
            }
        }

        f5.close();
        f4.close();

        if (flag == 1) {
            cout << "\tContact Deleted...";
        } else {
            cout << "\tContact Not Found...";
        }

        remove("contact_management_system.txt");
        rename("temp.txt", "contact_management_system.txt");
    }

    void edit_Contact() {
        long long phone;
        fstream f6("contact_management_system.txt");

        cout << "Edit contact";
        cout << "\n======================================\n";
        cout << "Enter the phone number to be edited: ";
        cin >> phone;

        if (!f6.is_open()) {
            cout << "Error opening the file." << endl;
            return;
        }

        while (f6 >> first_name >> last_name >> phone_number) {
            getline(f6, address);
            if (phone == phone_number) {
                cout << "Enter new record: \n";
                create_Contact();
                f6.seekg(-(static_cast<long>(sizeof(*this)) + address.length() + 1), ios::cur);

                f6 << first_name << " " << last_name << " " << phone_number << " " << address << endl;
                cout << "\tContact Successfully Updated..." << endl;
                return;
            }
        }

        cout << "\nNo Record Found" << endl;
        f6.close();
    }
};

void menu(Contact c1) {
    cout << "\n\n\n\n\n\n\n\n\n\n *WELCOME TO THE CONTACT MANAGEMENT SYSTEM*";
    getch();
    while (1) {
        int choice;

        system("cls");
        system("Color 03");
        cout << "\nCONTACT MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";
        cout << "\n===========================================\n";
        cout << "[1] Add a new Contact\n";
        cout << "[2] List all Contacts\n";
        cout << "[3] Search for Contact\n";
        cout << "[4] Delete a Contact\n";
        cout << "[5] Edit a Contact\n";
        cout << "[0] Exit";
        cout << "\n============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system("cls");
                c1.write_onFile();
                break;

            case 2:
                system("cls");
                c1.read_FromFile();
                break;

            case 3:
                system("cls");
                c1.search_onFile();
                break;
            case 4:
                system("cls");
                c1.delete_FromFile();
                break;
            case 5:
                system("cls");
                c1.edit_Contact();
                break;
            case 0:
                system("cls");
                cout << "\n\n\n\t\t\tThank You for using this Customer Management System." << endl << endl;
                exit(0);
                break;
            default:
                continue;
        }

        int opt;
        cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin >> opt;

        switch (opt) {
            case 0:
                system("cls");
                cout << "\n\n\n\t\t\tThank You for using this Customer Management System." << endl << endl;
                exit(0);
                break;
            default:
                continue;
                    }

}
}
int main()
{

    system("cls");
    system("Color 3F");
    Contact C1;
    menu(C1);

    return 0;
}
