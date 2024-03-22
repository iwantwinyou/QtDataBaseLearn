#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QDebug>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    void updateUser(QSqlDatabase db,const int &id,const QString &username);         // 更操作，修改数据
    void queryAllUser(QSqlDatabase db);                                             // 查操作，查询所有数据记录
    void selectQueryUser(QSqlDatabase db,const QString &username);                  // 查操作，直接执行SQL语句方式
    void preparedQueryUser(QSqlDatabase db,const QString &username);                // 查操作，名称绑定方式
    void deleteUser(QSqlDatabase db,const QString &username);                       // 删操作
    void insertUserName(QSqlDatabase db,const int &userid, const QString &name);    // 增操作
    void createConnectionByName(const QString &connectionName);                     //使用自定义 connectionName 创建连接
    QSqlDatabase getConnectionByName(const QString &connectionName);                // 使用自定义 connectionName 获取连接
};

#endif // DATABASEWIDGET_H
