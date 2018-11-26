#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include <deque>
#include <iterator>

#define MENU_ROWS 2
#define COFFEE_TYPES 3

using namespace std;

/*
*The 5 STARs making BUCKS machine
*/

bool is_number(const std::string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != 999999999999999;
}

bool is_valid_name(const std::string& s)
{
    for(int i = 0; i < s.length(); i++)
        if(!((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A')))
            return false;
    return true;
}

void WhereDoYouEarFrom()
{
    std::deque<string> dictionary;

    std::ifstream myfile ("names.txt");
    if ( myfile.is_open() ) {
        copy(istream_iterator<string>(myfile),
             istream_iterator<string>(),
             back_inserter<std::deque<string>>(dictionary));
        myfile.close();
    }

    int random = rand() % 4945;

    std::cout << dictionary[random];
}

int main()
{
    std::string coffeeChoise;
    std::string money = "0.0";
    std::string coffeeMenu [MENU_ROWS][COFFEE_TYPES] = {{"Latte","Maciato","Americano"} ,
                                                        {"1.73" ,"2.34"   ,"0.75"}};
    std::string userName;
    int CoffeeIndex;

    std::cout << "Good day sir.\nWhat coffee would you like?\n(Select number)" << std::endl;
    for(int i = 0; i < COFFEE_TYPES; i++)
    {
        std::cout << (i + 1) << ". " << std::setw(9) << coffeeMenu[0][i] << std::endl;
    }

    RESELECT:
    std::cin >> coffeeChoise;
    std::istringstream iss(coffeeChoise);
    iss >> CoffeeIndex ;
    if (iss.eof() == false){
        std::cout << "Please select by index (int): " << std::endl;
        goto RESELECT;
        }
    std::cout << coffeeMenu[0][CoffeeIndex - 1] << " great choice!" << std::endl;
    std::cout << "Thet will be " << coffeeMenu[1][CoffeeIndex - 1] << "$ please.\n(Give cashier money)" << std::endl;

    REPAY:
    std::cin >> money;
        if(!is_number(money)){
        std::cout << "Sorry, we take only bucks here.\nPlease pay using double/int value" << std::endl;
        goto REPAY;
        }

    MORE_MONEY:
    double d1 = atof(coffeeMenu[1][CoffeeIndex - 1].c_str());
    double d2 = atof(money.c_str());
        if(d1 - d2 > 0){
            std::cout << "It is not enough money for us.\nMORE MORE MORE" << std::endl;
            std::cin >> money;
            goto MORE_MONEY;
            }
    std::cout << "Your change is: " << (d1 - d2) << "$"<< std::endl;

    std::cout << "May I ask your name: " << std::endl;

    SAID_WHAT:
    std::cin >> userName;
    if(!is_valid_name(userName)){
        std::cout << "Can you please repeat it?.\n(Name can contain only alphabet chars)" << std::endl;
        std::cin;
        goto SAID_WHAT;
    }

    bool nameApproval = false;
    string usersChoice;
    while(nameApproval == false)
    {
        WhereDoYouEarFrom(); std::cout << "? \n(y/n)";
        std::cin >> usersChoice;
        if(usersChoice[0] == 'y' || usersChoice[0] == 'Y')
            break;
    }

    std::cout << "OK ";
    WhereDoYouEarFrom();
    std::cout << ", Your coffee will be ready right away.";

    return 0;
}
