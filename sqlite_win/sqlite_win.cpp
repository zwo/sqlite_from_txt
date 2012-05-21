// sqlite_win.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "sqlite3.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	sqlite3 *db;
	char *zErrMsg = 0;
	const int LENGTH=255;	
	char buffer[LENGTH];
	
	//initial the database
	if ( sqlite3_open("E:\\dunjia.sqlite", &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		exit(0);
	}
	ifstream fin("E:\\1_utf8.txt");
	//fin.getline(buffer,LENGTH);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS table1 (id integer primary key, item text);", 0, 0, &zErrMsg);
	//sqlite3_exec(db, "insert into table1 (row, data) values (1,'yi');", 0, 0, &zErrMsg);
	/*
	sqlite3_stmt *stmt;
	char *update="INSERT OR REPLACE INTO table1 (row, data) VALUES (?,?);";
	if (sqlite3_prepare(db,update,-1,&stmt,0) == SQLITE_OK)
	{
		sqlite3_bind_int(stmt,1,2);
		sqlite3_bind_text(stmt,2,buffer,-1,NULL);
	}
	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		printf("error");
		exit(1);
	}
	sqlite3_finalize(stmt);
	*/

	for (int i1=1;i1<=8;i1++)
	{
		for (int i2=1;i2<=8;i2++)
		{
			for (int i3=1;i3<=8;i3++)
			{
				fin.getline(buffer,LENGTH);
				char *update="INSERT OR REPLACE INTO table1 (id, item) VALUES (?,?);";
				sqlite3_stmt *stmt;
				if (sqlite3_prepare(db,update,-1,&stmt,0) == SQLITE_OK)
				{
					sqlite3_bind_int(stmt,1,(i1*100+i2*10+i3));
					sqlite3_bind_text(stmt,2,buffer,-1,NULL);
				}
				if (sqlite3_step(stmt) != SQLITE_DONE)
				{
					printf("error");
					exit(1);
				}
				sqlite3_finalize(stmt);
			}
		}
	}

	sqlite3_close(db);
	fin.close();
	return 0;
}

