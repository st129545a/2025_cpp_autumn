#include <gtest/gtest.h>
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

    void addText(std::string text)Û
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

    std::string getFullText()
    {
        std::string result;
        std::stack<char> tempLeft = left;
        std::stack<char> tempRight = right;

        std::stack<char> reversed;
        while (!tempLeft.empty())
        {
            reversed.push(tempLeft.top());
            tempLeft.pop();
        }

        while (!reversed.empty())
        {
            result.push_back(reversed.top());
            reversed.pop();
        }

        while (!tempRight.empty())
        {
            result.push_back(tempRight.top());
            tempRight.pop();
        }

        return result;
    }
};

TEST(TextEditorTest, Test1_AddTextBasic)
{
    TextEditor editor;
    editor.addText("Hello");

    std::string result = editor.cursorLeft(0);
    EXPECT_EQ(result, "Hello");
}

TEST(TextEditorTest, Test2_DeleteTextWithinBounds)
{
    TextEditor editor;
    editor.addText("Hello World");

    int deleted = editor.deleteText(5);
    EXPECT_EQ(deleted, 5);

    std::string result = editor.cursorLeft(0);
    EXPECT_EQ(result, "Hello ");
}

TEST(TextEditorTest, Test3_DeleteTextExceedsBounds)
{
    TextEditor editor;
    editor.addText("Hi");

    int deleted = editor.deleteText(10);
    EXPECT_EQ(deleted, 2);

    std::string result = editor.cursorLeft(0);
    EXPECT_TRUE(result.empty());
}

TEST(TextEditorTest, Test4_CursorLeftWithReturnLimit)
{
    TextEditor editor;
    editor.addText("123456789012345");

    std::string result = editor.cursorLeft(0);
    EXPECT_EQ(result, "1234567890");

    editor.cursorLeft(5);
    result = editor.cursorLeft(0);
    EXPECT_EQ(result, "12345");
}

TEST(TextEditorTest, Test5_CursorRightBasic)
{
    TextEditor editor;
    editor.addText("Hello");
    editor.cursorLeft(3);

    std::string result = editor.cursorRight(2);
    EXPECT_EQ(result, "Hel");

    result = editor.cursorRight(1);
    EXPECT_EQ(result, "Hell");
}

TEST(TextEditorTest, Test6_CombinedOperations)
{
    TextEditor editor;
    editor.addText("Hello");
    editor.cursorLeft(2);
    editor.addText("world");

    std::string result = editor.cursorLeft(0);
    EXPECT_EQ(result, "Helworldlo");
}

TEST(TextEditorTest, Test7_EmptyEditorOperations)
{
    TextEditor editor;

    int deleted = editor.deleteText(5);
    EXPECT_EQ(deleted, 0);

    std::string result = editor.cursorLeft(5);
    EXPECT_TRUE(result.empty());

    result = editor.cursorRight(5);
    EXPECT_TRUE(result.empty());
}

TEST(TextEditorTest, Test8_CursorMovementBounds)
{
    TextEditor editor;
    editor.addText("Test");

    editor.cursorLeft(10);
    std::string result = editor.cursorLeft(0);
    EXPECT_TRUE(result.empty());

    editor.cursorRight(10);
    result = editor.cursorLeft(0);
    EXPECT_EQ(result, "Test");
}

TEST(TextEditorTest, Test9_MultipleAddTextOperations)
{
    TextEditor editor;
    editor.addText("Hello");
    editor.addText(" ");
    editor.addText("World");

    std::string result = editor.cursorLeft(0);
    EXPECT_EQ(result, "Hello World");
}

TEST(TextEditorTest, Test10_DeleteAndAddSequence)
{
    TextEditor editor;
    editor.addText("ABCDEF");

    editor.cursorLeft(3);
    int deleted = editor.deleteText(2);
    EXPECT_EQ(deleted, 2);

    editor.addText("XYZ");
    std::string result = editor.cursorLeft(0);
    EXPECT_EQ(result, "ABCXYZ");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}