/*
2SAT
    Tekst zadatka
        2SAT predstavlja problem zadovoljivosti iskazne formule date u konjuktivnoj normalnoj formi (KNF) pri cemu svaki konjunkt sadrzi tacno dva literala (literal je iskazno slovo ili negacija iskaznog slova). Jedan primer formule u trazenom obliku je:
            (a or not b) and (c or d) and (not a or e) and (not b or not f)
        Standard za predstavljanje KNF formula u racunaru je DIMACS o kom mozete vise procitati ovde: https://jix.github.io/varisat/manual/0.2.0/formats/dimacs.html
        Za datu KNF formulu u kojoj svaki konjunkt sadrzi tacno dva literala, koja je data u DIMACS formatu, ispitati da li je iskazno zadovoljiva.
    Primer
        Ulaz
            p cnf 4 5
             1 -2 0
            -1  3 0
             2  3 0
            -3 -4 0
             4 -1 0
        Izlaz
            true
        Ulaz
            p cnf 4 7
             1  2 0
            -1  3 0
            -3  4 0
            -4  2 0
             2 -3 0
            -1 -4 0
             1 -2 0
        Izlaz
            false
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <cstdlib>

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
            /*
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
            */
            
            void dfs_simple(int v){
                visited.resize(neighbours.size());
                
                dfs_simple_help(v);
            }
            
            void dfs_simple_help(int v){
                visited[v] = true;
                // input processing/on discovery START
                std::cout << "Entering: " << v << std::endl;
                // input processing/on discovery END
                
                for(auto neighbour : neighbours[v])
                    if(!visited[v])
                        dfs_simple_help(neighbour);
                
                // output processing/on completion START
                std::cout << "Leaving (Backtracking): " << v << std::endl;
                // output processing/on completion END
            }
            
            void scc_tarjan(int v){
                visited.resize(neighbours.size());
                
                pre.resize(neighbours.size());
                current_pre = 0;
                lowlink.resize(neighbours.size());
                onTarjansStack.resize(neighbours.size());
                
                scc_tarjan_help(v);
            }
            
            void scc_tarjan_help(int v){
                visited[v] = true;
                // input processing/on discovery START
                //std::cout << "Entering: " << v << std::endl;
                lowlink[v] = pre[v] = current_pre++;
                tarjansStack.emplace(v);
                onTarjansStack[v] = true;
                // input processing/on discovery END
                for(auto neighbour : neighbours[v])
                    if(!visited[neighbour]){
                        scc_tarjan_help(neighbour);
                        if(lowlink[v] > lowlink[neighbour])
                            lowlink[v] = lowlink[neighbour];
                    } else if(onTarjansStack[neighbour]){
                        if(lowlink[v] > pre[neighbour])
                            lowlink[v] = pre[neighbour];
                    }
                
                // output processing/on completion START
                //std::cout << "Leaving (Backtracking): " << v << std::endl;
                if(lowlink[v] == pre[v]){
                    components.emplace_back();
                    int t;
                    do{
                        t = tarjansStack.top();
                        tarjansStack.pop();
                        onTarjansStack[t] = false;
                        
                        components.back().insert(t);
                    } while(t != v);
                }
                // output processing/on completion END
                /*
                for(int i=0; i<neighbours.size(); i++)
                    if(!visited[i])
                        scc_tarjan_help(i);
                */
            }
            
            void twoSat(int vertices){
                add_vertex();
                int t = neighbours.size() - 1;
                for(int i=0; i<t; i++)
                    add_edge(t, i);
                
                scc_tarjan(t);
                
                for(auto component : components)
                    for(int v : component)
                        if(v < vertices){
                            if(component.contains(v + vertices)){
                                std::cout << "false" << std::endl;
                                return;
                            }
                        } else {
                            if(component.contains(v - vertices)){
                                std::cout << "false" << std::endl;
                                return;
                            }
                        }
                std::cout << "true" << std::endl;
            }
        
        private:
            bool directed;
            std::vector<std::vector<int>> neighbours;
            
            std::vector<bool> visited;
            
            std::vector<int> pre;
            int current_pre;
            std::vector<int> lowlink;
            std::stack<int> tarjansStack;
            std::vector<bool> onTarjansStack;
            std::vector<std::unordered_set<int>> components;
    };
}

int main(){
    
    my::Graph graf(true);
    
    int vertices, edges;
    std::string dummy;
    std::cin >> dummy >> dummy >> vertices >> edges;
    for(int i=0; i<vertices; i++){
        graf.add_vertex();
        graf.add_vertex();
    }
    int x, y;
    for(int i=0; i<edges; i++){
        std::cin >> x >> y >> dummy;
        if(x>0){
            x--;
        } else {
            x = std::abs(x + 1) + vertices;
        };
        if(y>0){
            y--;
        } else {
            y = std::abs(y + 1) + vertices;
        }
        if(x < vertices){
            graf.add_edge(x + vertices, y);
        } else {
            graf.add_edge(x - vertices, y);
        }
        if(y < vertices){
            graf.add_edge(y + vertices, x);
        } else {
            graf.add_edge(y - vertices, x);
        }
    }
    
    graf.twoSat(vertices);
    
    return 0;
}

/*
    Primer
        Ulaz
            p cnf 4 5
            1 -2 0
            -1  3 0
            2  3 0
            -3 -4 0
            4 -1 0
        Izlaz
            true
        Ulaz
            p cnf 4 7
            1  2 0
            -1  3 0
            -3  4 0
            -4  2 0
            2 -3 0
            -1 -4 0
            1 -2 0
        Izlaz
            false
*/

/*
1 - 0
2 - 1
3 - 2
4 - 3
...
-1 - vert
-2 - vert + 1
-3 - vert + 2
*/