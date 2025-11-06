#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class GenericArray {
private:
    T* data;
    int length;

public:
    // Constructor
    GenericArray() : data(nullptr), length(0) {}

    // Destructor
    ~GenericArray() {
        delete[] data;
    }

    // Add an element to the end
    void addElement(T value) {
        T* newData = new T[length + 1]; // allocates new array
        for (int i = 0; i < length; ++i) {
            newData[i] = data[i]; // copies old data
        }
        newData[length] = value; // adds new element

        delete[] data; // frees old memory
        data = newData;
        length++;
    }

    // Returns value at a given index
    T at(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    // Return size of array
    int size() const {
        return length;
    }

    // Sum of all elements
    T sum() const {
        if (length == 0) return 0;
        T total = 0;
        for (int i = 0; i < length; ++i) {
            total += data[i];
        }
        return total;
    }

    // Maximum element
    T max() const {
        if (length == 0) throw runtime_error("Array is empty");
        T maxVal = data[0];
        for (int i = 1; i < length; ++i) {
            if (data[i] > maxVal) maxVal = data[i];
        }
        return maxVal;
    }

    // Minimum element
    T min() const {
        if (length == 0) throw runtime_error("Array is empty");
        T minVal = data[0];
        for (int i = 1; i < length; ++i) {
            if (data[i] < minVal) minVal = data[i];
        }
        return minVal;
    }

    // Return a new array (slice)
    T* slice(int begin, int end) const {
        if (begin < 0 || end >= length || begin > end) {
            throw out_of_range("Invalid slice bounds");
        }

        int sliceSize = end - begin + 1;
        T* sliceArr = new T[sliceSize];

        for (int i = 0; i < sliceSize; ++i) {
            sliceArr[i] = data[begin + i];
        }

        return sliceArr; // caller must delete[] it
    }
};

int main() {
    GenericArray<int> int_array;

    // Add elements
    for (int i = 0; i < 10; ++i) {
        int_array.addElement(i * 2); 
    }

    cout << "Array contents: ";
    for (int i = 0; i < int_array.size(); ++i) {
        cout << int_array.at(i) << " ";
    }
    cout << "\n";

    cout << "Size of array: " << int_array.size() << endl;
    cout << "Sum of array: " << int_array.sum() << endl;
    cout << "Max of array: " << int_array.max() << endl;
    cout << "Min of array: " << int_array.min() << endl;

    // Slice example
    try {
        int* sliced = int_array.slice(2, 5);
        cout << "Sliced array [2..5]: ";
        for (int i = 0; i <= (5 - 2); ++i) {
            cout << sliced[i] << " ";
        }
        cout << endl;
        delete[] sliced; // cleanup
    } catch (out_of_range& e) {
        cout << "Slice error: " << e.what() << endl;
    }

    return 0;
}

