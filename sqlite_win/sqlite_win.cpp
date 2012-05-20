// sqlite_win.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	sqlite3 *db;
	char *zErrMsg = 0;
	const int LENGTH=255;
	char buffer[LENGTH];
	
	string str;
	if ( sqlite3_open("E:\\t.sqlite", &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		exit(0);
	}
	ifstream fin("E:\\2.txt");
	fin.getline(buffer,LENGTH);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS table1 (row integer primary key, data text);", 0, 0, &zErrMsg);
	sqlite3_exec(db, "insert into table1 (row, data) values (1,'yi');", 0, 0, &zErrMsg);

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

	sqlite3_close(db);
	fin.close();
	return 0;
}

