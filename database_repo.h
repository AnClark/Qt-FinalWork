#ifndef DATABASE_REPO_H
#define DATABASE_REPO_H

#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlTableModel>

#include<QMessageBox>

class DatabaseRepo{

public:
    QSqlDatabase db;
    const QString dbFileName="test.db";
    const QString dbTableName="person";

    QSqlTableModel *model;

    DatabaseRepo();

    bool connectToDatabase();

};
#endif // DATABASE_REPO_H
