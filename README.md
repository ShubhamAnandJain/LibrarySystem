# LibrarySystem

This is a book management system created to maintain the database for the society library. Currently in C++ and MySQL, the first version is complete. This will be updated in the future to a Windows Application using Visual Studio. The following assumptions have been made as of now (Which are based on the rules in my society):  
1. Only one card can be created per flat 
2. Only one book can be issued at a time per card 
3. There are no fines for late returns 
4. Admins use weak passwords, because the database used is not secure 
5. There are no deliberate SQL injection attacks by the librarians, which would wipe the database 

To use this code, note the following points:

1. Compile with ```g++ -o l LibrarySystem.cpp -L/usr/lib -lmysqlcppconn``` 
2. At the start, both username and password are "admin". You can remove this at any point, but if there are no admins, then the program will automatically default to this setting. 

##Setup your Environment

```sudo apt-get install libmysqlcppconn-dev```  \
```sudo apt-get install mysql-server```  \
```sudo mysql```  \
After logging into mysql, do the following:  \
```USE mysql;```  \
```CREATE user 'user'@'localhost' identified by 'Password';```  \
```GRANT ALL PRIVILEGES ON LibraryManagement.* TO 'user'@'localhost';```  \
Now you can exit mysql, and compile the program as follows:  \
```g++ -o l LibrarySystem.cpp -L/usr/lib -lmysqlcppconn```  \
Use the program as follows:  \
```./l``` 
