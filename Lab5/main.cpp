#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "Profit.h"
#include "KWP.h"
#include "KYP.h"
using namespace std;

void readin(const char*, Profit*, float&);
void clearOutputFile();
char readinOption();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Follow this format: ./Lab5_3973887764 input.txt." << endl;
    } else {
        int z;
        cout << "Please enter the number of weeks (Integer between 0 and 52): ";
        cin >> z;
        if (z == 0) {
            cout << "KW's profit for 0 number of weeks in average is estimated" << 
                "$0.00, out of which 10%, i.e., $0.00 is KY's. " << endl;
            return 0;
        }
        // Read in input.txt file
        Profit first_three_week[3];
        float U;
        readin(argv[1], first_three_week, U);
        clearOutputFile();
        KWP kanye(first_three_week, z);
        //
        char option = readinOption();
        //cout << option << endl;
        
        // Calculate Kanye's profit
        Profit kanyeProfit;
        kanyeProfit.dollar = kanye.calAvgProfit(option);
        kanyeProfit.duration = z;
        kanye.setProfit(kanyeProfit);
        // Calculate K.. Y..'s Profit
        KYP ky;
        Profit kyProfit;
        kyProfit.dollar = kanye.getProfit().dollar * U / 100;
        kyProfit.duration = z;
        ky.setProfit(kyProfit);
        // Print on screen
        cout << "KW's profit for " << z << 
            " number of weeks in average is estimated $" << 
            kanye.getProfit().dollar << ", out of which " <<
            U << "%, i.e., $" << ky.getProfit().dollar << " is KY's. " << endl;
    }
}


void readin(const char* filename, Profit* weeks, float& U) {
    ifstream input;
    input.open(filename);
    string line;
    int counter = 0;
    while (getline(input, line)) {
        if (line.rfind("//") != 0 && !line.empty()) {
            stringstream ss(line);
            if(counter < 3) {
                ss >> weeks[counter].duration >> weeks[counter].dollar;
                counter++;
            } else {
                ss >> U;
            } 
        }
    }
    input.close();
}
 
void clearOutputFile() {
    ofstream out("output.txt");
    out.clear();
    out.close();
}

char readinOption() {
    cout << "To solve it recursively, press R. To solve it iteratively, Press I: ";
    string option;
    cin >> option;
    
    while(option.length() != 1) {
        cout << "Only 'Y' and 'R' are acceptable. Please retry: ";
        cin >> option;
    }
    
    while(option != "R" && option != "r" && option != "I" && option != "i") {
        cout << "Only 'Y' and 'R' are acceptable. Please retry: ";
        cin >> option;
    }
    
    if (option == "R" || option == "r") {
        return 'R';
    } else {
        return 'I';
    }
}

