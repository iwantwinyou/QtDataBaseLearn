#include "DataBaseWidget.h"
#include<QSqlQuery>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //获取数据库驱动列表
    qDebug() << QSqlDatabase::drivers();
    //创建一个数据库连接，指定数据库驱动
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //数据库连接需要设置的信息
    //db.setHostName("");

        // [1]创建名为 firstConnect 的数据库连接
        createConnectionByName("firstConnect");
        // 获取数据库
        QSqlDatabase db = getConnectionByName("firstConnect");

        // 实例化QSqlQuery，用于执行sql语句
        QSqlQuery query(db);
        // 创建一个表
        query.exec("create table newUser (id int primary key,username varchar(20))");


        // [2]增操作
        qDebug() << "---- insert operation start----";
        insertUserName(db,1,"xiaoqiao");
        insertUserName(db,2,"wang");
        query.exec("INSERT INTO newUser (id, username) VALUES (3, 'alex')");
        insertUserName(db,4,"lili");

        queryAllUser(db); // 查询增操作结果
        qDebug() << "---- insert operation end----- " << "\n ";


        // [3]查询操作
        qDebug() << "---- query operation start----- ";
        selectQueryUser(db,"lili"); // 直接执行sql语句方式
        preparedQueryUser(db,"wang");
        qDebug() << "---- query operation end----- " << "\n ";

        qDebug() << "---- query all data start----- ";
        queryAllUser(db); // 查询所有数据
        qDebug() << "---- query all data end----- " << "\n ";


        // [4]删操作
        qDebug() << "---- delete operation start----";
        deleteUser(db,"alex");
        query.exec(" DELETE FROM newUser WHERE username='wang' ");

        queryAllUser(db);
        qDebug() << "---- query operation end----" << "\n ";


        // [5]改操作,根据id修改数据
        qDebug() << "---- update operation start----";
        qDebug() << "---- before update id 1: ----";
        queryAllUser(db);

        updateUser(db,1,"yase");// ID为1，数据修改为 yase
        query.exec(" update newUser set username='newname' WHERE id=4");

        qDebug() << "---- after update id 1: ----";
        queryAllUser(db);
        qDebug() << "---- update operation end----" << "\n ";


        // 仅仅是测试需要，删除数据表中的所有数据，为了不影响下次运行程序观察结果
        query.exec(" DELETE FROM newUser");

}

Widget::~Widget()
{

}

/*
 * 功能描述：更新数据
 * 修改传入的 id 的 username
 * @param QSqlDatabase：数据库连接
 * @param id:用户id
 * @param username:用户名
 */
void Widget::updateUser(QSqlDatabase db,const int &id,const QString &username)
{
    QSqlQuery query(db);
    query.prepare("update newUser set username=:username WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":username", username);
    query.exec();
}


/*
 * 功能描述：数据查操作，查询所有数据
 * 执行SQL语句的方式，查询所有的用户数据记录
 * @param QSqlDatabase：数据库连接
 */
void Widget::queryAllUser(QSqlDatabase db)
{
    QString sql = "SELECT id, username FROM newUser" ; // 组装sql语句
    QSqlQuery query(db);                               // [1] 传入数据库连接
    query.exec(sql);                                   // [2] 执行sql语句
    while (query.next())
    {                             // [3] 遍历查询结果
        qDebug() << QString("Id: %1, Username: %2")
                    .arg(query.value("id").toInt())
                    .arg(query.value("username").toString());
    }
}

/*
 * 功能描述：查询一条数据记录
 * 数据查操作，SQL语句的方式实现
 * @param QSqlDatabase：数据库连接
 * @param username:用户名
 */
void Widget::selectQueryUser(QSqlDatabase db,const QString &username)
{
    QString sql = "SELECT * FROM newUser WHERE username='" + username + "'";
    QSqlQuery query(db);    // [1] 传入数据库连接
    query.exec(sql);        // [2] 执行sql语句
    while (query.next())
    {  // [3] 遍历查询结果
        qDebug() << QString("Id: %1, Username: %2")
                    .arg(query.value("id").toInt())
                    .arg(query.value("username").toString());

    }
}

/*
 * 功能描述：查询一条数据记录
 * 数据查操作，名称绑定的方式实现
 * @param QSqlDatabase：数据库连接
 * @param username:用户名
 */
void Widget::preparedQueryUser(QSqlDatabase db,const QString &username)
{
    QString sql = "SELECT * FROM newUser WHERE username=:username";
    QSqlQuery query(db);                    // [1] 传入数据库连接
    query.prepare(sql);                     // [2] 使用名称绑定的方式解析 SQL 语句
    query.bindValue(":username", username); // [3] 把占位符替换为传入的参数
    query.exec();                           // [4] 执行数据库操作
    while (query.next())
    {                  // [5] 遍历查询结果
        qDebug() << QString("Id: %1, Username: %2")
                    .arg(query.value("id").toInt())
                    .arg(query.value("username").toString());

    }
}



/*
 * 功能描述：数据删操作
 * 从数据库中删除一条数据，名称绑定的方式实现
 * @param QSqlDatabase：数据库连接
 * @param username:用户名
 */
void Widget::deleteUser(QSqlDatabase db,const QString &username)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM newUser WHERE username=:username");
    query.bindValue(":username", username);
    query.exec();
}


/*
 * 功能描述：数据增操作
 * 向数据库中插入一条数据记录，名称绑定的方式实现
 * @param QSqlDatabase：数据库连接
 * @param id:用户id
 * @param username:用户名
 */
void Widget::insertUserName(QSqlDatabase db,const int &userid, const QString &name)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO newUser (id, username) VALUES (:id, :username)");
    query.bindValue(":id", userid);
    query.bindValue(":username", name);
    query.exec();
}


/*
 * 功能描述：创建数据库连接
 * 使用自定义 connectionName 创建连接
 * @param connectionName：连接的名称
 */
void Widget::createConnectionByName(const QString &connectionName)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    // 数据库连接需要设置的信息
   // db.setHostName("172.16.1.16"); // 数据库服务器IP，我用的是本地电脑
    db.setDatabaseName("TestDB.db");// 数据库名
    db.setUserName("root");// 用户名
    db.setPassword("123456");// 密码
    db.setPort(3306);// 端口号

    // 连接数据库判断
    bool ok = db.open();

    if (ok)
    {
        qDebug() << "database connect is ok";
    } else
    {
        qDebug() << "database connect is fail";
    }

}

/*
 * 功能描述：获取数据库连接
 * 使用自定义 connectionName 获取连接
 * @param connectionName：连接的名称
 * @return 返回一个数据库连接
 */
QSqlDatabase Widget::getConnectionByName(const QString &connectionName)
{
    // 获取数据库连接
    return QSqlDatabase::database(connectionName);
}

