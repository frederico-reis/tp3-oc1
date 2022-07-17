#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <math.h>
/*Não entenda o código, sinta o código :D */
using namespace std;

class Palavra{
    // 32 bits
    public:
        string p;
    Palavra(){
        p = "vazio";
    }
};

class Bloco{
    // 4 palavras de 32 bits
    public:
        vector<Palavra> b;
        Bloco(){
            b.resize(4);
        }

};


class Cache{
    //64 blocos. cada bloco com 4 palavras de 32 bits
    public:
        vector<Bloco> c;

        Cache(){
            c.resize(64);
        }
};

class MemoriaDados{
    // 1024 palavras de 32 bits
    public:
    void escreveMemoriaDados(){ //para o write back

    }
};



int main(){

/*  22 bits de tag
    6 bits indice 
    2 bits offset bloco
    2 bits offset palavra
*/

/*  A memória usa o byte adressing. Por exemplo, o endereço nº 6 se refere ao terceiro byte da segunda palavra da memória.
    Tem tanto o offset da palavra no bloco quanto o offset do byte na palavra.
    Repare que o offset de bloco no endereço 6 ficaria 01 (segunda palavra?) e o offset na palavra seria 10 (terceiro byte da palavra?).
*/

    Cache cache;
    MemoriaDados memoriaDados;

    int N = 0, tipoOperacao, numeroBloco = 0, numeroPalavra;
    int num_miss = 0; 
    int num_hit = 0;
    int missRate, hitRate;
    int num_operacoes = 0;
    int num_reads = 0;
    int num_writes = 0;
    int teste = 0;
   
    string dado;
    bool hit;
    Palavra palavra;
    while(cin>>N){
        teste++;
        //cout<<N<<" "<<endl;
        bitset<sizeof(N) *__CHAR_BIT__> bitsN(N);
        bitset<sizeof(6) *__CHAR_BIT__> bitsIndice;
        bitset<sizeof(2) *__CHAR_BIT__> bitsOffsetBloco;
        for(int i = 4; i <= 9; i++){
             bitsIndice[i - 4] = bitsN[i];
        }
        numeroBloco = bitsIndice.to_ulong();
        bitsOffsetBloco[0] = bitsN[2];
        bitsOffsetBloco[1] = bitsN[3];
        numeroPalavra = bitsOffsetBloco.to_ulong();

        cin >> tipoOperacao;
            if(tipoOperacao == 1){ //escrita
                num_writes++;
                cin >> dado;
                palavra.p = dado;
                
                if(cache.c[numeroBloco].b[numeroPalavra].p == "vazio"){   //escreve na cache os endereços do mesmo bloco
                    cout<<"o endereço "<<N<<" foi escrito na cache"<<endl;
                    switch (numeroPalavra){

                    case 0:   //melhor jeito que eu pensei pra preencher tudo do jeito certo
                        cache.c[numeroBloco].b[0].p = N;
                        cache.c[numeroBloco].b[1].p = N+1;
                        cache.c[numeroBloco].b[2].p = N+2;
                        cache.c[numeroBloco].b[3].p = N+3;
                        break;
                   
                    case 1:
                        cache.c[numeroBloco].b[0].p = N-1;
                        cache.c[numeroBloco].b[1].p = N;
                        cache.c[numeroBloco].b[2].p = N+1;
                        cache.c[numeroBloco].b[3].p = N+2;
                        break;

                    case 2:
                        cache.c[numeroBloco].b[0].p = N-2;
                        cache.c[numeroBloco].b[1].p = N-1;
                        cache.c[numeroBloco].b[2].p = N;
                        cache.c[numeroBloco].b[3].p = N+1;
                        break;

                    case 3:
                        cache.c[numeroBloco].b[0].p = N-3;
                        cache.c[numeroBloco].b[1].p = N-2;
                        cache.c[numeroBloco].b[2].p = N-1;
                        cache.c[numeroBloco].b[3].p = N;
                        break;

                    default: //deixei só por segurança, pq vai que dá ruim né
                        cache.c[numeroBloco].b[0].p = N;
                        cache.c[numeroBloco].b[1].p = N;
                        cache.c[numeroBloco].b[2].p = N;
                        cache.c[numeroBloco].b[3].p = N;
                        break;
                    }
                } else {
                    cout<<"o endereço "<<N<<" ja tava escrito na cache"<<endl;  //cout auxiliar, só pra ver o que ta acontecendo com cada operação
                }
                
            }else{//leitura
                num_reads++;

                if(cache.c[numeroBloco].b[0].p == "vazio"){ //não tá na cache, só confiro o primeiro pq escreve no bloco todo, então não faz diferença
                    hit = false;
                    num_miss++;
                    cout<<"o endereço "<<N<<" deu miss"<<endl;
                } else { //deu o hit
                    hit = true;
                    num_hit++;
                    cout<<"o endereço "<<N<<" deu hit"<<endl;
                }
            
                if(!hit){     //caso não dê hit, tem que escrever esse endereço na cache
                   switch (numeroPalavra){
                        
                    case 0:  //sim, eu só copiei e colei do outro, seria mais inteligente encapsular numa função
                        cache.c[numeroBloco].b[0].p = N;
                        cache.c[numeroBloco].b[1].p = N+1;
                        cache.c[numeroBloco].b[2].p = N+2;
                        cache.c[numeroBloco].b[3].p = N+3;
                        break;
                   
                    case 1:
                        cache.c[numeroBloco].b[0].p = N-1;
                        cache.c[numeroBloco].b[1].p = N;
                        cache.c[numeroBloco].b[2].p = N+1;
                        cache.c[numeroBloco].b[3].p = N+2;
                        break;

                    case 2:
                        cache.c[numeroBloco].b[0].p = N-2;
                        cache.c[numeroBloco].b[1].p = N-1;
                        cache.c[numeroBloco].b[2].p = N;
                        cache.c[numeroBloco].b[3].p = N+1;
                        break;

                    case 3:
                        cache.c[numeroBloco].b[0].p = N-3;
                        cache.c[numeroBloco].b[1].p = N-2;
                        cache.c[numeroBloco].b[2].p = N-1;
                        cache.c[numeroBloco].b[3].p = N;
                        break;

                    default: //deixei só por segurança, pq vai que dá ruim né
                        cache.c[numeroBloco].b[0].p = N;
                        cache.c[numeroBloco].b[1].p = N;
                        cache.c[numeroBloco].b[2].p = N;
                        cache.c[numeroBloco].b[3].p = N;
                        break;
                    }
                }
            }
    }

    float missRate2, hitRate2;
    cout<<"reads: "<<num_reads<<endl;
    cout<<"writes: "<<num_writes<<endl;
    cout<<"hits: "<<num_hit<<endl;
    cout<<"miss: "<<num_miss<<endl;
    missRate2 = (float)num_miss/num_reads;
    hitRate2 = 1 - missRate2;
    cout<<"Hit rate:"<<hitRate2<<endl;
    cout<<"miss rate:"<<missRate2<<endl;

    return 0;
}