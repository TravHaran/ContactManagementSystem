#include <iostream>
// #include <conio.h>
#include <fstream>

using namespace std;

class contact {
    private:
        char fName[50], lName[50], address[50], email[50];
        long long phNo;
    public:
        void createContact() {
            cout<<"Enter your first name: ";
            cin>>fName;

            cout<<"Enter your last name: ";
            cin>>lName;

            cout<<"Enter your phone number: ";
            cin>>phNo;

            cout<<"Enter address: ";
            cin>>address;

            cout<<"Enter email: ";
            cin>>email;
        }

        void showContact() {
            cout<<"Name: " <<fName<<" "<<lName<<endl;
            cout<<"Phone: " <<phNo<<endl;
            cout<<"Address: " <<address<<endl;
            cout<<"Email: " <<email<<endl;
        }

        void writeOnFile() {
            char ch;
            ofstream f1;
            f1.open("CMS.dat", ios::binary | ios::app);

            do {
                createContact();
                f1.write(reinterpret_cast<char*>(this), sizeof(*this));
                cout<<"Do you have next data?(y/n)";
                cin>>ch;
            }while(ch=='y');

            cout<<"Contact has been Successfully Created...";
            f1.close();
        }

        void readFromFile() {
            ifstream f2;
            f2.open("CMS.dat", ios::binary);

            cout<<"\n===========================================\n";
            cout<<"LIST OF CONTACT";
            cout<<"\n===========================================\n";

            while(!f2.eof()) {
                if(f2.read(reinterpret_cast<char*>(this), sizeof(*this)
                )) {
                    showContact();
                    cout<<"\n===========================================\n";
                }
                f2.close();
            }
        }

        void searchOnFile() {
            ifstream f3;
            long long phone;
            cout<<"Enter phone no.";
            cin>>phone;
            f3.open("CMS.dat", ios::binary);

            while(!f3.eof()) {
                if(f3.read(reinterpret_cast<char*>(this), sizeof(*this)
                )) {
                    if(phone == phNo) {
                        showContact();
                        return;
                    }
                }
            }
            cout<<"\n\n No record found";
            f3.close();
        }

        void deleteFromFile() {
            long long phone;
            int flag = 0;
            ofstream f4;
            ifstream f5;

            f5.open("CMS.dat", ios::binary);
            f4.open("temp.dat", ios::binary);

            cout<<"Enter phone no. to delete: ";
            cin>>phone;

            while(!f5.eof()) {
                if(f5.read(reinterpret_cast<char*>(this), sizeof(*this)
                )) {
                    if(phNo != phone) {
                        f4.write(reinterpret_cast<char*>(this), sizeof(*this));
                    }
                    else flag = 1;
                }
            }
            f5.close();
            f4.close();
            remove("CMS.dat");
            rename("temp.dat", "CMS.dat");

            flag == 1 ?
            cout<<"\tContact Deleted...":
            cout<<"\tContact Not Found...";
        }

        void editContact() {
            long long phone;
            fstream f6;

            cout<<"Edit contact";
            cout<<"\n===========================================\n";
            cout<<"Enter the phone number to be edit: ";
            cin>>phone;

            f6.open("CMS.dat", ios::binary|ios::out|ios::in);

            while(!f6.eof()) {
                if(f6.read(reinterpret_cast<char*>(this), sizeof(*this)
                )) {
                    if(phone == phNo) {
                        cout<<"Enter new record\n";
                        createContact();

                        int pos = -1*sizeof(*this);
                        f6.seekp(pos, ios::cur);
                        f6.write(reinterpret_cast<char*>(this), sizeof(*this));
                        cout<<endl<<endl<<"\tContact Successfully Updated...";
                        return;
                    }
                }
            }
            cout<<"\n\nNo Record found";
            f6.close();
        }
};

int main() {
    system("clear");
    system("Color 3F"); // Color XY, X = background color, Y = text color

    cout<<"\n\n\n\n\n\n\n\t\t * WELCOME TO THE CONTACT MANAGEMENT SYSTEM *";
    getchar();

    while(1) {
        contact c1;
        int choice;

        system("clear");
        system("Color 03");

        cout<<"\nCONTACT MANAGEMENT SYSTEM";
        cout<<"\n\nMAIN MENU";
        cout<<"\n===========================================\n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] List all Contacts\n";
        cout<<"[3] Search for Contact\n";
        cout<<"[4] Delete a Contact\n";
        cout<<"[5] Edit a Contact\n";
        cout<<"[0] Exit";
        cout<<"\n===========================================\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice) {
            case 1:
            system("clear");
            c1.writeOnFile();
            break;

            case 2:
            system("clear");
            c1.readFromFile();

            case 3:
            system("clear");
            c1.searchOnFile();

            case 4:
            system("clear");
            c1.deleteFromFile();

            case 5:
            system("clear");
            c1.editContact();


            case 0:
            system("clear");
            cout<<"\n\n\n\t\t\t Thank you for using CMS."<<endl<<endl;
            exit(0);
            break;

            default:
            continue;
        }

        int opt;
        cout<<"\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin>>opt;

        switch(opt) {
            case 0:
            system("clear");
            cout<<"\n\n\n\t\t\t Thank you for using CMS."<<endl<<endl;
            exit(0);
            break;

            default:
            continue;
        }
    }

    return 0;

}