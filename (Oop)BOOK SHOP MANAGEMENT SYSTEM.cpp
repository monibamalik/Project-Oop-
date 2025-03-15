#include<iostream>
#include<string.h>
#include <fstream>
#include <iomanip>

using namespace std;

class book
{
private:
    char *author, *title, *publisher;
    float *price;
    int *stock;
    float *dailySale;
    float *weeklySale;

public:
    book()
    {
        author = new char[20];
        title = new char[20];
        publisher = new char[20];
        price = new float;
        stock = new int;
        dailySale = new float;
        *dailySale = 0.0;
        weeklySale = new float;
        *weeklySale = 0.0;
    }

    ~book()
    {
        delete[] author;
        delete[] title;
        delete[] publisher;
        delete price;
        delete stock;
        delete dailySale;
        delete weeklySale;
    }

    void feeddata();
    void showdata();
    int search(char[], char[]);
    void buybook();
    void displayAllBooks();
    void writeDataToFile();
    void readDataFromFile();
    void buyMoreBooks();
    void calculateBill();
};

void book::feeddata()
{
    cin.ignore();
    cout << "\nEnter Author Name: ";
    cin.getline(author, 20);
    cout << "Enter Title Name: ";
    cin.getline(title, 20);
    cout << "Enter Publisher Name: ";
    cin.getline(publisher, 20);
    cout << "Enter Price: ";
    cin >> *price;
    cout << "Enter Stock Position: ";
    cin >> *stock;

    // Open the file in append mode and write the book data
    ofstream file("bookdata.txt", ios::app);
    file << author << "," << title << "," << publisher << "," << *price << "," << *stock << endl;
    file.close();
}

void book::showdata()
{
    cout << "\nAuthor Name: " << author;
    cout << "\nTitle Name: " << title;
    cout << "\nPublisher Name: " << publisher;
    cout << "\nPrice: " << *price;
    cout << "\nStock Position: " << *stock;
}

int book::search(char tbuy[20], char abuy[20])
{
    if (strcmp(tbuy, title) == 0 && strcmp(abuy, author) == 0)
        return 1;
    else
        return 0;
}

void book::buybook()
{
    int count;
    cout << "\nEnter Number Of Books to buy: ";
    cin >> count;
    if (count <= *stock)
    {
        *stock = *stock - count;
        cout << "\nBooks Bought Successfully";
        cout << "\nAmount: $" << (*price) * count;
    }
    else
        cout << "\nRequired Copies not in Stock";
}

void book::writeDataToFile()
{
    ofstream outFile("book_data.txt", ios::app);
    if (!outFile)
    {
        cout << "Error opening the file.";
        return;
    }

    outFile << author << endl;
    outFile << title << endl;
    outFile << publisher << endl;
    outFile << *price << endl;
    outFile << *stock << endl;

    outFile.close();
}

void book::readDataFromFile()
{
    ifstream inFile("book_data.txt");
    if (!inFile)
    {
        cout << "Error opening the file.";
        return;
    }

    while (!inFile.eof())
    {
        inFile.getline(author, 20);
        inFile.getline(title, 20);
        inFile.getline(publisher, 20);
        inFile >> *price;
        inFile >> *stock;
        inFile.ignore();

        if (strlen(author) > 0)
            showdata();
    }

    inFile.close();
}

void book::displayAllBooks()
{
    ifstream file("bookdata.txt");
    if (!file)
    {
        cout << "No books found in the inventory." << endl;
        return;
    }

    cout << "\n\n\t\t\t========== All Books ==========" << endl;
    cout << setw(20) << "Author" << setw(20) << "Title" << setw(20) << "Publisher" << setw(10) << "Price" << setw(10) << "Stock" << endl;

    char author[20], title[20], publisher[20];
    float price;
    int stock;

    while (file.getline(author, 20, ','))
    {
        file.getline(title, 20, ',');
        file.getline(publisher, 20, ',');
        file >> price;
        file.ignore();
        file >> stock;
        file.ignore();

        cout << setw(20) << author << setw(20) << title << setw(20) << publisher << setw(10) << price << setw(10) << stock << endl;
    }

    file.close();
}

void book::buyMoreBooks()
{
    int count;
    cin.ignore();
    cout << "Enter Title Name: ";
    cin.getline(title, 20);
    cout << "\nEnter Author Name: ";
    cin.getline(author, 20);
    cout << "\nEnter Number Of Additional Books to buy: ";
    cin >> count;
    if (count <= *stock)
    {
        *stock = *stock - count;
        cout << "\nAdditional Books Bought Successfully";
        cout << "\nAmount: $" << (*price) * count;
        *dailySale += (*price) * count;
        *weeklySale += (*price) * count;
    }
    else
        cout << "\nRequired Copies not in Stock";
}

    void book::calculateBill()
{
    int count;
    float totalBill = 0.0, bill;
    cout << "\nEnter Number Of Books to buy: ";
    cin >> count;
    if (count <= *stock)
    {
        *stock = *stock - count;
        cout << "\nBooks Bought Successfully";
        for (int i = 0; i < count; i++)
        {
            cout << "\nEnter the price of book " << (i + 1) << ": $";
            cin >> bill;
            totalBill += bill;
        }
        cout << "\nAmount: $" << totalBill;
        *dailySale += totalBill;
        *weeklySale += totalBill;
    }
    else
    {
        cout << "\nRequired Copies not in Stock";
    }
}



int main()
{
    book *B[20];
    int i = 0, r, t, choice, x = 0;
    char titlebuy[20], authorbuy[20];

    while (1)
    {
        cout << "\n\n====== Book Shop Management System ======";
        cout << "\n1. Entry of New Book";
        cout << "\n2. Buy Book";
        cout << "\n3. Search For Book";
        cout << "\n4. Display All Books";
        cout << "\n5. Exit";
        cout << "\n\nEnter your Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            B[i] = new book;
            B[i]->feeddata();
            i++;
            break;

        case 2:
        a:
            cin.ignore();
            cout << "\nEnter Title Of Book: ";
            cin.getline(titlebuy, 20);
            cout << "Enter Author Of Book: ";
            cin.getline(authorbuy, 20);
            for (t = 0; t < i; t++)
            {
                if (B[t]->search(titlebuy, authorbuy))
                {
                    cout << "\n1. Buy More Books";
                    cout << "\n2. Calculate Bill";
                    cout << "\nEnter your choice: ";
                    int buyChoice;
                    cin >> buyChoice;
                    switch (buyChoice)
                    {
                    case 1:
                        B[t]->buyMoreBooks();
                        goto a;
                        break;
                    case 2:
                        B[t]->calculateBill();
                        break;
                    default:
                        cout << "\nInvalid Choice Entered";
                        break;
                    }
                    break;
                }
                x++;
            }
            if (t == i)
                cout << "\nThis Book is Not in Stock";
            break;
        case 3:
            cin.ignore();
            cout << "\nEnter Title Of Book: ";
            cin.getline(titlebuy, 20);
            cout << "Enter Author Of Book: ";
            cin.getline(authorbuy, 20);

            for (t = 0; t < i; t++)
            {
                if (B[t]->search(titlebuy, authorbuy))
                {
                    cout << "\nBook Found Successfully";
                    B[t]->showdata();
                    break;
                }
            }
            if (t == i)
                cout << "\nThis Book is Not in Stock";
            break;

        case 4:
            B[i] = new book;
            B[i]->displayAllBooks();
            i++;

            for (t = 0; t < i; t++)
            {
                if (B[t]->search(titlebuy, authorbuy))
                {
                    cout << "\nBook Found Successfully";
                    B[t]->showdata();
                    break;
                }
            }
            if (t == i)
                cout << "\nThis Book is Not in Stock";
            break;

        case 5:
            exit(0);
        default:
            cout << "\nInvalid Choice Entered";
        }
    }

    cout << "SN.          Title          Author " << endl;
    cout << "-----------------------------------" << endl;

    for (int i = 0; i < x; i++)
    {
        cout << i << "          " << titlebuy[i] << "          " << authorbuy[i] << endl;
        cout << "-------------------------------------------------------------" << endl;
    }
    return 0;
}
