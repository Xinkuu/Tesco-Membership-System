/***
//// Last Build : 16_4_2020
//// Compiler   : VS2019
//// Programmer : Kieran Saw Kai Ren
//// Capability : Implementing a variable size record.
//// Function   : add, modify, delete, search, display record, exit
***/


/////////////     Includes    /////////////

#include <cstdlib> // system()
#include <conio.h> // getch()
#include <fstream>
#include <sys\stat.h> // stat(status of a file)
#include <iostream>
#include <string>
#include <ctime>
#include <string.h>
#include <sstream>
#include <windows.h> //system.time



using namespace std;


/////////////     Data types    /////////////
int MembershipID = 100;


struct Membership_Record // Membership record
{
    //Declare all variables after this line
    //12 Feb 2020
    int MembershipID;
    string First_name;
    string Last_name;
    string Phone_No;
    char Email[40];
    string Age;
    char Nationality;
    char DateOfBirth[40];
    string IC_No;
    string Mship_Type;
    string Mship_Name;
    string Pass_No;
    char Address1[40];
    string Postcode;
    string BirthPlace;
    string Passexpirydate;
    string Gender;
    string YearIC;
    string GenderIC;
    int IC_Age;
    int IC_Num;
    int IC_Num2;
    int IC_Num3;
    string DateDay;
    string DateMonth;
    int DateYear;
    string States;
    int LocalDay;
    int LocalMonth;
    int LocalYear;
    int LocalSecond;
    int LocalMinute;
    int LocalHour;
    string MemExpiryDate;
    int MshipYear;
    string NationalityYesNo;







    //Don't touch after this line
    bool deleted;
};


/////////////     Variable Declarations & Constants /////////////

#define MEMBERSHIP_FILE_NAME "Memberships.txt" // name of the database file to store Memberships informations

Membership_Record Membership;
char     choice; // for choice in menu
fstream* fs = NULL, * fs1 = NULL;// file streams for files : fs -> 'Membership', fs1 -> 'temp'
bool     deletion = false; // if any record has been deleted


/////////////     Function Prototypes    /////////////

void closeFile(fstream*); // closes a file with its pointer, then deletes the file pointer
bool isFileExist(const char*); // check if a file exists
void SearchICNumber();
int SearchMembershipID;

/////////////     Main    /////////////
int main()
{
    ifstream input;
    input.open("id.txt"), ios::in;
    input >> MembershipID;
    ofstream output;


    while (true)
    {
        do ////// Menu //////
        {
            system("cls"); // clear screen
        mainmenu:
            cout << "\n    < Memberships Database > \n\n";
            cout << "(1) Add a new Record \n";
            cout << "(2) Modify an existing Record\n";
            cout << "(3) Delete an existing Record\n";
            cout << "(4) Search an existing Record \n";
            cout << "(5) Display Records \n";
            cout << "(6) Exit \n\n";
            cout << " Enter a choice (1-6) : " << flush;
            choice = _getch();
        } while (choice < '1' || choice > '6'); // while we have no good(between 1 and 6), show menu again

        system("cls");

        // to modify, delete, search or display records, database file should exist, then we have some records           
        if (choice == '2' || choice == '3' || choice == '4' || choice == '5')
        {
            if (!isFileExist(MEMBERSHIP_FILE_NAME)) // if database file doesn't exist
            {
                cout << "\n Database file ('" << MEMBERSHIP_FILE_NAME << "') doesn't exist, then there are no records." << endl;
                system("pause");
                continue; // show the menu again
            }
        }



        switch (choice)
        {
            int recs_num; // number of records before the record for modifying(deletion)


        case '1': ////// Add Record //////
        loopaddcase:

            cout << "\n\t\t < Entering a new record > ";
            cout << "\n   Enter the following informations for the new record : " << endl;

            //25 Feb
            cout << endl;
            Membership.MembershipID = ++MembershipID;
            cout << "Membership ID\t\t\t: " << Membership.MembershipID << endl;
            if (output.open("id.txt"), ios::out)
            {
                output << MembershipID;
            }
            else cout << "the file is empty.";
            output.close();

            //12 Feb 2020
            cout << "\nFirst name\t\t\t: ";

            getline(cin, Membership.First_name);
            while (Membership.First_name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
            {
                cout << "\n\tError! Please enter in a valid name." << endl;
                cout << "\nFirst name\t\t\t: ";
                getline(cin, Membership.First_name);
            }

            cout << "\nLast name\t\t\t: ";
            getline(cin, Membership.Last_name);

            while (Membership.Last_name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
            {
                cout << "\n\tError! Please enter in a valid name." << endl;
                cout << "\nLast name\t\t\t: ";
                getline(cin, Membership.Last_name);
            }

            cout << "\nPhone number\t\t\t: ";
            cin >> Membership.Phone_No;

            while (Membership.Phone_No.find_first_of("01234567890"))
            {
                cout << "\n\tError! Please enter in a valid phone number." << endl << endl;
                cout << "Phone number\t\t\t: ";
                cin >> Membership.Phone_No;
            }

            cout << "\nEmail\t\t\t\t: ";
            cin.ignore();
            cin.getline(Membership.Email, 40);

            cout << "\nAddress\t\t\t\t: ";
            cin.getline(Membership.Address1, 40);

            cout << "\nPostcode\t\t\t: ";
            cin >> Membership.Postcode;

            while (Membership.Postcode.find_first_of("0123456789") == string::npos || Membership.Postcode.size() != 5)
            {
                cout << "\n\tError! Please only enter exactly 5 numbers." << endl;
                cout << "\nPostcode\t\t\t: ";
                cin >> Membership.Postcode;
            }

            cout << "\nNationality " << endl;
            cout << "\n\t F. Foreigner" << endl << "\n\t M. Malaysian" << endl << "\nEnter F or M\t\t\t: ";
            cin >> Membership.Nationality;
            //24Feb
            while ((Membership.Nationality != 'F' && Membership.Nationality != 'f') && (Membership.Nationality != 'M' && Membership.Nationality != 'm'))
            {
                cout << "\n\tError! Please input either 'f' for foreigner or 'm' for Malaysian.\n" << endl;
                cout << "Nationality\t\t\t: ";
                cin >> Membership.Nationality;
            }

            if (Membership.Nationality == 'M' || Membership.Nationality == 'm')
            {
                cout << endl;
                cout << "\tMalaysian";
                cout << endl;
                cout << "\nIC number\t\t\t: ";
                cin >> Membership.IC_No;
                cout << endl;
                while (Membership.IC_No.find_first_of("0123456789") == string::npos || (Membership.IC_No.size() != 12))
                {
                    cout << "\n\tError! Please only input exactly 12 numbers." << endl << endl;

                    cout << "IC number\t\t\t:";
                    cin >> Membership.IC_No;
                }

                Membership.YearIC = Membership.IC_No.substr(0, 2);
                Membership.GenderIC = Membership.IC_No.substr(8, 4);
                Membership.DateMonth = Membership.IC_No.substr(2, 2);
                Membership.DateDay = Membership.IC_No.substr(4, 2);
                Membership.States = Membership.IC_No.substr(6, 2);

                stringstream geek(Membership.GenderIC);
                geek >> Membership.IC_Num2;

                stringstream IC_No(Membership.YearIC);
                IC_No >> Membership.IC_Num;


                if (Membership.IC_Num < 20 && Membership.IC_Num >= 0)
                {
                    Membership.IC_Age = 20 - (Membership.IC_Num);
                }
                else if (Membership.IC_Num > 20 && Membership.IC_Num <= 99)
                {
                    Membership.IC_Age = 2020 - (Membership.IC_Num + 1900);
                }

                if (Membership.IC_Num2 % 2 == 0)
                {
                    Membership.Gender = "Female";
                }
                else
                {
                    Membership.Gender = "Male";
                }

                switch (stoi(Membership.DateDay))
                {
                case 1:
                    Membership.DateDay = "1"; break;

                case 2:
                    Membership.DateDay = "2"; break;

                case 3:
                    Membership.DateDay = "3"; break;

                case 4:
                    Membership.DateDay = "4"; break;

                case 5:
                    Membership.DateDay = "5"; break;

                case 6:
                    Membership.DateDay = "6"; break;

                case 7:
                    Membership.DateDay = "7"; break;

                case 8:
                    Membership.DateDay = "8"; break;

                case 9:
                    Membership.DateDay = "9"; break;

                case 10:
                    Membership.DateDay = "10"; break;

                case 11:
                    Membership.DateDay = "11"; break;

                case 12:
                    Membership.DateDay = "12"; break;

                case 13:
                    Membership.DateDay = "13"; break;

                case 14:
                    Membership.DateDay = "14"; break;

                case 15:
                    Membership.DateDay = "15"; break;

                case 16:
                    Membership.DateDay = "16"; break;

                case 17:
                    Membership.DateDay = "17"; break;

                case 18:
                    Membership.DateDay = "18"; break;

                case 19:
                    Membership.DateDay = "19"; break;

                case 20:
                    Membership.DateDay = "20"; break;

                case 21:
                    Membership.DateDay = "21"; break;

                case 22:
                    Membership.DateDay = "22"; break;

                case 23:
                    Membership.DateDay = "23"; break;

                case 24:
                    Membership.DateDay = "24"; break;

                case 25:
                    Membership.DateDay = "25"; break;

                case 26:
                    Membership.DateDay = "26"; break;

                case 27:
                    Membership.DateDay = "27"; break;

                case 28:
                    Membership.DateDay = "28"; break;

                case 29:
                    Membership.DateDay = "29"; break;

                case 30:
                    Membership.DateDay = "30"; break;

                case 31:
                    Membership.DateDay = "31"; break;

                default:
                    Membership.DateDay = "N/A"; break;

                }

                switch (stoi(Membership.DateMonth))
                {
                case 1:
                    Membership.DateMonth = "January"; break;

                case 2:
                    Membership.DateMonth = "February"; break;

                case 3:
                    Membership.DateMonth = "March"; break;

                case 4:
                    Membership.DateMonth = "April"; break;

                case 5:
                    Membership.DateMonth = "May"; break;

                case 6:
                    Membership.DateMonth = "June"; break;

                case 7:
                    Membership.DateMonth = "July"; break;

                case 8:
                    Membership.DateMonth = "August"; break;

                case 9:
                    Membership.DateMonth = "September"; break;

                case 10:
                    Membership.DateMonth = "October"; break;

                case 11:
                    Membership.DateMonth = "November"; break;

                case 12:
                    Membership.DateMonth = "December"; break;

                default:
                    Membership.DateMonth = "N/A"; break;
                }

                if (Membership.IC_Num < 20 && Membership.IC_Num >= 0)
                {
                    Membership.DateYear = 2000 + Membership.IC_Num;
                }
                else if (Membership.IC_Num > 20 && Membership.IC_Num <= 99)
                {
                    Membership.DateYear = 1900 + Membership.IC_Num;
                }

                switch (stoi(Membership.States))
                {
                case 1:
                    Membership.States = "Johor"; break;

                case 2:
                    Membership.States = "Kedah"; break;

                case 3:
                    Membership.States = "Kelantan"; break;

                case 4:
                    Membership.States = "Malacca"; break;

                case 5:
                    Membership.States = "Negeri Sembilan"; break;

                case 6:
                    Membership.States = "Pahang"; break;

                case 7:
                    Membership.States = "Penang"; break;

                case 8:
                    Membership.States = "Perak"; break;

                case 9:
                    Membership.States = "Perlis"; break;

                case 10:
                    Membership.States = "Selangor"; break;

                case 11:
                    Membership.States = "Terengganu"; break;

                case 12:
                    Membership.States = "Sabah"; break;

                case 13:
                    Membership.States = "Sarawak"; break;

                case 14:
                    Membership.States = "Kuala Lumpur"; break;

                case 15:
                    Membership.States = "Labuan"; break;

                case 16:
                    Membership.States = "Putrajaya"; break;

                default:
                    Membership.States = "N/A"; break;
                }


                cout << endl;
                cout << "\tInformation collected through IC Number\n";
                cout << "------------------------------------------------------" << endl;
                cout << "Gender                          : " << Membership.Gender << endl;
                cout << "\nAge                             : " << Membership.IC_Age << endl << endl;
                cout << "Date of Birth (Day|Month|Year)  : " << Membership.DateDay << " " << Membership.DateMonth << " " << Membership.DateYear;
                cout << "\n\nState                           : " << Membership.States << endl;
                cout << "------------------------------------------------------" << endl;

            }

            else if (Membership.Nationality == 'F' || Membership.Nationality == 'f')
            {
                cout << endl;

                cout << "\tForeigner";

                cout << "\n\nPassport number(E.g. A123456789): ";
                cin >> Membership.Pass_No;

                while (Membership.Pass_No.find_first_of("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789") == string::npos || (Membership.Pass_No.size() != 10))
                {
                    cout << "\n\tError! Please enter a valid passport number.\n\n";
                    cout << "Passport number\t\t\t: ";
                    cin >> Membership.Pass_No;
                }

                cout << "\nPlace of Birth\t\t\t: ";
                cin >> Membership.BirthPlace;
                getline(cin, Membership.BirthPlace);

                while (Membership.BirthPlace.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"))
                {
                    cout << "\n\tError! Please only input letters." << endl;
                    cout << "\nPlace of Birth\t\t\t: ";
                    cin >> Membership.BirthPlace;
                }

                cout << "\nAge\t\t\t\t: ";
                cin >> Membership.Age;
                //14Feb
                while (Membership.Age.find_first_of("0123456789") == string::npos)
                {

                    cout << "\n\tError! Please only input numbers." << endl;
                    cout << "\nAge\t\t\t\t: ";
                    cin >> Membership.Age;
                }

                cout << "\nDate of Birth (DD/MM/YY)\t: ";
                cin.ignore();
                cin.getline(Membership.DateOfBirth, 40);

                cout << "\nPassport Expiry date\t\t: ";
                getline(cin, Membership.Passexpirydate);



            }

            cout << "\nMembership Type: \n" << endl;
            cout << "\t 1. Diamond" << endl << endl;
            cout << "\t 2. Platnium" << endl << endl;
            cout << "Enter 1 or 2\t\t\t: ";
            cin >> Membership.Mship_Type; '\n';

            while (Membership.Mship_Type.find_first_of("12") || (Membership.Mship_Type.size() != 1))
            {
                cout << "\n\tError! Please input either 1 for diamond or 2 for platnium." << endl;
                cout << "\nMembership Type\t\t\t: ";
                cin >> Membership.Mship_Type; '\n\n';
            }
            cout << endl;

            switch (stoi(Membership.Mship_Type))

            {
            case 1: Membership.Mship_Name = "Diamond"; break; '\n';

            case 2: Membership.Mship_Name = "Platnium"; break; '\n';
            }
            cout << endl;
            SYSTEMTIME It;
            GetLocalTime(&It);
            Membership.LocalDay = (It.wDay);
            Membership.LocalMonth = (It.wMonth);
            Membership.LocalYear = (It.wYear);
            Membership.LocalSecond = (It.wSecond);
            Membership.LocalMinute = (It.wMinute);
            Membership.LocalHour = (It.wHour);

            if (stoi(Membership.Mship_Type) == 1)
            {
                Membership.MshipYear = (It.wYear) + 2;
                cout << "Membership Expiry Date\t\t: " << Membership.LocalDay << " " << Membership.LocalMonth << " " << Membership.MshipYear << endl;
            }
            else if (stoi(Membership.Mship_Type) == 2)
            {
                Membership.MshipYear = (It.wYear) + 1;
                cout << "Membership Expiry Date\t\t: " << Membership.LocalDay << " " << Membership.LocalMonth << " " << Membership.MshipYear << endl;
            }
            cout << "\n------------------------------------------------------" << endl;
            cout << "\nRegistration Date\t\t: " << Membership.LocalDay << "/" << Membership.LocalMonth << "/" << Membership.LocalYear << "|" << Membership.LocalHour << ":" << Membership.LocalMinute << ":" << Membership.LocalSecond << endl;
            cout << endl;
            cout << "------------------------------------------------------" << endl;


            //Don't touch after this line

            Membership.deleted = 0;

            fs = new fstream(MEMBERSHIP_FILE_NAME, ios::out | ios::app | ios::binary);

            if (!fs)
            {
                cout << "\nCan't open or create" << MEMBERSHIP_FILE_NAME << "'file" << endl;
                system("pause");
                break;
            }

            cout << "\nDo you want to save this record?: \n";
            cout << "\n\t1. Yes \n\n\t2. No \n\n\t3. Save and Add";
            cout << endl;
            cout << "\nEnter 1 or 2 or 3\t\t: ";
            char confirm;
        loopadd:
            cin >> confirm;
            cin.ignore();
            system("cls");

            if (confirm == '1')
            {
                fs->write((char*)&Membership, sizeof(Membership));
                closeFile(fs);
                goto mainmenu;
                break;
            }
            if (confirm == '2')
            {
                cout << "Record not added " << endl;
                system("pause");
                goto mainmenu;
                break;
            }
            if (confirm == '3')
            {
                fs->write((char*)&Membership, sizeof(Membership));
                closeFile(fs);

                goto loopaddcase;
            }
            else
            {
                cout << "\n\n\tError!\n";
                cout << "\nPlease enter (1 = Yes 2 = No 3 = Save and Add) To Confirm Add Record.\n";
                cout << "\nDo you want to add this record?\n\n\t1. Yes \n\n\t2. No \n\n\t3. Save and Add\n\n";
                cout << "Enter 1 or 2 or 3\t\t:";
                goto loopadd;
            }




        case '2': ////// Modify Record //////

            system("cls");

            cout << "\n\n";
            cout << "\t\t#Membership Registration for Tesco#" << endl;
            cout << "\t#Update Specific Record#" << endl;

            cout << "\n\n";
            cout << "Enter Membership ID, that you want to update its information: ";
            cin >> SearchMembershipID;
            cin.ignore();

            fs = new fstream(MEMBERSHIP_FILE_NAME, ios::in | ios::out | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << MEMBERSHIP_FILE_NAME << "'file" << endl;
                system("pause");

                break;
            }

            recs_num = -1;

            while (fs->read((char*)&Membership, sizeof(Membership)))
            {
                recs_num++;

                if (SearchMembershipID == Membership.MembershipID && !Membership.deleted) /* if user deleted a driver then added another one
                                                                                 with the same ID in the same instance of program
                                                                                 runs, deleted driver is still there, then we should
                                                                                 go through all the file*/
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
            {
                cout << "\n Your specified Membership doesn't exist in file." << endl;
                closeFile(fs);
                system("pause");
                goto mainmenu;
                break;
            }




        UpdateList:
            cout << "\t\t Membership ID\t\t: " << Membership.MembershipID << endl;
            cout << "Select specific record to update: \n";

            cout << "A. First name\t\t\t: " << Membership.First_name << endl;
            cout << "B. Last name\t\t\t: " << Membership.Last_name << endl;
            cout << "C. Phone number\t\t\t: " << Membership.Phone_No << endl;
            cout << "D. Email\t\t\t: " << Membership.Email << endl;
            cout << "E. Address line 1\t\t: " << Membership.Address1 << endl;
            cout << "F. Postcode\t\t\t: " << Membership.Postcode << endl;
            if (Membership.Nationality == 'M' || Membership.Nationality == 'm')
            {
                cout << "G. Nationality\t\t\t:" << " Malaysian" << endl;
                cout << "H. IC number\t\t\t: " << Membership.IC_No << endl;
            }
            else
            {
                cout << "G. Nationality\t\t\t:" << " Foreigner" << endl;
                cout << "I. Passport number\t\t: " << Membership.Pass_No << endl;
                cout << "J. Place of Birth\t\t: " << Membership.BirthPlace << endl;
                cout << "K. Age\t\t\t\t: " << Membership.Age << endl;
                cout << "L. Date of Birth\t\t: " << Membership.DateOfBirth << endl;
                cout << "M. Passport Expiry date\t\t: " << Membership.Passexpirydate << endl;
            }
            if (stoi(Membership.Mship_Type) == 1)
            {
                cout << "N. Membership type\t\t: Diamond" << endl;
            }
            else
            {
                cout << "N. Membership type\t\t: Platnium" << endl;
            }




            cout << "Enter specific number to update or chance the record, enter 0 to save record: " << endl;

            char choice;
            cin >> choice;

            if (choice == '0')
            {
                goto update;
            }

            switch (choice)
            {

            case 'A'://Update first name

                system("cls");
                cout << "First name\t\t: ";
                cin.ignore();
                getline(cin, Membership.First_name);

                while (Membership.First_name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
                {
                    cout << "\n\tError! Please enter in a valid name." << endl;
                    cout << "\nFirst name\t\t\t: ";
                    getline(cin, Membership.First_name);
                }
                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'B'://Update last name

                system("cls");
                cout << "Last name\t\t: ";
                cin.ignore();
                getline(cin, Membership.Last_name);

                while (Membership.Last_name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
                {
                    cout << "\n\tError! Please enter in a valid name." << endl;
                    cout << "\nLast name\t\t\t: ";
                    getline(cin, Membership.Last_name);
                }
                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'C'://Update Phone number

                system("cls");
                cout << "Phone number\t\t: ";
                cin.ignore();
                cin >> Membership.Phone_No;

                while (Membership.Phone_No.find_first_of("01234567890"))
                {
                    cout << "\n\tError! Please enter in a valid phone number." << endl << endl;
                    cout << "Phone number\t\t\t: ";
                    cin >> Membership.Phone_No;
                }
                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'D'://Update Email

                system("cls");

                cout << "\nEmail\t\t\t\t: ";
                cin.ignore();
                cin.getline(Membership.Email, 40);

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'E'://Update Address

                system("cls");

                cout << "\nAddress\t\t\t: ";
                cin.ignore();
                cin.getline(Membership.Address1, 40);

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;



            case 'F'://Update Postcode

                system("cls");

                cout << "\nPostcode\t\t\t: ";
                cin.ignore();
                cin >> Membership.Postcode;

                while (Membership.Postcode.find_first_of("0123456789") == string::npos || Membership.Postcode.size() != 5)
                {
                    cout << "\n\tError! Please only enter exactly 5 numbers." << endl;
                    cout << "\nPostcode\t\t\t: ";
                    cin >> Membership.Postcode;
                }

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'G'://Update Nationality

                system("cls");

                cout << "\nNationality " << endl;
                cout << "\n\t F. Foreigner" << endl << "\n\t M. Malaysian" << endl << "\nEnter F or M\t\t\t: ";
                cin.ignore();
                cin >> Membership.Nationality;
                cout << endl;
                while ((Membership.Nationality != 'F' && Membership.Nationality != 'f') && (Membership.Nationality != 'M' && Membership.Nationality != 'm'))
                {
                    cout << "\n\tError! Please input either 'f' for foreigner or 'm' for Malaysian.\n" << endl;
                    cout << "Nationality\t\t\t: ";
                    cin >> Membership.Nationality;
                }

                if (Membership.Nationality == 'M' || Membership.Nationality == 'm')
                {
                    cout << "\nIC number\t\t\t: ";
                    cin.ignore();
                    cin >> Membership.IC_No;
                    cout << endl;

                    while (Membership.IC_No.find_first_of("0123456789") == string::npos || (Membership.IC_No.size() != 12))
                    {
                        cout << "\n\tError! Please only input exactly 12 numbers." << endl << endl;

                        cout << "IC number\t\t\t:";
                        cin >> Membership.IC_No;
                    }

                    cout << "To continue update.";
                    system("pause");
                    system("cls");
                    goto UpdateList;
                    break;
                }

                else
                {
                List1:

                    cout << "\tSelect specific record to change for Foreigner\n" << endl;
                    cout << "1. Passport number\t\t: " << Membership.Pass_No << endl;
                    cout << "2. Place of Birth\t\t: " << Membership.BirthPlace << endl;
                    cout << "3. Age\t\t\t\t: " << Membership.Age << endl;
                    cout << "4. Date of Birth\t\t: " << Membership.DateOfBirth << endl;
                    cout << "5. Passport Expiry date\t\t: " << Membership.Passexpirydate << endl;

                    cout << "Press 0 to save record or press 1-5 to change records" << endl;
                    cout << "or 6 to go back to continue updating the record.\n\n";
                    cout << "Answer\t\t\t\t: ";
                    "\b";

                    cin.ignore();
                    int choice1;
                    cin >> choice1;

                    if (choice1 == '0')
                    {
                        goto loopaddcase;
                    }

                    if (choice1 == '6')
                    {
                        goto UpdateList;
                        cout << endl << endl << endl;
                    }
                    switch (choice1)
                    {
                    case 1: //Update Passport number

                        system("cls");
                        cout << "\n\nPassport number (E.g. A123456789)\t\t: ";
                        cin.ignore();
                        cin >> Membership.Pass_No;

                        while (Membership.Pass_No.find_first_of("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789") == string::npos || (Membership.Pass_No.size() != 10))
                        {
                            cout << "\n\tError! Please enter a valid passport number.\n\n";
                            cout << "Passport number\t\t\t: ";

                            cin >> Membership.Pass_No;
                        }
                        cout << "To continue update.";
                        system("pause");
                        system("cls");
                        goto List1;
                        break;




                    case 2://Update Place of Birth

                        system("cls");
                        cout << "\nPlace of Birth\t\t\t: ";
                        cin.ignore();
                        getline(cin, Membership.BirthPlace);

                        while (Membership.BirthPlace.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"))
                        {
                            cout << "\n\tError! Please only input letters." << endl;
                            cout << "\nPlace of Birth\t\t\t: ";
                            getline(cin, Membership.BirthPlace);
                        }

                        cout << "To continue update.";
                        system("pause");
                        system("cls");
                        goto List1;
                        break;


                    case 3://Update Age

                        system("cls");

                        cout << "\nAge\t\t\t\t: ";
                        cin.ignore();
                        cin >> Membership.Age;

                        while (Membership.Age.find_first_of("0123456789") == string::npos)
                        {

                            cout << "\n\tError! Please only input numbers." << endl;
                            cout << "\nAge\t\t\t\t: ";
                            cin >> Membership.Age;
                        }

                        cout << "To continue update.";
                        system("pause");
                        system("cls");
                        goto List1;
                        break;


                    case 4://Update Date of Birth

                        system("cls");

                        cout << "\nDate of Birth (DD/MM/YY)\t: ";
                        cin.ignore();
                        cin.getline(Membership.DateOfBirth, 40);

                        cout << "To continue update.";
                        system("pause");
                        system("cls");
                        goto List1;
                        break;

                    case 5://Update Passport Expiry Date

                        system("cls");

                        cout << "\nPassport Expiry date\t\t: ";
                        cin.ignore();
                        getline(cin, Membership.Passexpirydate);

                        cout << "To continue update.";
                        system("pause");
                        system("cls");
                        goto List1;
                        break;
                    }







                    cout << "To continue update.";
                    system("pause");
                    system("cls");
                    goto UpdateList;
                    break;

            case 'H'://Update IC number

                system("cls");

                cout << "\nIC number\t\t\t: ";
                cin.ignore();
                cin >> Membership.IC_No;
                cout << endl;

                while (Membership.IC_No.find_first_of("0123456789") == string::npos || (Membership.IC_No.size() != 12))
                {
                    cout << "\n\tError! Please only input exactly 12 numbers." << endl << endl;

                    cout << "IC number\t\t\t:";
                    cin >> Membership.IC_No;
                }

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'I'://Update Passport number

                system("cls");

                cout << "\n\nPassport number (E.g. A123456789)\t\t: ";
                cin.ignore();
                cin >> Membership.Pass_No;

                while (Membership.Pass_No.find_first_of("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm0123456789") == string::npos || (Membership.Pass_No.size() != 10))
                {
                    cout << "\n\tError! Please enter a valid passport number.\n\n";
                    cout << "Passport number\t\t: ";

                    cin >> Membership.Pass_No;
                }

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'J'://Update Place of Birth

                system("cls");

                cout << "\nPlace of Birth\t\t\t: ";
                cin.ignore();
                getline(cin, Membership.BirthPlace);

                while (Membership.BirthPlace.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"))
                {
                    cout << "\n\tError! Please only input letters." << endl;
                    cout << "\nPlace of Birth\t\t\t: ";
                    getline(cin, Membership.BirthPlace);
                }

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'K'://Update Age

                system("cls");

                cout << "\nAge\t\t\t\t: ";
                cin.ignore();
                cin >> Membership.Age;

                while (Membership.Age.find_first_of("0123456789") == string::npos)
                {

                    cout << "\n\tError! Please only input numbers." << endl;
                    cout << "\nAge\t\t\t\t: ";
                    cin >> Membership.Age;
                }

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'L'://Update Date of Birth

                system("cls");


                cout << "\nDate of Birth (DD/MM/YY)\t: ";
                cin.ignore();
                cin.getline(Membership.DateOfBirth, 40);


                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'M'://Update Passport Expiry Date

                system("cls");

                cout << "\nPassport Expiry date\t\t\t: ";
                cin.ignore();
                getline(cin, Membership.Passexpirydate);

                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'N'://Update Membership Type

                system("cls");

                cout << "\nMembership Type: \n" << endl;
                cout << "\t 1. Diamond" << endl << endl;
                cout << "\t 2. Platnium" << endl << endl;
                cout << "Enter 1 or 2\t\t\t: ";
                cin.ignore();
                cin >> Membership.Mship_Type; '\n';

                while (Membership.Mship_Type.find_first_of("12") || (Membership.Mship_Type.size() != 1))
                {
                    cout << "\n\tError! Please input either 1 for diamond or 2 for platnium." << endl;
                    cout << "\nMembership Type\t\t\t: ";
                    cin >> Membership.Mship_Type; '\n\n';
                }


                cout << "To continue update.";
                system("pause");
                system("cls");
                goto UpdateList;
                break;
                }

            update:
                fs->seekp(sizeof(Membership) * recs_num, ios::beg); // go to the first of the record to be modified
                fs->write((char*)&Membership, sizeof(Membership));

                closeFile(fs);

                cout << "\n Record is modified." << endl;
                system("pause");
                goto mainmenu;
                break;

            default:
                goto UpdateList;
                break;
            } //end(update)switch



        case '3': ////// Delete Record //////

            system("cls");

            cout << "\n\n";
            cout << "\t\t#Membership Registration for Tesco#" << endl;
            cout << "\t#Delete Specific Record#" << endl;

            cout << "\n\n";
            cout << "Enter Membership ID, that you want to delete its information: ";
            cin >> SearchMembershipID;
            cin.ignore();

            fs = new fstream(MEMBERSHIP_FILE_NAME, ios::in | ios::out | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create" << MEMBERSHIP_FILE_NAME << "file." << endl;
                system("pause");
                break;
            }

            recs_num = -1;
            while (fs->read((char*)&Membership, sizeof(Membership)))
            {
                recs_num++;

                if (SearchMembershipID == Membership.MembershipID && !Membership.deleted)

                    /* If user deleted a driver then added another
                    one with the same Membership ID in the same instance
                    of program runs,deleted driver is still there,
                    then we should go through all the file*/
                    break;
            }

            if (fs->eof()) // if (the record is not in the file or it's there but its deleted)
            {
                cout << "\n Your specified Membership doesn't exist in file." << endl;
                closeFile(fs);
                system("pause");
                goto mainmenu;
                break;
            }

            Membership.deleted = 1;

            fs->seekp(sizeof(Membership) * recs_num, ios::beg);
            fs->write((char*)&Membership, sizeof(Membership));
            closeFile(fs);

            deletion = true; //we have some deleted records
            cout << "\nRecord is deleted." << endl;

            system("pause");
            goto mainmenu;
            break;

        case '4'://Search an existing Record

            system("cls");
        SearchList:
            cout << "\n\n";
            cout << "\t\t#Membership Registration for Tesco#" << endl;
            cout << "\t#Search Specific Record#" << endl;

            cout << "\n\n";
            cout << "Enter Membership ID, that you want to search its information: ";
            cin >> SearchMembershipID;
            cin.ignore();

            fs = new fstream(MEMBERSHIP_FILE_NAME, ios::in | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << MEMBERSHIP_FILE_NAME << "'file" << endl;
                system("pause");

                break;
            }

            recs_num = -1;

            while (fs->read((char*)&Membership, sizeof(Membership)))
            {
                recs_num++;

                if (SearchMembershipID == Membership.MembershipID && !Membership.deleted) /* if user deleted a driver then added another one
                                                                                 with the same ID in the same instance of program
                                                                                 runs, deleted driver is still there, then we should
                                                                                 go through all the file*/
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
            {
                cout << "\n Your specified Membership doesn't exist in file." << endl;
                closeFile(fs);
                system("pause");
                goto mainmenu;
                break;
            }
            fs->seekp(sizeof(Membership) * recs_num, ios::beg); //go to the searched record
            fs->read((char*)&Membership, sizeof(Membership)); //display the searched record

            if (!Membership.deleted)
            {
                cout << "\t\t Membership ID\t\t: " << Membership.MembershipID << endl;
                cout << "Search an existing record: \n";

                cout << "First name\t\t\t: " << Membership.First_name << endl;
                cout << "Last name\t\t\t: " << Membership.Last_name << endl;
                cout << "Phone number\t\t\t: " << Membership.Phone_No << endl;
                cout << "Email\t\t\t\t: " << Membership.Email << endl;
                cout << "Address\t\t\t\t: " << Membership.Address1 << endl;
                cout << "Postcode\t\t\t: " << Membership.Postcode << endl;
                if (Membership.Nationality == 'M' || Membership.Nationality == 'm')
                {
                    cout << "Nationality\t\t\t:" << " Malaysian" << endl;
                    cout << "IC number\t\t\t: " << Membership.IC_No << endl;
                    cout << "Gender\t\t\t\t: " << Membership.Gender << endl;
                    cout << "Age \t\t\t\t: " << Membership.IC_Age << endl;
                    cout << "Date of Birth (Day|Month|Year)\t: " << Membership.DateDay << " " << Membership.DateMonth << " " << Membership.DateYear;
                    cout << "\nState\t\t\t\t: " << Membership.States << endl;
                }
                else
                {
                    cout << "Nationality\t\t\t:" << " Foreigner" << endl;
                    cout << "Passport number\t\t\t: " << Membership.Pass_No << endl;
                    cout << "Place of Birth\t\t\t: " << Membership.BirthPlace << endl;
                    cout << "Age\t\t\t\t: " << Membership.Age << endl;
                    cout << "Date of Birth\t\t\t: " << Membership.DateOfBirth << endl;
                    cout << "Passport Expiry date\t\t: " << Membership.Passexpirydate << endl;
                }
                if (stoi(Membership.Mship_Type) == 1)
                {
                    cout << "Membership type\t\t\t: Diamond" << endl;
                }
                else
                {
                    cout << "Membership type\t\t\t: Platnium" << endl;
                }

                cout << "Registration Date\t\t: " << Membership.LocalDay << "/" << Membership.LocalMonth << "/" << Membership.LocalYear << "|" << Membership.LocalHour << ":" << Membership.LocalMinute << ":" << Membership.LocalSecond << endl;

                cout << endl;
            }
            cout << "\nTo return to menu.";
            system("pause");
            closeFile(fs);
            goto mainmenu;
            break;

        case '5': // Display Records

              ////// Print Membership records...

            system("cls");

            cout << "\n\n";
            cout << "\t\t#Membership Registration for Tesco#" << endl;
            cout << "\t#Display All Records#" << endl;
            cout << "\n\n";

            fs = new fstream(MEMBERSHIP_FILE_NAME, ios::in | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << MEMBERSHIP_FILE_NAME << "' file." << endl;
                system("pause");
                break;
            }

            while (fs->read((char*)&Membership, sizeof(Membership))) // display records
            {
                if (!Membership.deleted)
                {
                    cout << "\t\t Membership ID\t\t: " << Membership.MembershipID << endl;
                    cout << "Search an existing record: \n";

                    cout << "First name\t\t\t: " << Membership.First_name << endl;
                    cout << "Last name\t\t\t: " << Membership.Last_name << endl;
                    cout << "Phone number\t\t\t: " << Membership.Phone_No << endl;
                    cout << "Email\t\t\t\t: " << Membership.Email << endl;
                    cout << "Address\t\t\t\t: " << Membership.Address1 << endl;
                    cout << "Postcode\t\t\t: " << Membership.Postcode << endl;
                    if (Membership.Nationality == 'M' || Membership.Nationality == 'm')
                    {
                        cout << "Nationality\t\t\t:" << " Malaysian" << endl;
                        cout << "IC number\t\t\t: " << Membership.IC_No << endl;
                        cout << "Gender\t\t\t\t: " << Membership.Gender << endl;
                        cout << "Age \t\t\t\t: " << Membership.IC_Age << endl;
                        cout << "Date of Birth (Day|Month|Year)\t: " << Membership.DateDay << " " << Membership.DateMonth << " " << Membership.DateYear;
                        cout << "\nState\t\t\t\t: " << Membership.States << endl;
                    }
                    else
                    {
                        cout << "Nationality\t\t\t:" << " Foreigner" << endl;
                        cout << "Passport number\t\t\t: " << Membership.Pass_No << endl;
                        cout << "Place of Birth\t\t\t: " << Membership.BirthPlace << endl;
                        cout << "Age\t\t\t\t: " << Membership.Age << endl;
                        cout << "Date of Birth\t\t\t: " << Membership.DateOfBirth << endl;
                        cout << "Passport Expiry date\t\t: " << Membership.Passexpirydate << endl;
                    }
                    if (stoi(Membership.Mship_Type) == 1)
                    {
                        cout << "Membership type\t\t\t: Diamond" << endl;
                    }
                    else
                    {
                        cout << "Membership type\t\t\t: Platnium" << endl;
                    }

                    cout << "Registration Date\t\t: " << Membership.LocalDay << "/" << Membership.LocalMonth << "/" << Membership.LocalYear << "|" << Membership.LocalHour << ":" << Membership.LocalMinute << ":" << Membership.LocalSecond << endl;

                    cout << endl;
                }
            }

            cout << "\nTo return to menu,";
            system("pause");
            closeFile(fs);
            goto mainmenu;
            break;



        case '6': // Exit

            if (deletion) // if there is any deletion, then update database file (create a new temp file that doesn't have deleted records, then remove the old database file and rename temp file to database file name)
            {
                cout << "\n Updating '" << MEMBERSHIP_FILE_NAME << "' File..." << endl;

                fs = new fstream(MEMBERSHIP_FILE_NAME, ios::in | ios::binary);
                if (!fs)
                {
                    cout << "\n Can't open '" << MEMBERSHIP_FILE_NAME << "' file, then Updating is incomplete." << endl;
                    system("pause");

                    system("cls");
                    return 1;
                }

                fs1 = new fstream("temp", ios::out | ios::binary);
                if (!fs1)
                {
                    cout << "\n Can't create temp file, then Updating is incomplete." << endl;
                    system("pause");

                    closeFile(fs);
                    system("cls");
                    return 1;
                }

                // write nondeleted records to the temp file
                while (fs->read((char*)&Membership, sizeof(Membership)))
                    if (!Membership.deleted)
                        fs1->write((char*)&Membership, sizeof(Membership));

                closeFile(fs);
                closeFile(fs1);

                if (remove(MEMBERSHIP_FILE_NAME) == -1) // if there is an error
                {
                    cout << "\n Can't delete '" << MEMBERSHIP_FILE_NAME << "' file, then Updating is incomplete." << endl;
                    system("pause");

                    system("cls");
                    return 1;
                }


                struct stat st; // to check size of the temp file
                int res = stat("temp", &st);

                if (st.st_size == 0) // if all of records are deleted then the temp file size is zero                        
                    remove("temp"); // we have no records, then no database file is needed, just delete the temp file
                else
                    if (rename("temp", MEMBERSHIP_FILE_NAME))
                    {
                        cout << "\n Can't rename temp file, then Updating is incomplete." << endl;
                        system("pause");

                        system("cls");
                        return 1;
                    }

                cout << "\n Updating database file completed." << endl;
                system("pause");
            }

            system("cls");
            //Exit Splash Screen
            system("cls");
            cout << "\n";
            cout << "\n";
            cout << "\t*This membership registration system*" << endl;
            cout << "\t*is created by*" << endl;
            cout << "\t*Mr.Kieran Saw Kai Ren*" << endl;
            cout << "\t*Thank you for using my code*" << endl;
            cout << "\tGoodbye!";
            return 0;
            break;

        } // end 'switch'
    } // end 'while'

    return 0;
}     // end 'main()'


/////////////     Function Definitions    /////////////

void closeFile(fstream* fs)
{
    fs->close(); // close the file
    delete fs;
    fs = NULL;
}


bool isFileExist(const char* file_name)
{
    struct stat st; // to check status of file
    int res = stat(file_name, &st);
    return (res == 0); // if file exists     
}
