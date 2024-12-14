#include <iostream>
//#define NDEBUG
#include <cassert>

// custom exception class to handle out of bounds array access.
class IndexOutOfBoundsException : public std::exception {
public:
    [[nodiscard]]
    const char* what() const noexcept override {
        return "Index out of bounds.";
    }
};

class IntArray {

private :
    int* m_ptr{nullptr}; // pointer
    int  m_size{0};      // size of array

public:
    IntArray()  = default; // synthesize a default constructor, create empty array as defined in private member implementation.

    // the explicit keyword instructs the compiler to not use this as the implicit constructor.
    // mark one argument constructors with explicit keyword.
    explicit IntArray(int size) {
        if(size != 0){
            // memory allocated with new must be released invoking delete.
            m_ptr = new int[size]{}; // allocate a block of memory with a safe clear array object
            m_size = size;
        }
    }

    // destructor to free memory block for the array.
    ~IntArray(){
        delete[] m_ptr; // can be safely invoked on a nullptr value
    }

    // query size of array
    [[nodiscard]]
    int Size() const { // const don't modify array, return readonly properties.
        return m_size;
    }

    // query if array is empty.
    [[nodiscard]]
    bool IsEmpty() const { // const don't modify array, return readonly properties.
         return (m_size == 0);
    }

    // read only bounds checking to prevent buffer overflows
    [[nodiscard]]
    bool IsValidIndex(int index) const {
        return (index >= 0) && (index < m_size);
    }

    // access to array elements
    // return a reference not the value.
    int& operator[](int index){
        if(!IsValidIndex(index)){
            // throw an exception if index is out of bounds.
            throw IndexOutOfBoundsException{};
        }
        return m_ptr[index];
    }

    // allow readonly access to a value in an array.
    int operator[](int index) const {
        if(!IsValidIndex(index)){
            // throw an exception if index is out of bounds.
            throw IndexOutOfBoundsException{};
        }
        return m_ptr[index];
    }
};



int main() {
    using std::cout;

    try {

        cout << " Creating an empty array.\n";
        IntArray a{}; // create empty array
        cout << " a.Size() is " << a.Size() << "\n";
        assert(a.IsEmpty());

        cout << " -----------------------------------------\n";

        cout << " Creating an array containing 10 elements.\n";
        IntArray b{10};
        cout << " b.Size() is " << b.Size() << "\n";
        assert(!b.IsEmpty());

        cout << " -----------------------------------------\n";

        cout << " Setting b[0] = 10 \n";
        b[0] = 10;
        cout << " b[0] is " << b[0] << "\n";

        cout << " -----------------------------------------\n";

        cout << " Getting b[0] \n";
        cout << " b[0] is " << b[0] << "\n";

        cout << " -----------------------------------------\n";

        cout << " Trying to access b[12] \n";
        cout << " b[12] is " << b[12] << "\n";
    }
    catch (const IndexOutOfBoundsException& e){ // catch the original exception, not a copy
        cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}

