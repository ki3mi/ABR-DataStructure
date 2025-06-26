#include<iostream>
using namespace std;

int main(){
    int newId = 1000, cifras = 0, i = 0, digito;
    // bool isZero = false;
    do{
        // if(newId%10 == 0 && i == 0){
            //     newId++;
            // }
            // i = 1;
            cifras ++;
            newId = newId/10;
        }while(newId!=0);
    // if(newId/10 == 0){
    //     cifras ++;
    // }
    cout<<cifras<<"\n";
    //Obteniendo una lista del ID
    int listId[cifras];
    newId = 1000;
    for(int j = 1; j<=cifras;j++){
        digito = newId%10;
        listId[cifras-j] = digito;
        newId = newId/10;
    }
    
    for(int j = 0; j<cifras; j++){
        cout<<listId[j]<<"\n";
    }
    system("pause");
}