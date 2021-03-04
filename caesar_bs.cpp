#include <iostream>
#include <fstream>
#include <stdio.h>
#include "enc_library_bs.hpp"
using namespace std;



int main(int argc,const char *argv[])
{
    Decryptor Decr(argv[1]);
    cout << endl << "Name of encrypted file: " << argv[1] << endl;
    Decr.detect_shift();
    Decr.print_analysis_array();
    cin.get();
    cout << "Suggested shift: " << Decr.shift << endl << "\nThat how the text will looks like if you continiue with suggested shift:\n" << endl << "---------------------------------------------------------- \n";
    ifstream encrypted(argv[1]);
    char buff[50];
    for (int i = 0; i < 50; i++)
    {
        buff[i] = 0;
    }
    encrypted.getline(buff, 50);
    encrypted.close();
    for (int i = 0; i < 50; i++)
    {
        Decr.decrypt(&buff[i], Decr.shift);
        cout << buff[i];
    }
    cout << endl << "---------------------------------------------------------- " << endl;
    cout << endl << "Type 0 to continue with estimated shift or enter shift mannualy from 1-26: " << endl;
        int input = 0;
        cin >> input;
        if (input == 0)
        {
            cout << "Starting decryption with shift " << Decr.shift << endl;
            FILE * encrypted = fopen(argv[1], "r");
            FILE * decrypted = fopen(argv[2], "w");
            char temp = '\0';
            for (int i = 0; fscanf(encrypted, "%c", &temp) != EOF; i++)
            {
                Decr.decrypt(&temp, Decr.shift);
                fprintf(decrypted, "%c", temp);
            }
            fclose(encrypted);
            fclose(decrypted);
            cout << "\nFile was succesfully decrypted and saved as " << argv[2] << endl;
        }
        else if ((input >= 1) && (input <=26))
        {
            Decr.shift = input;
            cout << "Starting decryption with shift " << Decr.shift << endl;
            FILE * encrypted = fopen(argv[1], "r");
            FILE * decrypted = fopen(argv[2], "w");
            char temp = '\0';
            for (int i = 0; fscanf(encrypted, "%c", &temp) != EOF; i++)
            {
                Decr.decrypt(&temp, Decr.shift);
                fprintf(decrypted, "%c", temp);
            }
            fclose(encrypted);
            fclose(decrypted);
            cout << "\nFile was succesfully decrypted and saved as " << argv[2] << endl;
        }
        else
        {
            cout << "Error! Shift should be in range from 1 to 26 only." << endl << "Terminating the program..." << endl;
            return 0;
        }
    return 0;
}
