#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

#define PERCENT 10

template <class T>
void checkValidStream(T &,string);
void addToFile(ofstream &,string,int &,int,bool &);

int main()
{
    string inFile,trainFile,validFile,testFile;
    vector<string> fileContents;

    cout << "Enter the name of the Input file: ";
    cin >> inFile;
    ifstream input(inFile);
    checkValidStream(input,inFile);


    cout << "Enter the name of the Training file: ";
    cin >> trainFile;
    ofstream outputTrain(trainFile);
    checkValidStream(outputTrain,trainFile);


    cout << "Enter the name of the Validation file: ";
    cin >> validFile;
    ofstream outputValid(validFile);
    checkValidStream(outputValid,validFile);


    cout << "Enter the name of the Test file: ";
    cin >> testFile;
    ofstream outputTest(testFile);
    checkValidStream(outputTest,testFile);

    string line;
    int lineCount=0;

    // Counts number of lines
    while(input)
    {
        std::getline(input,line);
        if(line.length() > 0)
        {
            fileContents.push_back(line);
            lineCount++;
        }
    }
    input.close();

    // Randomize the data
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,PERCENT-1);
    std::shuffle(fileContents.begin(),fileContents.end(),generator);

    // Number of data for Validation and Test sets
    int testNum = ( lineCount + PERCENT - 1 ) / PERCENT;
    int validNum = testNum;

    // Number of data for Train set
    int trainNum = lineCount - (validNum + testNum);

    // Count of number of data currently in each set
    int testCount=0, validCount=0, trainCount=0;

    // To randomize the data
    int randNum;
    bool added;

    for(auto iter : fileContents)
    {
        line = iter;

        // Skips blank lines
        if(line.length() == 0)
            continue;

        randNum = distribution(generator); // Picks a random number from 0-9
        added = false;

        switch(randNum)
        {
        // Training Dataset
        case 0 ... 7:
            addToFile(outputTrain,line,trainCount,trainNum,added);
            addToFile(outputTest,line,testCount,testNum,added);
            addToFile(outputValid,line,validCount,validNum,added);
            break;
        // Testing Dataset
        case 8:
            addToFile(outputTest,line,testCount,testNum,added);
            addToFile(outputValid,line,validCount,validNum,added);
            addToFile(outputTrain,line,trainCount,trainNum,added);
            break;
        // Validation Dataset
        case 9:
            addToFile(outputValid,line,validCount,validNum,added);
            addToFile(outputTrain,line,trainCount,trainNum,added);
            addToFile(outputTest,line,testCount,testNum,added);
            break;
        }
    }
    /*
    cout << trainCount << " " << trainNum << endl;
    cout << testCount << " " << testNum << endl;
    cout << validCount << " " << validNum << endl;
    */
    input.close();
    outputTest.close();
    outputValid.close();
    outputTrain.close();
}


template <class T>
void checkValidStream(T &stream, string fileName)
{
    if (!stream)
    {
        cerr << "Error: could not open " << fileName << "\n";
        exit(1);
    }
}


void addToFile(ofstream &stream, string line, int &curLines, int maxLines, bool &added)
{
    if(added == true)
        return;

    if(curLines != maxLines)
    {
        stream << line << endl;
        curLines++;
        added = true;
    }
    else
        added = false;
}
