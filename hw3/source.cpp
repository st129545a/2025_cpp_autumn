#include <iostream>
#include <string>
#include <vector>

class BankAccount
{
    std::string accountNumber;
    double balance;
    std::string accountHolder;

public:
    BankAccount(std::string number, double initialBalance, std::string holder)
    {
        accountNumber = number;
        balance = initialBalance;
        accountHolder = holder;
    }

    void Deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }

    bool Withdraw(double amount)
    {
        if (amount > 0 && balance >= amount)
        {
            balance -= amount;
            return true;
        }
        else
        {
            std::cout << "Error: Insufficient funds for withdrawal from account " << accountNumber << std::endl;
            return false;
        }
    }

    double GetBalance()
    {
        return balance;
    }

    std::string GetAccountHolder()
    {
        return accountHolder;
    }

    std::string GetAccountNumber()
    {
        return accountNumber;
    }

    void PrintAccountInfo()
    {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
};

class Bank
{
    std::vector<BankAccount> accounts;

public:
    void AddAccount(BankAccount account)
    {
        accounts.push_back(account);
    }

    double GetTotalBalance()
    {
        double total = 0;
        for (size_t i = 0; i < accounts.size(); i++)
        {
            total += accounts[i].GetBalance();
        }
        return total;
    }

    void PrintAllAccounts()
    {
        std::cout << "=== Bank Accounts Information ===" << std::endl;
        for (size_t i = 0; i < accounts.size(); i++)
        {
            accounts[i].PrintAccountInfo();
        }
        std::cout << "Total bank balance: $" << GetTotalBalance() << std::endl;
    }

    BankAccount* FindAccount(std::string accountNumber)
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].GetAccountNumber() == accountNumber)
            {
                return &accounts[i];
            }
        }
        return nullptr;
    }
};

int main()
{
    Bank myBank;

    BankAccount account1("ACC001", 1000.0, "Vladimir Putin");
    BankAccount account2("ACC002", 2500.0, "Vladimir Zelensky");
    BankAccount account3("ACC003", 500.0, "Donal Trump");

    myBank.AddAccount(account1);
    myBank.AddAccount(account2);
    myBank.AddAccount(account3);

    std::cout << "=== Initial Account Information ===" << std::endl;
    myBank.PrintAllAccounts();

    std::cout << "\n=== Performing Transactions ===" << std::endl;

    BankAccount* acc1 = myBank.FindAccount("ACC001");
    if (acc1)
    {
        acc1->Deposit(500.0);
        std::cout << "Deposited $500 to ACC001" << std::endl;
    }

    BankAccount* acc2 = myBank.FindAccount("ACC002");
    if (acc2)
    {
        if (acc2->Withdraw(1000.0))
        {
            std::cout << "Withdrew $1000 from ACC002" << std::endl;
        }
    }

    BankAccount* acc3 = myBank.FindAccount("ACC003");
    if (acc3)
    {
        if (!acc3->Withdraw(1000.0))
        {
            std::cout << "Failed to withdraw $1000 from ACC003" << std::endl;
        }
        acc3->Deposit(300.0);
        std::cout << "Deposited $300 to ACC003" << std::endl;
    }

    std::cout << "\n=== Final Account Information ===" << std::endl;
    myBank.PrintAllAccounts();

    return 0;
}