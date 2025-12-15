#include <iostream>

template <class T, size_t size>
class Array
{
    T array[size];
public:
    Array() {}

    Array(T* b)
    {
        for (size_t i = 0; i < size; i++)
        {
            array[i] = b[i];
        }
    }

    void show()
    {
        for (size_t i = 0; i < size; i++)
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    T minimum()
    {
        T min = array[0];
        for (size_t i = 1; i < size; i++)
        {
            if (array[i] < min)
            {
                min = array[i];
            }
        }
        return min;
    }
};

int main()
{
    int intArray[] = { 5, 2, 8, 1, 9, 3 };
    Array<int, 6> arr1(intArray);

    std::cout << "Integer array: ";
    arr1.show();
    std::cout << "Minimum value: " << arr1.minimum() << std::endl;

    double doubleArray[] = { 3.5, 1.2, 4.7, 0.8, 2.9 };
    Array<double, 5> arr2(doubleArray);

    std::cout << "\nDouble array: ";
    arr2.show();
    std::cout << "Minimum value: " << arr2.minimum() << std::endl;

    char charArray[] = { 'z', 'a', 'm', 'c', 'f' };
    Array<char, 5> arr3(charArray);

    std::cout << "\nChar array: ";
    arr3.show();
    std::cout << "Minimum value: " << arr3.minimum() << std::endl;

    return 0;
}