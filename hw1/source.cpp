#include <iostream>

bool isOperator(const char* token)
{
    return (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/') && token[1] == '\0';
}

double evaluateRPN(const char* expression)
{
    double stack[100];
    int top = -1;

    int i = 0;
    while (expression[i] != '\0')
    {
        while (expression[i] == ' ') i++;
        if (expression[i] == '\0') break;

        int start = i;
        while (expression[i] != ' ' && expression[i] != '\0') i++;

        char token[20];
        int j = 0;
        for (int k = start; k < i; k++)
        {
            token[j++] = expression[k];
        }
        token[j] = '\0';

        if (isOperator(token))
        {
            if (top < 1)
            {
                std::cerr << "Error: insufficient operands for operator " << token << std::endl;
                return 0;
            }

            double b = stack[top--];
            double a = stack[top--];
            double result;

            switch (token[0])
            {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0)
                {
                    std::cerr << "Error: division by zero" << std::endl;
                    return 0;
                }
                result = a / b;
                break;
            default:
                std::cerr << "Error: unknown operator " << token << std::endl;
                return 0;
            }

            stack[++top] = result;
        }
        else
        {
            double num = 0;
            double fraction = 0;
            int decimal = 0;
            bool negative = false;
            bool hasDecimal = false;

            j = 0;
            if (token[0] == '-')
            {
                negative = true;
                j = 1;
            }

            for (; token[j] != '\0'; j++)
            {
                if (token[j] == '.')
                {
                    hasDecimal = true;
                    decimal = 1;
                }
                else if (token[j] >= '0' && token[j] <= '9')
                {
                    if (hasDecimal)
                    {
                        fraction = fraction * 10 + (token[j] - '0');
                        decimal *= 10;
                    }
                    else
                    {
                        num = num * 10 + (token[j] - '0');
                    }
                }
                else
                {
                    std::cerr << "Error: invalid token " << token << std::endl;
                    return 0;
                }
            }

            double value = num;
            if (hasDecimal)
            {
                value += fraction / decimal;
            }
            if (negative)
            {
                value = -value;
            }

            stack[++top] = value;
        }
    }

    if (top != 0)
    {
        std::cerr << "Error: invalid expression" << std::endl;
        return 0;
    }

    return stack[top];
}

int main()
{
    const int MAX_LINE = 256;
    char buffer[MAX_LINE];

    while (std::cin.getline(buffer, MAX_LINE))
    {
        if (buffer[0] == '\0') continue;

        double result = evaluateRPN(buffer);

        std::cout << buffer << " = " << result << std::endl;
    }

    return 0;
}