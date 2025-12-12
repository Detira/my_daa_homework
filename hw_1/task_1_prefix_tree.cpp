/*
Prefiksno drvo: Autocorrect [1.5 poen]
    Tekst zadatka
        Dat je niz stringova words, duzine n koji predstavlja recnik poznatih reci. Koris-
        nik sa standardnog ulaza unosi m reci iz recnika i povremeno moze pogresiti. Za
        svaku unetu rec koja ne pripada recniku, a u kojoj je korisnik pogresio na tacno
        jednom mestu, ispisati spisak svih mogucih reci iz recnika na koje je korisnik
        potencijalno mislio. Smatrati da korisnik uvek unosi rec sa jednakim brojem
        karaktera kao ispravna rec, tj. da samo moze pogresiti pri kucanju karaktera.
        Korisnik moze uneti proizvoljnu rec - potrebno je detektovati iskljucivo reci koje
        sadrze jedan pogresan karakter. U ostalim slucajevima ispisati prazan red.
        Opis ulaza i izlaza
        Ulaz: Na standardni ulaz unosi se broj n, a potom n stringova koji predstavl-
        jaju niz words. Nakon toga, unosi se broj m, a potom m reci.
        Izlaz: Na standardni izlaz za svaku od unetih m reci potrebno je ispisati sve
        reci (odvojene razmakom) u skladu sa uslovima zadatka.
    Primer
        Ulaz:
            6
            mikro
            makro
            mleko
            red
            sed
            sistem
            4
            mekro
            sleko
            red
            ped
        Izlaz:
            makro mikro
            mleko
            sed red
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

namespace my{
    class TrieNode{
        public:
            TrieNode(): indicator(false){}
            ~TrieNode(){
                for(auto child : this->children){
                    delete child.second;
                }
            }
            
            void insert(std::string t){
                TrieNode* t_node = this;
                for(char it : t){
                    if(t_node->children.contains(it)){
                        t_node = t_node->children[it];
                    } else {
                        t_node->children.emplace(it, new TrieNode());
                        t_node = t_node->children[it];
                    }
                }
                t_node->indicator = true;
            }
            
            void insert(std::vector<std::string> t){
                for(std::string it : t)
                    insert(it);
            }
           
            void process(std::string &t){
                TrieNode* t_node = this;
                bool t_indicator = true;
                for(char it : t){
                    if(t_node->children.contains(it)){
                        t_node = t_node->children[it];
                    } else {
                        t_indicator = false;
                        break;
                    }
                }
                if(t_indicator)
                    return;
                std::string prefix, suffix;
                for(int i=0; i<t.length(); i++){
                    t_node = this;
                    t_indicator = true;
                    prefix = t.substr(0, i);
                    suffix = t.substr(i+1, t.length()-i-1);
                    for(char it : prefix){
                        if(t_node->children.contains(it)){
                            t_node = t_node->children[it];
                        } else {
                            t_indicator = false;
                            break;
                        }
                    }
                    if(!t_indicator)
                        break;  // break umesto conitnue, jer ako jedan prefix ne poklopim necu moci ni naredni (duzi)
                    for(auto child : t_node->children){
                        t_indicator = true;
                        TrieNode* tt_node = child.second;
                        for(char it : suffix){
                            if(tt_node->children.contains(it)){
                                tt_node = tt_node->children[it];
                            } else {
                                t_indicator = false;
                                break;
                            }
                        }
                        if(t_indicator)
                            std::cout << prefix + child.first + suffix + " ";
                    }
                }
            }
            
        private:
            bool indicator;
            std::unordered_map<char, my::TrieNode*> children;
    };
}

int main(){
    
    int n;
    std::cin >> n;
    
    std::vector<std::string> words(n);
    for(int i=0; i<n; i++)
        std::cin >> words[i];
    
    my::TrieNode trie;
    trie.insert(words);
    
    int m;
    std::cin >> m;
    
    std::string t;
    std::queue<std::string> que;
    for(int i=0; i<m; i++){
        std::cin >> t;
        que.emplace(t);
    }
    
    for(int i=0; i<m; i++){
        trie.process(que.front());
        que.pop();
        std::cout << std::endl;
    }
    
    return 0;
}