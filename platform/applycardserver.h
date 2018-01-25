#ifndef APPLYCARDSERVER_H
#define APPLYCARDSERVER_H

#include <QtNetwork>
#include <QTcpSocket>
#include <QWidget>
class ApplyCardServer:public QWidget
{
    Q_OBJECT
public:
    ApplyCardServer();
    void setMessage(QString message);   //向银行发送数据流
    QString getMessage();//获取银行返回的数据
    void onDealAddCard();//处理银行返回的添加银行卡处理结果
    void onDealBuy();//处理银行返回的支付处理结果

signals:
    void recMess();
    void successBuy(); //向外发送成功购买信号
    void successAdd();//向外发送成功添加银行卡信号

private slots:
    void readMessageFromTcpServer();//从socket通道有数据时响应应
public:
    QTcpSocket * tcpClient;//宋玉建立socket通信
    QString sendStr;//发送字符串
    QString getStr;//接受字符串
};

#endif // APPLYCARDSERVER_H
