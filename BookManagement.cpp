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

}

void deleteBook(){


}

void issueBook(){

}

void listBook(){


}