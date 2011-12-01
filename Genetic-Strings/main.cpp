// Pseudo-Genetic Algorithm (End-Goal Directed)
// Uses a Pseudo-Genetic Algorithm to match a target number from an initial population of random numbers

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// Evaluates similarity of numbers on digit by digit basis; lower is better
int evalNumSimilarity(vector <int> testNum, vector <int> targetNum)
{
    int difference = 0;

    // Return error if vectors aren't same size
    if (testNum.size() != targetNum.size()) return -1;

    // Find number of digits that are different
    for (unsigned int i = 0; i < testNum.size(); i++)
    {
        if (!(testNum[i] == targetNum[i])) difference++;
    }

    return difference;
}

void writeVector(vector <int> inpVector)
{
    for (unsigned int i = 0; i < inpVector.size(); i++)
    {
        cout << inpVector[i];
    }
}

int main()
{
    // Get the final target number
    string inpString;
    vector <int> targetNum;
    while(!(atoi(inpString.c_str())))
    {
        cout << "Enter a target number:" << endl;
        getline(cin, inpString);
    }

    // Convert to array of digits
    const int ASCII_CONVERT = 48;
    for (unsigned int i = 0; i < inpString.length(); i++)
    {
        targetNum.push_back(0);
        targetNum[i] = inpString[i] - ASCII_CONVERT;
    }



    // Initialize a population of random strings
    const int POP_SIZE = 100;
    vector < vector <int> > population(POP_SIZE);

    for (int i = 0; i < POP_SIZE; i++)
    {
        population[i].resize(inpString.length());
        for (unsigned int j = 0; j < inpString.length(); j++)
        {

            population[i][j] = rand() % 10;

            cout << endl;
        }
    }

    // Loop flag
    bool flag = false;

    // Loop through population, selectively breeding
    for (int generation = 0; flag != true; generation++)
    {
        const int MATES_CHOSEN = 5;
        vector <int> randNum(MATES_CHOSEN);
        for (int i = 0; i < MATES_CHOSEN; i++)
        {
            randNum[i] = rand() % POP_SIZE;
            cout << "Parent Chosen: " << randNum[i] << endl;
        }

        int worstParent = 0;
        vector <int> bestOffspring;
        bestOffspring.resize(targetNum.size());
        // It's possible for randNum[1] == randNum[2] == randNum[3], but whatever

        // Interbreed all chosen and select best offspring to replace worst parent
        // In a true genetic algorithm, there's no end result to compare to
        for (int i = 0; i < MATES_CHOSEN; i++)
        {

                // Keep track of worst parent found so far
                if (evalNumSimilarity(population[randNum[i]], targetNum) > evalNumSimilarity(population[worstParent], targetNum)) worstParent = randNum[i];

                for (int j = 0; j < MATES_CHOSEN; j++)
                {
                    // Don't self breed
                    if (i != j)
                    {
                        // Breed a new offspring by random combination of parents; default copy one parent with overwrite of other
                        vector <int> offspring;
                        offspring.resize(targetNum.size());

                        for (unsigned int k = 0; k < offspring.size(); k++)
                        {
                            int overwriteChance = rand();
                            // 50/50 chance of overwrite
                            if (overwriteChance % 100 < 49)
                            {
                                offspring[k] = population[randNum[i]][k];
                            }
                            else if (overwriteChance % 100 < 98)
                            {
                                offspring[k] = population[randNum[j]][k];
                            }
                            else
                            {
                                offspring[k] = rand() % 10;
                            }
                        }

                        if (evalNumSimilarity(offspring, targetNum) < evalNumSimilarity(bestOffspring, targetNum) && evalNumSimilarity(bestOffspring, targetNum) != -1) bestOffspring = offspring;
                    }

                }
        }

        // Replace worst parent with best offspring
        population[worstParent] = bestOffspring;

        // Output
        system("cls");

        cout << "Current Generation: " << generation << endl;
        cout << "Target Number: ";
        writeVector(targetNum);
        cout << endl;
        cout << "Currnt Offspr: ";
        writeVector(bestOffspring);
        cout << endl;
        cout << "Current Score: " << evalNumSimilarity(bestOffspring, targetNum) << endl;

        if (evalNumSimilarity(bestOffspring, targetNum) == 0)
        {
            cout << "Match Created!";
            break;
        }


    }

    return 0;
}
