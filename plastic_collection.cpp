//  plastic_collection.cpp
//  Input format:
//  1) height and width of the rectangular area of the ocean,
//  2) two-dimensional array of volumes that float through the particular point,
//  3) two-dimensional array of cost to instantiate the garbage collector at the particular point.

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

#define pb push_back
#define sz(a) (int)a.size()

const int inf = (int)1e9;

const int GEN = 100, N = 20, TOUR_SIZE = 5, MAX_COST = 250, BITS = 100;

int h, w, VOLUME[100][100], COST[100][100];
vector<bitset<100> > population;

bitset<100> select(){
    int min_volume = -inf;
    bitset<100> fittest;
    for(int i = 0; i < TOUR_SIZE; ++i){
        int rnd = rand() % sz(population);
        bitset<100> cur = population[rnd];
        
        string str = cur.to_string<char,std::string::traits_type,std::string::allocator_type>();
        
        int cost = 0, volume = 0;
        
        for(int j = 0; j < sz(str); ++j){
            cost += (str[j] - '0') * COST[j / 10][j % 10];
            volume += (str[j] - '0') * VOLUME[j / 10][j % 10];
        }
        
        if(volume > min_volume && cost < MAX_COST){
            min_volume = volume;
            fittest = cur;
        }
    }
    return fittest;
}

void evolvePopulation(){
    vector<bitset<100> > new_population;
    for(int i = 0; i < N; ++i){
        bitset<100> parent1 = select();
        bitset<100> parent2 = select();
        
        bitset<100> child;
        int rnd = rand() % BITS;
        
        for(int j = 0; j < BITS; ++j){
            if(j < rnd){
                child[j] = parent1[j];
            }else{
                child[j] = parent2[j];
            }
        }
        
        new_population.pb(child);
    }
    
    for(int i = 0; i < sz(new_population); ++i){
        int rnd = rand() % BITS;
        new_population[i].flip(rnd);
    }
    population = new_population;
}

bitset<100> calculateFittest(){
    int min_volume = -inf;
    bitset<100> fittest;
    for(int i = 0; i < sz(population); ++i){
        
        bitset<100> cur = population[i];
        
        string str = cur.to_string<char,std::string::traits_type,std::string::allocator_type>();
        
        int cost = 0, volume = 0;
        
        for(int j = 0; j < sz(str); ++j){
            cost += (str[j] - '0') * COST[j / 10][j % 10];
            volume += (str[j] - '0') * VOLUME[j / 10][j % 10];
        }
        
        if(volume > min_volume && cost < MAX_COST){
            min_volume = volume;
            fittest = cur;
        }
        
    }
    return fittest;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand (time(NULL));
    freopen("in", "r", stdin);
    int total_volume = 0, total_cost = 0;
    cin >> h >> w;
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            cin >> VOLUME[i][j];
            total_volume += VOLUME[i][j];
        }
    }
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            cin >> COST[i][j];
            total_cost += COST[i][j];
        }
    }
    
    cout << "Initial cost: " << total_cost << ", initial volume: " << total_volume << "\n";
    
    bitset<100> b;
    b.reset();
    population.pb(b);
    population.pb(b.flip());
    b.flip();
    for(int i = 0; i < N; ++i){
        int rnd = rand() % (BITS);
        population.pb(b.flip(rnd));
    }
    for(int i = 0; i < GEN; ++i){
        evolvePopulation();
    }
    
    bitset<100> fittest = calculateFittest();
    int cost = 0, volume = 0;
    for(int j = 0; j < BITS; ++j){
        cost += (fittest.test(j)) * COST[j / 10][j % 10];
        volume += (fittest.test(j)) * VOLUME[j / 10][j % 10];
    }
    cout << "Best cost: " << cost << ", best volume: " << volume << "\n";
    
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            cout << ((fittest[i * 10 + j] == 1) ? "o" : "x");
        }
        cout << "\n";
    }
    return 0;
}

