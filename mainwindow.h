#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dbhandler.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:      /************  槽函数   *************/
    void slotAddRecordDialog();         //“添加记录”
    void slotDeleteRecord();            //“删除记录”
    void slotCommit();                  //“提交修改”
    void slotRollBack();                //“回退修改”

private:
    Ui::MainWindow *ui;

    /*****************  我自己写的 DBHandler 数据库操作类，在这里定义，以待实现！ ******************/
    DBHandler *handler;
};

#endif // MAINWINDOW_H
