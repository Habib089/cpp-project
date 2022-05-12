#include<iostream>
#include<algorithm>
#include<assert.h>
using namespace std;

const int MAX_BOOK = 10;
const int MAX_USER = 10;

struct book{
    int id;
    string name;
    int total_quantity;
    int total_borrowed;

    book()
    {
        id = -1;
        total_quantity = total_borrowed = 0;
        name = "";
    }

    void read()
    {
        cout <<"Enter Book's ID, Name and Total Quantity : "<< endl;
        cin >> id >> name >> total_quantity;
        total_borrowed = 0;
    }

    bool borrow()
    {
        if(total_quantity-total_borrowed == 0)
            return false;
        ++total_borrowed;
        return true;
    }

    void return_copy()
    {
        assert(total_borrowed > 0);
        --total_borrowed;
    }

    bool has_prefix(string prefix)
    {
        if(prefix.size() > name.size())
            return false;

        for(int i=0;i<prefix.size();i++)
        {
            if(prefix[i] != name[i])
            return false;
        }
        return true;
    }

    void print()
    {
        cout <<"ID = "<< id <<", Name = "<< name <<", Total Quantity = " << total_quantity <<", Total Borrowed = " << total_borrowed << endl;
    }
};

bool print_lib_cmp_by_id(book &a, book &b)
{
    return a.id < b.id;
}

bool print_lib_cmp_by_name(book &a, book &b)
{
    return a.name < b.name;
}

struct user{
    int id;
    string name;
    int borrowed_books_id[MAX_BOOK];
    int len;

    user()
    {
        id = -1;
        name = "";
        len = 0;
    }

    void read()
    {
        cout <<"Enter Name and National ID : ";
        cin >> name >> id;
    }

    void borrow(int book_id)
    {
        borrowed_books_id[len++] = book_id;
    }

    bool is_borrowed(int book_id)
    {
        for(int i=0;i<len;i++)
        {
            if(borrowed_books_id[i] == book_id)
                return true;
        }
        return false;
    }
    void return_copy(int book_id)
    {
        bool removed = false;
        for(int i=0;i<len;i++)
        {
            if(borrowed_books_id[i] == book_id)
            {
                for(int j=i+1;j<len;j++)  //shifting left
                {
                    borrowed_books_id[j-1] = borrowed_books_id[j];
                }
                removed = true;
            --len;
            break;
            }
        }
        if(!removed)
            cout <<"User " << name <<" has never borrowed book id "<< book_id << endl;
    }

    void print()
    {
        sort(borrowed_books_id, borrowed_books_id + len);
        cout << "User = " << name <<", ID = "<< id <<", Borrowed Books ID = ";
        for(int i=0;i<len;i++)
            cout << borrowed_books_id[i] <<" ";
        cout <<""<< endl;
    }

};

struct library_system{
    int total_books;
    book books[MAX_BOOK];
    int total_users;
    user users[MAX_USER];

    library_system()
    {
        total_books = total_users = 0;
    }

    void run()
    {
        while(true)
        {
            int choice = menu();
            if(choice == 1)
                add_book();
            else if(choice == 2)
                search_books_by_prefix();
            else if(choice == 3)
                print_who_borrowed_by_name();
            else if(choice == 4)
                print_library_by_id();
            else if(choice == 5)
                print_library_by_name();
            else if(choice == 6)
                add_user();
            else if(choice == 7)
                user_borrow_book();
            else if(choice == 8)
                user_return_book();
            else if(choice == 9)
                print_users();
            else
                break;
        }
    }

    int menu()
    {
        int choice = -1;
        while(choice == -1)
        {
            cout <<"\nMenu"<< endl;
            cout <<"1.Add Book"<< endl;
            cout <<"2.Search Books By Prefix"<< endl;
            cout <<"3.Print Who Borrowed By Name"<< endl;
            cout <<"4.Print Library By ID"<< endl;
            cout <<"5.Print Library By Name"<< endl;
            cout <<"6.Add user"<< endl;
            cout <<"7.User Borrow Book"<< endl;
            cout <<"8.User Return Book"<< endl;
            cout <<"9.Print Users"<< endl;
            cout <<"10.Exit"<< endl;
            cout <<"\nEnter your choice from menu[1-10] : ";
            cin >> choice;
            if(choice < 1 && choice >10)
            {
                cout <<"Invalid Choice! Enter proper choice"<<endl;
                choice == -1;
            }
        }
        return choice;
    }

    void add_book()
    {
        books[total_books++].read();
    }

    void search_books_by_prefix()
    {
        string prefix;
        cout <<"Enter Book's Prefix : ";
        cin >> prefix;
        bool has_prefix = false;
        for(int i=0;i<total_books;i++)
        {
            if(books[i].has_prefix(prefix))
                cout << books[i].name << endl;
            has_prefix = true;
        }
        if(!has_prefix)
        {
            cout <<"No books found with prefix - "<< prefix <<endl;
        }
    }

    void add_user()
    {
        users[total_users++].read();
    }

    int find_user_by_name(string namee)
    {
        for(int i=0;i<total_users;i++)
        {
            if(namee == users[i].name)
                return i;
        }
        return -1;
    }

    int find_book_by_name(string namee)
    {
        for(int i=0;i<total_books;i++)
        {
            if(namee == books[i].name)
                return i;
        }
        return -1;
    }

    void user_borrow_book()
    {
        string user_name, book_name;
        cout <<"Enter the user name and book name : ";
        cin >> user_name >> book_name;

        int user_idx = find_user_by_name(user_name);
        if(user_idx == -1)
        {
           cout <<"Invalid User Name"<< endl;
        }
        int book_idx = find_book_by_name(book_name);
        if(book_idx == -1)
        {
           cout <<"Invalid Book Name"<< endl;
        }

        if(book_idx == -1 || user_idx == -1)
            return;

        int book_id = books[book_idx].id;

        if(!books[book_idx].borrow())
            cout <<"No More Copies Available of This Book " << endl;
        else
        {
            users[user_idx].borrow(book_id);
        }
    }

    void user_return_book()
    {
        string user_name, book_name;
        cout <<"Enter the user name and book name : ";
        cin >> user_name >> book_name;

        int user_idx = find_user_by_name(user_name);
        if(user_idx == -1)
        {
           cout <<"Invalid User Name"<< endl;
        }
        int book_idx = find_book_by_name(book_name);
        if(book_idx == -1)
        {
           cout <<"Invalid Book Name"<< endl;
        }

        if(book_idx == -1 || user_idx == -1)
            return;

        int book_id = books[book_idx].id;
        books[book_idx].return_copy();
        users[user_idx].return_copy(book_id);
    }

    void print_library_by_id()
    {
        sort(books, books + total_books, print_lib_cmp_by_id);
        for(int i=0;i<total_books;i++)
        {
            books[i].print();
        }
    }

    void print_library_by_name()
    {
        sort(books, books + total_books, print_lib_cmp_by_name);
        for(int i=0;i<total_books;i++)
        {
            books[i].print();
        }
    }

    void print_users()
    {
        for(int i=0;i<total_users;i++)
            users[i].print();
    }

    void print_who_borrowed_by_name()
    {
        string book_name;
        cout <<"Enter the book name : ";
        cin >> book_name;

        int book_idx = find_book_by_name(book_name);
        if(book_idx == -1)
        {
            cout <<"This book doesn't exist here, let alone being borrowed by anyone!"<< endl;
            return;
        }
        int book_id = books[book_idx].id;
        if(books[book_idx].total_borrowed == 0)
           cout <<"No One Borrowed this book yet!"<<endl;
        else
        {
            cout <<"People who borrowed "<< book_name <<" are - "<< endl;
            for(int i=0;i<total_users;i++)
            {
                if(users[i].is_borrowed(book_id))
                    cout << users[i].name << endl;
            }
        }
    }
};

int main()
{
    library_system library;
    library.run();
    return 0;
}
