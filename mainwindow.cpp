#include "mainwindow.h"
#include "ui_mainwindow.h"
#define QH Qt::Horizontal
#define CLK SIGNAL(clicked(bool))

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /******************  初始化数据库与用户界面  **************/
    handler = new DBHandler();          //实例化DBHandler
    ui->tblStudents->setModel(handler->getModel());     //给TableView应用模型类，以设置界面，并显示数据库之记录
    ui->tblStudents->resizeColumnsToContents();         //自动调整列宽

    /**********************  连接信号与槽  *************************/
    connect(ui->btnAddRecord,CLK,this,SLOT(slotAddRecordDialog()));     //“添加记录”按钮
    connect(ui->btnDeleteRecord,CLK,this,SLOT(slotDeleteRecord()));     //“删除记录”按钮
    connect(ui->btnCommit,CLK,this,SLOT(slotCommit()));                 //“提交修改”按钮
    connect(ui->btnRollBack,CLK,this,SLOT(slotRollBack()));             //“回退修改”按钮
    connect(ui->btnClose,CLK,this,SLOT(close()));                       //“关闭”按钮
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*************  槽函数实现区域  **************/

/************ “添加记录”按钮 *************/
void MainWindow::slotAddRecordDialog(){

    //检查输入是否存在空值
    if((ui->txtName->text().isEmpty()) || (ui->txtClass->text().isEmpty()) || (ui->txtCollege->text().isEmpty())) {
        QMessageBox::warning(this,"错误","信息未填写完整，请重新填写！");
        ui->txtName->setFocus();
        return;
    }

    //【核心】添加记录到数据库中
    handler->addRecord(ui->txtName->text(), ui->txtCollege->text(), ui->txtClass->text());

    //刷新数据库列表
    ui->tblStudents->setModel(handler->refreshModel());         //利用refreshModel方法快速刷新（实际上调用的是数据模型的select方法）
    ui->tblStudents->resizeColumnsToContents();         //自动调整列宽
}

/***********  “删除记录”按钮  ***********/
void MainWindow::slotDeleteRecord(){
    //处理TableView当前选中情形的成员是currentIndex，属于QModelIndex类型

    //获取当前选中情况
    QModelIndex index = ui->tblStudents->currentIndex();
    //【核心】将当前选中情况传入deleteRecord方法中，以删除记录
    handler->deleteRecord(index);
    //刷新数据库列表
    ui->tblStudents->setModel(handler->refreshModel());
}

/*************  “提交修改”按钮  ***************/
void MainWindow::slotCommit(){
    handler->saveChanges();
}

/*************  “回退修改”按钮  **************/
void MainWindow::slotRollBack(){
    handler->rollBack();
}
