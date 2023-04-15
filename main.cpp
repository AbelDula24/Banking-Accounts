/*
Name: Abel N. Dula
Date: 4/10/2023
Project Name: Bank accounts, assignment 5.
Project Purpose : Use Object Oriented Design to portray accounts with their transaction history with a bank
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "BankAccountsClass.h"
#include "CheckingAccountsClass.h"
#include "InterestCheckingAccountsClass.h"
#include "SavingsAccountsClass.h"
#include "TransactionsClass.h"

using namespace std;

const string BANK_CONFIGURATION_FILE_NAME_STR         = "InfoBankConfig.txt";
const string BANK_ACCOUNTS_FILE_NAME_STR              = "InfoBankAccounts.txt";
const string BANK_ACCOUNTS_TRANSACTIONS_FILE_NAME_STR = "InfoBankAccountsTransactions.txt";

void CheckFileStreamOpen(string fileNameStr, ifstream& inFile);
void CheckFileStreamOpen(string fileNameStr, ofstream& outFile);
void ReadConfigurationFile(string bankConfigurationFileNameStr);
void ReadInFromBankAccountsFile
(string bankAccountsFileNameStr,
 BankAccountsClass** &bankAccountsAry, unsigned& accountsCount);
void ReadInFromTransactionsFile
(string transactionsFileNameStr,
 TransactionsClass*  &transactionsAry, unsigned& transactionsCountUns);
void ProcessTransactions
(TransactionsClass*   transactionsAry, unsigned& transactionsCountUns,
 BankAccountsClass**& bankAccountsAry, unsigned& accountsCountUns);
bool getMatchingBankAccountIndexUns(
  BankAccountsClass**& bankAccountsAry, unsigned  accountsCountUns,
  string accountIdStr, unsigned& bankAccountIndex);
void UpdateBankAccountsFile
(string   bankAccountsFileNameStr,
 BankAccountsClass**& bankAccountsAry, unsigned totalNoBankAccountsUns);

int main() {
  BankAccountsClass** bankAccountsAry      = nullptr;
  TransactionsClass*  transactionsAry      = nullptr;
  unsigned            accountsCountUns     = 0;
  unsigned            transactionsCountUns = 0;

  cout << setprecision(2) << fixed << showpoint;           //  set up output for dollar amounts

  ReadConfigurationFile     (BANK_CONFIGURATION_FILE_NAME_STR);
  ReadInFromBankAccountsFile(BANK_ACCOUNTS_FILE_NAME_STR, 
                             bankAccountsAry, accountsCountUns);
  ReadInFromTransactionsFile(BANK_ACCOUNTS_TRANSACTIONS_FILE_NAME_STR,
                             transactionsAry, transactionsCountUns);
  ProcessTransactions       (transactionsAry, transactionsCountUns,
                             bankAccountsAry, accountsCountUns);
  UpdateBankAccountsFile    (BANK_ACCOUNTS_FILE_NAME_STR,
                             bankAccountsAry, accountsCountUns);

} // int main()

void CheckFileStreamOpen(string fileNameStr, ifstream& inFile) {
  
}

void CheckFileStreamOpen(string fileNameStr, ofstream& outFile) {
    if (outFile.fail())
    {
        cout << "File " << fileNameStr << "could not be opened. " << endl;
        cout << endl << "Press the enter key once key once or twice to continue..." << endl;
        cin.ignore();
        cin.get();
        exit(1);
  }
}

void ReadConfigurationFile(string bankConfigurationFileNameStr) {
    ifstream InFile(bankConfigurationFileNameStr);
    CheckFileStreamOpen(bankConfigurationFileNameStr, InFile);

    cout << "Configuration Information : " << endl
        << "===========================" << endl
        << endl;

    float valueFloat;
    InFile >> valueFloat; SavingsAccountsClass::setSavingsInterestRate(valueFloat);
    cout << "Savings Interest Rate : " << SavingsAccountsClass::getSavingsInterestRate() << endl;

    InFile >> valueFloat; CheckingAccountsClass::setCheckingMinimumFl(valueFloat);
    cout << "Checking Minimum Balance : " << CheckingAccountsClass::getCheckingMinimumFl() << endl;

    InFile >> valueFloat; CheckingAccountsClass::setChargePerCheckFl(valueFloat);
    cout << "Charge Per Check : " << CheckingAccountsClass::getChargePerCheckFl() << endl;

    InFile >> valueFloat; InterestCheckingAccountsClass::setInterestCheckingRate(valueFloat);
    cout << "Interest Checking Rate : " << InterestCheckingAccountsClass::getInterestCheckingRate() << endl;

    InFile >> valueFloat; InterestCheckingAccountsClass::setMinimmunBlanceRequired(valueFloat);
    cout << "Interest Checking Minimum Balance : " << InterestCheckingAccountsClass::getInterestCheckingRate() << endl;

    InFile >> valueFloat; InterestCheckingAccountsClass::setMonthlyFeeChargeNoMinimumBalance(valueFloat);
    cout << "Interest Checking Monthly Fee Charge : " << InterestCheckingAccountsClass::getMonthlyFeeChargeNoMinimumBalance() << endl;

    cout << endl << endl;
    
    InFile.close();
}

void ReadInFromBankAccountsFile
(string bankAccountsFileNameStr, 
 BankAccountsClass** &bankAccountsAry, unsigned& accountsCountUns) {
    
    ifstream file(bankAccountsFileNameStr);
    CheckFileStreamOpen(bankAccountsFileNameStr, file);

    string InFileBuffer;

    accountsCountUns = 0;
    while (getline(file, InFileBuffer)) ++accountsCountUns;
    
    bankAccountsAry = new BankAccountsClass * [accountsCountUns];

    file.clear();
    file.seekg(0, ios::beg);
    const char COMMA_DELIMTER_CHAR = ',';

    string acountIdStr;
}//ReadInFromBankAccountsFile()

void ReadInFromTransactionsFile
(string transactionsFileNameStr,
 TransactionsClass* &transactionsAry,  unsigned& transactionsCountUns) {
  
    ifstream file(transactionsFileNameStr);
    CheckFileStreamOpen(transactionsFileNameStr, file);

    string InFileBuffer;

    transactionsCountUns = 0;
    while (getline(file, InFileBuffer)) ++transactionsCountUns;

    transactionsAry = new TransactionsClass [transactionsCountUns];

    file.clear();
    file.seekg(0, ios::beg);
    const char COMMA_DELIMTER_CHAR = ',';

    string accountIdStr;
    string accoountTransactionIdStr;
    string accountTransactionAmountStr;
    float accountTransactionAmountFl;

    cout << "Transactions : " << endl
        << "_____________" << endl
        << endl;

    for (unsigned Count = 0; Count < transactionsCountUns; Count++)
    {
        getline(file, InFileBuffer);
        istringstream isStringStream(InFileBuffer);

        getline(isStringStream, accountIdStr, COMMA_DELIMTER_CHAR);
        transactionsAry[Count].setIdentifcationStr(accountIdStr);

        getline(isStringStream, accoountTransactionIdStr, COMMA_DELIMTER_CHAR);
        transactionsAry[Count].setTransactionIdStr(accountTransactionAmountStr);

        if (accoountTransactionIdStr != "interest")
        {
            getline(isStringStream, accountTransactionAmountStr, COMMA_DELIMTER_CHAR);
            accountTransactionAmountFl = stof(accountTransactionAmountStr);
            transactionsAry[Count].setTransactionArgumentFl(accountTransactionAmountFl);
        }
        transactionsAry[Count].displayTransaction();
    }//for
    cout << endl;
    file.close();

}//ReadInFromTransactionsFile

void ProcessTransactions
(TransactionsClass   *transactionsAry, unsigned& transactionsCountUns,
 BankAccountsClass** &bankAccountsAry, unsigned& accountsCountUns) {
  
    string accountIdstr;
    string accountTransactionIdStr;
    string accountTransactionAmountStr;
    float accountTransactionAmountFl;

    unsigned bankAccountIndex;

    cout << "ProcessTransactions" << endl
        << "___________________" << endl
        << endl;

    for (unsigned Count = 0; Count < transactionsCountUns; ++Count)
    {
        accountIdstr = transactionsAry[Count].getIdentifcationStr();
        if (!getMatchingBankAccountIndexUns(bankAccountsAry, accountsCountUns, accountIdstr, bankAccountIndex))
        {
            cout << "*** account identification not found " << endl
                << "Account ID : " << accountIdstr << endl
                << endl;
            return;
        }
        accountTransactionIdStr = transactionsAry[Count].getTransactionIdStr();

        switch (accountIdstr.at(0))
        {
        case 'S':
        case 's':
                    cout << "Account Before Transaction" << endl
                        << "__________________________" << endl;
                    static_cast <SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex]) -> display();

                    transactionsAry[Count].displayTransaction();

                    if (accountTransactionIdStr == "deposit")
                    {
                        accountTransactionAmountFl = transactionsAry[Count].getTransactionArgumentFl();
                        bankAccountsAry[bankAccountIndex]->deposit(accountTransactionAmountFl);
                    }
                    else if (accountTransactionIdStr == "withdraw")
                    {
                        accountTransactionAmountFl = transactionsAry[Count].getTransactionArgumentFl();
                        static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->savingsWithdraw(accountTransactionAmountFl);
                    }
                    else if (accountTransactionAmountStr == "interest")
                    {
                        static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->calculateInterest();
                    }
                    else
                    {
                        cout << "Invalid Transaction Id : " << accountTransactionIdStr << endl
                            << endl;
                    }

                    cout << "Acount After Transaction" << endl
                        << "________________________" << endl;

                    static_cast<SavingsAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();
                    
                    break;

        case 'C':
        case 'c':
            cout << "Account Before Transaction" << endl
                << "__________________________" << endl;
            static_cast <CheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            transactionsAry[Count].displayTransaction();

            if (accountTransactionIdStr == "deposit")
            {
                accountTransactionAmountFl = transactionsAry[Count].getTransactionArgumentFl();
                accountTransactionAmountFl = bankAccountsAry[bankAccountIndex]->getAccountBalanceFl() + accountTransactionAmountFl;
                bankAccountsAry[bankAccountIndex]->setAccountBalanceFl(accountTransactionAmountFl);
            }
            else if (accountTransactionIdStr == "check")
            {
                accountTransactionAmountFl = transactionsAry[Count].getTransactionArgumentFl();
                static_cast<CheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->cashCheck(accountTransactionAmountFl);
            }
        
            cout << "Acount After Transaction" << endl
                << "________________________" << endl;

            static_cast<CheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            break;

        case 'I':
        case 'i':
            cout << "Account Before Transaction" << endl
                << "__________________________" << endl;
            static_cast <InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            transactionsAry[Count].displayTransaction();

            if (accountTransactionIdStr == "deposit")
            {
                accountTransactionAmountFl = transactionsAry[Count].getTransactionArgumentFl();
                accountTransactionAmountFl = bankAccountsAry[bankAccountIndex]->getAccountBalanceFl() + accountTransactionAmountFl;
                bankAccountsAry[bankAccountIndex]->setAccountBalanceFl(accountTransactionAmountFl);
            }
            else if (accountTransactionIdStr == "check")
            {
                accountTransactionAmountFl = transactionsAry[Count].getTransactionArgumentFl();
                static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->cashCheck(accountTransactionAmountFl);
            }
            else if (accountTransactionIdStr == "interest")
            {
                static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->calculateInterest();
            }

            cout << "Acount After Transaction" << endl
                << "________________________" << endl;

            static_cast<InterestCheckingAccountsClass*>(bankAccountsAry[bankAccountIndex])->display();

            break;

        default:
            cout << "*** illegal account identification in transaction*** " << endl
                << "Account ID : " << accountIdstr << endl
                << endl;
        }//switch
    }//for
    cout << endl;
    
}//ProcessTransactions

bool getMatchingBankAccountIndexUns(
BankAccountsClass** &bankAccountsAry, unsigned  accountsCountUns, 
string              accountIdStr,     unsigned& bankAccountIndex) {
  bankAccountIndex = 0;
  for (; bankAccountIndex < accountsCountUns; ++bankAccountIndex)
    if (bankAccountsAry[bankAccountIndex]->getAcountIdStr() == accountIdStr) {
      return true;
    }
  return false;
}

void UpdateBankAccountsFile
(string bankAccountsFileNameStr,
 BankAccountsClass**& bankAccountsAry, unsigned accountsCountUns) {

  ofstream outFile(bankAccountsFileNameStr);
  CheckFileStreamOpen(bankAccountsFileNameStr, outFile);

  cout << "Updating " << bankAccountsFileNameStr << endl <<
          "-----------------------------" << endl;

  for (unsigned writeIndex = 0; writeIndex < accountsCountUns; ++writeIndex)
    outFile <<
    bankAccountsAry[writeIndex]->getAcountIdStr()      << "," <<
    bankAccountsAry[writeIndex]->getAccountOwnerStr()  << "," <<
    bankAccountsAry[writeIndex]->getAccountBalanceFl() << endl;

  outFile.close();
};
