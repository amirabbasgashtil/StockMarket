#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
//Back up e sho gereftam  :]
using namespace std;

class Account{
    protected:
        string user_name;
        string password;
        //login ^

        string full_name;
        string national_id;
        string account_num;
        string sheba;
        int debt;
        int ballance;
        int total_asset;
        //account information ^

    public:
        Account(){
            debt = 0;
            ballance =0;
        }

        void signUp(string user, string pass){
            user_name = user;
            password = pass;
        }

        void setName(string nameInput){
            if(nameInput.length() <= 40)
                    full_name = nameInput;
            else{
                cout<<"Enter a valid Name. (less than 40 characters)"<<endl;
                getline(cin, nameInput);
                cin.ignore();
                setName(nameInput);
            }        
        }
            
        void setNationalID(string NationalIdInput){
            if(NationalIdInput.length() == 10) 
                national_id = NationalIdInput;
            else{
                cout<<"Enter a valid national id (10 characters)"<<endl;
                cin>>NationalIdInput;
                setNationalID(NationalIdInput);
            }        
        }

        void setAccountNum(string accountNumInput){
            if(accountNumInput.length() == 10)
                    account_num = accountNumInput;
            else{
                cout<<"Enter a valid account number (10 characters)"<<endl;
                cin>>accountNumInput;
                setAccountNum(accountNumInput);
            }
        }

        void setSheba(string shebaInput){
            if(shebaInput.at(0) == 'I' && shebaInput.at(1) == 'R' && shebaInput.length() == 12)
                                sheba = shebaInput;
            else{
                cout<<"Enter a valid sheba number (12 characters an it begins with IR)"<<endl;
                cin>>shebaInput;
                setSheba(shebaInput);
            }
        }

        void increaseDebt(int debtInput){
            debt += debtInput;
        }

        bool check(string user, string pass){
            if(user == user_name && pass == password)
                    return true;
            else
                return false;
        }

        void increaseBallance(int amount){
            ballance += amount;   
        }

        void decreaseBallance(int amount){
            ballance -= amount;
        }
};

class Stock: public Account{
    private:
        string stocks_user_have[100];
        string full_name[100];
        int amountOfStock[100];
        int current_price[100];
        int tedadESahm;

    public:

        Stock(){
            tedadESahm =0;
        }

        void buyShare(string symbolInput, int amountInput){
            string line, line1, line2, line3;
            int price;
            stringstream s;
            fstream myFile;
            
            myFile.open("stock_market_data.csv", ios::in);
            int cnt =0;
            while(true){
                    getline(myFile, line, ',');
                    if(line == symbolInput){
                        line1 = line; // symbol
                        cnt++;
                    }
                    if(cnt == 1){
                        line2 = line; // full name 
                        cnt++;
                    }
                    if(cnt == 2){
                        line3 = line; // current price
                        cnt++;
                    }
                    if(cnt == 3){
                        break;
                    }
            }
            s << line3;
            s >> price;
            if(price * amountInput <= ballance){
                stocks_user_have[tedadESahm] = line1;
                full_name[tedadESahm] = line2;
                current_price[tedadESahm] = price;
                ballance -= price * amountInput;
                cout<<"sahm e shoma ba movafaghiat kharidari shod."<<endl;
            }
            else
                cout<<"you dont have enough money for buy this stock."<<endl;
                
            cnt =0; 
        }

        void saleShare(){
            string Input;
            cout<<"your stocks: "<<endl;
            seeShares();
            cout<<"what stock do you sale?(Input the symbol)"<<endl;
            cin>>Input;
            int i;
            for(i=0; i<tedadESahm; i++){
                if(Input == stocks_user_have[i])
                    break;
            }
            ballance = ballance + amountOfStock[i] * current_price[i];
            for(int j = i; j<tedadESahm - 1; j++){
                stocks_user_have[j] = stocks_user_have[j+1];
            }

            stocks_user_have[tedadESahm].clear();
            
            tedadESahm --;
        }

        void allStocks(){
                string line;
                fstream myFile;
                myFile.open("stock_market_data.csv", ios::in);
                int cnt =0;
                while(myFile.good()){
                    getline(myFile, line, ',');
                    cout<<line;
                    if(cnt % 4 == 0)
                        cout<<endl;
                    else
                        cout<<" ,";
                }
        }

        void seeShares(){
            for(int i=0; i<tedadESahm; i++){
                cout<<"**********************************"<<endl;
                cout<<"Share: "<<stocks_user_have[i]<<endl;
                cout<<"full name: "<<full_name[i]<<endl;
                cout<<"current price: "<<current_price[i]<<endl;
                cout<<"arzesh dar sabad: "<<amountOfStock[i] * current_price[i]<<endl;
            }
        }

        void saveInfo(){
            fstream file;
            file.open("newFile.csv", ios::out);
            file<< user_name<<" , "<< password<<" , "<< full_name<<" , "<< national_id<<" , "
                << account_num<<" , "<<sheba<<" , "<< debt<<" , "<< ballance<<" , "<< total_asset<<endl;
            for(int i=0; i<tedadESahm; i++){
                file<<stocks_user_have[i]<<" , "<<full_name[i]<<" , "
                    <<current_price[i]<<" , "<<amountOfStock[i]<<endl;
            }
        }
};

int main(){
        int Input;
        string userInput;

        string username;
        string password;
        int cnt = 0;
        string nameInput;
        string nationalIDInput;
        string accountNumInput;
        string shebaInput;

        Account acc_obj[100];
        Stock st_obj[100];

        while(true){
        cout<<"1.Sign Up \t 2.log in \t 3.exit";
        cin>> Input;
        switch(Input){
            case 1:
                cout<<"Here are two steps. 1.Sign Up \t 2.save information"<<endl<<"lets go"<<endl;

                cout<<"Enter a User Name: ";
                cin>>username; 
                cout<<"Enter a password: ";
                cin>>password;
                acc_obj[cnt].signUp(username, password);

                cout<<"Enter your full name: \'without space\'";
                cin>>nameInput;
                acc_obj[cnt].setName(nameInput);
            
                cout<<"Enter your national ID: ";
                cin>>nationalIDInput;
                acc_obj[cnt].setNationalID(nationalIDInput);

                cout<<"Enter your account number: ";
                cin>>accountNumInput;
                acc_obj[cnt].setAccountNum(accountNumInput);

                cout<<"Enter your sheba number: ";
                cin>>shebaInput;
                acc_obj[cnt].setSheba(shebaInput);
                cout<<"signUp was succesfully."<<endl;
                break;

            case 2:
                cout<<"User Name: ";
                cin>>username;
                cout<<"Password: ";
                cin>>password;
                bool check;
                int cnt1;
                for(int i=0; i<100; i++){
                    if(acc_obj[i].check(username, password) == true)
                       {check =true;
                        cnt1 = i;
                        break;}
                }
                if(check == true){
                    cout <<"1.change information \t 2.charge \t 3.market menu"<<endl;
                    cin>>Input;
                    switch(Input){
                        case 1:
                            cout<<"change what?"<<endl;
                            cout<<"1.full name\t2.nationalID\t3.account number\t4.sheba number"<<endl;
                            cin>>Input;
                            switch(Input){
                                case 1:
                                    cout<<"enter new full name: \'without space\' ";
                                    cin>>nameInput;
                                    acc_obj[cnt1].setName(nameInput);
                                    break;

                                case 2:
                                    cout<<"enter new national ID: ";
                                    cin>>nationalIDInput;
                                    acc_obj[cnt1].setNationalID(nationalIDInput);
                                    break;

                                case 3:
                                    cout<<"enter your new account number: ";
                                    cin>>accountNumInput;
                                    acc_obj[cnt1].setAccountNum(accountNumInput);
                                    break;

                                case 4:
                                    cout<<"enter new sheba number: ";
                                    cin>>shebaInput;
                                    acc_obj[cnt1].setSheba(shebaInput);
                                    break;

                                default:
                                    break;
                            }
                            break;
                        case 2:
                            cout<<"1.charge \t 2.withdrawal"<<endl;
                            cin>>Input;
                            switch(Input){
                                case 1:
                                    cout<<"How much? ";
                                    cin>>Input;
                                    acc_obj[cnt1].increaseBallance(Input);
                                    break;
                                case 2:
                                    cout<<"How much? ";
                                    cin>>Input;
                                    acc_obj[cnt1].decreaseBallance(Input);
                                    break;
                            }
                            break;
                        case 3:
                            cout<<"Welcome to market menu"<<endl;
                              cout<<"Enter user name again pls: ";
                                    cin>>username;
                                    cout<<"Enter ur password: ";
                                    cin>> password;
                                    for(int i=0; i<100; i++){
                                        if(acc_obj[i].check(username, password) == true){
                                            check =true;
                                            cnt1 = i;
                                                break;}
                                    }
                            cout<<"1.Buy a share \t 2.sale a share \t 3.my shares \t 4.stocks list \t 5.save information"<<endl;
                            cin>>Input;
                            switch(Input){
                                case 1:
                                    cout<<"Enter the symbol of stock u want: ";
                                    cin>> userInput;
                                    cout<<"How much u want? ";
                                    cin>>Input;
                                    st_obj[cnt1].buyShare(userInput, Input);
                                    break;
                                case 2:
                                        st_obj[cnt1].saleShare();
                                    break;
                                case 3:  
                                    cout<<"Here are all of shares you have:"<<endl;
                                        st_obj[cnt1].seeShares();
                                    break;
                                case 4:
                                    cout<<"Here are all of stocks in market:"<<endl;
                                        st_obj[cnt1].allStocks();
                                    break;
                                case 5:
                                    st_obj[cnt1].saveInfo();
                                    cout<<"information saved succesfully."<<endl;
                                    break;
                            }
                            break;
                        default:
                            break;
                    }
                }
                break;

            case 3:
                return 0;

            default:
                break;
        }

    }
    return 0;
}