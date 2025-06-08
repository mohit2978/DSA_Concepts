### Intro 

The STL or Standard Template Library is a set of C++ template classes to provide common programming data structures and functions such as lists, stacks, arrays, etc. It is a library of container classes, algorithms, and iterators. It is a generalized library and so, its components are parameterized. Whenever a scenario arises that needs an implementation of a particular data structure or for say a binary search or any particular sorting technique, the STL library provides us with the particular function. Using this function, one does not need to write the complete code for a specific operation, instead the STL library provides the best-optimised way of doing it using STL containers and algorithm.

STL divide into parts

1. Containers: A container or container classes store objects and data. There are in total seven standards “first-class” container classes and three container adaptor classes and only seven header files that provide access to these containers or container adaptors.

    - Simple or Sequence Containers: These implement data structures which can be accessed in a sequential manner. For eg.,
        - Pair: The pair container is a simple container defined in header consisting of two data elements or objects.
        - Vector: Vectors are same as dynamic arrays with the ability to resize itself automatically when an element is inserted or deleted, with their storage being handled automatically by the container.
        - forward_list: Forward list in STL implements singly linked list. Introduced from C++11, the forward list is useful than other containers in insertion, removal and moving operations (like sort) and allows time constant insertion and removal of elements.
        - List: Lists are sequence containers that allow non-contiguous memory allocation.
    - Container Adaptors: These provide a different interface for sequential containers. For eg.,
        - Stack: Stacks are a type of container adaptors with LIFO(Last In First Out) type of work, where a new element is added at one end and (top) an element is removed from that end only.
        - Queue: Queues are a type of container adaptors which operate in a first in first out (FIFO) type of arrangement. Elements are inserted at the back (end) and are deleted from the front.
        - Priority_queue: Priority queues are a type of container adapters, specifically designed such that the first element of the queue is the greatest of all elements in the queue and elements are in non-increasing order(hence we can see that each element of the queue has a priority{fixed order}).
    - Associative Containers: These implement sorted data structures that can be quickly searched (O(log n) complexity). For eg.,
        - Set: Sets are a type of associative containers in which each element has to be unique because the value of the element identifies it. The value of the element cannot be modified once it is added to the set, though it is possible to remove and add the modified value of that element.
        - Map: Maps are associative containers that store elements in a mapped fashion. Each element has a key value and a mapped value. No two mapped values can have same key values.
        - Unordered_set: An unordered_set is implemented using a hash table where keys are hashed into indices of a hash table so that the insertion is always randomized.
        - Unordered_map: The unordered_map is an associated container that stores elements formed by a combination of key-value and a mapped value. The key value is used to uniquely identify the element and mapped value is the content associated with the key. Both key and value can be of any type of predefined or user-defined.

2. Algorithm: The header algorithm defines a collection of functions specially designed to be used on ranges of elements. They act on containers and provide means for various operations for the contents of the containers. For eg., binary_search, find, reverse, sort etc. The algorithms use the concept of iterators        

3. Iterators: As the name suggests, iterators are used for working upon a sequence of values. They are the major feature that allows generality in STL.