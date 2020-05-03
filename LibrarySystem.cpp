#include<iostream>
#include "ManageSQLDatabase.cpp"
using namespace std;

int main(){

	cout<<"Welcome to the Library System!\n";
	cout<<"Please enter your credentials\n";

	string usern, pass;
	cin>>usern>>pass;
	if(usern == "admin" && pass == "admin"){
		cout<<"Welcome!\n";
	}
	else{
		cout<<"Error: Wrong username or password!\n";
		return 0;
	}

	while(true){
		cout<<"Press the corresponding number for the following options:\n";
		
		cout<<"1. Add a book\n";
		cout<<"2. Delete a book\n";
		cout<<"3. Issue a book\n";
		cout<<"4. Get list of books available\n";
		cout<<"5. Make a new card\n";
		cout<<"6. Get books issued by a card\n";
		cout<<"7. Get list of issuers in the library\n";
		cout<<"8. Add an admin\n";

		string input;		
		cin>>input;
		if(input < "1" || input > "9"){
			cout<<"Incorrect input format!\n";
			continue;
		} 
		else if(input == "1"){
			addBook();
		}
		else if(input == "2"){
			deleteBook();
		}
		else if(input == "3"){
			issueBook();
		}
		else if(input == "4"){
			listBook();
		}
		else if(input == "5"){
			addCard();
		}
		else if(input == "6"){
			checkCard();
		}
		else if(input == "7"){
			listCard();
		}
		else if(input == "8"){
			addAdmin();
		}
	}

	return 0;
}