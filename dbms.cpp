#include<bits/stdc++.h>
using namespace std;
int ld=1,gd=2;
int flag=0;
//global depth assumed to be 2, local depth assumed to be 1 , blocking factor assumed to be 2 , hashing to be mod10 function

struct bucket
{
    int x=-1,y=-1,ld=1;
    int str[15]={};
};

vector <bucket*> directory;
bucket b0;
bucket b1;
bucket* ptr0=&b0;
bucket* ptr1=&b1;

int position(int arr[])
{
  int temp=gd;
  int pos=0;
  int power=0;
  while(temp!=0)
  {
   int num=pow(2,power)*arr[power]; 
   pos+=num;
   power++;
   temp--;
  }
  return pos;
  
}

void dectobin(int arr[],int x)
{

 int num=x,i=0,r;
 while(num!=0)
{
  r = num%2;
  arr[i++] = r ;
  num /= 2;
}
}

int value(int arr[],int l)
{
  int temp=l;
  int pos=0;
  int power=0;
  while(temp!=0)
  {
   int num=pow(2,power)*arr[power]; 
   pos+=num;
   power++;
   temp--;
  }
  return pos;
}

void rearrange1(bucket* ptr,int p)
{
int k=p%10;  
int d=ptr->x;
int a=d%10;
int e=ptr->y;
int b=e%10;
int c=ptr->ld;

ptr->x=-1;
ptr->y=-1;
ptr->str[c-1]=0;
bucket* ptr2=new bucket;
ptr2->ld=c;
int i;
for( i=0;i<c-1;i++)
{ptr2->str[i]=ptr->str[i];
}
ptr2->str[i]=1;


//rearranging the numbers nowwww

int arrx[15]={};
int arry[15]={};
int arrk[15]={};
dectobin(arrx,a);
dectobin(arry,b);
dectobin(arrk,k);
if(value(arrx,c)==value(ptr->str,c))
{
  ptr->x=d;
}
else
{
  ptr2->x=d;
}
if(value(arry,c)==value(ptr->str,c))
{
  if(ptr->x==-1)
  ptr->x=e;
  else
  ptr->y=e;
}
else 
{
  if(ptr2->x==-1)
  ptr2->x=e;
  else
  ptr2->y=e;
}
if(value(arrk,c)==value(ptr->str,c))
{
  if(ptr->x==-1)
  ptr->x=p;
  else if(ptr->y==-1)
  ptr->y=p;
  else if(ptr->x!=-1 && ptr->y!=-1)
  { 
   cout<<"UNEXPECTED INPUT .....Quitting\n"<<endl;
   flag=1;
  }
}
else 
{
  if(ptr2->x==-1)
  ptr2->x=p;
  else if(ptr2->y==-1)
  ptr2->y=p;
  else if(ptr2->x!=-1 && ptr2->y!=-1)
  { 
   cout<<"UNEXPECTED INPUT .....Quitting\n"<<endl;
   flag=1;
   return;
  }
}
//directory change nowwwwww
 i=0;
 int num2=value(ptr->str,c);
 int num3=value(ptr2->str,c);
 while(i!=(pow(2,gd)))
 {
   int arr[15]={};
   dectobin(arr,i);
   int num=value(arr,c);
   if(num==num2)
   {directory[i]=ptr;}
   else if(num==num3)
   {directory[i]=ptr2;}
   i++;
 }
}

void rearrange2(bucket*ptr ,int k)
{
  
  vector<bucket> buck;
  for(int i=0;i<pow(2,gd-1);i++)
  {
    bucket*ptr=directory[i];
    buck.push_back(*ptr);
  }
  
  directory.resize(pow(2,gd));
  for(int i=0;i<buck.size();i++)
  {
    int num=value(buck[i].str,buck[i].ld);
    for(int j=0;j<pow(2,gd);j++)
    {
      int arr[15]={};
      dectobin(arr,j);
      int num2=value(arr,buck[i].ld);
      if(num2==num)
      {
        bucket* ppp=&buck[i];
        directory[j]=ppp;
      }

    }
  }
  
  rearrange1(ptr,k);

}



void insert(int k)
{int arr[15]={};
 int hashed=k%10;
 dectobin(arr,hashed);
 int pos=position(arr);
 bucket* ptr=directory[pos];
 if(ptr->x==-1)
 {
  cout<<"x insertion\n";
  ptr->x=k;
 }
 else if(ptr->y==-1)
 {
  cout<<"y insertion\n";
   ptr->y=k;
 }
 else if(ptr->ld < gd)
 { 
   cout<<"Bucket Overflow Situation(ld<gd)\n";
   (ptr->ld)+=1;
   rearrange1(ptr,k);
 }
 else if(ptr->ld==gd)
 {
   cout<<"Bucket Overflow Situation(ld==gd)\n\n";
   (ptr->ld)+=1;
   gd++;
   rearrange2(ptr,k);
 }
}

void insertoption()
{
    cout<<"Enter value to be inserted: ";
     int x,arr[15]={};
     cin>>x;
     insert(x);
     if(flag==1)
     return ;
     //printing gui type work
     //first what directory points to what bucket
     for(int j=0;j<directory.size();j++)
     {
       cout<<"Directory ";
       int arr[15]={};
       dectobin(arr,j);
       for(int t=gd-1;t>=0;t--)
       {
        cout<<arr[t];
       } 
       cout<<" points to ";
       bucket*ptr =directory[j];
       for(int t=ptr->ld-1;t>=0;t--)
       {
         cout<<ptr->str[t];
       }
       cout<<" which contains the input values: ";
       int ding=0;
       if(ptr->x==-1)
       cout<<" None at the moment.";
       else if(ptr->x!=-1)
       cout<<ptr->x;
       if(ptr->x!=-1 && ptr->y==-1)
       cout<<" only";
       else if(ptr->y!=-1)
       cout<<" and "<<ptr->y<< "(Bucket is full now)";
       cout<<"\n";
     }
}


void start()
{
b0.str[0]=0;
b1.str[0]=1;
directory.push_back(ptr0);
directory.push_back(ptr1);
directory.push_back(ptr0);
directory.push_back(ptr1);
}

void search()
{
  cout<<"Enter value to be searched: ";
  int k;
  cin>>k;
  int num=k%10;
  int arr[15]={};
  dectobin(arr,num);
  int pos=position(arr);
  bucket* ptr=directory[pos];
  if(ptr->x==k || ptr->y==k)
  {
    cout<<"FOUND ";
  }
  else 
  cout<<"NOT FOUND";
}

int main()
{
    cout<<"Goodmorning Sir/Ma'am!"<<endl;
    cout<<"For the extended hasing implementation we have assumed the following:"<<endl;
    cout<<"Hash function: mod 10"<<endl;
    cout<<"Initial global depth:2"<<endl;
    cout<<"Initial local depth:1"<<endl;
    cout<<"Initial number of buckets is 2 and number of directory entries is 4\n";
    cout<<"Blocking factor=2 and size on one block assumed to be equal to size of one bucket.\n";
    start(); 
    int n;
    while( n!=3)
    { 
      cout<<"\nPress 1 to Insert,2 to Search,3 to Quit.\n";
      cin>>n;
      if(n==1)//input
     {
      insertoption();
      if(flag==1)
      return 0; 
     }
     else if (n==2)
     {
      search();
     } 
    else if(n==3)
    {
      cout<<"Thank you for your time. Have a great day!\n";
    }
    }
return 1;
}