#include "database_repo.h"

DatabaseRepo::DatabaseRepo(){
    connectToDatabase();
}

bool DatabaseRepo::connectToDatabase()
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbFileName);

        if(!db.open()){
            QMessageBox::critical(0,"出错啦！","无法打开数据库",QMessageBox::Cancel);
            return false;
        }


        QSqlQuery query;
        query.exec("create table " + dbTableName + " (id int primary key, "
                        "name varchar(30), college varchar(30), class varchar(30))");

        query.exec("insert into person values(101, 'Danny', 'Young', '333')");
        query.exec("insert into person values(109, 'sssss', 'Yxoung', '33d3')");



        return true;
    }

