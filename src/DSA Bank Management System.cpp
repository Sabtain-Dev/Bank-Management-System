#include <iostream>		//Added for input/output	
#include <fstream>		 //Added for reading and writing files
#include <iomanip>		//Added for setwidth and set precision
#include <algorithm> //Added for all_of function and auto function
#include <conio.h>  //Added for getch() function
#include <thread>  // Required for std::this_thread::sleep_for
//#include <ctime>

using namespace std;

void sleep_for(unsigned int milliseconds)
{
    this_thread::sleep_for( chrono::milliseconds(milliseconds));
//makes the current thread to sleep for the specified number of milliseconds,so that the program does not exit before the thread completes its execution.
    
}

// Customer structure representing a bank account
struct Customer {
    char name[50];
    int accountNumber;
    double balance;
    char password[20];
    char email[20];
    char address[50];
    char phoneNumber[15];
    char accountType[5];
    Customer* next;
    Customer* prev;
};

// Function prototypes
void displayMenu();
void createAccount();
void deleteAccount();
bool validatePassword(Customer* customer);
bool validateEmail(const char* email);
bool isNumber(const char* str);
bool isPositiveNumber(const char* str);
bool isValidPhoneNumber(const char* str);
bool isValidAccountType(const char* str);
bool accountExists(int accountNumber);
void hidePasswordInput(char* password, int maxSize);
void displayAllAccounts();
void deposit();
void withdraw();
void searchAccount();
void transferMoney();
void displayAccountNumbers();
void sortAccounts();
void loadAccounts();
void saveAccounts();
void cleanup();

// Global variables
Customer* head = nullptr;

int main() {
    loadAccounts();  // Load existing accounts from file

    int choice;
    do {					//The do-while loop is a post-test loop, meaning that it checks the loop condition after executing the loop body
        displayMenu();
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deleteAccount();
                break;
            case 3:
                searchAccount();
                break;
            case 4:
                transferMoney();
                break;
            case 5:
                deposit();
                break;
            case 6:
                withdraw();
                break;
            case 7:
                sortAccounts();
                break;
            case 8:
                displayAllAccounts();
                break;
            case 9:
                saveAccounts();  // Save accounts to file before exiting
                cout << "\nyour request is being processed please wait";
                cout << ".";
                sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
                cout << ".";
                sleep_for(500);
                cout << ".";
                sleep_for(2000);
                system("cls");//To clean the screen from speech
                cout << ".";
                sleep_for(500);
                cout << ".";
                sleep_for(500);
                cout << ".";
                system("cls");
                sleep_for(500);
                cout << ".";
                sleep_for(500);
                cout << ".";
                sleep_for(500);
                cout << ".";
                system("cls");
                cout << "\t\t\t\t\tTHANK YOU \n\t\t\t\t    FOR BANKING WITH US\n";
                cleanup();  // Cleanup allocated memory
                break;
            default:
                cout << "\nInvalid Choice. Please Try Again\n";
        }
    } while (choice != 9);

    return 0;
}

void hidePasswordInput(char* password, int maxSize) {
    char ch;
    int i = 0;
    while (i < maxSize - 1) {
        ch = getch();  // Hide the input

        if (ch == 13) {  // Enter key in ASCII
            break;
        } else if (ch == 8) {  // Backspace key in ASCII
            if (i > 0) {
                cout << "\b \b";  // Move the cursor back, erase the character, and move back again
                i--;
            }
        } else {
            password[i++] = ch;
            cout << '*';
        }
    }
    password[i] = '\0';  // Null-terminate the password array to mark its end.
}
 
bool validatePassword(Customer* customer) {
    char enteredPassword[20];
    cout << "			Enter account password 		=	";
    hidePasswordInput(enteredPassword, sizeof(enteredPassword)); //Function Call Hide Password
    return strcmp(customer->password, enteredPassword) == 0; // strcmp used for comparing two strings
}

void displayMenu() {
	sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
	sleep_for(5000);
	system("cls"); //time delay
        
	cout << "\t\t\t\t**************************************" << endl;
    cout << "\n\t\t\t\t\tBank Management System\n";
    cout << "\n\t\t\t\t**************************************" << endl;
    cout << "\t\t\t\t*\t1. Create Account            *\n";
    cout << "\t\t\t\t*\t2. Delete Account            *\n";        
    cout << "\t\t\t\t*\t3. Search Account            *\n";
    cout << "\t\t\t\t*\t4. Transfer Money            *\n";
    cout << "\t\t\t\t*\t5. Deposit                   *\n";
    cout << "\t\t\t\t*\t6. Withdraw                  *\n";
    cout << "\t\t\t\t*\t7. Sort Accounts             *\n";
    cout << "\t\t\t\t*\t8. Display All Accounts      *\n";
    cout << "\t\t\t\t**************************************" << endl;
    cout << "\t\t\t\t*\t9. Exit                      *\n";
    cout << "\t\t\t\t**************************************" << endl;
}

void createAccount() {
    system("cls");

    // Seed the random number generator with the current time
    srand(static_cast<unsigned>(time(nullptr)));

    Customer* newCustomer = new Customer;

    // Get customer name
    while (true) {
        cout << "\nLoading";
        cout << ".";
        sleep_for(1000);
        cout << ".";
        sleep_for(500);
        cout << ".";
        sleep_for(2000);
        system("cls");
        cout << "\t\t\t\t*******************************" << endl;
        cout << "\t\t\t\t*\t CREATE ACCOUNTS      *" << endl;
        cout << "\t\t\t\t*******************************" << endl;
        cout << "\n\n			Enter customer name 			 = 	";
        string name;
        cin.ignore();
        getline(cin, name);	//It checks if a specified condition holds true for all elements in the given range (here, the characters in the name string)
							//[](char c) { return ::isalpha(c) || ::isspace(c); }: This is a lambda function (anonymous function) that takes a character
        if (all_of(name.begin(), name.end(), [](char c) { return ::isalpha(c) || ::isspace(c); })) {		//c as a parameter and returns true
            strncpy(newCustomer->name, name.c_str(), sizeof(newCustomer->name));
            break; // if c is an alphabetic character (isalpha(c)) or a space character (isspace(c)). The lambda function checks whether each character in the
        } else {																// if c is an alphabet string satisfies the specified conditions
            cout << "\nPlease enter a valid name (e.g Ali)\n";
        }
    }

    // Input and validate email address                                          //The strncpy function copies characters from name.c_str() to
    while (true) {																//newCustomer->name, ensuring that it doesn't exceed the size 
        cout << "			Enter email address 			 = 	";				//specified by sizeof(newCustomer->name). This helps prevent 
        cin >> newCustomer->email;												//buffer overflow by limiting the number of characters copied to the size of
		if (!validateEmail(newCustomer->email)) {								//the destination array.        
//            cout << "Invalid";
        } else {
            break;
        }
    }

    // Get and validate phone number
    while (true) {
        cout << "			Enter phone number 			 = 	";
        string phoneNumber;
        cin >> phoneNumber;
////It checks if a specified condition holds true for all elements in the given range
        if (all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit) && phoneNumber.size() == 11 &&
            phoneNumber.compare(0, 4, "0300") >= 0 && phoneNumber.compare(0, 4, "0350") <= 0) {
            strncpy(newCustomer->phoneNumber, phoneNumber.c_str(), sizeof(newCustomer->phoneNumber));
            break;
        } else {
            cout << "\nInvalid Phone Number (e.g., 03174856933).\n";
        }
    }

    // Input address (allowing numbers, strings, and characters)
    cout << "			Enter address 				 = 	";
    cin.ignore();   															//It is used to ignore characters in the input buffer, typically 
    cin.getline(newCustomer->address, sizeof(newCustomer->address));            // to discard unwanted characters like newline characters

    // Input and hide account password
    cout << "			Set account password (max 20 characters) =	";
    char ch;
    int i = 0;
    while (i < sizeof(newCustomer->password) - 1) {
        ch = getch();  // Hide the input

        if (ch == 13) {  // Enter key
            break;
        } else if (ch == 8) {  // Backspace key
            if (i > 0) {
                cout << "\b \b";  // Move the cursor back, erase the character, and move back again
                i--;
            }
        } else {
            newCustomer->password[i++] = ch;
            cout << '*';
        }
    }
    newCustomer->password[i] = '\0';  // Null-terminate the password

    // Input and validate initial balance
    while (true) {
        cout << "\n			Enter initial balance 			 = 	$";
        cin >> newCustomer->balance;
////cin.fail(): Checks if the input operation failed. It returns true if the last input operation failed
        if (cin.fail() || newCustomer->balance < 0 || newCustomer->balance > 1000000) {
            cout << "\nInvalid initial balance. Please enter a valid amount.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }	//This line discards any remaining characters in the input buffer up to and including the newline character ('\n'). It ensures that any invalid input is
											// cleared from the buffer before attempting further input.
    // Get and validate account type
    while (true) {
        cout << "			Enter account type = " << endl;
        cout << "				1. Saving 	" << endl;
        cout << "				2. Current	" << endl;
        cout << "				3. Default 			 = 	";
        int accountType;
        cin >> accountType;

        if (cin.fail() || accountType < 1 || accountType > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a valid account type (1, 2, or 3).\n";
        } else {
            switch (accountType) {		//it's about managing memory properly while storing information.
                case 1:
                    strncpy(newCustomer->accountType, "Saving", sizeof(newCustomer->accountType));
                    break;
                case 2:
                    strncpy(newCustomer->accountType, "Current", sizeof(newCustomer->accountType));
                    break;
                case 3:
                    strncpy(newCustomer->accountType, "Default", sizeof(newCustomer->accountType));
                    break;
            }
            break;
        }
    }

    newCustomer->accountNumber = rand() % 1000 + 1000;  // Random account number
    newCustomer->next = nullptr;
    newCustomer->prev = nullptr;

    if (head == nullptr) {
        head = newCustomer;
    } else {
        Customer* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newCustomer;
        newCustomer->prev = current;
    }
// It establishing a bidirectional link by storing the pointer to the previous node.
    cout << "			Your Account number 			 = 	" << newCustomer->accountNumber << "\n";
    cout << "\t\t\t\t\n\nYour Account has been Created.\n" << endl;
    saveAccounts();
    sleep_for(500);
    sleep_for(5000);
    system("cls");
}

bool validateEmail(const char* email) {
    // Validate email format: should contain exactly one '@' and at least one '.' with a non-empty domain part
    int atCount = 0;
    int dotCount = 0;
    int atIndex = -1; // Track the index of the '@' symbol
    bool domainPartExists = false;

    for (int i = 0; email[i] != '\0'; ++i) {
        if (email[i] == '@') {
            atCount++;
            atIndex = i;
        } else if (email[i] == '.') {
            dotCount++;
            if (atIndex != -1 && i > atIndex + 1) {
                domainPartExists = true;
            }
        }
    }

    if (atCount != 1 || dotCount < 1 || atIndex == 0 || atIndex == strlen(email) - 1 || !domainPartExists) {
        cout <<"\nInvalid Email Format (e.g ali@gmail.com)\n";
        return false;
    }

    // Validate email content: no numbers, negative sign, or spaces
    for (int i = 0; email[i] != '\0'; ++i) {
        if (!isalpha(email[i]) && email[i] != '@' && email[i] != '.' && email[i] != '_') {
            cout << "Example: ahmed@example.com\n";
            return false;
        }
    }

    return true;
}

bool isPositiveInteger(const string& str) {
    for (char ch : str) {											//Iterates through each character in the string using a range-based for loop
        if (!isdigit(ch)) {  
            return false;
        }
    }
    return true;
}

int getPositiveIntegerInput() {
    string input;
    while (true) {
        cin >> input;
        if (isPositiveInteger(input)) {
            return stoi(input);			//If the input is a positive integer, it converts the string to an integer using stoi and returns the result
        } else {
            cout << "Invalid input.\n			Please enter a valid input 	=	";
        }
    }
}

void deleteAccount() {
    system("cls");
    if (head == nullptr) {
        cout << "\n\nNo accounts available right now! \n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    cout << "\nSelect account to delete:\n";
    displayAllAccounts();
	cout << "\n\n		****************************************************"<< endl;
    cout << "\n			Enter account number 		=	";
    int accountNumber = getPositiveIntegerInput();

    Customer* current = head;
    while (current != nullptr) {  							//Enters a while loop to iterate through the linked list
        if (current->accountNumber == accountNumber) {
            if (validatePassword(current)) {
                if (current->prev == nullptr) {        //current->prev == nullptr: This condition checks if the current node is the head of 
                    head = current->next;			//the linked list. If it is, it means there is no previous node, so updating head to current->next 
                } else {							//effectively removes the current node from list and next node become new head
                    current->prev->next = current->next;
                }

                if (current->next != nullptr) {		//If the current node is not the head, it means there is a previous node (current->prev is not nullptr).
                    current->next->prev = current->prev;  //In this case, we need to update the next pointer of the previous node to skip the current node.
                }	//If there is, it updates the prev pointer of the next node to skip the current node.

                delete current;
                cout << "\n\nAccount has been deleted.\n";
                saveAccounts();  // Save accounts to file after deletion
                sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
			    sleep_for(5000);
			    system("cls");
                return;
            	} else {
                cout << "\n\nIncorrect password. Access denied.\n";
                sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
			    sleep_for(5000);
			    system("cls");
                return;
            }
        }
        current = current->next;
    }

    cout << "\nAccount not found.\n";
    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
	sleep_for(5000);
	system("cls");
			    
}

void displayAllAccounts() {
    system("cls");
    if (head == nullptr) {
        cout << "\n*******************************" << endl;
        cout << "\nNo accounts available.\n";
        cout << "\n*******************************" << endl;
        sleep_for(500);
        sleep_for(5000);
        system("cls");
        return;
    }

    cout << "\n				***********************************" << endl;
    cout << "					  All Accounts:";
    cout << "\n				***********************************" << endl;
    cout << "\n\n";
    cout << setw(20) << "Account Number" << setw(20) << "Customer Name" << setw(20) << "Email"
         << setw(20) << "Phone Number" << setw(20) << "Address" << setw(20) << "Balance" << setw(20) << "Account Type" << "\n";
    cout << setfill('-') << setw(140) << "\n" << setfill(' ');

    Customer* current = head;
    while (current != nullptr) {
        cout << setw(20) << current->accountNumber << setw(20) << current->name << setw(20) << current->email
             << setw(20) << current->phoneNumber << setw(20) << current->address << setw(20) << fixed << setprecision(2)
             << current->balance << setw(20) << current->accountType << "\n";

        current = current->next;
    }

    // Prompt user to continue
    string continueOption;
    cout << "\nDo you want to continue? (yes/no): ";
    cin >> continueOption;

    // Validate user input
    while (true) {
        if (continueOption == "yes" || continueOption == "y") {
            return;
        } else if (continueOption == "no" || continueOption == "n") {
            // Terminate the program
	        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
			sleep_for(5000);
			system("cls");
	        cout << "\n\n\t\t\tTHANK YOU FOR BANKING WITH US. HAVE A GREAT DAY!\n";
            exit(0);
        } else {
            // Invalid input, ask again
            cout << "\nInvalid input. Please enter 'yes' or 'no': ";
            cin >> continueOption;
        }
    }
}

void deposit() {
    system("cls");
    
    if (head == nullptr) {
        cout << "\nNo accounts available. Create your account first.\n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
		return;
    }

    int accountNumber;
    cout << "\n";
    displayAllAccounts();
    cout << "\n\n       			**************************************************************"<< endl;
    cout << "\n			Enter account number	 	=	";

    // Validate account number
    while (true) {
        cin >> accountNumber;

        if (accountNumber < 0 || cin.fail()) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input" <<endl;
            cout << "			Re-enter account number 	=	";
        } else {
            break; 																		//cin.fail(): Checks if the input operation failed. It returns true if the last input operation failed (e.g., if the user entered a character instead of an integer).
		}																				//cin.clear(): Clears the error state of the stream. If there was a previous error, this line resets the error flag so that future input operations can be attempted.
    }      																				//numeric_limits<streamsize>::max(): Represents the maximum value that can be held by a variable of type streamsize. In this context, it indicates that we want to ignore the maximum number of characters in the input buffer.
     																					//cin.ignore(numeric_limits<streamsize>::max(), '\n'): Ignores the remaining characters in the input buffer up to and including the newline character ('\n'). This is necessary to discard the invalid input and prepare for the next input operation.
    Customer* current = head;
    while (current != nullptr) {
        if (current->accountNumber == accountNumber) {
            if (validatePassword(current)) {
                double amount;
                cout << "\n			Enter deposit amount 		=	$";
                cin >> amount;

                if (amount <= 0) {
                    cout << "Invalid deposit amount.\n";
                    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
					sleep_for(5000);
					system("cls");
                    return;
                }

                current->balance += amount;
                cout << "\nDeposit successful. Updated balance: $" << fixed << setprecision(2) << current->balance << "\n";
                 saveAccounts();  // Save accounts to file after deposit
                sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
				sleep_for(5000);
				system("cls");
                return;
            } else {
                cout << "\nIncorrect password. Access denied.\n";
                sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
				sleep_for(5000);
				system("cls");
                return;
            }
        }
        current = current->next;
    }

    cout << "\nAccount not found.\n";
    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
	sleep_for(5000);
	system("cls");
}

void withdraw() {
    system("cls");

    if (head == nullptr) {
        cout << "\nNo accounts available. Create your account first.\n";
	    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    int accountNumber;
    displayAllAccounts();
    cout << "\n\n       			**************************************************************"<< endl;
    cout << "\n			Enter account number 		= 	";

    // Validate account number
    while (true) {
        cin >> accountNumber;

        if (accountNumber < 0 || cin.fail()) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input" <<endl;
            cout << "			Re-enter account number 	=	";
        } else {
            break;
        }
    }

    Customer* current = head;
    while (current != nullptr) {
        if (current->accountNumber == accountNumber) {
            if (validatePassword(current)) {
                double amount;
                cout << "\n			Enter withdrawal amount		= 	$";
                cin >> amount;

                if (amount <= 0 || amount > current->balance) {
                    cout << "\nInvalid withdrawal amount or insufficient balance.\n";
            	    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
					sleep_for(5000);
					system("cls");
                    return;
                }

                // Apply withdrawal charges
                amount += 10;
                current->balance -= amount;

                // Ensure the updated balance is not negative
                current->balance = max(0.0, current->balance); //It ensures that current->balance is set to the maximum of 0.0 and its current
//It ensures that current->balance is set to the maximum of 0.0 and its current value. If current->balance is negative, it will be set to 0.0.
                cout << "\nWithdrawal successful. Updated balance: $" << fixed << setprecision(2) << current->balance << " + TAX\n"; // If it's already greater
                 saveAccounts();  // Save accounts to file after withdrawal											//than or equal to 0.0, it remains unchanged
		        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
				sleep_for(5000);
				system("cls");
                return;
            } else {
                cout << "\nIncorrect password. Access denied.\n";
                sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
				sleep_for(5000);
				system("cls");
                return;
            }
        }
        current = current->next;
    }

    cout << "\nAccount not found.\n";
    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
	sleep_for(5000);
	system("cls");
}

void searchAccount() {
    system("cls");

    if (head == nullptr) {
        cout << "\nNo accounts available. First, create an account.\n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
		return;
    }

    cout << "\nAvailable Account Numbers:\n";
    displayAccountNumbers();

    int accountNumber;
    cout << "			*****************************************************"<< endl;
    cout << "\n			Enter account number to search		=	 ";

    // Validate account number
    while (true) {
        cin >> accountNumber;

        if (accountNumber < 0 || cin.fail() || !accountExists(accountNumber)) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input"<<endl;
			cout << "			Please enter a valid account number	=	 ";
        } else {
            break;
        }
    }

    Customer* current = head;
    while (current != nullptr) {
        if (current->accountNumber == accountNumber) {
        	cout << "\n";
            cout << "Account found:\n";
            cout << "\nAccount Number 		= " << current->accountNumber << "\n";
            cout << "Customer Name	    	= " << current->name << "\n";
            cout << "Email			= " << current->email << "\n";
            cout << "Phone Number		= " << current->phoneNumber << "\n";
            cout << "Address			= " << current->address << "\n";
            cout << "Balance			= " << fixed << setprecision(2) << current->balance << "\n";
            cout << "Account Type		= " << current->accountType << "\n";
            sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
			sleep_for(5000);
			system("cls");
            return;
        }
        current = current->next;
    }

    cout << "\nAccount not found.\n";
    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
	sleep_for(5000);
	system("cls");
}

void displayAccountNumbers() {
    Customer* current = head;
    while (current != nullptr) {
        cout << current->accountNumber << "\n";
        current = current->next;
    }
}

bool accountExists(int accountNumber) {
    Customer* current = head;
    while (current != nullptr) {
        if (current->accountNumber == accountNumber) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void transferMoney() {
    system("cls");

    // Check if there are no accounts available
    if (head == nullptr) {
        cout << "\nNo accounts available. First, create an account.\n";
	    sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    int sourceAccountNumber, targetAccountNumber;
    cout << "\nAvailable Account Numbers:\n";
    displayAccountNumbers();
    cout << "				*****************************************************"<< endl;
    // Get valid source account number
    cout << "\n				Enter source account number		  = ";
    sourceAccountNumber = getPositiveIntegerInput();

    // Get valid target account number
    cout << "				Enter target account number		  = ";
    targetAccountNumber = getPositiveIntegerInput();

    Customer* sourceAccount = nullptr;
    Customer* targetAccount = nullptr;

    // Find source and target accounts
    Customer* current = head;
    while (current != nullptr) {
        if (current->accountNumber == sourceAccountNumber) {
            sourceAccount = current;
        } else if (current->accountNumber == targetAccountNumber) {
            targetAccount = current;
        }

        current = current->next;

        // Break loop if both accounts are found
        if (sourceAccount && targetAccount) {
            break;
        }
    }

    // Check if both accounts are found
    if (!sourceAccount || !targetAccount) {
        cout << "\nOne or both accounts not found.\n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    // Get password for source account
    string password;
    cout << "				Enter the password for the source account = ";
    cin >> password;

    if (password != sourceAccount->password) {
        cout << "\nIncorrect password for source account. Access denied.\n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    if (sourceAccount->balance <= 0) {
        cout << "\nInsufficient balance in the source account.\n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    double amount;
    cout << "				Enter the amount to transfer		  = $";
    cin >> amount;

    if (amount <= 0 || amount > sourceAccount->balance) {
        cout << "\nInvalid transfer amount or insufficient balance.\n";
        sleep_for(500);//to pause or "sleep" for 500 milliseconds before continuing to execute.
		sleep_for(5000);
		system("cls");
        return;
    }

    // Apply transfer charges (5% tax)
    amount += 0.05 * amount;

    // Perform the transfer
    sourceAccount->balance -= amount;
    targetAccount->balance += amount;

    // Ensure the updated balance is not negative
    sourceAccount->balance = max(0.0, sourceAccount->balance);
    targetAccount->balance = max(0.0, targetAccount->balance);

    cout << "\nAmount Transferred!!!";
    cout << "\nUpdated balance in source account (" << sourceAccount->accountNumber << "): "
         << fixed << setprecision(2) << sourceAccount->balance << "\n";
    cout << "Updated balance in target account (" << targetAccount->accountNumber << "): "
         << fixed << setprecision(2) << targetAccount->balance << "\n";

     saveAccounts(); // Save accounts to file after transfer
}

// Function to delete a linked list
void deleteLinkedList(Customer* node) {
    while (node != nullptr) {
        Customer* temp = node;
        node = node->next;
        delete temp;
    }
}

void sortAccounts() {   // Updated sortAccounts function
    system("cls");

    if (head == nullptr) {
        cout << "No accounts available. Create an account first.\n";
        sleep_for(500);
        sleep_for(5000);
        system("cls");
        return;
    }

    if (head->next == nullptr) {
        cout << "Only one account available. No sorting needed.\n";
        sleep_for(500);
        sleep_for(5000);
        system("cls");
        return;
    }

    int count = 0;
    Customer* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    cout << "\nSorting using Insertion Sort.\n";

    // Function to perform Insertion Sort based on account numbers
    auto insertionSort = [](Customer* arr, int n) {
        int i, j;
        Customer key;
        for (i = 1; i < n; i++) {
            key = arr[i];
            j = i - 1;

            while (j >= 0 && arr[j].accountNumber > key.accountNumber) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    };

    // Convert linked list to an array for sorting
    Customer* arr = new Customer[count];
    temp = head;
    for (int i = 0; i < count; i++) {
        arr[i] = *temp;
        temp = temp->next;
    }

    insertionSort(arr, count);

    // Create a new linked list with sorted values
    Customer* newHead = nullptr;
    Customer* newTail = nullptr;
    for (int i = 0; i < count; i++) {
        Customer* newNode = new Customer();
        *newNode = arr[i];  // Copy the entire structure

        // Copy array-type attributes individually
        strcpy(newNode->name, arr[i].name);
        strcpy(newNode->password, arr[i].password);
        strcpy(newNode->email, arr[i].email);
        strcpy(newNode->address, arr[i].address);
        strcpy(newNode->phoneNumber, arr[i].phoneNumber);

        newNode->next = nullptr;
        newNode->prev = nullptr;  // Initialize prev pointer

        if (newHead == nullptr) {
            newHead = newTail = newNode;
        } else {
            newTail->next = newNode;
            newNode->prev = newTail;
            newTail = newNode;
        }
    }

    // Update the head pointer to point to the sorted list
    deleteLinkedList(head);
    head = newHead;

    delete[] arr;
	
    sleep_for(500);
    sleep_for(5000);
    system("cls");
    cout << "\nAccounts sorted successfully.\n\n";
    saveAccounts();  // Save accounts to file after sorting
    sleep_for(1000);
    displayAllAccounts();
    sleep_for(5000);
    system("cls");
}

void loadAccounts() {
    ifstream file("accounts.txt");

    if (file.is_open()) {
        while (!file.eof()) {
            Customer* newCustomer = new Customer;

            file >> newCustomer->name;
            file >> newCustomer->accountNumber;
            file >> newCustomer->balance;
            file >> newCustomer->password;
            file >> newCustomer->email;
            file >> newCustomer->address;
            file >> newCustomer->phoneNumber;
            file >> newCustomer->accountType;

            newCustomer->next = nullptr;
            newCustomer->prev = nullptr;

            if (head == nullptr) {
                head = newCustomer;
            } else {
                Customer* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newCustomer;
                newCustomer->prev = current;
            }
        }
        file.close();
    }
}

void saveAccounts() {
    ofstream file("accounts.txt");

    if (file.is_open()) {
        Customer* current = head;
        while (current != nullptr) {
            file << current->name << " ";
            file << current->accountNumber << " ";
            file << current->balance << " ";
            file << current->password << " ";
            file << current->email << " ";
            file << current->address << " ";
            file << current->phoneNumber << " ";
            file << current->accountType << "\n";

            current = current->next;
        }
        file.close();
    }
}

void cleanup() {
    while (head != nullptr) {
        Customer* temp = head;
        head = head->next;
        delete temp;
    }
}
