#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    srand(time(0));
    int randomnumber, attemptsleft=10, attemptsused=0, n, guessed=0;
    randomnumber = rand()%100 +1;
    cout<<"guess a number between 1 and 100 ";
    while(guessed==0){
        cin>>n;
        attemptsused+=1;
        attemptsleft-=1;
        if(n==randomnumber) {
            cout<<"congratulations, you guessed the number! you guessed the number in "<<attemptsused<<" tries";
            guessed=1;
            break;
        }

        else if(n<randomnumber) {
            cout<<"too low, try again!";
        }

        else if(n>randomnumber){
            cout<<"too high, try again!";
        }
        if(attemptsleft==0) {
            cout<<"you failed to guess the number! the number is "<<randomnumber;
            break;
        }
    }
    return 0;   
}