#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>


typedef struct Population
{
    int population[100];
    int fitness[100];
} t_population;

typedef struct Data
{
    t_population joueur;
    t_population adv1;
    t_population adv2;
} t_data;

int change_random_most_significant_bit(int n)
{
    int temp;
    temp = n;
    temp = (temp >> 31) | rand() % 2;
    temp = (temp << 31);
    n = n | temp;
    return (n);
}
void    print_bits_two_by_two(int n)
{
    for (int i = 0; i < 32; i += 2)
    {
        printf("%d%d ", (n >> (31 - i)) & 1, (n >> (30 - i)) & 1);
    }
}

t_data   init_population()
{
    t_data Data;

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        Data.joueur.population[i] = change_random_most_significant_bit(rand());
        Data.adv1.population[i] = change_random_most_significant_bit(rand());
        Data.adv2.population[i] = change_random_most_significant_bit(rand());
    }
    return (Data);
}
void print_population(t_data *Data)
{
    for (int i = 0; i < 100; i++)
    {
        printf("\n");
        print_bits_two_by_two(Data->joueur.population[i]);
        printf("\n");
    }
}

void find_fitness(t_data *Data)
{
    for (int i = 0; i < 100; i++)
    {
        Data->joueur.fitness[i] = 0;
        Data->adv1.fitness[i] = 0;
        Data->adv2.fitness[i] = 0;
    }
}


int main()
{
    t_data Data = init_population();
    print_population(&Data);
    return 0;
}