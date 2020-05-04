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


}

void checkCard(){

}

void listCard(){


}
