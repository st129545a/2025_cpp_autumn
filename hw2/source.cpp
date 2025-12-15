#include <iostream>
#include <string>
#include <stack>

class TextEditor
{
    std::stack<char> left;
    std::stack<char> right;

public:
    TextEditor()
    {

    }

    void addText(std::string text)
    {
        for (char c : text)
        {
            left.push(c);
        }
    }

    int deleteText(int k)
    {
        int deleted = 0;
        while (!left.empty() && k > 0)
        {
            left.pop();
            deleted++;
            k--;
        }
        return deleted;
    }

    std::string cursorLeft(int k)
    {
        while (!left.empty() && k > 0)
        {
            right.push(left.top());
            left.pop();
            k--;
        }

        std::string result;
        std::stack<char> temp;

        int count = 0;
        while (!left.empty() && count < 10)
        {
            temp.push(left.top());
            left.pop();
            count++;
        }

        while (!temp.empty())
        {
            result.push_back(temp.top());
            left.push(temp.top());
            temp.pop();
        }

        return result;
    }

    std::string cursorRight(int k)
    {
        while (!right.empty() && k > 0)
        {
            left.push(right.top());
            right.pop();
            k--;
        }

        std::string result;
        std::stack<char> temp;

        int count = 0;
        while (!left.empty() && count < 10)
        {
            temp.push(left.top());
            left.pop();
            count++;
        }

        while (!temp.empty())
        {
            result.push_back(temp.top());
            left.push(temp.top());
            temp.pop();
        }

        return result;
    }
};

int main()
{
    TextEditor editor;

    editor.addText("Hello");
    std::cout << "Added text: Hello" << std::endl;

    std::string leftResult = editor.cursorLeft(2);
    std::cout << "cursorLeft(2) returned: " << leftResult << std::endl;

    editor.addText("world");
    std::cout << "Added text: world" << std::endl;

    int deleted = editor.deleteText(3);
    std::cout << "deleteText(3) deleted: " << deleted << " characters" << std::endl;

    std::string rightResult = editor.cursorRight(2);
    std::cout << "cursorRight(2) returned: " << rightResult << std::endl;

    return 0;
}