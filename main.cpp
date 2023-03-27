#include <iostream>
#include "Dictionary.h"

int main() {
    //test rozszerzania się słownika oraz nadpisywania elementu o kluczu a
    Dictionary<string,int> dict;
    dict.add(pair<string,int>("a",5));
    dict.add(pair<string,int>("c",7));
    dict.add(pair<string,int>("a",2));
    dict.add(pair<string,int>("b",3));
    dict.add(pair<string,int>("d",1));
    dict.add(pair<string,int>("e",5));
    dict.add(pair<string,int>("f",7));
    dict.add(pair<string,int>("g",2));
    dict.add(pair<string,int>("h",3));
    dict.add(pair<string,int>("i",1));
    dict.add(pair<string,int>("j",5));
    dict.add(pair<string,int>("k",7));
    dict.add(pair<string,int>("l",2));
    dict.add(pair<string,int>("m",3));
    dict.add(pair<string,int>("n",1));
    dict.print();
    std::cout<<"===========================================\n";


    //test usuwania elementów
    dict.remove_by_key("k");
    dict.remove_by_key("a");
    dict.remove_by_key("c");
    dict.remove_by_key("f");
    dict.remove_by_key("b");
    dict.remove_by_key("i");
    dict.remove_by_key("l");
    dict.remove_by_key("d");
    dict.remove_by_key("e");
    dict.remove_by_index(0);
    dict.print();
    std::cout<<"===========================================\n";


    //test czyszczenia słownika
    dict.clear();
    dict.add(pair<string,int>("n",1));
    for(const auto& i: dict){
        std::cout<<i.first<<" - "<<i.second<<"\n";
    }
    std::cout<<"===========================================\n";

    //test drugiego konstruktora słownika

    Dictionary<std::string,int> dict2 = {std::pair<string,int>("a",4),std::pair<string,int>("ba",8)};
    dict2.print();
    std::cout<<"===========================================\n";

    //test gettera
    std::cout<<dict2["ba"]<<"\n";

    //test wektorów kluczy i wartości
    for(auto i: dict2.keys())
        std::cout<<i;
    std::cout<<"\n===========================================\n";
    for(auto i: dict2.values())
        std::cout<<i;

    return 0;
}
