#include<iostream>
#include<vector>
#include<math.h>

using namespace std;
int squaresum(int number){
int num2 = 0 ;

while(number!=0){
    num2 += pow(number%10,2);
    number/=10;
}
return num2;

}
int main(){

int num;
cin>>num;
cout<<squaresum(num);

    return 0;
}