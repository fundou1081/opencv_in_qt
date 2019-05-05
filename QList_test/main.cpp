#include <QDebug>
#include <QQueue>

int main(int argc, char *argv[])
{
    QList<QString> list;
    QString str("This is a test string");
    list<<str;
    qDebug()<<list[0]<<"howwwwwww";

    QQueue<QString> list2;
    list2<<str;
    qDebug()<<list2[0]<<"howwwwwww";
    QQueue<QString>::iterator ilist2;
    ilist2 = list2.begin();
    qDebug()<<*ilist2;

    QMap<QString,QString> map;
    map.insert("a","1");
    map.insert("b","2");
    map.insert("c","3");
    map.insert("d","4");
    QMap<QString,QString>::iterator imap;
    imap=map.begin();
    while(imap!=map.end())
    {
        qDebug()<<imap.key()<<imap.value();
        ++imap;
    }


    return 0;
}
