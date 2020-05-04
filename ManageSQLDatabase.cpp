#include "CommonHeader.h"
#include "BookManagement.cpp"
#include "AdminManagement.cpp"
#include "CardManagement.cpp"

void initialize(){

	initializeBook();
	initializeAdmin();
	initializeCard();
	
}

void issueBook(){

	string bookid, flatno;

	cout<<"Enter book id to issue\n";
	cin>>bookid;
	cout<<"Enter flat number to issue to\n";
	cin>>flatno;

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	string chkphrase = "SELECT * FROM BOOK WHERE id = \"" 
		+ bookid +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next() == 0){
		cout<<"This book does not exist!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}

	if(res->getBoolean("is_issued") == 1){
		cout<<"This book is already issued to "<<res->getString("issued_to")<<"!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}

	string chkflat = "SELECT * FROM CARD WHERE FlatNo = \"" 
		+ flatno +
		"\";";

	res = stmt->executeQuery(chkflat);

	if(res->next() == 0){
		cout<<"This flat does not have a card issued!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}

	if(res->getBoolean("is_book_issued") == 1){
		cout<<"This flat already has the book "<<res->getString("issued_book_id")<<endl;

		delete res;
		delete stmt;
		delete con;
		return;
	}

	string updatebook = "UPDATE BOOK "
	"SET is_issued = 1 "
	", issued_to = \"" +
	flatno+"\""
	" WHERE id = \""+
	bookid + "\";";

	string updatecard = "UPDATE CARD "
	"SET is_book_issued = 1 "
	", issued_book_id = \"" +
	bookid + "\""
	" WHERE FlatNo = \""+
	flatno + "\";";

	stmt->execute(updatebook);
	stmt->execute(updatecard);

	cout<<"Book "<<bookid<<" has been issued to "<<flatno<<"!\n";

	delete res;
	delete stmt;
	delete con;

}

void returnBook(){

	string bookid, flatno;
	cout<<"Enter the book id to be returned\n";
	cin>>bookid;
	cout<<"Enter the flat no that is returning this book\n";
	cin>>flatno;

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	string chkphrase = "SELECT * FROM BOOK WHERE id = \"" 
		+ bookid +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next() == 0){
		cout<<"This book does not exist!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}

	if(res->getBoolean("is_issued") == 0){
		cout<<"This book has not been issued as of now!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}

	if(res->getString("issued_to") != flatno){
		cout<<"This book has not been issued to this flat no!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}

	string updatebook = "UPDATE BOOK "
	"SET is_issued = 0"
	" WHERE id = \""+
	bookid + "\";";

	string updatecard = "UPDATE CARD "
	"SET is_book_issued = 0"
	" WHERE FlatNo = \""+
	flatno + "\";";

	stmt->execute(updatebook);
	stmt->execute(updatecard);

	cout<<"Book "<<bookid<<" has been returned to the library!\n";

	delete res;
	delete stmt;
	delete con;

}