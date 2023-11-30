#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Global variables:
std::vector<int> available;
std::vector<std::vector<int>> allocation;
std::vector<std::vector<int>> max;

//Reads in the data from an input file
//REQUIRES: Data must be in the order: allocation, max, and available, with spaces or newline character between each
//          System must have 5 processes with 3 resources each
void readData(std::string fileName) {
    std::vector<int> allData; //to store all the numbers from the input file into
    std::string dataFile = fileName;
    std::ifstream input;
    input.open(dataFile); //open the file who's name was input by the user

    if (input.is_open()) {
        std::cout << "Successful file open" << std::endl;

        int temp;
        while(input >> temp) { //reads in one integer token at a time (numbers separated by space or newline character)
            allData.push_back(temp); //put all the numbers in order into one vector
        }

        input.close();
        std::cout << "Successful file close" << std::endl;
    }
    else { //if file did not open, tell the user and exit the program
        std::cout << "Could not open file" << std::endl;
        exit(1);
    }

    for (int i = 0; i < 15; ++i) { //first 15 numbers of the file will go into the allocation vector
        if (i % 3 == 0 && i != 0) { //checks if 3 numbers are in available
            allocation.push_back(available); //adds these 3 numbers to the back of the allocation vector
            available.clear(); //clear the temporary holding vector to start again
        }
        available.push_back(allData[i]); //temporarily load one number at a time into available vector
    }
    allocation.push_back(available); //last 3 numbers held in available need to be added to the back of allocation
    available.clear(); //clear available to use it for more computations below

    for (int i = 15; i < 33; ++i) { //rest of the numbers (16-33) will be loaded into the max and available vectors
        if (i % 3 == 0 && i != 15) { //checks if 3 numbers are in available
            max.push_back(available); //adds these 3 numbers to the back of max vector
            available.clear(); //clear the temporary holding vector to start again
        }
        available.push_back(allData[i]); //temporarily load one number at a time into available vector,
    }                                    //but the last 3 numbers added into the available vector stay there,
}                                        //as these are what's actually supposed to be held in the available vector

//Function that checks whether the system is safe, and prints the safe sequence if it is
//"safety algorithm" is referring to slide 7.47 in the "Deadlocks" slides on Canvas
void safeChecker() {
    int processes = max.size(); //number of processes
    int resources = available.size(); //number of resources

    std::vector<std::vector<int>> need(processes, std::vector<int>(resources, 0)); //initialize need full of zeroes
    std::vector<int> work(available); //copy constructor copying available into work (safety algorithm step 1a)
    std::vector<bool> finish(processes, false); //initialize everything in finish to false (safety algorithm steb 1b)
    std::vector<int> safeSequence; //empty vector we will add safe sequence into later

    for (int i = 0; i < processes; ++i) { //looping through need vector
        for (int j = 0; j < resources; ++j) {
            need[i][j] = max[i][j] - allocation[i][j]; //need = max - allocation
        }
    }

    int safeCount = 0; //number of safe processes found
    while(safeCount < processes) {
        bool foundSafe = false;
        for (int i = 0; i < processes; ++i) {
            if (finish[i] == false) { //checking that finish[i] is false (step 2a of safety algorithm)
                int j;
                for (j = 0; j < resources; ++j) {
                    if (need[i][j] > work[j]) break; //will loop all the way through if need is never more than work
                }
                //true to if statement below goes to step 3 of safety algorithm, false skips step 3 and goes to step 4
                if (j == resources) { //checking to make sure that need is <= work (step 2b of safety algorithm)
                    for (int k = 0; k < resources; ++k) {
                        work[k] = work[k] + allocation[i][k]; //step 3a of safety algorithm
                    }
                    finish[i] = true; //step 3b of safety algorithm
                    foundSafe = true; //to show that we found a next process in the safe sequence
                    safeSequence.push_back(i); //add process to safe sequence
                    ++safeCount; //increase number of safe processes found
                }
            }
        }
        if (foundSafe == false) { //if next safe process cannot be found
            std::cout << "System is not in safe state" << std::endl;
        }
    }
    //program is in safe state (step 4 in safety algorithm: finish[i] == true for all i)
    std::cout << "System is in safe state" << std::endl;
    std::cout << "The safe sequence is: ";
    for (int i = 0; i < processes; ++i) {
        std::cout << 'P' << safeSequence[i] << ' ';
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Enter file name to read from: ";
    std::string file;
    std::cin >> file;
    readData(file); //calls function above to read data from file
    safeChecker(); //calls function above to check if system is safe or not and print safe sequence
    return 0;
}
