/*
Union-find: Relacije [1.5 poen]
    Tekst zadatka
        Dat je niz stringova eq koji predstavlja niz relacija izmedju promenljivih (mala
        slova abecede, u opsegu ’a’-’z’) u obliku x==y ili x!=y. Potrebno je utvrditi
        da li je moguce dodeliti cele brojeve svim promenljivim tako da su sve zadate
        relacije ispunjene. Vrati true ako je to moguce, inace false.
    Opis ulaza i izlaza
        Ulaz: Na standardni ulaz unosi se broj n, a potom n stringova koji predstavl-
              jaju niz eq.
        Izlaz: Na standardni izlaz ispisati true ili false u skladu sa uslovima zadatka.
    Primer 1
        Ulaz:
            2
            a==b
            b!=a
        Izlaz:
            false
    Primer 2
        Ulaz:
            5
            a==b
            c==d
            b!=c
            d==e
            a!=e
        Izlaz:
            true
*/

#include <iostream>
#include <vector>

namespace my{
    class UnionFind{
        public:
            UnionFind(int n):
                parent(n),
                size(n, 1){
                for(int i=0; i<n; i++)
                    parent[i] = i;
            }
            ~UnionFind(){}
            
            void u(char x, char y){
                int koren_x = f(x);
                int koren_y = f(y);
                
                if(koren_x == koren_y)
                    return;
                
                if(size[koren_x] > size[koren_y]){
                    parent[koren_y] = koren_x;
                    size[koren_x] += size[koren_y];
                } else {
                    parent[koren_x] = koren_y;
                    size[koren_y] += size[koren_x];
                }
            }
            
            int f(int x){
                while(x != parent[x])
                    x = (parent[x] = parent[parent[x]]);
                return x;
            }
            
        private:
            std::vector<int> parent;
            std::vector<int> size;
            
    };
}

int main(){
    
    int n;
    std::cin >> n;
    
    std::vector<std::string> eq(n);
    for(int i=0; i<n; i++)
        std::cin >> eq[i];
    
    my::UnionFind uf(26);
    std::vector<int> inequalities;
    
    for(int i=0; i<n; i++){
        if(eq[i][1] == '=')
            uf.u(eq[i][0] - 'a', eq[i][3] - 'a');
        else
            inequalities.push_back(i);
    }
    
    for(int i=0; i<inequalities.size(); i++){
        if(uf.f(eq[inequalities[i]][0] - 'a') == uf.f(eq[inequalities[i]][3] - 'a')){
            std::cout << "false" << std::endl;
            return 0;
        }
    }
    
    std::cout << "true" << std::endl;
    
    return 0;
}