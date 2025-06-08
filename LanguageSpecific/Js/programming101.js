console.log("Hi Js");

console.log("------------------------------");

function method(){
    console.log("Hi from fucntion");
    
}

method();

console.log("------------------------------");

function sum(a,b){
    return a+b;
}

console.log( sum(2,4));
console.log("------------------------------");


let arr = Array(10).fill(-1);

function printArr(arr){
    for(let val of arr){
       process.stdout.write(val+" ");
    }
}

printArr(arr)
console.log();
console.log("------------------------------");

//vector<vector<int>> mat(5, vector<int>(10, -1));  2d array
let arr2d=Array(5).fill().map(()=>Array(10).fill(-1)); 

function print2d(arr){
    for(let val of arr){
        printArr(val);
        console.log();
    }
}

print2d(arr2d);

console.log("------------------------------");

let str= "Mohit Kumar Rakheja"

function prtStr1(str){
    for (let ch of str) {
        process.stdout.write(ch+" ");
    }
}

function prtStr2(str){
    str.split('').forEach(ch => {
        process.stdout.write(ch+" ");
    });
}

function prtStr3(str){
    for (let i = 0; i < str.length; i++) {
        process.stdout.write(str[i]+" ");
    }
}

prtStr1(str);
console.log();

prtStr2(str);
console.log();

prtStr3(str);
console.log();

console.log("--------------------------------");

//queue 

let queue = [];

// Enqueue
queue.push(10);
queue.push(20);
queue.push(30);

// Dequeue reoves first element 
console.log(queue.shift()); // 10

// Front element
console.log(queue[0]);  // 20

// Check empty
console.log(queue.length === 0);  // false

//for larger elements make by Linkedlist

console.log("--------------------------------");

let stack = [];

// Push
stack.push(10);
stack.push(20);
stack.push(30);

// Pop
console.log(stack.pop()); // 30

// Top element (peek)
console.log(stack[stack.length - 1]); // 20

// Check empty
console.log(stack.length === 0);  // false

console.log("--------------------------------");

//Linkedlist
class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedList {
    constructor() {
        this.head = null;
    }

    insertAtHead(data) {
        const newNode = new Node(data);
        newNode.next = this.head;
        this.head = newNode;
    }

    printList() {
        let current = this.head;
        while (current !== null) {
            console.log(current.data);
            current = current.next;
        }
    }
}

let list = new LinkedList();
list.insertAtHead(10);
list.insertAtHead(20);
list.insertAtHead(30);

list.printList();  // 30 20 10

console.log("--------------------------------");

//Map 

let myMap = new Map();
//Keys can be any type (not just strings).

myMap.set('a', 1);
myMap.set(42, 'answer');
myMap.set(true, 'yes');

console.log(myMap.get('a'));   // 1
console.log(myMap.get(42));    // "answer"


myMap.set([1,2,3,5],{"name":"hi", "from":"map"});
console.log(myMap.get([1,2,3,5])); 
//returns undefined as both array point to different location , both are different array

let key = [1, 2, 3, 5];
myMap.set(key, {"name":"hi", "from":"map"});

console.log(myMap.get(key));  // works correctly

console.log(myMap.has('a'));  // true
console.log(myMap.has('b')); //false

myMap.delete(42);


console.log(myMap.size);

for (let [key, value] of myMap) {
    console.log(key, value);
}

console.log("---------------------------------");

let mySet = new Set();

mySet.add(10);
mySet.add(20);
mySet.add(10);  // duplicate, ignored

console.log(mySet.has(10));  // true
console.log(mySet.has(30));  // false

mySet.delete(10);

console.log(mySet.size);  // current size of set

for (let value of mySet) {
    console.log(value);
}


console.log("------------------------------");

//No pq here need to write whole code

class MinHeap {
    constructor() {
        this.heap = [];
    }

    getParentIndex(i) { return Math.floor((i - 1) / 2); }
    getLeftChildIndex(i) { return 2 * i + 1; }
    getRightChildIndex(i) { return 2 * i + 2; }

    swap(i, j) {
        [this.heap[i], this.heap[j]] = [this.heap[j], this.heap[i]];
    }

    insert(val) {
        this.heap.push(val);
        this.heapifyUp();
    }

    heapifyUp() {
        let index = this.heap.length - 1;
        while (index > 0) {
            let parentIndex = this.getParentIndex(index);
            if (this.heap[parentIndex] > this.heap[index]) {
                this.swap(parentIndex, index);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    extractMin() {
        if (this.heap.length === 0) return null;
        if (this.heap.length === 1) return this.heap.pop();

        const min = this.heap[0];
        this.heap[0] = this.heap.pop();
        this.heapifyDown();
        return min;
    }

    heapifyDown() {
        let index = 0;
        const length = this.heap.length;

        while (this.getLeftChildIndex(index) < length) {
            let smallerChildIndex = this.getLeftChildIndex(index);
            let rightChildIndex = this.getRightChildIndex(index);

            if (rightChildIndex < length && this.heap[rightChildIndex] < this.heap[smallerChildIndex]) {
                smallerChildIndex = rightChildIndex;
            }

            if (this.heap[index] > this.heap[smallerChildIndex]) {
                this.swap(index, smallerChildIndex);
                index = smallerChildIndex;
            } else {
                break;
            }
        }
    }

    peek() {
        return this.heap.length === 0 ? null : this.heap[0];
    }

    size() {
        return this.heap.length;
    }
}


// JavaScript engines implement Map and Set using hash tables internally.

// Because of hashing, operations like insert, lookup, and delete are expected to be constant time on average.
