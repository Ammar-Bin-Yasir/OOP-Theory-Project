#ifndef CLASSARRAY_H
#define CLASSARRAY_H

#include <stdexcept>

using namespace std;

template <typename T>
class ClassArray 
{
    private:
        T* data;
        int currentSize;
        int currentCapacity;

        
        // Private method to grow the array when capacity is reached
        void grow()
        {
            currentCapacity = (currentCapacity == 0) ? 2 : currentCapacity * 2;
            
            // Allocate new memory
            T* newData = new T[currentCapacity];
            
            // Copy old data to new memory
            for (int i = 0; i < currentSize; ++i) {
                newData[i] = data[i];
            }

            // Free old memory and update pointer
            delete[] data;
            data = newData;
        }

    public:
        // Constructor
        ClassArray() : data(nullptr), currentSize(0), currentCapacity(0) {}
        ~ClassArray() 
        {
            delete[] data;
        }



        // Copy Constructor 
        ClassArray(const ClassArray& other) : data(nullptr), currentSize(0), currentCapacity(0)
        {
            *this = other;
        }

        // Assignment Operator 
        ClassArray& operator=(const ClassArray& other)
        {
            // If not same
            if (this != &other) 
            {
                delete[] data;
                currentSize = other.currentSize;
                currentCapacity = other.currentCapacity;
                if (currentCapacity > 0) {
                    data = new T[currentCapacity];
                    for (int i = 0; i < currentSize; ++i) {
                        data[i] = other.data[i];
                    }
                } else {
                    data = nullptr;
                }
            }
            return *this;
        }


        // Add item to array
        void add(const T& item)
        {
            if (currentSize == currentCapacity) {
                grow();
            }
            data[currentSize++] = item;
        }


        // Get number of elements
        int getSize() const
        {
            return currentSize;
        }

        // Access element with bounds check (Non-const version)
        T& operator[](int index)
        {
            if (index < 0 || index >= currentSize) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }


        // Access element with bounds check (Const version)
        const T& operator[](int index) const
        {
            if (index < 0 || index >= currentSize) {
                throw std::out_of_range("Index out of bounds");
            }
            return data[index];
        }

        // Remove element at index
        void remove(int index)
        {
            if (index < 0 || index >= currentSize) {
                throw std::out_of_range("Index out of bounds");
            }

            // Shift elements left from the index to "remove" the element
            for (int i = index; i < currentSize - 1; ++i) {
                data[i] = data[i + 1];
            }
            currentSize--;
        }

};

#endif