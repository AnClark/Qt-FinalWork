#ifndef DBHANDLER_H
#define DBHANDLER_H

/****************  数据库操作类  ******************
 * 将Qt数据库访问接口，以及我自定义的操作数据库之方法，
 * 全部封装到这个类中。
 * 使用new关键字动态创建，即可使用。
*************************************************/


/**********导入数据库相关的类***********
 * 友情提示：QSqlQueryModel 与 QSqlTableModel 的最大区别在于：
 * 前者为只读，后者为可读写
 * ******************************/

#include<QtSql>                 //Qt 数据库的命名空间
#include<QSqlDatabase>          //Qt 数据库对象类，用于连接数据库
#include<QSqlQuery>             //Qt SQL查询类，用于执行SQL语句
#include<QSqlTableModel>        //Qt 数据表模型，用于在TableView中显示出数据库的记录，同时支持编辑

#include<QMessageBox>           //消息框类
#include<QTableView>            //用于支持deleteRecord_Recoverable方法

class DBHandler
{
private:
    QSqlDatabase db;            //数据库对象。可直接静态访问
    QSqlTableModel *model;      //数据表模型。一般需要动态创建

    bool loadDatabaseFile();    //打开数据库文件。内部方法，对外不可访问。
public:
    DBHandler();                //构造函数，主要用于连接数据库
    ~DBHandler();               //析构函数，主要用于关闭数据库连接

    QSqlDatabase getDatabase();         //返回数据库对象（备用）
    QSqlTableModel *getModel();         //设置好本程序专用的数据表模型，然后返回该模型
    QSqlTableModel *refreshModel();     //刷新数据表模型

    /**************  基本数据库操作  *************/
    /*       前两者直接调用SQL语句，即时生效       */
    /*       后三者通过数据表模型实现，可回退       */
    bool addRecord(QString name, QString college, QString theclass);        //添加记录
    bool deleteRecord(const QModelIndex currentIndex);                      //删除记录

    //void deleteRecord_Recoverable(QTableView &tableView);       //安全删除记录（记录可恢复）
    void saveChanges();         //提交修改
    void rollBack();            //回退修改

};

#endif // DBHANDLER_H
