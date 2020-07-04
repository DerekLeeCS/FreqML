#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#define PERCENT 10

template <class T>
void checkValidStream(T &,string);

int main()
{
    string inFile,trainFile,validFile,testFile;

    cout << "Enter the name of the Input file: ";
    cin >> inFile;
    std::ifstream input(inFile);
    checkValidStream(input,inFile);


    cout << "Enter the name of the Training file: ";
    cin >> trainFile;
    std::ofstream outputTrain(trainFile);
    checkValidStream(outputTrain,trainFile);


    cout << "Enter the name of the Validation file: ";
    cin >> validFile;
    std::ofstream outputValid(validFile);
    checkValidStream(outputValid,validFile);


    cout << "Enter the name of the Test file: ";
    cin >> testFile;
    std::ofstream outputTest(testFile);
    checkValidStream(outputTest,testFile);

    string line;
    int lineCount=0;

    while(input)
    {
        std::getline(input,line);
        lineCount++;
    }
    input.clear();
    input.seekg(0, std::iostream::beg);

    // Number of data for Validation and Test sets
    int testNum = ( lineCount + PERCENT - 1 ) / PERCENT;
    int validNum = testNum;

    // Number of data for Train set
    int trainNum = lineCount - (validNum + trainNum);

    // Count of number of data currently in each set
    int testCount=0, validCount=0;

    while(input)
    {
        std::getline(input,line);

        if(testCount != testNum)
        {
            outputTest << line << endl;
            testCount++;
        }
        else if(validCount != validNum)
        {
            outputValid << line << endl;
            validCount++;
        }
        else
            outputTrain << line << endl;

    }
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
