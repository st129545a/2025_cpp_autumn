#include <gtest/gtest.h>
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

    double GetBalance() const
    {
        return balance;
    }

    std::string GetAccountHolder() const
    {
        return accountHolder;
    }

    std::string GetAccountNumber() const
    {
        return accountNumber;
    }

    void PrintAccountInfo() const
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

    double GetTotalBalance() const
    {
        double total = 0;
        for (size_t i = 0; i < accounts.size(); i++)
        {
            total += accounts[i].GetBalance();
        }
        return total;
    }

    void PrintAllAccounts() const
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

    size_t GetAccountCount() const
    {
        return accounts.size();
    }

    const BankAccount* GetAccount(size_t index) const
    {
        if (index < accounts.size())
        {
            return &accounts[index];
        }
        return nullptr;
    }
};

// ====================== Tests for BankAccount ======================

TEST(BankAccountTest, Test1_ConstructorInitializesCorrectly)
{
    BankAccount acc("ACC001", 1000.0, "John Doe");

    EXPECT_EQ(acc.GetAccountNumber(), "ACC001");
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 1000.0);
    EXPECT_EQ(acc.GetAccountHolder(), "John Doe");
}

TEST(BankAccountTest, Test2_DepositPositiveAmount)
{
    BankAccount acc("ACC002", 500.0, "Jane Smith");

    acc.Deposit(200.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 700.0);

    acc.Deposit(300.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 1000.0);
}

TEST(BankAccountTest, Test3_DepositNegativeOrZeroAmount)
{
    BankAccount acc("ACC003", 500.0, "Bob Johnson");

    acc.Deposit(-100.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 500.0);

    acc.Deposit(0.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 500.0);
}

TEST(BankAccountTest, Test4_WithdrawSuccessful)
{
    BankAccount acc("ACC004", 1000.0, "Alice Brown");

    bool result = acc.Withdraw(300.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 700.0);

    result = acc.Withdraw(700.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 0.0);
}

TEST(BankAccountTest, Test5_WithdrawInsufficientFunds)
{
    BankAccount acc("ACC005", 200.0, "Charlie Davis");

    testing::internal::CaptureStdout();
    bool result = acc.Withdraw(500.0);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 200.0);
    EXPECT_NE(output.find("Error: Insufficient funds"), std::string::npos);
}

TEST(BankAccountTest, Test6_WithdrawNegativeOrZeroAmount)
{
    BankAccount acc("ACC006", 500.0, "Eve Wilson");

    testing::internal::CaptureStdout();
    bool result = acc.Withdraw(-100.0);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 500.0);

    result = acc.Withdraw(0.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 500.0);
}

TEST(BankAccountTest, Test7_MultipleOperationsSequence)
{
    BankAccount acc("ACC007", 1000.0, "Frank Miller");

    acc.Deposit(500.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 1500.0);

    acc.Withdraw(200.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 1300.0);

    acc.Withdraw(1300.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 0.0);

    acc.Deposit(100.0);
    EXPECT_DOUBLE_EQ(acc.GetBalance(), 100.0);
}

// ====================== Tests for Bank ======================

TEST(BankTest, Test8_BankAddAccount)
{
    Bank bank;

    EXPECT_EQ(bank.GetAccountCount(), 0);

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    bank.AddAccount(acc1);
    EXPECT_EQ(bank.GetAccountCount(), 1);

    BankAccount acc2("ACC002", 2000.0, "Jane Smith");
    bank.AddAccount(acc2);
    EXPECT_EQ(bank.GetAccountCount(), 2);
}

TEST(BankTest, Test9_BankTotalBalance)
{
    Bank bank;

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    BankAccount acc2("ACC002", 2000.0, "Jane Smith");
    BankAccount acc3("ACC003", 1500.0, "Bob Johnson");

    bank.AddAccount(acc1);
    bank.AddAccount(acc2);
    bank.AddAccount(acc3);

    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 4500.0);
}

TEST(BankTest, Test10_BankFindAccountSuccess)
{
    Bank bank;

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    BankAccount acc2("ACC002", 2000.0, "Jane Smith");

    bank.AddAccount(acc1);
    bank.AddAccount(acc2);

    BankAccount* found = bank.FindAccount("ACC002");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->GetAccountNumber(), "ACC002");
    EXPECT_DOUBLE_EQ(found->GetBalance(), 2000.0);
    EXPECT_EQ(found->GetAccountHolder(), "Jane Smith");
}

TEST(BankTest, Test11_BankFindAccountNotFound)
{
    Bank bank;

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    bank.AddAccount(acc1);

    BankAccount* found = bank.FindAccount("NONEXISTENT");
    EXPECT_EQ(found, nullptr);
}

TEST(BankTest, Test12_BankOperationsThroughFindAccount)
{
    Bank bank;

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    bank.AddAccount(acc1);

    BankAccount* found = bank.FindAccount("ACC001");
    ASSERT_NE(found, nullptr);

    found->Deposit(500.0);
    EXPECT_DOUBLE_EQ(found->GetBalance(), 1500.0);

    bool result = found->Withdraw(300.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(found->GetBalance(), 1200.0);
}

TEST(BankTest, Test13_BankMultipleAccountsOperations)
{
    Bank bank;

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    BankAccount acc2("ACC002", 2000.0, "Jane Smith");

    bank.AddAccount(acc1);
    bank.AddAccount(acc2);

    BankAccount* acc1Ptr = bank.FindAccount("ACC001");
    BankAccount* acc2Ptr = bank.FindAccount("ACC002");

    ASSERT_NE(acc1Ptr, nullptr);
    ASSERT_NE(acc2Ptr, nullptr);

    acc1Ptr->Deposit(500.0);
    acc2Ptr->Withdraw(1000.0);

    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 2500.0);
}

TEST(BankTest, Test14_BankEmptyOperations)
{
    Bank bank;

    EXPECT_EQ(bank.GetAccountCount(), 0);
    EXPECT_DOUBLE_EQ(bank.GetTotalBalance(), 0.0);

    BankAccount* found = bank.FindAccount("ANY");
    EXPECT_EQ(found, nullptr);
}

TEST(BankTest, Test15_BankAccountGetFunction)
{
    Bank bank;

    BankAccount acc1("ACC001", 1000.0, "John Doe");
    BankAccount acc2("ACC002", 2000.0, "Jane Smith");

    bank.AddAccount(acc1);
    bank.AddAccount(acc2);

    const BankAccount* accPtr = bank.GetAccount(0);
    ASSERT_NE(accPtr, nullptr);
    EXPECT_EQ(accPtr->GetAccountNumber(), "ACC001");

    accPtr = bank.GetAccount(1);
    ASSERT_NE(accPtr, nullptr);
    EXPECT_EQ(accPtr->GetAccountNumber(), "ACC002");

    accPtr = bank.GetAccount(10);
    EXPECT_EQ(accPtr, nullptr);
}

// ====================== Main ======================

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}