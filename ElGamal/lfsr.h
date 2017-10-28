#include <vector>
#include <NTL/ZZ.h>



#ifndef ElGamal_2_0_lfsr_h
#define ElGamal_2_0_lfsr_h

typedef int tipo;
typedef std::vector<bool> Vector;


using namespace NTL;
using namespace std;




ZZ aleatorio(){
    time_t t;
    srand((unsigned) time(&t));
    int res=rand();
    return to_ZZ(res);
}
ZZ modulo_for_ZZ(ZZ a,ZZ n)
{
    if(abs(a) == abs(n))
        return to_ZZ("0");
    if (a<0 && (a+n)!=0)
    {
        ZZ xd;
        xd= a + n*(((-1*a)/n)+1);
        if(xd == n){ return to_ZZ("0"); }
        return xd;
    }
    return a - n * ( a/n );
}

Vector llenar(Vector & i_contenedor, tipo tam_bits);
void   imprimir(Vector & i_contenedor);

ZZ exponenciar_rapidamente (ZZ a, ZZ n)
{
    ZZ  x = a;
    ZZ exp;
    exp=1;
    while (n >0)
    {
        if (modulo_for_ZZ(n,to_ZZ(2))==1){
            exp = (exp*x);}
        x =   (x*x);
        n = n>>1;
    }
    return (exp);
}

ZZ expo_modular_rapida_II (ZZ a, ZZ k, ZZ n){
    ZZ b; b=conv<ZZ>(1);
    if (k==0) return b;
    ZZ A; A=a;
    
    if(bit(k,0)==1) b=a;
    
    int tamano;
    tamano=NumBits(k);
    
    for (int i=1;i<tamano;i++){
        A=modulo_for_ZZ(A*A,n);
        if(bit(k,i)==1){
            b=modulo_for_ZZ(A*b, n);
        }
    }
    
    return b;
}


bool miller_binario(ZZ m){
    ZZ b=m-1;
    ZZ g=to_ZZ(1);ZZ x,h;
    ZZ cociente=b;
    ZZ num_bits;
    num_bits=NumBits(m);

    
    for(ZZ i=num_bits-1;i>=0;i--){
        x=g;
        g=modulo_for_ZZ(g*g,m);
        if(g==1 and x!=1 and x!=b)
            return 0;
        if(bit(m,conv<int>(i))==conv<ZZ>(1)){
            g=modulo_for_ZZ(g<<2,m);
        }
        if(g==1) return 1;
    }
    return 0;
}


bool test_primalidad_MIll_Rabin(ZZ n, int loops){
    ZZ a;
    a= n-to_ZZ("1");
    vector<ZZ> values;
    int i = 0;
    
    while (a != 0){
        i++;
        a /= to_ZZ("2");
        if (a>>1<<1 != a){
            values.push_back(to_ZZ(i));
            values.push_back(a);
            
        }
    }
    
    
    values.push_back(to_ZZ(i));
    values.push_back(a);
    ZZ s = values[0];
    ZZ r = values[1];
    
    
    ZZ j;
    for(j=0;j<loops;j++){
        ZZ rndom = modulo_for_ZZ(aleatorio(),n-2)+2;
        ZZ y = expo_modular_rapida_II(rndom,r,n);
        if( y != 1 && y!=n - to_ZZ("1")){
            ZZ j =  to_ZZ("1");
            while (j <= s - to_ZZ("1") && y != n - to_ZZ("1")){
                y = expo_modular_rapida_II(y,to_ZZ("2"),n);
                if (y == 1){
                    return 0;
                }
                j++;
            }
            if(y != n - to_ZZ("1") )
                return 0;
        }
    }
    return 1;
}

ZZ Conv_Bin(Vector Total)
{
    ZZ suma;
    int j=0;
    for(int i=Total.size()-1;i>-1;i--)
    {
        if(Total[i]==1) suma+= exponenciar_rapidamente(to_ZZ(2),to_ZZ(j));//to_ZZ(pow(2,j));
        j++;
    }
    return suma;
}

bool taps (Vector comodin, int num_taps){
    
    bool total;
    for(int i=0;i<num_taps;i++){
        total^=comodin[rand()%128+0];
    }
    return total;
}


ZZ funcion(tipo tam_bits, tipo largo_semilla, tipo num_vueltas, tipo num_particiones, tipo num_taps){
    
    Vector i_contenedor;
    i_contenedor.resize(largo_semilla);
    llenar(i_contenedor,tam_bits);
    
    ZZ numero;
    
    Vector comodin (i_contenedor.begin(),i_contenedor.end());
    
    
    //imprimir(comodin);
    
    for(int i=0;i<num_vueltas;i++){
        int indice_1=0;
        int indice_2=tam_bits/num_particiones;
        indice_2=indice_2*2-1;
        int largo_bloque=tam_bits/num_particiones;
        
        for(int p=0;p<num_particiones/2;p++){
            
            for(int m=0;m<largo_bloque;m++){
                //cout<<indice_1<<endl;
                //cout<<"    "<<indice_2<<endl;
                comodin[indice_1]=comodin[indice_1+1];
                comodin[indice_2]=comodin[indice_2-1];
                indice_1++;
                indice_2--;
            }
            
            
            //cout<<endl<<"-----------------"<<endl;
            //cout<<indice_1<<endl;
            comodin[indice_1]=taps(comodin, num_taps);
            indice_1+=largo_bloque;
            
            comodin[indice_2]=taps(comodin, num_taps);
            
            indice_2+=largo_bloque*3;
            
        }
        
        //cout<<endl<<"{{{{{{{{{{{{{{{}}}}}}}}}}"<<endl;
        comodin[comodin.size()-1]=1;
        //imprimir(comodin);
        
        numero=Conv_Bin(comodin);
        //cout<<numero<<endl;
        
        
        //if(ProbPrime(numero)){
        if(miller_binario(numero)==1){
        //if(test_primalidad_MIll_Rabin(numero,10)){
            //cout<<"I found a prime number : "<<numero<<endl;
            return numero;
            break;
        }
        
        else {
            
            ZZ a;
            a=conv<ZZ>(2);
            
            while(miller_binario(numero)==1){
            //while(ProbPrime(numero)!=1){
                //while(test_primalidad_MIll_Rabin(numero,10)!=1){
                
                if(miller_binario(numero-a)==1){
                //if(ProbPrime(numero-a)==1) {
                    //if(test_primalidad_MIll_Rabin(numero-a,10)==1) {
                    numero=numero-a;
                    //cout<<"Numero Primo : "<<numero<<endl;
                    break;
                    
                }
                else if(miller_binario(numero)==1){
                //else if(ProbPrime(numero+a)==1){
                    //else if(test_primalidad_MIll_Rabin(numero+a,10)==1){
                    numero=numero+a;
                    //cout<<"Numero Primo : "<<numero<<endl;
                    break;
                    
                }
                a+=2;
                
            }
            // cout<<endl<<"Tiempo total : "<<GetTime()<<endl;
            break;
        }
    }
    
    return numero;
}



void imprimir(Vector & i_contenedor){
    for (int x : i_contenedor) std::cout<<x;
    std::cout<<std::endl;
}

Vector copiar_model(Vector &i_contenedo){
    i_contenedo.clear();
    Vector copi;
    
    copi.resize(3);
    copi[0]=1;  copi[1]=0;  copi[2]=1;
    
    for (int i=0;i<copi.size();i++) i_contenedo.push_back(copi[i]);
    
    return i_contenedo;
}

Vector llenar(Vector & i_contenedor, tipo tam_bits){
    
    clock_t t;
    t = clock();
    srand (t);
    
    for (int i=0;i<i_contenedor.size();i++) i_contenedor[i]=rand()%2+0;
    
    //-------------RepeticionDeCeros---------//
    int i_count_zero = count(i_contenedor.begin(),i_contenedor.end(),0);
    if(i_count_zero  ==i_contenedor.size())
        copiar_model(i_contenedor);
    //--------------------------------------//
    
    
    //-----------LlenandoVector-------------//
    int tamano_anterior=i_contenedor.size();
    i_contenedor.resize(tam_bits);
    for(int i=tamano_anterior+1, j=0 ;i<i_contenedor.size();i++,j++)    i_contenedor[i]=(i_contenedor[j]^i_contenedor[j+1]);
    //--------------------------------------//
    
    return i_contenedor;
}





#endif
