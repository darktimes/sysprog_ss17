#include "../includes/Buffer.h"

#include <iostream>

using namespace std;

int main(void) {
    const char* filePath = "test.txt";
    
    //Test: READ ALL    
    cout << "TEST#1: READ ALL" <<endl;
    Buffer* testBuffer1 = new Buffer(filePath);
    char c;
    while(true)
    {   
        c = testBuffer1->getChar();
        if (c!='\0')
            cout << "Char at position " << testBuffer1->getCurrentPos()  - 1 << ": " << c << endl;
        else
            break;
    }
    cout << "EOF reached at position " << testBuffer1->getCurrentPos()  - 1 << endl;
    testBuffer1->~Buffer();
    
    //Test: GET-UNGET
    cout << "TEST#2: get-unget" <<endl;
    Buffer* testBuffer2 = new Buffer(filePath);
    int j = 0;
    while(j<3)
    {
        cout << "Char at position " << testBuffer2->getCurrentPos() - 1 << ": " << testBuffer2->getChar() << endl;
        j++;
    }
    
    printf("Unget on 2 \n");
    testBuffer2->ungetChar(2);
    j=0;
    while(j<3)
    {
        cout << "Char at position " << testBuffer2->getCurrentPos()  - 1 << ": " << testBuffer2->getChar() << endl;
        j++;
    }
    
    
}

