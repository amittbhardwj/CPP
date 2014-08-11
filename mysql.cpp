#include<iostream>
#include<stdio.h>
#include<mysql/mysql.h>
#define host "localhost"
#define username "amit"
#define password "amitt"
#define database "cpp"
using namespace std;

MYSQL *conn;
int main()
{
	conn = mysql_init(NULL);
	mysql_real_connect(conn,host,username,password,database,0,NULL,0);
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	unsigned int i;
	mysql_query(conn,"SELECT * FROM users WHERE userid=1"); 
	res_set = mysql_store_result(conn); 
	unsigned int numrows = mysql_num_rows(res_set); 
	while ((row = mysql_fetch_row(res_set)) != NULL) 
	{
		for (i=0; i<mysql_num_fields(res_set); i++) 
		{
			cout<<"%s\n",row[i] != NULL ? row[i] : "NULL";
		}
	}
	mysql_close(conn); 
	return 0; 
} 
