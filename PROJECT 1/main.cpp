#include<iostream>
using namespace std;

const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;
string names[MAX_SPECIALIZATION][MAX_QUEUE];
int status[MAX_SPECIALIZATION][MAX_QUEUE];
int queue_length[MAX_SPECIALIZATION];
int menu()
{
    int choice = -1;
    while(choice == -1)
    {
        cout <<"Menu"<< endl;
        cout <<"1.Add Patient"<< endl;
        cout <<"2.Print Patients"<< endl;
        cout <<"3.Get Next Patient"<< endl;
        cout <<"4.Exit"<< endl;
        cout <<"Enter which option you want to perform : ";
        cin >> choice;
        if(!(choice >=1 && choice <=4))
        {
            cout <<"Pls enter your choice only from 1 to 4!"<< endl;
            choice = -1;
        }
    }
    return choice;
}

void shift_right(int spec)
{
    int len = queue_length[spec];
    for(int i=len;i>0;i--)
    {
        names[spec][i] = names[spec][i-1];
        status[spec][i] = status[spec][i-1];
    }
}
void add_patient()
{
    int spec, st;
    string name;
    cout <<"Enter patient's Specialization, name and status(0-regular, 1-Urgent)"<< endl;
    cin >> spec >> name >> st;
    int pos = queue_length[spec];
    if(pos >=MAX_QUEUE)
    {
        cout <<"Specialization " << spec << " is already filled. Try different Specialization"<< endl;
        return;
    }
    if(st == 0)
    {
        names[spec][pos] = name;
        status[spec][pos] = st;
        queue_length[spec]++;//now its 1, as its 1D array, so always queue_length[spec(5)] will increment, there's no position here!
    }
    else
    {
        shift_right(spec);
        names[spec][0] = name;
        status[spec][0] = st;
        queue_length[spec]++;
    }
}

void print_patient(int spec)
{
    int len = queue_length[spec];
    if(len == 0)
        return;
    cout <<"There are "<< len << " Patients in Specialization " << spec << endl;
    for(int pos=0;pos<len;pos++)
    {
        cout << names[spec][pos];
        if(status[spec][pos] == 0)
            cout <<" Regular";
        else
            cout <<" Urgent";
        cout <<"\n";
    }
}
void print_patients()
{
    for(int spec=0;spec<MAX_SPECIALIZATION;spec++)
        print_patient(spec);

}

void shift_left(int spec)
{
    int len = queue_length[spec];
    for(int pos=0;pos<len;pos++)
    {
        names[spec][pos] = names[spec][pos+1];
        status[spec][pos] = status[spec][pos+1];
    }
}
void get_next_patient()
{
    int spec;
    cout << "Enter the specialization from which a patient will go Doc's room" << endl;
    cin >> spec;
    int len = queue_length[spec];
    if(len == 0)
    {
        cout <<"Sorry Doctor! There's no patient in specialization " << spec << " at the moment " << endl;
        return;
    }
    cout << names[spec][0] <<" pls go inside" << endl;
    shift_left(spec);
    queue_length[spec]--;
}
void hospital_system()
{
    while(true)
    {
        int choice = menu();
        if(choice == 1)
            add_patient();
        else if(choice == 2)
            print_patients();
        else if(choice == 3)
            get_next_patient();
        else
            break;
    }
}

int main()
{
    hospital_system();
    return 0;
}
