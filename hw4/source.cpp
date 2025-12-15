#include <iostream>
#include <cstring>

class String
{
private:
    char* data;
    size_t length;

public:
    class Proxy
    {
    private:
        const String* parent;
        size_t start;

    public:
        Proxy(const String* parent, size_t i) : parent(parent), start(i) {}

        String operator[](size_t end) const
        {
            size_t subLen = end - start;
            char* subData = new char[subLen + 1];

            for (size_t i = 0; i < subLen; i++)
            {
                subData[i] = parent->data[start + i];
            }
            subData[subLen] = '\0';

            String result(subData);
            delete[] subData;
            return result;
        }
    };

    String(const char* str = "")
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    String(const String& other)
    {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    ~String()
    {
        delete[] data;
    }

    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    Proxy operator[](size_t i) const
    {
        return Proxy(this, i);
    }

    const char* c_str() const
    {
        return data;
    }

    size_t size() const
    {
        return length;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        os << str.data;
        return os;
    }
};

int main()
{
    String const hello("hello");

    String const hell = hello[0][4];
    std::cout << "hello[0][4] = " << hell << std::endl;

    String const ell = hello[1][4];
    std::cout << "hello[1][4] = " << ell << std::endl;

    String const empty = hello[2][2];
    std::cout << "hello[2][2] = '" << empty << "' (empty string)" << std::endl;

    String const lo = hello[3][5];
    std::cout << "hello[3][5] = " << lo << std::endl;

    return 0;
}