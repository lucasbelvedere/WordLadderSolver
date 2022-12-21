#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


// Node will be used for convert.
struct Node {
    std::string word;
    std::string prev;
    int lc_distance;
    int sum;
      
    Node()
    {
        word = "";
        prev = "";
        lc_distance = -1;
        sum = -1;
    }
    
    Node(std::string word, std::string prev, int lcd, int sum)
    {
        this->word = word;
        this->prev = prev;
        this->lc_distance = lcd;
        this->sum = sum;
    }
    
    const bool operator<(const Node& other) const
    {
        return (lc_distance+sum < other.lc_distance+other.sum) ? true : false;
    }
    
    const bool operator>(const Node& other) const
    {
        return (lc_distance+sum > other.lc_distance+other.sum) ? true : false;
    }
    
};

template<typename Object>
class MyPriorityQueue
{
private:
	// member variable.
    std::vector<Object> minheap;
    
public:

	MyPriorityQueue();

	~MyPriorityQueue();

 	size_t size() const noexcept;

	bool isEmpty() const noexcept;

	void insert(const Object & elem);

	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, I will do this.
	const Object & min() const; 

	void extractMin();
    
};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{}

template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
    return minheap.size();
}

template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
    return minheap.empty();
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
    minheap.push_back(elem);
	if( minheap.size() != 1 )
    {
        size_t index = minheap.size();
        while( minheap[(index/2)-1] > minheap[index-1] )
        {
            
            // swap operation.
            Object tmp = minheap[(index/2)-1];
            minheap[(index/2)-1] = minheap[index-1];
            minheap[index-1] = tmp;
            
            // changes index.
            index = ( index/2 );
            if( index == 1 ) break;
        }
    }
}

template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	if(minheap.empty())
        throw RuntimeException("Error: Min Heap is empty");
    
    // returns value at index 0, which should be min.
    return minheap[0];
}

template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
    
    if(minheap.empty())
        throw RuntimeException("Error: Min Heap is empty");
    if(minheap.size() == 1)
        minheap.pop_back();
    
    else{
        // swap min with max.
        minheap[0] = minheap[minheap.size()-1];
        minheap.pop_back();
        Object tmp;
        unsigned index = 1;
        
        while( !( index * 2 > minheap.size() ))
        {
            if( ( ( index * 2 ) + 1  > minheap.size() ) )
            {// makes comparisson with left child only.
                if( minheap[ index-1 ] > minheap[ (index*2) - 1 ] )
                { // if value of index is greater, swaps.
                    tmp = minheap[ index - 1 ];
                    minheap[ index-1 ] = minheap[ (index*2) - 1 ];
                    minheap[ (index*2) - 1 ] = tmp;
                    
                    index *= 2;
                }
                else break;
            }
            else{ // makes comparissons with both childs.
                if( minheap[ (index*2) - 1 ] < minheap[ (index*2) ] )
                { // case where left child is lower.
                    if( minheap[ (index) - 1 ] > minheap[ (index*2) - 1] )
                    { // if value of index is greater, swaps.
                        tmp = minheap[ index - 1 ];
                        minheap[ index - 1 ] = minheap[ (index*2) - 1 ];
                        minheap[ (index*2) - 1 ] = tmp;
                        
                        index *= 2;
                    }
                    else break;
                }
                else { // case where right child is lower.
                    // TODO: CHECK FOR CASES WHERE REPETITIVE CHARS ARE IN.
                    if( minheap[ (index) - 1 ] > minheap[ (index*2) ] )
                    { // if value of index is greater, swaps.
                        tmp = minheap[ index - 1 ];
                        minheap[ index - 1 ] = minheap[ index*2 ];
                        minheap[ index*2 ] = tmp;
                        
                        index = ( index * 2 ) + 1;
                    }
                    else break;
                }
            }
        }
    }
}

#endif 
