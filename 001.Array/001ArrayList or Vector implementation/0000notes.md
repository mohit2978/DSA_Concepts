# Notes
![alt text](<002 AL implemenataion_231018_213227.jpg>)

 ![alt text](<002 AL implemenataion_231018_213227(1).jpg>) ![alt text](<002 AL implemenataion_231018_213227(2).jpg>) ![alt text](<002 AL implemenataion_231018_213227(3).jpg>)

![alt text](<002 AL implemenataion_231018_213227(4).jpg>)

## Code

```cpp

#include <iostream>
using namespace std;


class ArrayList {
    int *arr;
    int num_elements;
    int capacity;

public:
    ArrayList(){
        capacity=2;
        arr=new int[capacity];
        num_elements=0;
    }
    ArrayList(int size) {
        arr = new int[size];
        num_elements = 0;
        capacity = size;
    }
    void insert(int val) {
        if(num_elements < capacity) {
            arr[num_elements]=val;
            num_elements++;
        } else {
            resize();
            arr[num_elements]=val;
            num_elements++;
        }
    }
    
    int getAt(int index){
       return arr[index];
    }

    void resize() {
        int* tempArr=new int[capacity*2];
        capacity*=2;

        for(int i=0; i<num_elements; i++) {
            tempArr[i]=arr[i];
        }

        delete [] arr;
        arr=tempArr;
    }
    int size(){
        return capacity;
    }
    int length() {

        return num_elements;
    }

    void print() {
        for(int i=0; i<num_elements; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

};

int main() {
    ArrayList arr;
    cout << "Arr length : " << arr.length() << endl;
    arr.insert(1);
    arr.insert(2);
    cout<<" Arr size: "<< arr.size()<<" no of elements: "<< arr.length()<<endl; 
    arr.insert(3);
    cout<<" Arr size: "<< arr.size()<<" no of elements: "<< arr.length()<<endl; 
    arr.insert(4);
    cout<<" Arr size: "<< arr.size()<<" no of elements: "<< arr.length()<<endl;
    arr.insert(5);
    cout<<" Arr size: "<< arr.size()<<" no of elements: "<< arr.length()<<endl; 
    arr.insert(6);
    arr.insert(7); 
    arr.insert(8);
    cout <<  "Arr length : " << arr.length() << endl;
    cout << "Array : ";
    arr.print();  
    cout << "Element at index 5 is " << arr.getAt(4) << endl;  
}

/*
rr length : 0
 Arr size: 2 no of elements: 2
 Arr size: 4 no of elements: 3
 Arr size: 4 no of elements: 4
 Arr size: 8 no of elements: 5
Arr length : 8
Array : 1 2 3 4 5 6 7 8 
Element at index 5 is 5
*/
```





