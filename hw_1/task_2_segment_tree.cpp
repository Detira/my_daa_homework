/*
Segmentno stablo: Dobre trojke [2 poena]
    Tekst zadatka
        Dat je niz pozitivnih celih brojeva arr. Uredjena trojka indeksa (i,j,k) za
        koju vazi i < j < k je dobra trojka niza arr ako vazi jedan od naredna dva
        uslova: arr[i] < arr[j] < arr[k] ili arr[i] > arr[j] > arr[k]. Odrediti
        broj uredjenih trojki niza arr.
    Opis ulaza i izlaza
        Ulaz: Na standardni ulaz unosi se broj n, a nakon toga n celih brojeva koji
              predstavljaju niz arr.
        Izlaz: Na standardni izlaz ispisati broj dobrih trojki niza arr.
    Primer
        Ulaz:
            5
            2 5 3 4 1
        Izlaz:
            3
    Objasnjenje: U pitanju su trojke (0,2,3), (1,2,4) i (1,3,4)
*/

#include <iostream>
#include <vector>
#include <bit>

namespace my{
    class SegmentTree{
        public:
            SegmentTree(unsigned int n):
                half_size(std::bit_ceil(n)),
                data(2*half_size),
                lazy(2*half_size){}
            ~SegmentTree(){}
            
            void point_update(int index, int increment){
                index += half_size - 1;
                
                while(index > 0){
                    data[index] += increment;
                    index /= 2;
                }
            }
            
            void range_update(int a, int b, int increment){
                range_update_recursive(a+half_size-1, b+half_size-1, increment, 1, half_size, 2*half_size-1);
            }
            
            int point_query(int queried_index){
                queried_index += half_size - 1;
                int current_index = 1;
                int x = half_size;
                int y = 2 * half_size - 1;
                
                while(current_index != queried_index){
                    if((queried_index - x) < (y - queried_index)){
                        current_index *= 2;
                        y = (x+y)/2;
                    } else {
                        current_index = current_index * 2 + 1;
                        x = (x+y)/2+1;
                    }
                    
                    data[current_index] += lazy[current_index] * (y-x+1);
                    if(x != y){
                        lazy[current_index*2] += lazy[current_index];
                        lazy[current_index*2+1] += lazy[current_index];
                    }
                    lazy[current_index] = 0;
                }
                return data[current_index];
            }
            
            int range_query(int a, int b){
                int result = 0;
                range_query_recursive(a+half_size-1, b+half_size-1, result, 1, half_size, 2*half_size-1);
                return result;
            }
            
            void print_all(){
                std::cout << "half_size = " << half_size << std::endl;
                std::cout << "data: ";
                for(auto t : data)
                    std::cout << t << " ";
                std::cout << std::endl;
                std::cout << "lazy: ";
                for(auto t : lazy)
                    std::cout << t << " ";
                std::cout << std::endl;
            }
            
        private:
            const unsigned int half_size;
            std::vector<int> data;
            std::vector<int> lazy;
            
            void range_update_recursive(int a, int b, int increment, int index, int x, int y){
                //std::cout << "range_update_recursive: a= " << a << " b= " << b << " inc= " << increment << " index= " << index << " x= " << x << " y= " << y << std::endl;
                data[index] += lazy[index] * (y-x+1);
                if(x != y){
                    lazy[index*2] += lazy[index];
                    lazy[index*2+1] += lazy[index];
                }
                lazy[index] = 0;
                
                if(a<=x && y<=b){//std::cout << "podskup" << std::endl;
                    data[index] += increment * (y-x+1);
                    if(x != y){
                        lazy[index*2] += increment;
                        lazy[index*2+1] += increment;
                    }
                } else if(y>=a && x<=b){//std::cout << "presek" << std::endl;
                    range_update_recursive(a, b, increment, index*2, x, (x+y)/2);
                    range_update_recursive(a, b, increment, index*2+1, (x+y)/2+1, y);
                    
                    data[index] = data[index*2] + data[index*2+1];
                }
            }
            
            void range_query_recursive(int a, int b, int& result, int index, int x, int y){
                data[index] += lazy[index] * (y-x+1);
                if(x != y){
                    lazy[index*2] += lazy[index];
                    lazy[index*2+1] += lazy[index];
                }
                lazy[index] = 0;
                
                if(a<=x && y<=b){
                    result += data[index];
                } else if(y>=a && x<=b){
                    range_query_recursive(a, b, result, index*2, x, (x+y)/2);
                    range_query_recursive(a, b, result, index*2+1, (x+y)/2+1, y);
                    
                    data[index] = data[index*2] + data[index*2+1];
                }
            }
            
    };
}

int main(){
    
    int n;
    std::cin >> n;
    
    std::vector<int> arr(n);
    unsigned int max = 1;
    for(int i=0; i<n; i++){
        std::cin >> arr[i];
        if(arr[i] > max)
            max = arr[i];
    }
    
    my::SegmentTree tree1(max);
    std::vector<int> earlier_lesser(n, 0);
    std::vector<int> earlier_greater(n, 0);
    my::SegmentTree tree2(max);
    std::vector<int> later_lesser(n, 0);
    std::vector<int> later_greater(n, 0);
    
    for(int i=0; i<n; i++){
        if(arr[i] != 1)
            earlier_lesser[i] = tree1.range_query(1, arr[i]-1);
        if(arr[i] != max)
            earlier_greater[i] = tree1.range_query(arr[i]+1, max);
        tree1.point_update(arr[i], 1);
    }
    
    for(int i=n-1; i>=0; i--){
        if(arr[i] != 1)
            later_lesser[i] = tree2.range_query(1, arr[i]-1);
        if(arr[i] != max)
            later_greater[i] = tree2.range_query(arr[i]+1, max);
        tree2.point_update(arr[i], 1);
    }
    
    int result = 0;
    for(int i=0; i<n; i++)
        result += earlier_lesser[i] * later_greater[i] + earlier_greater[i] * later_lesser[i];
    
    std::cout << result << std::endl;
    
    /*
    for(int i=0; i<n; i++)
        tree.point_update(arr[i], 1);
    std::cout << "print_all after point_update(s)" << std::endl;
    tree.print_all();
    
    tree.range_update(2, 5, 1);
    std::cout << "print_all after range_update" << std::endl;
    tree.print_all();
    
    std::cout << tree.range_query(2, 6) << std::endl;
    std::cout << "print_all after range_query" << std::endl;
    tree.print_all();
    
    for(int j=1; j<=8; j++)
        std::cout << tree.point_query(j) << " ";
    std::cout << std::endl;
    std::cout << "print_all after point_query('ies)" << std::endl;
    tree.print_all();
    */
   
    /*
    std::cout << "earlier_lesser:  ";
    for(auto t : earlier_lesser)
        std::cout << t << " ";
    std::cout << std::endl;
    std::cout << "earlier_greater: ";
    for(auto t : earlier_greater)
        std::cout << t << " ";
    std::cout << std::endl;
    std::cout << "later_lesser:    ";
    for(auto t : later_lesser)
        std::cout << t << " ";
    std::cout << std::endl;
    std::cout << "later_greater:   ";
    for(auto t : later_greater)
        std::cout << t << " ";
    std::cout << std::endl;
    */
   
    return 0;
}