#include<iostream>
using namespace std;
int main(){
    pair <int, char> PAIR1 ;

    PAIR1.first = 100;
    PAIR1.second = 'G' ;

    cout << PAIR1.first << " " ;
    cout << PAIR1.second << endl ;
    //output: 100 G

    pair <string,double> PAIR2 ("GeeksForGeeks", 1.23);

    cout << PAIR2.first << " " ;
    cout << PAIR2.second << endl ;
    //output:GeeksForGeeks 1.23

    pair <int, double> PAIR3 ;
    pair <string, char> PAIR4 ;

    cout << PAIR3.first ;  // it is initialised to 0
    cout << PAIR3.second ; // it is initialised to 0

    cout << " ";

    cout << PAIR4.first ;  // it prints nothing i.e NULL
    cout << PAIR4.second <<endl; // it prints nothing i.e NULL

    pair <string, double> PAIR5=make_pair ("Mohit",4.56);
    cout << PAIR5.first << " " ;
    cout << PAIR5.second << endl ;

    //output:Mohit 4.56

   pair<int,int>p1(10,13);
   pair<int,int>p2(9,11);

   cout<< (p1>p2)<<endl; //ouput :1 as p1.first>p2.first

   pair<int,int>temp=p1;
   p1=p2;
   p2=temp;

   cout<<p1.first<<" "<<p1.second<<endl;
   cout<<p2.first<<" "<<p2.second<<endl;

   //output:
   // 9 11
   // 10 13

   cout<< (p1>p2)<<endl; //0 as p1.first <p2.first

   p1.first=10; 
    cout<< (p1>p2)<<endl;//after first second is compared so p1.seond <p2.second

    pair<int,int>p3;
    cin>>p3.first;
    cin>>p3.second;
    // we can take input like this too
    return 0;
}