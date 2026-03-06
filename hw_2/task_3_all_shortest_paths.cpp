/*
Prijateljsko putovanje
    Tekst zadatka
        Tri prijatelja, A, B i C, planiraju zajednicko putovanje. Prijatelj A poseduje automobil i zapocinje putovanje iz jednog grada, sa ciljem da stigne do unapred zadatog odredista. Izmedju gradova postoje putevi, pri cemu je za svaki put poznata cena putovanja. Tokom putovanja, A mora usput da pokupi prijatelje B i C. Preuzimanje prijatelja moguce je iskljucivo prolaskom kroz tacno odredjene puteve, pri cemu se B i C preuzimaju na razlicitim putevima. Redosled preuzimanja prijatelja nije unapred odredjen. Odrediti najmanju mogucu cenu putovanja od pocetnog grada do krajnjeg odredista uz uslov da je potrebno pokupiti B i C.
    Primer
        Ulaz
            10 14
            1 2 4
            1 3 2
            2 4 7
            3 4 3
            3 5 6
            4 6 1
            5 6 2
            6 7 3
            7 10 5
            6 8 4
            8 9 1
            9 10 2
            5 9 8
            2 5 5
            1 10
            3 4
            6 7
        Izlaz
            14
*/

#include <iostream>
#include <vector>
#include <stack>
#include <limits>

#define INF std::numeric_limits<int>::max()

namespace my{
    class Graph{
        public:
            Graph(int vertices, bool directed): directed(directed), matrix(vertices, std::vector<int>(vertices, INF)){
                for(int i=0; i<vertices; i++)
                    matrix[i][i] = 0;
            }
            ~Graph(){}
            
            void add_edge(int x, int y, int w){
                if(matrix.size() <= x || matrix.size() <= y){
                    std::cout << "Provided vertices don't exist." << std::endl;
                    return;
                }
                
                matrix[x][y] = w;
                
                if(!directed)
                    matrix[y][x] = w;
            }
            
            void route(int start, int finish, int bx, int by, int cx, int cy){
                auto shortestPaths = matrix;
                
                for(int i=0; i<matrix.size(); i++){
                    for(int j=0; j<i; j++){
                        for(int k=0; k<i; k++){
                            if(matrix[i][k] != INF && shortestPaths[k][j] != INF && matrix[i][k] + shortestPaths[k][j] < shortestPaths[i][j])
                                shortestPaths[i][j] = matrix[i][k] + shortestPaths[k][j];
                            
                            if(shortestPaths[j][k] != INF && matrix[k][i] != INF && shortestPaths[j][k] + matrix[k][i] < shortestPaths[j][i])
                                shortestPaths[j][i] = shortestPaths[j][k] + matrix[k][i];
                        }
                    }
                    for(int j=0; j<i; j++){
                        for(int k=0; k<i; k++){
                            if(shortestPaths[j][i] != INF && shortestPaths[i][k] != INF && shortestPaths[j][i] + shortestPaths[i][k] < shortestPaths[j][k])
                                shortestPaths[j][k] = shortestPaths[j][i] + shortestPaths[i][k];
                        }
                    }
                }
                
                int p1, p2, q1, q2, t, min = INF;
                for(int i=0; i<8; i++){
                    switch(i){
                        case 0:
                            p1 = bx; p2 = by; q1 = cx; q2 = cy;
                            break;
                        case 1:
                            p1 = bx; p2 = by; q2 = cx; q1 = cy;
                            break;
                        case 2:
                            p2 = bx; p1 = by; q1 = cx; q2 = cy;
                            break;
                        case 3:
                            p2 = bx; p1 = by; q2 = cx; q1 = cy;
                            break;
                        case 4:
                            q1 = bx; q2 = by; p1 = cx; p2 = cy;
                            break;
                        case 5:
                            q1 = bx; q2 = by; p2 = cx; p1 = cy;
                            break;
                        case 6:
                            q2 = bx; q1 = by; p1 = cx; p2 = cy;
                            break;
                        case 7:
                            q2 = bx; q1 = by; p2 = cx; p1 = cy;
                            break;
                    }
                    
                    if(shortestPaths[start][p1] != INF && matrix[p1][p2] != INF && shortestPaths[p2][q1] != INF && matrix[q1][q2] != INF && shortestPaths[q2][finish] != INF){
                        t = shortestPaths[start][p1] + matrix[p1][p2] + shortestPaths[p2][q1] + matrix[q1][q2] + shortestPaths[q2][finish];
                        
                        if(t < min)
                            min = t;
                    }
                }
                std::cout << min << std::endl;
            }
            
        private:
            bool directed;
            std::vector<std::vector<int>> matrix;
    };
}

int main(){
    
    int vertices, edges;
    std::cin >> vertices >> edges;
    
    my::Graph graf(vertices+1, true);
    
    int x, y, w;
    for(int i=0; i<edges; i++){
        std::cin >> x >> y >> w;
        graf.add_edge(x, y, w);
    }
    
    int start, finish, bx, by, cx, cy;
    std::cin >> start >> finish >> bx >> by >> cx >> cy;
    
    graf.route(start, finish, bx, by, cx, cy);
    
    return 0;
}

/*
Primer
    Ulaz
        10 14
        1 2 4
        1 3 2
        2 4 7
        3 4 3
        3 5 6
        4 6 1
        5 6 2
        6 7 3
        7 10 5
        6 8 4
        8 9 1
        9 10 2
        5 9 8
        2 5 5
        1 10
        3 4
        6 7
    Izlaz
        14
*/