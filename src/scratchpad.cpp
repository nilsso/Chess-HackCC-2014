#include"chess.h"
#include<iostream>
#include<string>

using namespace std;

int main(){
   string email = "suthe.rick@gmail.com";
   
   Board b;
   
   b.setup();
   
   b.move(email, 1,1,2,2,);
   
   return 0;

}

