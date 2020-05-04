#include "CommonHeader.h"

void initializeBook(){

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	// Create the original database, in case it does not exist

	stmt->execute("CREATE DATABASE IF NOT EXISTS LibraryManagement;");
	stmt->execute("USE LibraryManagement;");

	// Creates table book. Stores the following information:
	// Current book number from the start,
	// People issued to until now,
	// Is the book issued as of now,
	// ID of the book (barcode-type)

	stmt->execute("CREATE TABLE IF NOT EXISTS BOOK("
		"bookno INT NOT NULL PRIMARY KEY AUTO_INCREMENT,"
		"issued_to VARCHAR(150), "
		"is_issued BOOL DEFAULT 0,"
		"id VARCHAR(150) NOT NULL UNIQUE"
		");");

	delete stmt;
	delete con;

}

void addBook(){

	string bookid;
	cout<<"Enter book ID"<<endl;
	cin>>bookid;

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	// Create the original database, in case it does not exist

	stmt->execute("USE LibraryManagement;");

	string chkphrase = "SELECT * FROM BOOK WHERE id = \"" 
		+ bookid +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next()){
		cout<<"This book ID already exists!"<<endl;

		delete res;
		delete stmt;
		delete con;
		return;
	}

	string toInsert = "INSERT INTO BOOK(id)" 
		" VALUES(\""
		+ bookid +"\");";

	stmt->execute(toInsert);

	cout<<"The book has been successfully added!"<<endl;

	delete res;
	delete stmt;
	delete con;

}

void listBook(){

	cout<<"The list of books current are as follows:\n";
	cout<<"book number  book id\n";

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	res = stmt->executeQuery("SELECT * FROM BOOK");

	while(res->next()){
		cout<<res->getString("bookno")<<"  "<<res->getString("id")<<endl;
	}

	delete res;
	delete stmt;
	delete con;

}

void deleteBook(){

	cout<<"Enter book ID to be deleted\n";
	string bookid;
	cin>>bookid;

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
		cout<<"This book ID does not exist!\n";

		delete res;
		delete stmt;
		delete con;
		return;
	}
	if(res->getBoolean("is_issued") == 1){
		cout<<"This book cannot be deleted, as it has been currently issued to "<<res->getString("issued_to")<<endl;

		delete res;
		delete stmt;
		delete con;
		return;
	}

	string toDelete = "DELETE FROM BOOK "
	"WHERE id = \"" +
	bookid +
	"\";";

	stmt->execute(toDelete);
	cout<<"The book has been successfully deleted!\n";

	delete res;
	delete stmt;
	delete con;

}

void checkBook(){

	string bookid;
	cout<<"Enter the book id to be checked\n";
	cin>>bookid;

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

	cout<<"This book has been issued to Flat Number "<<res->getString("issued_to")<<endl;

	delete res;
	delete stmt;
	delete con;

}