#ifndef FSTRING_H
#define FSTRING_H
#include <iostream>
#include <string>

using namespace std;

class FString
{
public:
    FString(const char* cstr=0);
    FString(const FString& str);
    FString& operator = (const FString& str);
    ~FString();
    char* getData() const {return m_data;}
private:
    char* m_data;
};

FString::FString(const char *cstr)
{
    if(cstr){
        m_data = new char[strlen(cstr)+1];
        strcpy(m_data,cstr);
    }
    else{
        m_data = new char[1];
        *m_data = '\0';
    }
}

FString::FString(const FString& str)
{
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);

}

inline FString&
FString::operator = (const FString& str)
{
    if(m_data == str.m_data) return *this;
    delete[] m_data;
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
    return *this;
}

FString::~FString()
{
    delete[] m_data;
}

ostream& operator << (ostream& os, FString& str)
{
    os << str.getData();
    return os;
}


#endif // FSTRING_H
