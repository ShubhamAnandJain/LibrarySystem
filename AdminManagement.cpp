#include "CommonHeader.h" 

void initializeAdmin(){

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement;");

	// Creates table admin, for library administrators
	// Stores the following information:
	// Admin number, which is auto-incremented
	// username of the admin
	// password of the admin

	stmt->execute("CREATE TABLE IF NOT EXISTS ADMIN("
		"adminno INT NOT NULL PRIMARY KEY AUTO_INCREMENT,"
		"username VARCHAR(150) UNIQUE,"
		"password VARCHAR(150)"
		");");

	res = stmt->executeQuery("SELECT * FROM ADMIN");

	if(res->next() == 0){
		stmt->execute(
		"INSERT INTO ADMIN(username, password)"
		"VALUES (\"admin\",\"admin\")"
		";");
	}

	delete stmt;
	delete con;
	delete res;

}

bool checkAdmin(string username, string password){

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement");

	string chkphrase = "SELECT * FROM ADMIN WHERE username = \"" 
		+ username +
		"\" AND password = \""
		+ password +"\";";

	res = stmt->executeQuery(chkphrase);
	
	bool to_ret = res->next();

	delete res;
	delete stmt;
	delete con;

	return to_ret;

}

void addAdmin(){
	
	string username, password, verify;
	cout<<"Enter a new username"<<endl;
	cin>>username;
	cout<<"Enter the password"<<endl;
	cin>>password;
	cout<<"Verify the entered password"<<endl;
	cin>>verify;
	if(password != verify){
		cout<<"Passwords do not match! Try again."<<endl;
		return;
	}

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement");

	string chkphrase = "SELECT * FROM ADMIN WHERE username = \"" 
		+ username +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next() == 1){
		cout<<"This username is already present! Please try again!\n";

		delete res;
		delete stmt;
		delete con;

		return;
	}

	string toInsert = "INSERT INTO ADMIN(username, password)" 
		" VALUES("
		"\""+username+"\", \""
		+ password +"\");";

	stmt->execute(toInsert);
	
	cout<<"Successfully inserted!"<<endl;

	delete res;
	delete stmt;
	delete con;

}

void removeAdmin(){

	string username, password, verify;
	cout<<"Enter the username to delete"<<endl;
	cin>>username;
	cout<<"Enter the password of the account"<<endl;
	cin>>password;
	cout<<"Verify the entered password"<<endl;
	cin>>verify;
	if(password != verify){
		cout<<"Passwords do not match! Try again."<<endl;
		return;
	}

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement");

	string chkphrase = "SELECT * FROM ADMIN WHERE username = \"" 
		+ username +
		"\";";

	res = stmt->executeQuery(chkphrase);

	if(res->next() == 0){
		cout<<"The username or password is incorrect! Please try again!\n";

		delete res;
		delete stmt;
		delete con;

		return;
	}

	string toDelete = "DELETE FROM ADMIN" 
		" WHERE username = \""
		+ username+"\" AND password = \""
		+ password +"\";";

	stmt->execute(toDelete);

	cout<<"This admin has been successfully removed!"<<endl;

	delete res;
	delete stmt;
	delete con;

}

void listAdmin(){

	cout<<"username\n";

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "Password");
	stmt = con->createStatement();

	stmt->execute("USE LibraryManagement");

	res = stmt->executeQuery("SELECT * FROM ADMIN;");

	while(res->next()){
		cout<<res->getString("username")<<endl;
	}

	delete con;
	delete stmt;
	delete res;

}