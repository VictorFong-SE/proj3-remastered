/*counter.h*/

//
// <<Victor Fong>>
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// The Counter container is a set with no duplicates.  However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter".  Users of the Counter container can test for set membership,
// as well as obtain an element's count.
//
// Example:  suppose C is a Counter, and you insert the elements 3, 11,
// 5, 11, 3, and 11.  Then C contains the elements {3, 5, 11}, where 3's
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities.  In terms of space, the container will
// consume at most 4N space.
//

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing:
using std::endl;


template<typename Type>
class Counter
{
private:

    class Set
    {
    public:
        Type value;
        int count;

        Set()
        {
            count = 0;
        }

        explicit Set(Type e)
        {
            value = e;
            count = 0;
        }

    };

    class iterator
    {
        //
        // TODO
        //

    public:
        typedef Type* pointer;

        pointer ptr;

        iterator(pointer ptrVal)
        {
            ptr = ptrVal;
        }

        iterator &operator++()
        {
            ptr++;
            return *this; // return updated iterator back:
        }

        const Type &operator*() // return const ref so can’t change set element:
        {
            return *ptr;
        }

        bool operator!=(const iterator &rhs) // i.e. lhs != rhs?
        {
            return ptr != rhs.ptr;
        }
    };



    Set *set;
    int numElements;
    int capacity;


public:
    //
    // constructor:
    //
    Counter()
    {
        //
        // TODO - DONE
        //
        numElements = 0;
        capacity = 4;

        set = new Set[capacity];
    }


    //
    // copy constructor:
    //
    Counter(const Counter &other)
    {
        //
        // TODO - DONE
        //
        numElements = other.numElements;
        capacity = other.capacity;
        set = new Set[other.capacity];

        std::copy(other.set, other.set + other.numElements, set);

    }


    //
    // destructor:
    //
    ~Counter()
    {
        //
        // TODO - DONE
        //
        delete[] set;
        numElements = 0;
        capacity = 0;
    }


    //
    // size()
    //
    // Returns the # of elements in the set.
    //
    // Time complexity: O(1).
    //
    int size() const
    {
        //
        // TODO - DONE
        //
        return numElements;
    }


    //
    // empty()
    //
    // Returns true if the set is empty, false if not.
    //
    // Time complexity: O(1).
    //
    bool empty() const
    {
        //
        // TODO - DONE
        //
        return numElements == 0;
    }


    //
    // clear()
    //
    // Empties the set, deleting all elements and counts.
    // - RESETS CLASS TO CONSTRUCTED STATE DUE TO LACK OF CLARITY
    void clear()
    {
        //
        // TODO - DONE
        //
        delete[] set;
        set = new Set[4];
        numElements = 0;
        capacity = 4;
    }

    /*
     * Helper function that uses binary search to give either the index of e or -1 if e DNE
     * helps pretty much all the methods below;
     */
    int findHelper(const Type &e) const
    {
        int left = 0;
        int right = numElements;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (set[mid].value == e)
            {  // Check if e is present at mid
                return mid;
            }
            if (set[mid].value < e)
            {   // If e greater, ignore left half
                left = mid + 1;
            }
            else
            {                // If e is smaller, ignore right half
                right = mid - 1;
            }
        }
        // else not present
        return -1;

    }


    //
    // [e]
    //
    // Returns true if set contains e, false if not.
    //
    // NOTE: since the type of e is unknown, elements are compared using <.
    // This implies 2 elements e and y are equal if (!(e<y)) && (!(y<e)).
    //
    // Time complexity: average-case O(lgN). - DONE USING BINARY SEARCH
    //
    bool operator[](const Type &e)
    {
        //
        // TODO - DONE
        //
        return findHelper(e) != -1;
    }

    //
    // (e)
    //
    // Returns a count of how many times e has been inserted into the set;
    // the count will be 0 if e has never been inserted.
    //
    // NOTE: since the type of e is unknown, elements are compared using <.
    // This implies 2 elements e and y are equal if (!(e<y)) && (!(y<e)).
    //
    // Time complexity: average-case O(lgN).
    //
    int operator()(const Type &e) const
    {
        //
        // TODO - DONE
        //
        int index = findHelper(e);
        if (index == -1)
        {
            return 0;
        }
        else
        {
            return set[index].count + 1 ;
        }
    }


    //
    // insert(e)
    //
    // If e is not a member of the set, e is inserted and e's count set to 0.
    // If e is already in the set, it is *not* inserted again; instead, e's
    // count is increased by 1.  Sets are unbounded in size, and elements are
    // inserted in order as defined by Type's < operator; this enables in-order
    // iteration.
    //
    // NOTE: since the type of e is unknown, elements are compared using <.
    // This implies 2 elements e and y are equal if (!(e<y)) && (!(y<e)).
    //
    // Time complexity: worst-case O(N).
    // Space complexity: 4N.
    //
    void insert(const Type &e)
    {
        //
        // TODO - DONE
        //
        int index = findHelper(e);
        if (index == -1)    //if value not in set
        {
            //insert e
            if (numElements == capacity)    // at max capacity
            {
                capacity *= 2;
                Set *buffer = new Set[capacity];
                std::copy(set,set + numElements, buffer);
                delete[] set;
                set = buffer;
            }
            // not full/no longer full
            int i;
            for (i = numElements - 1; (i >= 0 && set[i].value > e); i--)
            {
                set[i + 1].value = set[i].value;
            }
            set[i + 1].value = e;

            //add 0 to count and add to total number of elements
            numElements++;
            set[i+1].count = 0;
        }
        else
        {
            //increase count by 1
            set[index].count++;

        }
    }


    //
    // += e
    //
    // Inserts e into the set; see insert.
    //
    // Time complexity: worst-case O(N).
    // Space complexity: 4N.
    //
    Counter &operator+=(const Type &e)
    {
        //
        // insert e into "this" set:
        //
        this->insert(e);

        // return "this" updated set:
        return *this;
    }


    //
    // lhs = rhs;
    //
    // Makes a deep copy of rhs (right-hand-side) and assigns into
    // lhs (left-hand-side).  Any existing elements in the lhs
    // are destroyed *before* the deep copy is made.
    //
    // NOTE: the lhs is "this" object.
    //
    Counter &operator=(const Counter &rhs)
    {
        //
        // NOTE: where is the lhs in the function call?  The lhs operand is
        // hidden --- it's "this" object.  So think this->operator=(rhs).
        //

        // check for self-assignment:
        if (this == &rhs)
        {  // S = S;
            return *this;
        }


        //
        // TODO - DONE
        //
        delete[] set;
        set = new Set[rhs.capacity];
        numElements = rhs.numElements;
        capacity = rhs.capacity;


        //
        // return "this" updated set:
        //
        return *this;
    }


    //
    // begin()
    //
    // Returns an iterator denoting the first element of the set.  If the
    // set is empty, begin() == end().  The iterator will advance through
    // the elements in order, as defined by Type's < operator.
    //
    iterator begin()
    {
        return iterator(set[0]);
    }


    //
    // end()
    //
    // Returns an iterator denoting the end of the iteration space --- i.e.
    // one past the last element of the set.  If the set is empty, then
    // begin() == end().
    //
    iterator end()
    {
        return iterator(set[numElements]);
    }

};
