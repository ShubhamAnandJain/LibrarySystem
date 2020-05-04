#include "CommonHeader.h"
#include "ManageSQLDatabase.cpp"

int main(){

	initialize();

	cout<<"Welcome to the Library System!\n";

	string usern, pass;

	cout<<"Please enter your username\n";
	cin>>usern;		

	cout<<"Please enter your password\n";
	cin>>pass;

	if(checkAdmin(usern,pass)){
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
		cout<<"4. Return a book\n";
		cout<<"5. Check status of a book\n";
		cout<<"6. Get a complete list of books\n";
		cout<<"7. Make a new card\n";
		cout<<"8. Remove a card\n";
		cout<<"9. Check status of a card\n";
		cout<<"10. Get a complete list of cards\n";
		cout<<"11. Add an admin\n";
		cout<<"12. Remove an admin\n";
		cout<<"13. List all admins\n";

		string input;		
		cin>>input;

		if(input == "1"){
			addBook();
		}
		else if(input == "2"){
			deleteBook();
		}
		else if(input == "3"){
			issueBook();
		}
		else if(input == "4"){
			returnBook();
		}
		else if(input == "5"){
			checkBook();
		}
		else if(input == "6"){
			listBook();
		}
		else if(input == "7"){
			addCard();
		}
		else if(input == "8"){
			deleteCard();
		}
		else if(input == "9"){
			checkCard();
		}
		else if(input == "10"){
			listCard();
		}
		else if(input == "11"){
			addAdmin();
		}
		else if(input == "12"){
			removeAdmin();
		}
		else if(input == "13"){
			listAdmin();
		}

		else{
			cout<<"Incorrect input format!\n";
			continue;
		}

	}

	return 0;
}