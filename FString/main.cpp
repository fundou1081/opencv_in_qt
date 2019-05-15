#include <QCoreApplication>
#include "fstring.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FString ff("hello world");
    FString ff2;

    char ca;
    ca='9';

    char a1;
    int a2;
    float a3;
    double a4;
    long double a5;

    cout << ff<<endl;
    cout << strlen("cacc")<<endl;
    cout << sizeof(a1)<<endl;
    cout << sizeof(a2)<<endl;
    cout << sizeof(a3)<<endl;
    cout << sizeof(a4)<<endl;
    cout << sizeof(a5)<<endl;

    cout << sizeof(void*)<<endl;
    cout << sizeof(char*)<<endl;

    return a.exec();
}
