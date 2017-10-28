#include <NTL/ZZ.h>
#include <iostream>
#include <regex>
#include <math.h>


#include <sstream>

#include "lfsr.h"


#ifndef ElGamal_2_0_elGamal_h
#define ElGamal_2_0_elGamal_h

using namespace NTL;
using namespace std;

ZZ random_brutal(ZZ bits){
    
    //cout<<"NUMERO DE BITS "<<bits<<endl;
    ZZ q;
    if (bits>=8196) {
        q=funcion(8196-60, 91, 500, 16, 469);
        return q;
    }
    
    if(bits>=4096 and bits<=8195){
        q=funcion(4096-50, 91, 1000, 512, 20);
        return q;
        
    }
    if (bits>=2048 and bits<=4095) {
        q=funcion(2048-30, 91, 500, 16, 469);
        return q;
    }
    
    if(bits>=1024 and bits<=2047){
        q=funcion(1023-90,798,550,32,729);
        return q;
    }
    
    if(bits>=512 and bits<=1023){
        q=funcion(510-80,99,500,16,259);
        return q;
    }
    
    if(bits>=256 and bits<=511){
        q=funcion(255-60,91,505,64,247);
        return q;
    }
    if(bits>=128 and bits<=255){
        q=funcion(127-60,126,505,32,79);
        return q;
    }
    if(bits>=64 and bits<=127){
        q=funcion(62-15,38,387,8,37);
        return q;
    }
    
    if(bits>=32 and bits<=63){
        q=funcion(32-7, 3, 126, 4, 19);
        return q;
    }
    else if(bits>=16 and bits<=31){
        q=funcion(16-2,3,126,2,13);
        //cout<<"1"<<endl;
        return q;
    }
    //
    else if(bits>=8 and bits<=15){
        q=funcion(8-2, 3, 1000, 2, 6);
        // cout<<"2"<<endl;
        return q;
    }
    else if(bits>=4 and bits<=7){
        q=funcion(4, 2, 1000, 1, 2);
        //cout<<"3"<<endl;
        return q;
    }
    
    return q;
}



ZZ gcd_binary(ZZ x, ZZ y){
    ZZ t; ZZ g;
    g=conv<ZZ>(1);
    
    while( (bit(x, 0)==0) && (bit(y, 0)==0)){ // evalua si ambos son pares
        x=x>>1; y=y>>1; g=g<<1;               // divide ambos entre 2
    }
    while(x!=0){
        while (bit(x,0)==0) x=x>>1;
        while (bit(y,0)==0) y=y>>1;
        t=abs(x-y)>>1;
        if(x>=y) x=t;
        else y=t;
    }
    return g*y;
}

ZZ binary_extended_gcd (ZZ x, ZZ y){
    
    ZZ g=to_ZZ("1");
    ZZ a;ZZ b;ZZ u;ZZ v;
    ZZ A=to_ZZ("1"), B=to_ZZ("0"), C=to_ZZ("0"),D=to_ZZ("1");
    
    while(((bit(x,0))==0) && ((bit(y,0))==0)){
        x=x>>1; y=y>>1; g=g<<1;
    }
    u=x;
    v=y;
step:
    while((bit(u,0))==0) {
        u=u>>1;
        if((bit(A,0)==0) && (bit(B,0)==0) ){
            A=A>>1; B=B>>1;
        }
        else {
            A=(A+y)>>1; B=(B-x)>>1;
        }
    }
    
    while((bit(v,0))==0) {
        v=v>>1;
        if((bit(D,0)==0) && (bit(C,0)==0) ){
            C=C>>1; D=D>>1;
        }
        else {
            C=(C+y)>>1; D=(D-x)>>1;
        }
    }
    
    if(u>=v){
        u=u-v;  A=A-C;  B=B-D;
    }
    else {
        v=v-u;  C=C-A;  D=D-B;
    }
    if(u==0){
        a=C;    b=D;    //cout<<"a es : "<<a<<" b es : "<<b<<" otro : "<<g*v<<endl;
        return a; // que es la inversa
    }
    else goto step;
}


ZZ inversa(ZZ n1, ZZ n2){
    ZZ ret = binary_extended_gcd(n1, n2);
    if(ret<0)
    {
        ret += n2;
    }
    return ret;
}


class Gamal{
    
public:
    
    
    ZZ p;
    ZZ q;
    ZZ d;
    
    ZZ g;
    ZZ e1;
    ZZ e2;
    
    
    
    int num_bits;

    
    string abecedario="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:";
    
    
    Gamal(int bits){
        num_bits=bits;
        if (bits==8196) {
            q=funcion(8196, 91, 500, 16, 469);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            
        
            
            //g=funcion(8187, 91, 500, 16, 469);
            e1=find_GEN(p);

            d=funcion(8196, 91, 500, 16, 469);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        
        if (bits==2048) {
          
            q=funcion(2048, 91, 500, 16, 469);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            while(test_primalidad_MIll_Rabin(p, 40)!=1){
            //while(ProbPrime(p)!=1){
                q=funcion(2048, 91, 500, 16, 469);
                p=q*to_ZZ("2")+to_ZZ("1");
                //p=q*to_ZZ("2")+to_ZZ("1");
                //cout<<p<<endl;
                q=to_ZZ("0");
                //q=q+to_ZZ("2");
                
            }
            
            
            //g=funcion(2037, 91, 500, 16, 469);
            e1=find_GEN(p);
            
            
            d=funcion(2043, 91, 500, 16, 469);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==4096){
            
            q=funcion(4096, 91, 1000, 512, 20);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            // while(test_primalidad_MIll_Rabin(p, 40)!=1){
            
            while(ProbPrime(p)!=1){
                q=funcion(4096, 91, 1000, 512, 20);
                p=q*to_ZZ("2")+to_ZZ("1");
                //p=q*to_ZZ("2")+to_ZZ("1");
                //cout<<p<<endl;
                q=to_ZZ("0");
                //q=q+to_ZZ("2");
                
            }
            
            
            
            
            
            //g=funcion(4091, 91, 1000, 512, 20);
            e1=find_GEN(p);
            
            d=funcion(4093, 91, 1000, 512, 20);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==128){
            q=funcion(127,126,505,32,79);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(123,126,505,32,79);
            e1=find_GEN(p);
            
            
            d=funcion(125,126,505,32,79);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==1024){
            q=funcion(1023,798,550,32,729);
            //q=funcion(510,99,500,16,259);
            p=q*to_ZZ("2")+to_ZZ("1");
            
           while(test_primalidad_MIll_Rabin(p, 20)!=1){
                
            //while(ProbPrime(p)!=1){
                q=funcion(1023,798,550,32,729);
                //q=funcion(510,99,500,16,259);
                p=q*to_ZZ("2")+to_ZZ("1");
                //p=q*to_ZZ("2")+to_ZZ("1");
                //cout<<p<<endl;
                q=to_ZZ("0");
                //q=q+to_ZZ("2");
                
            }
            
            //q=funcion(1023,798,550,32,729);
            //p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(1020,798,550,32,729);
            e1=find_GEN(p);
            
            
            d=funcion(1021,798,550,32,729);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==256){
            q=funcion(255,91,505,64,247);
            p=q*to_ZZ("2")+to_ZZ("1");
            while(test_primalidad_MIll_Rabin(p, 100)!=1){
                
                q=funcion(255,91,505,64,247);
                p=q*to_ZZ("2")+to_ZZ("1");
                //cout<<"P ES IGUAL A "<<endl<<p<<endl;
                q=to_ZZ("0");
                
                
            }
            
            
            
            //q=funcion(255,91,505,64,247);
            //p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(250,91,505,64,247);
            e1=find_GEN(p);
            
            d=funcion(253,129,20,16,5);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==512){
            q=funcion(510,99,500,16,259);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            while(test_primalidad_MIll_Rabin(p, 10)!=1){
                
                q=funcion(510,99,500,16,259);
                p=q*to_ZZ("2")+to_ZZ("1");
                //p=q*to_ZZ("2")+to_ZZ("1");
                //cout<<p<<endl;
                q=to_ZZ("0");
                //q=q+to_ZZ("2");
                
            }
            //g=funcion(504,99,500,16,259);
            e1=find_GEN(p);
            
            
            d=funcion(509,99,500,16,259);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==64){
            p=to_ZZ("10") ;
            
            q=funcion(62,38,387,8,37);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(58,38,387,8,37);
            e1=find_GEN(p);
            
            d=funcion(57,38,387,8,37);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
            
        }
        
        if(bits==16){
            q=funcion(16,3,126,2,13);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(13, 2, 1000, 1, 2);
            e1=find_GEN(p);
            
            
            d=funcion(13,3,126,2,13);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        //
        if(bits==32){
            q=funcion(32, 3, 126, 4, 19);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(29, 2, 1000, 1, 2);
            e1=find_GEN(p);
            
            d=funcion(29, 3, 126, 4, 19);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
            
        }
        if(bits==8){
            q=funcion(8, 3, 1000, 2, 6);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(7, 2, 1000, 1, 2);
            e1=find_GEN(p);
            
            d=funcion(7, 3, 1000, 2, 6);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
        }
        if(bits==4){
            q=funcion(4, 2, 1000, 1, 2);
            p=q*to_ZZ("2")+to_ZZ("1");
            
            //g=funcion(3, 2, 1000, 1, 2);
            e1=find_GEN(p);
            
            d=funcion(4, 2, 1000, 1, 3);
            
            e2=expo_modular_rapida_II(e1, d, p);
            e2=e2+p;
            imprimir();
            
        }

    }
    
    void imprimir(){
        cout<<"   P             es : "<<endl<<"^^^^^^^^^^^^^^^^^^^^"<<endl<<p<<endl<<endl;
        cout<<"   e1 o GEN      es : "<<endl<<"^^^^^^^^^^^^^^^^^^^^"<<endl<<e1<<endl<<endl;
        cout<<"   e2 o Publica  es : "<<endl<<"^^^^^^^^^^^^^^^^^^^^"<<endl<<e2<<endl<<endl;
        cout<<"   d  o Privada  es : "<<endl<<"^^^^^^^^^^^^^^^^^^^^"<<endl<<d<<endl<<endl;
        
        
        
    }
    
    ZZ find_GEN(ZZ p){
        ZZ qq;
        qq=(p-1)/2;
        ZZ found; found=to_ZZ("0");
        ZZ g;
        ZZ i;
        
        i=p-random_brutal(conv<ZZ>(num_bits));
        //cout<<i<<endl;
        
        ZZ a;
        ZZ b;
        
        while(found!=1 and i<p-1){
            g=p-i;
            
            a=expo_modular_rapida_II(g, to_ZZ("2"), p);
            b=expo_modular_rapida_II(g, qq, p);
            //cout<<a<<endl;
            //cout<<b<<endl;
            
            if(b!= 1 and a!=1) {
                //cout<<b<<endl;
                //cout<<a<<endl;rr
                //cout<<" GEN es : "<<g<<endl;
                found=to_ZZ("1");
                return g;
                
                //cout<<b<<endl;
            }
            
            //else cout<<i<<endl;
            //cout<<endl;
            i++;
        }
        return g;
    }
    
    ZZ CC1;
    ZZ CC2;
    
    string cifrado(ZZ e1,ZZ e2, ZZ p, ZZ mensaje){
    
        stringstream ss;
        ss << p;
        string str1 = ss.str();
        int largo_N=str1.length();
        
        ZZ r;
        r=random_brutal(conv<ZZ>(largo_N));
        
        
        ZZ c1,c2,Km;
        
        c1=expo_modular_rapida_II(e1, r, p);
        Km=expo_modular_rapida_II(e2, r, p);
        c2=modulo_for_ZZ(mensaje*Km, p);
        cout<<"C1 es  --> "<<c1<<endl;
        cout<<"C2 es  --> "<<c2<<endl;
    
        CC1=c1;
        CC2=c2;

        return "as";
    }

    string descifrado(ZZ cc1,ZZ cc2){
    
        ZZ KKm=expo_modular_rapida_II(cc1, d, p);
        
        ZZ inv=inversa(KKm, p);
        cout<<endl<<"Descifrado es : "<<modulo_for_ZZ(cc2*inv, p)<<endl;
        
    
        return "hol";
    }
    
    string _CC1;
    string _CC2;
    
    
    string cifrado_bloques(ZZ e1,ZZ e2, ZZ p, string mensaje){
        
        stringstream ss;
        ss << p;
        string str1 = ss.str();
        int largo_N=str1.length();
        int tamano_bloque=largo_N-1;
        
        ZZ r;
        r=random_brutal(conv<ZZ>(largo_N));
        
        ZZ c1,c2,Km;
        
        string almacen;
        
        for(int i=0;i<mensaje.length();i++){
            ZZ numero;
            numero=abecedario.find(mensaje[i])+101;
            stringstream ss;
            ss << numero;
            string str1 = ss.str();
            
            almacen+=str1;
        }
        
        c1=expo_modular_rapida_II(e1, r, p);
        Km=expo_modular_rapida_II(e2, r, p);
        
        CC1=c1;
        
        stringstream bb;
        bb << CC1;
        string str0 = bb.str();
        if(str0.length()==largo_N) _CC1=str0;
        else {
            string a((largo_N-str0.length()),'0');
            _CC1=a+str0;
        }
        
        
        string nuevo_almacen;
        
        for(int i=0;i<almacen.length();){
            string temporal=almacen.substr(i,tamano_bloque);
            ZZ other;
            istringstream convert(temporal);
            if ( !(convert >> other) )  other = 0;
            c2=modulo_for_ZZ(other*Km, p);
            //cout<<other<<endl;
            stringstream ss;
            ss << c2;
            string str1 = ss.str();
            if(str1.length()==largo_N) nuevo_almacen+=str1;
            else {
                string a((largo_N-str1.length()),'0');
                nuevo_almacen+=a+str1;
            }
            i+=tamano_bloque;
            
        }
        
        stringstream jj;
        jj << nuevo_almacen;
        string str5 = jj.str();
        _CC2=str5;
        _CC1+=_CC2;
        _CC2=_CC1;
        
        cout<<endl;
        return nuevo_almacen;
    }
    
    
    
    
    string descifrado_bloques(string cc2){
        
        stringstream ss;
        ss << p;
        string str1 = ss.str();
        int largo_N=str1.length();
        int tamano_bloque=largo_N-1;
        string nuevo_almacen;
        
        
        int j=0;
        string nuevo=cc2.substr(j,largo_N);
        j+=largo_N;
        
        ZZ ot;
        istringstream convert(nuevo);
        if ( !(convert >> ot) )  ot = 0;
        
        
        ZZ KKm=expo_modular_rapida_II(ot, d, p);
        ZZ inv=inversa(KKm, p);
        
        
        for(;j<cc2.length()-1;){
            string nuevo=cc2.substr(j,largo_N);
            ZZ ot;
            istringstream convert(nuevo);
            if ( !(convert >> ot) )  ot = 0;
            
            //other=expo_modular_rapida_II(other, d, N);
            ot=modulo_for_ZZ(ot*inv, p);
            
            stringstream mm;
            mm << ot;
            string astr1 = mm.str();
            
            if(astr1.length()==tamano_bloque) nuevo_almacen+=astr1;
            else {
                string a((tamano_bloque-astr1.length()),'0');
                nuevo_almacen+=a+astr1;
            }
            
            j+=largo_N;
            
        }
        
        for (int i=0;i<nuevo_almacen.length();i+=3){
            string ll=nuevo_almacen.substr(i,3);
            ZZ other;
            istringstream convert(ll);
            if ( !(convert >> other) )  other = 0;
            
            //other=other-101;
            other=abs(other- conv<ZZ>(101));
            //cout<<other<<endl;
            cout<<abecedario[conv<int>(other)];
            
        }
        cout<<"      --- >>> LLEGUE A QUI"<<endl;
        //cout<<nuevo_almacen<<endl;
        
        return nuevo_almacen;
    }
    
};


#endif
