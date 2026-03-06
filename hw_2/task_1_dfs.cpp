/*
Planinarenje
    Tekst zadatka
        Stevan je strastveni planinar koji najvise uziva u sto duzim planinarskim avanturama. On se nalazi na planini Matriks, specificna po tome sto su njeni vrhovi poredjani u matricu velicine m x n. Stevan zeli da osvoji sto vise vrhova na planini Matriks, uz jedan uslov - nakon osvajanja jednog vrha, Stevan sledeci put mora osvojiti vrh koji je visi od tog osvjenog vrha, Stevanu su poznate visine svih vrhova na planini Matriks, a s obzirom da poseduje helikopter, moze poceti svoju avanturu sa bilo kog vrha na planini Matriks. Odrediti najveci moguci broj vrhova koje Stevan moze osvojiti, uzevsi u obzir da Stevan, krenuvsi sa jednog vrha, mora osvojiti vrh koji se u matrici nalazi neposredno levo, desno, gore ili dole, ili moze zavrsiti svoju planinarsku avanturu.
    Primer
        Ulaz
            3 3
            3 4 5
            3 2 6
            2 2 1
        Izlaz
            4
*/

#include <iostream>
#include <vector>
#include <stack>

namespace my{
    class Graph{
        public:
            Graph(bool directed): directed(directed){}
            ~Graph(){}
            
            void add_vertex(){
                neighbours.emplace_back();
            }
            
            void add_edge(int x, int y){
                if(neighbours.size() <= x || neighbours.size() <= y){
                    std::cout << "Provided vertices don't exist." << std::endl;
                    return;
                }
                
                neighbours[x].emplace_back(y);
                
                if(!directed)
                    neighbours[y].emplace_back(x);
            }
            
            void dfs(std::vector<int> x){
                std::vector<bool> visited(neighbours.size());
                
                std::stack<std::pair<int, bool>> s;
                for(int i = neighbours.size() - 1; i>=0; i--)
                    s.emplace(i, false);
                for(auto it = x.rbegin(); it != x.rend(); ++it)
                    s.emplace(*it, false);
                
                while(!s.empty()){
                    int v = s.top().first;
                    bool backtracking = s.top().second;
                    s.pop();
                    
                    if(visited[v]){
                        if(backtracking){
                            // output processing/on completion START
                            std::cout << "Leaving (Backtracking): " << v << std::endl;
                            // output processing/on completion END
                        }
                    } else {
                        visited[v] = true;
                        // input processing/on discovery START
                        std::cout << "Entering: " << v << std::endl;
                        // input processing/on discovery END
                        s.emplace(v, true);
                        for(auto it = neighbours[v].rbegin(); it != neighbours[v].rend(); ++it)
                            s.emplace(*it, false);
                    }
                }
            }
            
            int dfs_planinarenje(const std::vector<std::vector<int>> &mountain, int n){
                std::vector<bool> visited(neighbours.size());
                
                std::stack<std::pair<int, bool>> s;
                for(int i = neighbours.size() - 1; i>=0; i--)
                    s.emplace(i, false);
                
                int current = 0;
                int max = 1;
                
                while(!s.empty()){
                    int v = s.top().first;
                    bool backtracking = s.top().second;
                    s.pop();
                    
                    if(visited[v]){
                        if(backtracking){
                            // output processing/on completion START
                            std::cout << "Leaving (Backtracking): " << v << std::endl;
                            visited[v] = false;
                            current--;
                            // output processing/on completion END
                        }
                    } else {
                        visited[v] = true;
                        // input processing/on discovery START
                        std::cout << "Entering: " << v << std::endl;
                        current++;
                        if(current > max)
                            max = current;
                        // input processing/on discovery END
                        s.emplace(v, true);
                        for(auto it = neighbours[v].rbegin(); it != neighbours[v].rend(); ++it)
                            if(mountain[v/n][v%n] < mountain[*it/n][*it%n])
                                s.emplace(*it, false);
                    }
                }
                return max;
            }
        
        private:
            bool directed;
            std::vector<std::vector<int>> neighbours;
    };
}

int main(){
    
    my::Graph graf(false);
    
    int m, n;
    std::cin >> m >> n;
    
    for(int i=0; i<m*n; i++)
        graf.add_vertex();
    
    for(int i=0; i<m-1; i++){
        for(int j=0; j<n-1; j++){
            graf.add_edge(i*n+j, i*n+j+1);
            graf.add_edge(i*n+j, i*n+j+n);
        }
        graf.add_edge(i*n+n-1, i*n+n-1+n);
    }
    for(int j=0; j<n-1; j++)
        graf.add_edge((m-1)*n+j, (m-1)*n+j+1);
    
    int t;
    std::vector<std::vector<int>> mountain(m);
    for(int i=0; i<m*n; i++){
        std::cin >> t;
        mountain[i/n].emplace_back(t);
    }
    
    std::cout << graf.dfs_planinarenje(mountain, n) << std::endl;
    
    return 0;
}

/*
Primer
    Ulaz
        3 3
        3 4 5
        3 2 6
        2 2 1
    Izlaz
        4
*/