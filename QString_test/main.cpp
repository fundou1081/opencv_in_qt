#include <QCoreApplication>
#include <iostream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString str1 ="welcome";
    QString str2 ="to ";

    str1.append(str2);

    //std::cout<<str1.toStdString().data();

    QString str3;
    str3=QString("   %1    was   born   in   %2    ").arg("gg").arg(22);
    str3=str3.simplified();
    std::cout<<str3.toStdString();

    std::cout<<str3.startsWith("g",Qt::CaseSensitive);
    std::cout<<str3.contains("t",Qt::CaseSensitive);

    QString str4="3333";
    int xint;
    xint=str4.toInt();
    std::cout<<xint;

    return a.exec();
}
