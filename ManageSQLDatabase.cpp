#include "mysql_driver.h" 
#include "BookManagement.cpp"
#include "AdminManagement.cpp"
#include "CardManagement.cpp"

void initialize(){

	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "user", "password");

}