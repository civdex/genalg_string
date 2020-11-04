// SUMMARY 



/*
ALGORITHM SUMMARIZED: 

1) Randomly initialize populations p (in our ex - num_strings?)

2) Determine fitness of population \
    (calculate fitness and rank them - midterm lowest fitness)

3) Untill convergence repeat:
      a) Select parents from population \
        (in our ex single strings, in their ex i guess we'll see)
      b) Crossover and generate new population \
        (in our ex, replacing strings so that the E gets lower...? )
      c) Perform mutation on new population \
        (when gene of child is changed randomly - where random_num comes in?)
      d) Calculate fitness for new population
*/

/*
Operators of Genetic Algorithms

1) Selection operator - the idea is to give preference to the indivdiuals with good fitness
scores and allow them to passs their genes on 

2) Crossover operator - represents mating between individuals. Two individuals are selected 
using the SELECTION OPERATOR and corssover sites are chosen randomly. Then the genes at the 
crossover sites are exchanged, thus creating a completely new individual. 

3) Mutation operator - insert random genes in offspring to maintain diversity in population 
to avoid the premature convergence.  
*/

#include <iostream>
#include <vector>
#include <algorithm>


typedef std::string string; 

// number of individuals in each generation 
#define POPULATION_SIZE 100

// valid genes
const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP"\ 
"QRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}"; 

// target string to be generated 
const string TARGET = "This is a test"; 

// function to generate random numbers in a given range 
int random_num(int start, int end) 
{ 
    int range = (end-start)+1; 
    int random_int = start+(rand()%range); 
    return random_int; 
} 

// create random genes for mutation (random char from GENES)
char mutated_genes() 
{ 
    int len = GENES.size(); 
    int r = random_num(0, len-1); 
    return GENES[r]; 
} 

// create chromosome or string of genes 
string create_gnome() 
{ 
    // init output string 
    string gnome = ""; 

    // iterate through the target length of chromo
    for(int i = 0; i < TARGET.size(); i++) 
        gnome += mutated_genes(); 

    return gnome;  // ex: WpVt)AUj;8Jw7[=Cq eD
} 

// class representing individual in population - string of chars in this ex
class Individual 
{ 
public:
    // members
    string chromosome; 
    int fitness;

    // methods 
    Individual(string chromosome); 
    Individual mate(Individual parent2); 
    int cal_fitness(); 
}; 

// constructor definition
Individual::Individual(string chromosome)
{
    this->chromosome = chromosome; 
    fitness = cal_fitness(); 
}

// mate function (ie: crossover) - to produce offspring 
Individual Individual::mate(Individual parent2)
{
    // init offspring chromo
    string child_chromosome = ""; 
    
    // iterate through length of parent chromosome
    for(int i = 0; i < chromosome.size(); i++)
    {
        // random prob
        float p = random_num(0, 100) / 100; 

        // if prob is less than 0.45, insert gene from 
        // parent 1 
        if (p < 0.45)
            child_chromosome += chromosome[i]; 

        // if prob is between 0.45 and 0.90, insert 
        // gene from parent 2 
        else if (p < 0.9)
            child_chromosome += parent2.chromosome[i]; 

        // o/w insert random gene (mutated gene)
        else
            child_chromosome += mutated_genes();    
    }
    return Individual(child_chromosome); 
}

// fitnesss = number of chars in string which differ from target
// 0 is best, target string size = worst 
int Individual::cal_fitness()
{
    int fitness = 0; 

    // iterate through length of target 
    for (int i = 0; i < TARGET.size(); i++)
    {
        if(chromosome[i] != TARGET[i])
            fitness++; 
    }
    return fitness;
}

// Overloading < operator 
bool operator<(const Individual &ind1, const Individual &ind2) 
{ 
    return ind1.fitness < ind2.fitness; 
} 

// driver code 
int main() 
{
    srand((unsigned)(time(0)));

    // current generation 
    int generation = 0; 
    std::vector<Individual> population; 
    bool found_solution = false; 

    // create initial population 
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        string gnome = create_gnome(); 
        population.push_back(Individual(gnome)); 
    }

    while(! found_solution)
    {
        // sort the population in increasing order of fitness
        std::sort(population.begin(), population.end()); 

        // if individual having lowest fitness score ie: element 0, 
        //then we have reached targetand we can stop looping
        if (population[0].fitness <= 0)
        {
            found_solution = true; 
            break; 
        }

        // o/w generate new offspring for new gen
        std::vector<Individual> new_generation; 

        // perform elitism - means 10% of fittest pop goes to next gen
        int size_elite = (10 * POPULATION_SIZE) / 100; 
        for (int i = 0; i < size_elite; i++)
            new_generation.push_back(population[i]);
        
        // 50% of fittest population, individuals will mate/crossover 
        // to product offspring 
        int size_crossover = (90 * POPULATION_SIZE) / 100; 
        for (int i = 0; i < size_crossover; i++)
        {
            int half_population_size = 0.5 * POPULATION_SIZE; 
            
            // get random chromosome (individual) from fittest 50 in p1
            int r = random_num(0, half_population_size); 
            Individual parent1 = population[r]; 

            // get random chromosome (individual) from fittest 50 in p2
            r = random_num(0, half_population_size);
            Individual parent2 = population[r]; 
            
            // crossover
            Individual offspring = parent1.mate(parent2); 
            new_generation.push_back(offspring); 
        }
        population = new_generation; 
        std::cout << "Generation: " << generation << "\t"; 
        std::cout << "Fittest string/individual: " << population[0].chromosome << "\t"; 
        std::cout << "Fitness: " << population[0].fitness << "\n";
        generation++; 
    }
    std::cout << "Generation: " << generation << "\t"; 
    std::cout << "Fittest string/individual: " << population[0].chromosome << "\t"; 
    std::cout << "Fitness: " << population[0].fitness << "\n";
    return 0; 
}
