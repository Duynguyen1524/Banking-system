#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>

using namespace std;


#define MINBALANCE 500

class Insufficient_fund{};

class Account{
  private:
    long accountNumber;
    string FirstName;
    string LastName;
    float balance;
    static long NextAccountNumber;
  public:
    Account(){};
    Account(string fname,string lname,float balance);
    long getAccNo(){return accountNumber;}
    string getfirst();
    string getlast();
    float getBalance();

    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();
    friend ofstream & operator<<(ofstream &ofs, Account &acc);
    friend ifstream & operator>>(ifstream &ifs, Account &acc);
    friend ostream & operator<<(ostream &os, Account &acc);    
};
long Account::NextAccountNumber = 0;
class Bank
{
  private:
      map<long,Account> accounts;
  public:
    Bank();
    Account OpenAcc(string fname, string lname, float balance);
    Account BankEnquiry(long accountNumber);
    Account Deposit(long accountNumber, float amount);
    Account Withdraw(long accountNumber, float amount);
    void closeAcc(long accountNumber);
    void showAllAcc();
    ~Bank();
};
int main() {
  Bank b;
  Account acc;
  int choice;
  string lname,fname;
  long accountNumber;
  float balance;
  float amount;
  cout<<"***BANKING SYSTEM***"<<endl;
  do
  {
    cout<<"\n\tSelect an option";
    cout<<"\n\t1  Open accout";
    cout<<"\n\t2  Balance enquiry";
    cout<<"\n\t3  Deposit";
    cout<<"\n\t4  Withdrawal";
    cout<<"\n\t5  Close Account";
    cout<<"\n\t6  Show all account";
    cout<<"\n\t7  Quit";
    cout<<"\n\tEnter a choice:  ";
    cin>>choice;
    switch(choice){
      case 1:
        cout<<"Enter First Name:  ";
        cin>>fname;
        cout<<"Enter last Name:  ";
        cin>>lname;
        cout<<"Enter Initil balance:  ";
        cin>>balance;
        acc = b.OpenAcc(fname,lname,balance);
        cout<<endl<<"Congratulation, you have a new acc"<<endl;
        cout<<acc;
        break;
      case 2:
        cout<<"Enter Account Number  ";
        cin>>accountNumber;
        acc = b.BankEnquiry(accountNumber);
        cout<<"Your Account detail"<<endl;
        cout<<acc;
      break;
      case 3:
        cout<<"Enter Account Number:  ";
        cin>>accountNumber;
        cout<<"Enter Balance: ";
        cin>>amount;
        acc = b.Deposit(accountNumber,amount);
        cout<<endl<<"Amount is Deposited"<<endl;
        cout<<acc;
      break;
      case 4:
        cout<<"Enter Account Number  ";
        cin>>accountNumber;
        cout<<"Enter Balance: ";
        cin>>amount;
        acc = b.Withdraw(accountNumber,amount);
        cout<<endl<<"Amount is Deposited"<<endl;
        cout<<acc;
        break;
      case 5:
        cout<<"Enter Account Number  ";
        cin>>accountNumber;
        b.closeAcc(accountNumber);
        cout<<endl<<"Your accout has been closed";
        cout<<acc;
      case 6:
        b.showAllAcc();
        break;
      case 7:
        break;
      default:
        cout<<"Enter the correct choice";
        exit(0);
    }
  }while(choice!=7);
  return 0;
}
Account::Account(string fname,string lname,float balance){
  NextAccountNumber++;
  accountNumber = NextAccountNumber;
  FirstName = fname;
  LastName = lname;
  this->balance = balance;

}
void Account::Deposit(float amount){
  balance += amount;
}
void  Account::Withdraw(float amount){
  if(amount-balance<MINBALANCE){
    throw Insufficient_fund();
  }
  balance -= amount;
}
void Account::setLastAccountNumber(long accountNumber){
  NextAccountNumber = accountNumber;
}
long Account::getLastAccountNumber(){
  return NextAccountNumber;
}
 ofstream & operator<<(ofstream &ofs, Account &acc){
  ofs<<acc.accountNumber<<endl;
  ofs<<acc.FirstName<<endl;
  ofs<<acc.LastName<<endl;
  ofs<<acc.balance<<endl;
  return ofs;

}
 ifstream & operator>>(ifstream &ifs, Account &acc){
  ifs>>acc.accountNumber;
  ifs>>acc.FirstName;
  ifs>>acc.LastName;
  ifs>>acc.balance;
  return ifs;
}
 ostream & operator<<(ostream &os, Account &acc){
  os<<acc.accountNumber<<endl;
  os<<acc.FirstName<<endl;
  os<<acc.LastName<<endl;
  os<<acc.balance<<endl;
  return os;
}
Bank::Bank(){
    Account account;
    ifstream infile;
    infile.open("Bank.data");
    if(!infile){
      cout<<"Cannot open file"<<endl;
      return;
    }
    while(!infile.eof()){
      infile>>account;
      accounts.insert(pair<long,Account>(account.getAccNo(),account));
    }
    Account::setLastAccountNumber(account.getAccNo());
    infile.close();
};
Account Bank::OpenAcc(string fname, string lname, float balance){
    ofstream outfile;
    //create a new account object
    Account account(fname,lname,balance);
    //insert it into list of account
    accounts.insert(pair<long,Account>(account.getAccNo(),account));
    outfile.open("Bank.data", ios::trunc);

    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
    outfile<<itr->second;
     }
    outfile.close();
    return account;


};
Account Bank::BankEnquiry(long accountNumber){
  map<long,Account>::iterator itr=accounts.find(accountNumber);
  return itr->second;
};
Account Bank::Deposit(long accountNumber, float amount){
  map<long,Account>::iterator itr=accounts.find(accountNumber);
  itr->second.Deposit(amount);
  return itr->second;
};
Account Bank::Withdraw(long accountNumber, float amount){
  map<long,Account>::iterator itr = accounts.find(accountNumber);
  itr->second.Withdraw(amount);
  return itr->second;
};
void Bank::closeAcc(long accountNumber){
  map<long,Account>::iterator itr = accounts.find(accountNumber);
  cout<<"Account Deleted"<<itr->second;
 accounts.erase(accountNumber);
};
void Bank::showAllAcc(){
  map<long,Account>::iterator itr;
  for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
    cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
     }
};
Bank::~Bank(){
  ofstream outfile;
 outfile.open("Bank.data", ios::trunc);

 map<long,Account>::iterator itr;
 for(itr=accounts.begin();itr!=accounts.end();itr++)
 {
 outfile<<itr->second;
 }
 outfile.close();
};
