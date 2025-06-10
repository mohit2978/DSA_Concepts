#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<int> v = {1, 2, 3, 4, 5};

    for (int i : v) {
        cout << i << " ";
     }
        cout<<"\n";
    vector<pair<int,int>>v1;

    // by default all value zero in case of vector<int>
    //in case of bool it is false by default

    for(int i=0;i<4;i++){
        v1.push_back({i,i+1});
    }

    //like push_back() for insert we have pop_back() to delete for last element!!

    //for each loop
    for(pair<int,int>el:v1){
        cout<<el.first<<" "<<el.second<<endl;
    }
     cout<<"\n";

     /*
     1 2 3 4 5 
    0 1
    1 2
    2 3
    3 4
     */

    cout<<"iterator-----------"<<endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout<<endl;
    cout<<"iterator end---------------"<<endl;    

    /*
    iterator-----------
    1 2 3 4 5 
    iterator end---------------
    */

    //erase()--> removes an 
    //element from the vector by a position causing all 
    //subsequent elements to be shifted one position to the left.
    //This helps reduces the size of the vector by one.

    //size() --> tells size of vector

    v.erase(v.begin()+2); //erases v[2] and shift every other to left
    cout<<"begin--------------"<<endl;
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl<<"end----------------"<<endl;
    /*
    output:
    begin--------------
    1 2 4 5 
    end----------------
    */

   // insert()--> inserts elements at a specified position 
   //in the vector. It shifts all elements at and 
   //after the insertion point to the right, increasing the vector's size.

   v.insert(v.begin()+1,40);//insert 40 at v[1]
    cout<<"begin--------------"<<endl;
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl<<"end----------------"<<endl;

    /*Output:
    begin--------------
    1 40 2 4 5 
    end----------------
    */

   //swapping of two arrays using swap
    vector<int> v2 = {1, 2, 3};
   vector<int> v3= {4, 5, 6};
   cout<<"v2 array"<<endl;
   for( int i=0;i<v2.size();i++) cout<<v2[i]<<" ";
    cout<<endl;
    cout<<"v3 array"<<endl;
   for( int i=0;i<v3.size();i++) cout<<v3[i]<<" ";
   swap(v2,v3);
   cout<<endl<<"after swap--------------------"<<endl;

   cout<<"v2 array"<<endl;
   for( int i=0;i<v2.size();i++) cout<<v2[i]<<" ";
    cout<<endl;
    cout<<"v3 array"<<endl;
   for( int i=0;i<v3.size();i++) cout<<v3[i]<<" ";
    cout<<endl;
   /*
   output:
   v2 array
    1 2 3 
    v3 array
    4 5 6 
    after swap--------------------
    v2 array
    4 5 6 
    v3 array
    1 2 3 
   */
    //clear the vector
   v3.clear();

   cout<<"Size is "<<v3.size()<<endl;

   /*
   Size is 0
   */

  //2d vector
  vector<vector<int>>twoDv;
  for(int i=1;i<=3;i++){
    vector<int>oneDv(i,i*2);//1d vector of size i and all values 0
    twoDv.push_back(oneDv);

  }
cout<<"print 2d vector--------------------------"<<endl;
  for(int i=0;i<twoDv.size();i++){
    for(int j=0;j<twoDv[i].size();j++){
        cout<<twoDv[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"printing end--------------------------------"<<endl;

  /*
  output:
  print 2d vector--------------------------
    2 
    4 4 
    6 6 6 
    printing end--------------------------------
  */

 vector<vector<int>>twoDv1(5,vector<int>(3,-1));//2d vector of 5*3 having all values -1
   cout<<"print 2d vector--------------------------"<<endl;
  for(int i=0;i<twoDv1.size();i++){
    for(int j=0;j<twoDv1[i].size();j++){
        cout<<twoDv1[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<"printing end--------------------------------"<<endl;

  /*Output:
  print 2d vector--------------------------
    -1 -1 -1 
    -1 -1 -1 
    -1 -1 -1 
    -1 -1 -1 
    -1 -1 -1 
    printing end--------------------------------

  */
  vector<vector<char>>twoDv2(5,vector<char>(3,'f'));
  cout<<"print 2d vector using for each loop--------------------------"<<endl;
  for(vector<char>v:twoDv2){
    for(char ch:v){
        cout<<ch<<" ";
    }
    cout<<endl;
  }
    cout<<"printing end--------------------------------"<<endl;

    /*Output:
    print 2d vector using for each loop--------------------------
    f f f 
    f f f 
    f f f 
    f f f 
    f f f 
    printing end--------------------------------
    
    */
   vector<int>v5={4,5,6,7,8,9,10,11,12};

   for(auto it=v5.begin();it!=v5.end();++it){
    *it=*it+1;
   }
    cout<<"----------see incremented value----------------"<<endl;
   for(auto x:v5){
    cout<<x<<" ";
   }
    cout<<"--------------------------------"<<endl;
    // we do not want iterator to change value so use const iterator thats only read only
   vector<int>vec={4,5,6,7,8,9,10,11,12};
      vector<int>::const_iterator it;
   cout<<"----------see const iterator value----------------"<<endl;
    cout << "Elements in the vector: ";
    for (it = vec.cbegin(); it != vec.cend(); ++it) {
        cout << *it << " "; // Access value (read-only)
        // *it = 10; // Error: Cannot modify value using const_iterator
    }
    cout << endl;

     cout<<"--------------------------------";

     /*
     Output:
        ----------see incremented value----------------
        5 6 7 8 9 10 11 12 13 --------------------------------
        ----------see const iterator value----------------
        Elements in the vector: 4 5 6 7 8 9 10 11 12 
        --------------------------------
     
     
     */
    cout<<endl;
    //initialise vector by array
    // used when input is as an array and you need vector
    int arr[5]={20,30,40,50,60};
    vector<int>vecArr(arr,arr+5);
    cout<<"Size of vector is "<<vecArr.size()<<endl;
    //in case input an array initialise vecArr(arr, arr+n)
    /*
    Size of vector is 5
    */

   vector<int>vecCopy=vecArr; 
   //vecCopy is copy of vecArr any operation on vecCopy not affect vecArr

   vector<int>&vecCopy2=vecArr;
   //vecCopy2 is not copy of vecArr any operation on vecCopy will definitely affect vecArr
   //whenever passing any STL container to function we pass by reference
   //so function can perform changes on the container

  vector<int>v[4];// array of vectors v[0],v[1],v[2],v[3] all are vectors
   
    return 0;
}