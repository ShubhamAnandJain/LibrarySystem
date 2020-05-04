#include "CommonHeader.h"

void initializeCard(){

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	// Creates table card, for library cards. 
	// Stores the following information:
	// Flat No. for the library card issued to,
	// is a book currently issued to this flat,
	// the ID of the issued book
	// Local library only allows one book to be issued

	stmt->execute("CREATE TABLE IF NOT EXISTS CARD("
		"FlatNo VARCHAR(150) UNIQUE,"
		"is_book_issued BOOL DEFAULT 0,"
		"issued_book_id VARCHAR(150) UNIQUE"
		");");

	delete stmt;
	delete con;
	
}

void addCard(){

	string flatno;
	cout<<"Please enter flat number for the issued card\n";
	cin>>flatno;

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	string chkphrase = "SELECT * FROM CARD WHERE FlatNo = \"" 
		+ flatno +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next()){
		cout<<"This flat has already been issued a card!"<<endl;

		delete res;
		delete stmt;
		delete con;
	}

	string toInsert = "INSERT INTO CARD(FlatNo)" 
		" VALUES(\""
		+ flatno +"\");";

	stmt->execute(toInsert);

	cout<<"This flat has been issued a card!\n";

	delete res;
	delete stmt;
	delete con;

}

void checkCard(){

	string flatno;
	cout<<"Please enter flat number to check\n";
	cin>>flatno;

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	string chkphrase = "SELECT * FROM CARD WHERE FlatNo = \"" 
		+ flatno +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next()){
		if(res->getBoolean("is_book_issued")) cout<<"This flat has been issued the book "<<res->getString("issued_book_id")<<endl;
		else cout<<"This flat does not have a book issued!\n";

		delete res;
		delete stmt;
		delete con;

		return;
	}

	cout<<"This flat does not have a card issued!\n";

	delete res;
	delete stmt;
	delete con;

}

void listCard(){

	cout<<"Flat No\n";

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();
	stmt->execute("USE LibraryManagement;");

	res = stmt->executeQuery("SELECT * FROM CARD;");
	while(res->next()){
		cout<<res->getString("FlatNo")<<endl;
	}

	delete res;
	delete stmt;
	delete con;

}

void deleteCard(){

	cout<<"Enter flat number of the card to be deleted\n";
	string flatno;
	cin>>flatno;

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	string chkphrase = "SELECT * FROM CARD WHERE FlatNo = \"" 
		+ flatno +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next() == 0){
		cout<<"The card for this flat does not exist!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}
	if(res->getBoolean("is_book_issued") == 1){
		cout<<"This card cannot be deleted, as a book has been issued, with book ID "<<res->getString("issued_book_id")<<endl;

		delete res;
		delete stmt;
		delete con;
		return;
	}

	string toDelete = "DELETE FROM CARD "
	"WHERE FlatNo = \"" +
	flatno +
	"\";";

	stmt->execute(toDelete);
	cout<<"This card has been successfully deleted!\n";

	delete res;
	delete stmt;
	delete con;

}