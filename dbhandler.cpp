#include "dbhandler.h"
#define QH Qt::Horizontal

/*************  构造函数  **************
 * ■用于初始化并打开数据库。
 * ***********************************/
DBHandler::DBHandler()
{
    //建立数据库连接
    db = QSqlDatabase::addDatabase("QSQLITE");          //指定数据库的类型。这里使用SqLite
    db.setDatabaseName("test.db");          //指定要打开的数据库文件名。若第一次运行，则会先创建后打开

    //接下来读取数据库的工作由一个专门的函数来完成（旨在获取返回值以输出错误信息）
    loadDatabaseFile();

}

/***********  析构函数  *************
 * ■用于关闭数据库连接。
 * ********************************/
DBHandler::~DBHandler()
{
    db.close();         //关闭数据库连接
}


/**********  初始化/打开数据库  ***********
 * ■如果是第一次运行，则先打开数据库，后创建一个新表
 * ■如果已经创建过了，那么就直接打开。
 * ************************************/
bool DBHandler::loadDatabaseFile(){
        //调用open()方法打开数据库，同时做出判断，判断是否打开成功。
            //open方法返回的是一个布尔值。
        if(!db.open())      //若打开不成功
        {
            //输出错误信息
            QMessageBox::critical(0,"出错啦！","打开数据库时发生错误：" + db.lastError().text(),QMessageBox::Cancel);
            return false;       //结束函数执行
        }

        QSqlQuery query;        //建立SQL查询对象以执行SQL语句


        /***************** 【【▲警告！！！▲】】*************
                SQLite的语法和MySQL有所不同，必须要注意！
        *************************************************/
        //创建新表
        //本程序中，表的名字为“person”，字段有：ID（主键）、姓名、院系、班级。
        query.exec("CREATE TABLE person (ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                   "Name varchar(30), "
                                                   "College varchar(30), "
                                                   "Class varchar(20) "
                                                   ")");
        return true;
}


/********************  添加记录  **********************
 * ■调用SQL语句，添加新记录。
 * ■传入参数：三个字段的内容（姓名、院系和班级）
 * ▲本函数直接调用SQL语句进行操作，因此所做的更改都会立即生效！
 * ************************************************/
bool DBHandler::addRecord(QString name, QString college, QString theclass){
    QSqlQuery query;            //建立SQL查询对象以执行SQL语句
    //接下来将使用“绑定字段”方法
        //①准备好SQL语句，内含你希望绑定的字段，字段名以半角冒号开头。（ORACLE语法）
    query.prepare("INSERT INTO person (Name, College, Class) VALUES (:Name, :College, :Class)");
        //②绑定字段
    query.bindValue(":Name", name);
    query.bindValue(":College",college);
    query.bindValue(":Class", theclass);
        //③执行SQL语句，并退出函数过程
    return query.exec();
}

/********************  删除记录  **********************
 * ■调用SQL语句，删除记录。
 * ■传入参数：TableView的当前索引currentIndex（为QModelIndex对象）
 * ▲本函数直接调用SQL语句进行操作，因此所做的更改都会立即生效！
 * ************************************************/
bool DBHandler::deleteRecord(const QModelIndex currentIndex){
    //①先获取当前所选中记录的主键。
    int currentRow=currentIndex.sibling(currentIndex.row(),0).data().toInt();

    //②使用“绑定字段”方法删除条目
    QSqlQuery query;
    query.prepare("DELETE FROM person WHERE ID=:ID");
    query.bindValue(":ID", currentRow);

    //③执行SQL语句
    return query.exec();
}

/**************  安全删除记录  ******************
 * ■让记录可恢复，即在提交之前可回退修改。
 * 由于时间关系，暂不研究。
 * ********************************************/

//bool DBHandler::deleteRecord_Recoverable(QTableView *tableView){
//    model->removeRow()
//}


/******************  提交修改（参考了Qt示例：cachedTable）  ******************
 * ■将用户在TableView中所做的修改应用到数据库中。
 * ■这里利用了QSQLTableModel本身的特性——可以直接对数据库进行一些简单的操作。（甚至还可以直接执行SQL语句。）
 * ********************************************/
void DBHandler::saveChanges(){
    model->submitAll();
}

/******************  回退修改（参考了Qt示例：cachedTable）  ******************
 * ■放弃用户在TableView中所做的修改，并将TableView里显示的内容回退到修改之前的状态。
 * ■这里利用了QSQLTableModel本身的特性——可以直接对数据库进行一些简单的操作。（甚至还可以直接执行SQL语句。）
 * ********************************************/
void DBHandler::rollBack(){
    model->revertAll();
}




/*************  获取数据库对象（备用）  ***************/
QSqlDatabase DBHandler::getDatabase(){
    return db;
}

/*****************  设置数据表模型  ******************
 * ■ 主要包括两方面的工作：
 *      设置TableView的布局
 *      让TableView显示出数据库的内容
 * ■返回值：QSqlTableModel，可直接被应用到TableView中
 * *********************************************/

QSqlTableModel *DBHandler::getModel(){
    //①初始化数据表模型
    model = new QSqlTableModel(0,db);

    //②打开数据表
    model->setTable("person");          //将我们的数据表person与数据表模型绑定
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);         //设置如何提交修改（即把修改应用到数据库文件中）。这里设置为手动提交，取代系统默认的自动提交。

    //【▲这一步非常重要！】③让数据表的内容显示出来。
    //【【【▲警告！！】】缺少这一句的后果就是——不管怎么样，TableView里面都是空空如也的！
    model->select();

    //④设置表头
    model->setHeaderData(0, QH, "ID");
    model->setHeaderData(1, QH, "姓名");
    model->setHeaderData(2, QH, "院系");
    model->setHeaderData(3, QH, "班级");

    //⑤返回配置好的模型类
    return model;
}

/**************   刷新数据表模型  ******************
 * ■在UI中对数据表作出修改之后，调用本方法刷新数据表。
 * ■返回值：更新后的QSqlTableModel。需要重新应用到TableView中。
 * **********************************************/
QSqlTableModel *DBHandler::refreshModel(){
    model->select();
    return model;
}
