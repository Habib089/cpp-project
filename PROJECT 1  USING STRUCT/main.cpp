#include<iostream>
using namespace std;

const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

struct hospital_queue{
    string names[MAX_QUEUE];
    int status[MAX_QUEUE];
    int len, spec;
    hospital_queue()
    {
        len = 0;
        spec = -1; // default constructor where there is no specialization.
    }
    hospital_queue(int _spec) // suppose _spec = 5
    {
        len = 0; // for specialization 5 NO ELEMENT YET
        spec = _spec; // we can't say spec = -1, as for _spec = 5, spec = 5 not -1/0 as its not len; So spec = _spec
    }

    void add_end(string name, int st)
    {
        names[len] = name;
        status[len] = st;
        len++;
    }

    void add_front(string name, int st)
    {
        // shift right
        for(int i=len;i>0;i--)
        {
            names[i] = names[i-1];
            status[i] = status[i-1];
        }
        names[0] = name;
        status[0] = st;
        len++;
    }

    void print(int spec)
    {
        if(len !=0)
        {
            cout <<"There's " << len << " patients in specialization " << spec << endl;
            for(int i=0;i<len;i++)
            {
                cout << names[i] <<" ";
                if(status[i] == 0)
                    cout << "Regular";
                else
                    cout << "Urgent";
                cout <<""<< endl;
            }
        }
    }

    void remove_front(int spec)
    {
        if(len == 0)
        {
            cout <<"There's no patient in this specialization "<< spec <<" . Pls! Wait doc!"<< endl;
            return;
        }
        cout << names[0] << " ,pls go to Dr room" << endl; // ai struct e jei spec diye entry korecho, shetar member der access kora jabe ai vabei
        // shifting left
        for(int i=1;i<len;i++)
        {
            names[i-1] = names[i];
            status[i-1] = status[i];
        }
        len--;
    }
};

struct hospital_system{
hospital_queue queues[MAX_SPECIALIZATION];

    hospital_system()
    {
        for(int i=0;i<MAX_SPECIALIZATION;i++)
        queues[i] = hospital_queue(i);
    }

    void run()
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

    int menu()
    {
        int choice = -1;
        while(choice == -1)
        {
			cout << "Enter your choice:\n";
			cout << "1) Add new patient\n";
			cout << "2) Print all patients\n";
			cout << "3) Get next patient\n";
			cout << "4) Exit\n";

			cin >> choice;

			if (!(choice>0 && choice <= 4))
            {
				cout << "Invalid choice. Try again\n";
				choice = -1;
			}
		}
		return choice;
	}

	void add_patient()
	{
	    int spec, st;
	    string name;
	    cout <<"Enter Patient's Specialization No, Name and Status(0 for Regular, 1 for Urgent)"<< endl;
	    cin >> spec >> name >> st;
	    if(queues[spec].len == MAX_QUEUE)
        {
            cout << "This specialization is full. Try different one" << endl;
            return;
        }
	    if(st == 0)
            queues[spec].add_end(name, st);
        else
            queues[spec].add_front(name, st);
	}

	void  print_patients()
	{
	    for(int spec=0;spec<MAX_SPECIALIZATION;spec++)
            queues[spec].print(spec);
	}

	void get_next_patient()
	{
	    int spec;
	    cout <<"Enter Patient's Specialization : " << endl;
	    cin >> spec;
	    queues[spec].remove_front(spec); // queues[5] mane akhn hospital_queue er specialization 5 tai show korbe, like automatically oi queue te
	}   // spec = 5 (as amra access korechi e 5 diye) and len = spec e joto ache toto

};

int main()
{
    hospital_system hospital //= hospital_system();
    hospital.run();
    return 0;
}
