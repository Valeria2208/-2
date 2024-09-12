//
//  main.cpp
//  телефона книга2
//
//  Created by Valeria Dudinova on 12.09.2024.
//

#include <iostream>
using namespace std;

class Contact
{
private:
    char* fullName;
    char* homePhone;
    char* workPhone;
    char* mobilePhone;
    char* additionalInfo;

    char* copyString(const char* str)
    {
        int length = 0;
        while (str[length] != '\0')
        {
            length++;
        }
        char* newStr = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            newStr[i] = str[i];
        }
        newStr[length] = '\0';
        return newStr;
    }

public:
    Contact(const char* name = "", const char* home = "", const char* work = "",
            const char* mobile = "", const char* info = "")
    {
        fullName = copyString(name);
        homePhone = copyString(home);
        workPhone = copyString(work);
        mobilePhone = copyString(mobile);
        additionalInfo = copyString(info);
    }

    ~Contact()
    {
        delete[] fullName;
        delete[] homePhone;
        delete[] workPhone;
        delete[] mobilePhone;
        delete[] additionalInfo;
    }

    void display() const
    {
        cout << "Full Name: " << fullName << endl;
        cout << "Home Phone: " << homePhone << endl;
        cout << "Work Phone: " << workPhone << endl;
        cout << "Mobile Phone: " << mobilePhone << endl;
        cout << "Additional Info: " << additionalInfo << endl;
    }

    const char* getFullName() const
    {
        return fullName;
    }
};

class PhoneBook
{
private:
    Contact** contacts;
    int contactCount;

public:
    PhoneBook() : contacts(nullptr), contactCount(0) {}

    ~PhoneBook()
    {
        for (int i = 0; i < contactCount; i++)
        {
            delete contacts[i];
        }
        delete[] contacts;
    }

    void addContact(Contact* newContact)
    {
        Contact** temp = new Contact*[contactCount + 1];
        for (int i = 0; i < contactCount; i++)
        {
            temp[i] = contacts[i];
        }
        temp[contactCount] = newContact;
        delete[] contacts;
        contacts = temp;
        contactCount++;
    }

    void searchByName(const char* name) const
    {
        for (int i = 0; i < contactCount; i++)
        {
            if (compareStrings(contacts[i]->getFullName(), name))
            {
                contacts[i]->display();
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void displayAllContacts() const
    {
        if (contactCount == 0)
        {
            cout << "No contacts available." << endl;
            return;
        }
        for (int i = 0; i < contactCount; i++)
        {
            cout << "\nContact #" << i + 1 << ":" << endl;
            contacts[i]->display();
        }
    }
    void deleteContact(const char* name)
    {
        for (int i = 0; i < contactCount; i++)
        {
            if (compareStrings(contacts[i]->getFullName(), name))
            {
                delete contacts[i];
                for (int j = i; j < contactCount - 1; j++)
                {
                    contacts[j] = contacts[j + 1];
                }
                contactCount--;
                cout << "Contact deleted successfully." << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    bool compareStrings(const char* str1, const char* str2) const
    {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0')
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
            i++;
        }
        return str1[i] == str2[i];
    }
};

int main()
{
    PhoneBook phoneBook;

    while (true)
    {
        cout << "\nPhone Book Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact by Name\n";
        cout << "3. Display All Contacts\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            char name[100], homePhone[100], workPhone[100], mobilePhone[100], additionalInfo[200];

            cout << "Enter Full Name: ";
            cin.ignore();
            cin.getline(name, 100);
            cout << "Enter Home Phone: ";
            cin.getline(homePhone, 100);
            cout << "Enter Work Phone: ";
            cin.getline(workPhone, 100);
            cout << "Enter Mobile Phone: ";
            cin.getline(mobilePhone, 100);
            cout << "Enter Additional Info: ";
            cin.getline(additionalInfo, 200);

            Contact* newContact = new Contact(name, homePhone, workPhone, mobilePhone, additionalInfo);
            phoneBook.addContact(newContact);

        }
        else if (choice == 2)
        {
            char name[100];
            cout << "Enter Full Name to search: ";
            cin.ignore();
            cin.getline(name, 100);
            phoneBook.searchByName(name);

        } else if (choice == 3)
        {
            phoneBook.displayAllContacts();

        }
        else if (choice == 4)
        {
            char name[100];
            cout << "Enter Full Name to delete: ";
            cin.ignore();
            cin.getline(name, 100);
            phoneBook.deleteContact(name);

        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}

