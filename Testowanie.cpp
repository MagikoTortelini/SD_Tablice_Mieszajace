#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <numeric>
#include "Cuckoo.hpp"
#include <random>
#include <limits>

using namespace std::chrono;
using namespace std;
void Test_insert(int ilosc,int typ,int liczba_,int priorytet){

    std::vector<long long> duration_tablica;
    switch (typ)
    {
    case 1:{
        for(int z=0;z<10;z++){
            for(int i=0;i<10;i++){
                Cuckoo cuckoo(ilosc);
                std::string nazwa_pliku = "dane/dane_" + std::to_string(ilosc)+"_"+std::to_string(i) + ".txt";
                std::fstream plik(nazwa_pliku,std::ios_base::in);
                for(int i=0;i<ilosc;i++){
                    int e;
                    int p;
                    plik>>e>>p;

                    cuckoo.insert(e,p);

                }
                auto start=high_resolution_clock::now();
                cuckoo.insert(liczba_,priorytet);
                auto end=high_resolution_clock::now();
                duration_tablica.push_back(duration_cast<nanoseconds>(end-start).count());
            }
        }
        break;
    }

    default:
        break;
    }
    std::cout<<"Czas trwania dodawania: "<<std::accumulate(duration_tablica.begin(),duration_tablica.end(),0LL)/100<<"ns"<<std::endl;
    std::cout<<std::endl;
}

void Test_remove(int ilosc,int typ){

    std::vector<long long> duration_tablica;
    switch (typ)
    {
    case 1:{
         for(int z=0;z<10;z++){
            for(int i=0;i<10;i++){
                Cuckoo cuckoo(ilosc);
                int del_key;
                std::string nazwa_pliku = "dane/dane_" + std::to_string(ilosc)+"_"+std::to_string(i) + ".txt";
                std::fstream plik(nazwa_pliku,std::ios_base::in);
                for(int i=0;i<ilosc;i++){
                    int e;
                    int p;
                    plik>>e>>p;
                    if(i==0)
                    {
                        del_key=e;
                    }

                    cuckoo.insert(e,p);

                }
                auto start=high_resolution_clock::now();
                cuckoo.remove(del_key);
                auto end=high_resolution_clock::now();
                duration_tablica.push_back(duration_cast<nanoseconds>(end-start).count());
            }
        }
        break;
    }

    default:
        break;
    }
    std::cout<<"Czas trwania usuwania: "<<std::accumulate(duration_tablica.begin(),duration_tablica.end(),0LL)/100<<"ns"<<std::endl;
    std::cout<<std::endl;
}

void Test_search(int ilosc,int typ,int key_){

    std::vector<long long> duration_tablica;
    switch (typ)
    {
    case 1:{
        for(int z=0;z<10;z++){
            for(int i=0;i<10;i++){
                Cuckoo cuckoo(ilosc);
                std::string nazwa_pliku = "dane/dane_" + std::to_string(ilosc)+"_"+std::to_string(i) + ".txt";
                std::fstream plik(nazwa_pliku,std::ios_base::in);
                for(int i=0;i<ilosc;i++){
                    int e;
                    int p;
                    plik>>e>>p;

                    cuckoo.insert(e,p);

                }
                auto start=high_resolution_clock::now();
                cuckoo.search(key_);
                auto end=high_resolution_clock::now();
                duration_tablica.push_back(duration_cast<nanoseconds>(end-start).count());
            }
        }
        break;
    }

    default:
        break;
    }
    std::cout<<"Czas trwania szukania: "<<std::accumulate(duration_tablica.begin(),duration_tablica.end(),0LL)/100<<"ns"<<std::endl;
    std::cout<<std::endl;
}


void testy(int decyzja_){
    std::vector<int> zakres={5000,8000,10000,16000,20000,40000,60000,80000,100000};
    std::random_device rd;
    std::mt19937 gen(rd());

    int decyzja;
    std::string buff;
    bool temp=true;
    int liczba;
    int priorytet;
    while(temp){
    system("clear");
    std::cout<<"TESTOWANIE STRUKTURY:"<<std::endl<<"Wybierz opcje testu:"<<std::endl;
    std::cout<<"1. Test Insert"<<std::endl<<
               "2. Test remove"<<std::endl<<
               "3. Test Search"<<std::endl;

    std::cin>>decyzja;
    switch (decyzja)
    {
    case 1:{
        system("clear");

        for(int i=0;i<zakres.size();i++){
            std::uniform_int_distribution<int> dist(0,std::numeric_limits<int>::max());
            std::uniform_int_distribution<int> dist_p(0,zakres[i]*5);
            liczba=dist(gen);
            priorytet=dist_p(gen);
            std::cout<<"Test dla zakresu: "<<zakres[i]<<std::endl;
            Test_insert(zakres[i],decyzja_,liczba,priorytet);
        }
    }
        break;
    case 2:{
        system("clear");
        for(int i=0;i<zakres.size();i++){
            std::cout<<"Test dla zakresu: "<<zakres[i]<<std::endl;
            Test_remove(zakres[i],decyzja_);
        }
    }
        break;

    case 3:{
        system("clear");
        for(int i=0;i<zakres.size();i++){
            std::uniform_int_distribution<int> dist(0,std::numeric_limits<int>::max());
            liczba=dist(gen);

            std::cout<<"Test dla zakresu: "<<zakres[i]<<std::endl;
            Test_search(zakres[i],decyzja_,liczba);
        }
    }
        break;

    case 4:
        temp=false;
        break;
    default:
        temp=false;
        break;
    }

    std::cout<<std::endl<<"wpisz co kolwiek"<<std::endl;
    std::cin>>buff;
    }


}
void wybor_struktury(){
    system("clear");
    int decyzja;
    std::cout<<"TESTOWANIE STRUKTUR:"<<std::endl<<"Wybierz struktury do testu:"<<std::endl;
    std::cout<<"1. Cucko Hasing"<<std::endl<<
               "2. Lista"<<std::endl;
    std::cin>>decyzja;
    testy(decyzja);

}






int main(){
    while (true)
    {
    wybor_struktury();
    }
    return 0;
}