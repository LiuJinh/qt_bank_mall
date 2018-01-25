#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
class Server:public QWidget
{
    Q_OBJECT
public:
    Server();
    void sendMessage(QString str);//向电商系统返回信息

private slots:
    void newConnect();//响应新连接
    void readClient();//响应缓冲区数据流，读取数据
    void onAddCardRequest();//根据信息流判断结果响应添加银行卡请求
    void onBuyRequest();//根据信息流判断结果响应支付请求

public:
    QTcpServer * tcpServer;//监听
    QTcpSocket * tcpClient;//建立连接
    QString recStr;//接收字符串
    QString sendStr;//发送字符串
};

#endif // SERVER_H
