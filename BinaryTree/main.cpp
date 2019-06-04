#include <iostream>
#include <random>
#include <ctime>
#include <stack>

#define aSize 60000
using namespace std;


void showResult(int a[])
{
    for(int i=0;i<aSize;i++)
    {
        cout << a[i]<<' ';
    }
    cout <<endl;
}

void popsort(int a[]){
    int s=0;
    for(int i=0;i<aSize;i++)
    {
        for(int j=i;j<aSize-1;j++)
        {
            if(a[j] < a[j+1])
            {
                int tmp =a[j+1];
                a[j+1]=a[j];
                a[j] = tmp;
                s++;
            }
        }
    }
    cout<<"s="<<s<<endl;
}

void popsort2(int a[]){
    int s=0;
    for(int i=0;i<aSize;i++)
    {
        for(int j=i;j<aSize-1;j++)
        {
            if(a[j] < a[j+1])
            {
                int tmp =a[j+1];
                a[j+1]=a[j];
                a[j] = tmp;
            }
        }
    }
    cout<<"s="<<s<<endl;
}

void selectsort(int a[])
{
    int s=0;
    for(int i=0;i<aSize-1;i++){
        int max=i;
        for(int j=i+1;j<aSize;j++)
        {
            if(a[max] < a[j]){
                max = j;
                s++;
           }
        }
        int tmp = a[i];
        a[i]=a[max];
        a[max] = tmp;
    }
    cout<<"s="<<s<<endl;
}

void selectsort2(int a[])
{
    int s=0;
    for(int i=0;i<aSize;i++){
        int max=i;
        for(int j=aSize-1;j>i;j--)
        {
            if(a[max] < a[j]){
                 max = j;
                 s++;
            }
        }
        int tmp = a[i];
        a[i]=a[max];
        a[max] = tmp;

    }
    cout<<"s="<<s<<endl;
}

void qsort(int a[],int l,int r){

    if(l<r){
        int i=l;
        int j=r;
        int x=a[l];

        while(i<j)
        {
            while(a[j]>x && i<j)   j--;
            if(i<j){
                a[i]=a[j];
                i++;
                //showResult(a);
            }

            while(a[i]<x && i<j)   i++;
            if(i<j){
                a[j]=a[i];
                j--;
                //showResult(a);
            }
        }
        a[i]=x;
        //cout <<"@@@ ";
        //showResult(a);
        qsort(a,l,i-1);
        qsort(a,i+1,r);
    }
}

void qsort2(int a[]){
    stack<int> si;
    stack<int> sj;
    stack<int> smdata;

    int i=0;
    int j=0;
    int mdata;

    si.push(0);
    sj.push(aSize-1);
    smdata.push(a[i]);

    int af,bf;

    while(!(si.empty() && sj.empty() ))
    {
        i=si.top();
        j=sj.top();
        mdata=smdata.top();

        si.pop();
        sj.pop();
        smdata.pop();

        af=i;bf=j;

        if (af==bf) continue;

        mdata = a[i];
        while(i<j)
        {
            while(i<j && mdata < a[j]){
                j--;
            }
            if(i<j){
                a[i]=a[j];
                i++;
            }
            while(i<j && a[i] < mdata){
                i++;
            }
            if(i<j){
                a[j]=a[i];
                j--;
            }
        }
        a[i]=mdata;

        // B
        if(i+1<bf){
            si.push(i+1);
            sj.push(bf);
            smdata.push(a[i+1]);
        }

        // A
        if(af<i-1){
            si.push(af);
            sj.push(i-1);
            smdata.push(a[af]);
        }

        showResult(a);
    }

}

void mergeA(int a[], int first, int mid, int last, int temp[]){
    int i = first, j = mid + 1;
    int m = mid,   n = last;
    int k = 0;
    while (i <= m && j <= n)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= m)
        temp[k++] = a[i++];

    while (j <= n)
        temp[k++] = a[j++];

    for (i = 0; i < k; i++)
        a[first + i] = temp[i];

}

void merge(int a[],int first, int last, int p[]){
    if(first < last)
    {
        int mid = (first + last) / 2;
        merge(a,first,mid,p);
        merge(a,mid+1,last,p);
        mergeA(a,first,mid,last,p);
    }
}


void Mergesort(int a[]){
    int* p =new int[aSize];
    merge(a,0,aSize-1,p);
    delete[] p;
}


int main()
{
    default_random_engine e(211);
    uniform_int_distribution<int> u(0,100);

    clock_t start,finish;


    int a[aSize];
    int b[aSize];
    for(int i=0;i<aSize;i++)
    {
        a[i]=u(e);
        b[i]=a[i];
    }

    showResult(a);

    //
    start = clock();
    //popsort(a);
    //selectsort(a);
    //selectsort2(b);
    qsort(a,0,aSize-1);
    //qsort2(a);
    Mergesort(b);
    finish = clock();
    //
    int timeA = finish-start;

    //
    start = clock();
    Mergesort(b);
    finish = clock();
    //
    int timeB = finish-start;

    cout << "OK" <<endl;

    showResult(a);
    cout << "timeA=" << timeA << endl;
    cout << "timeB=" << timeB << endl;

    return 0;
}
