#include "mainwindow.h"
#include "ui_mainwindow.h"
#define QH Qt::Horizontal

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DatabaseRepo *myDatabase = new DatabaseRepo();

    QSqlTableModel *model = myDatabase->model;

    /***************  设置表头与关联数据库  ***************/
    model = new QSqlTableModel(this);
    model->setTable(myDatabase->dbTableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, QH, "ID");
    model->setHeaderData(1, QH, "姓名");
    model->setHeaderData(2, QH, "学院");
    model->setHeaderData(3, QH, "年级");

    ui->tblStudentInfo->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
