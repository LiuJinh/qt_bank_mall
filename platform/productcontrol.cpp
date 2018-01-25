#include "productcontrol.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
extern QString path;
extern QString choice;
ProductControl::ProductControl()
{

}

QVector<Book> ProductControl::getAllBooks()
{
    QVector<Book >  allBooks ;
    QString currentPath =path + "book\\details.txt";


    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    line = rd.readLine();


    int order = 0;
    while(!line.isNull()){

        Book book  ;
        book.order = order++;

        int k=0;
        QString sub="";

        for(int i=0;i<line.size();i++){


            if( line[i]!='&'  ){
                sub += line[i];
             }
            else{
                switch (k){
                case 0:book.setName(sub);break;
                case 1:book.setPrice(sub.toFloat());break;
                case 2:book.setSurplus((sub).toInt()) ;break;
                case 3:book.setImage(sub);break;
                case 4:book.setDiscount(sub.toFloat());break;
                case 5:book.setDetail(sub);break;
                }
                k++;
                sub = "";
            }


        }

        allBooks.push_back(book);
        line = rd.readLine();
    }

    file.close();
    return allBooks;
}

QVector<Food> ProductControl::getAllFoods()
{
    QVector<Food >  allBooks ;
    QString currentPath =path + "food\\details.txt";

    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    line = rd.readLine();

    int order = 0;
    while(!line.isNull()){

        Food book  ;

        book.order = order++;
        int k=0;
        QString sub="";

        for(int i=0;i<line.size();i++){


            if( line[i]!='&'  ){
                sub += line[i];
             }
            else{
                switch (k){
                case 0:book.setName(sub);break;
                case 1:book.setPrice(sub.toFloat());break;
                case 2:book.setSurplus((sub).toInt()) ;break;
                case 3:book.setImage(sub);break;
                case 4:book.setDiscount(sub.toFloat());break;
                case 5:book.setDetail(sub);break;
                }
                k++;
                sub = "";
            }


        }

        allBooks.push_back(book);
        line = rd.readLine();
    }

    file.close();
    return allBooks;
}

QVector<Clothing> ProductControl::getAllClothing()
{
    QVector<Clothing >  allBooks ;
    QString currentPath =path + "clothing\\details.txt";

    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    line = rd.readLine();

    int order = 0;
    while(!line.isNull()){

        Clothing book  ;

        book.order = order++;
        int k=0;
        QString sub="";

        for(int i=0;i<line.size();i++){


            if( line[i]!='&'  ){
                sub += line[i];
             }
            else {
                switch (k){
                case 0:book.setName(sub);break;
                case 1:book.setPrice(sub.toFloat());break;
                case 2:book.setSurplus((sub).toInt()) ;break;
                case 3:book.setImage(sub);break;
                case 4:book.setDiscount(sub.toFloat());break;
                case 5:book.setDetail(sub);break;
                }
                k++;
                sub = "";
            }


        }

        allBooks.push_back(book);
        line = rd.readLine();
    }

    file.close();
    return allBooks;
}

void ProductControl::setAllBooks(QVector<Book> allBooks)
{
    QString currentPath = path +"book\\details.txt";

    QFile file(currentPath);
    if(!file.open(QFile::WriteOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream wt(&file);
    wt<<"USER\\PWD\\NAME\\ID\\CARDS"<<endl;

    for(int i=0;i<allBooks.size();i++){

        wt<<((Book&)allBooks.at(i)).getName()+'&';
        wt<<QString::number(((Book&)allBooks.at(i)).getPrcie())+'&';
        wt<<QString::number(((Book&)allBooks.at(i)).getSurplus())+'&'+((Book&)allBooks.at(i)).getImg()+"&";

        wt<<QString::number(((Book&)allBooks.at(i)).getDiscount());
        wt<<"&"+((Book&)allBooks.at(i)).getDetails()+"&";
        wt<<"\n";
    }

    file.close();
}

void ProductControl::setAllFoods(QVector<Food> allFoods)
{
    QString currentPath = path +"food\\details.txt";

    QFile file(currentPath);
    if(!file.open(QFile::WriteOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream wt(&file);
    wt<<"USER\\PWD\\NAME\\ID\\CARDS"<<endl;

    for(int i=0;i<allFoods.size();i++){

        wt<<((Food&)allFoods.at(i)).getName()+'&';
        wt<<QString::number(((Food&)allFoods.at(i)).getPrcie())+'&';
        wt<<QString::number(((Food&)allFoods.at(i)).getSurplus())+'&'+((Food&)allFoods.at(i)).getImg()+"&";

        wt<<QString::number(((Food&)allFoods.at(i)).getDiscount());
        wt<<"&"+((Food&)allFoods.at(i)).getDetails()+"&";
        wt<<"\n";
    }

    file.close();
}

void ProductControl::setAllClothing(QVector<Clothing> allClothing)
{
    QString currentPath = path +"clothing\\details.txt";

    QFile file(currentPath);
    if(!file.open(QFile::WriteOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream wt(&file);
    wt<<"USER\\PWD\\NAME\\ID\\CARDS"<<endl;

    for(int i=0;i<allClothing.size();i++){

        wt<<((Clothing&)allClothing.at(i)).getName()+'&';
        wt<<QString::number(((Clothing&)allClothing.at(i)).getPrcie())+'&';
        wt<<QString::number(((Clothing&)allClothing.at(i)).getSurplus())+'&'+((Food&)allClothing.at(i)).getImg()+"&";

        wt<<QString::number(((Clothing&)allClothing.at(i)).getDiscount());
        wt<<"&"+((Clothing&)allClothing.at(i)).getDetails()+"&";
        wt<<"\n";
    }

    file.close();
}

QVector<Appoint> ProductControl::getAllAppoints()
{
    QVector<Appoint>  allAppoints ;
    QString currentPath =path + "appoints.txt";

    QFile file(currentPath);
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream rd(&file);
    QString line = rd.readLine();
    line = rd.readLine();

    while(!line.isNull()){

        Appoint appoint  ;
        int k=0;
        QString sub="";

        for(int i=0;i<line.size();i++){
            if( line[i]!='\\'  ){
                sub += line[i];
             }
            else{
                switch (k){
                case 0:appoint.userNumber = sub.toInt();break;
                case 1:appoint.goodNumber = sub.toInt();;break;
                case 2:appoint.goodKind = sub.toInt(); ;break;
                case 3:appoint.amount = sub.toInt();;
                }
                k++;
                sub = "";
            }


        }

        allAppoints.push_back(appoint);
        line = rd.readLine();
    }

    file.close();
    return allAppoints;
}

void ProductControl::setAllAppoint(QVector<Appoint> allAppoints)
{
    QString currentPath = path +"appoints.txt";

    QFile file(currentPath);
    if(!file.open(QFile::WriteOnly|QIODevice::Text)){
        qDebug()<<"something wrong";
    }

    QTextStream wt(&file);
    wt<<"USER\\Good\\Kind\\"<<endl;

    for(int i=0;i<allAppoints.size();i++){

        wt<<QString::number(((Appoint&)allAppoints.at(i)).userNumber)+'\\'+QString::number(((Appoint&)allAppoints.at(i)).goodNumber)+'\\'
            +QString::number(((Appoint&)allAppoints.at(i)).goodKind)+'\\'+QString::number(((Appoint&)allAppoints.at(i)).amount)+"\\\n";

    }

    file.close();
}

