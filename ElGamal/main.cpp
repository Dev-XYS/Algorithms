#include "elGamal.h"
#include <iostream>

int main(int argc, const char * argv[]) {

    //cout<<inversa(to_ZZ("13"), to_ZZ("11"))<<endl;
    Gamal objeto(1024);

    ZZ pp,ee1,dd,ee2;
    
        pp=objeto.p;
        ee1=objeto.e1;
        ee2=objeto.e2;
        dd=objeto.d;
    
        ZZ mensaje; mensaje=to_ZZ("100295100295100295100295100295100295100295100295100295100295100295");
    
    cout<<"Cifrado "<<endl<<endl<<objeto.cifrado_bloques(ee1, ee2, pp, "hola mundo como estan, hola mundo.... como estan hola mundo como estan hola mundo como estan hola mundo, como estan hola mundo como estan hola mundo como estan hola mundo, como estan:::hola mundo, como estan hola mundo como estan hola mundo como estan hola mundo como estan hola mundo como estan hola mundo como estan, hola mundo como estan hola mundo como estan hola mundo como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan hola mundo:::::: como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan hola mundo, como estan JESUS VERA CALLME..........");
    
    string __C2=objeto._CC2;
    
    //cout<<__C1<<endl<<endl;
    //cout<<__C2<<endl;
    
    
    cout<<endl<<endl<<endl<<"descifrado "<<endl<<endl;
    objeto.descifrado_bloques(__C2);
    
    //objeto.cifrado(ee1, ee2, pp, mensaje);
    
      //  ZZ CCCC1,CCCC2;
        //CCCC1=objeto.CC1;
        //CCCC2=objeto.CC2;
    
    //objeto.descifrado(CCCC1, CCCC2);
    
    
    
    cout<<endl<<GetTime()<<endl;
    
}
