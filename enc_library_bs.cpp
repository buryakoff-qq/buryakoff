#include <iostream>
#include <fstream>
#include "enc_library_bs.hpp" 

using namespace std;

Decryptor::Decryptor(string arg1)
    {
        file_name = arg1;
        shift = 0;
    }

void Decryptor::character_count()
/**Count the ammount of each character in the text.
 *@author Y Buryakov
 *@param[in]
 *@return
 *@date 10.01.2021
 *@test test1.txt -> passed, succesfully counted the letters.
 *@test test2.txt -> passed, succesfully counted the letters.
 *@test test3.txt -> passed, succesfully counted the letters.
 *@test test4.txt -> passed, succesfully counted the letters.
 *@test test5.txt -> passed, succesfully counted the letters.
 */
    {
        char current_character;
        for (int i = 0; i < 26; i++)
        {
            letter[i] = 0; //Fill the array with zero to remove trash in the memory
        }
        ifstream encrypted(file_name);
        for (int count = 0; !encrypted.eof(); count++)
        {
        encrypted >> current_character;
        if (((int)current_character < 123) && ((int)current_character > 96))
        {
            letter[(int)current_character - 97]++;
        }
            else if(((int)current_character < 91) && ((int)current_character > 64))
            {
                letter[(int)current_character - 65]++;
            }
        }
        encrypted.close();
    }
int Decryptor::max_index()
/**Find the most common letter in the text
 *@author Y Buryakov
 *@param[in]
 *@return the most common letter
 *@date 10.01.2021
 *@test test1.txt - > passed, expexted to get d as a most common letter
 *@test test2.txt - > passed, expexted to get k as a most common letter
 *@test test3.txt - > passed, expexted to get k as a most common letter
 *@test test4.txt - > passed, expexted to get n as a most common letter
 *@test test5.txt - > passed, expexted to get j as a most common letter
 */
    {
        this->character_count();
        int val = 0, pos = 0;
        for (int i =0; i < 26; i++)
        {
            if ((letter[i]) > (val))
            {
                pos = i;
                val = letter[i];
            }

        }
        return pos + 97;
    }
void Decryptor::decrypt(char *character, int shift)
/**Function to decrypt the character
 *@author Y Buryakov
 *@param[in] character,shift, character that should be decrypted; shift, which will be used to decrypt the text
 *@return
 *@date 10.01.2021
 *@test decrypt(g , 0) --> passed. Expected output: g, actual output: g
 *@test decrypt(h , 1) --> passed. Expected output: g, actual output: g
 *@test decrypt(e , 3) --> passed. Expected output: b, actual output: b
 *@test decrypt(Z , 10) --> passed. Expected output: P, actual output: P
 *@test decrypt(A , 5) --> passed. Expected output: V, actual output: V
 */
    {
        if ((*character >= 'a') && (*character <= 'z'))
        {
            *character = ((*character - 97) - shift) % 26 + 97;
            if (*character < 97)
            {
                *character += 26;
            }
        }
        else if ((*character >= 'A') && (*character <= 'Z'))
        {
            *character = ((*character - 65) - shift) % 26 + 65;
            if (*character < 65)
            {
                *character += 26;
            }
        }
    }

int Decryptor::detect_shift()
/**Detects the  shift of encrypted file
 *@author Y Buryakov
 *@param[in]
 *@return the shift of the text
 *@date 10.01.2021
 *@test Tpnf fodszqufe ufyu --> passed. Detected shift 3
 *@test Yusk ktixevzkj zkdz --> passed. Detected shift 6
 *@test Bxvn nwlahycnm cngc --> passed. Detected shift 9
 *@test Fbzr rapelcgrq grkg --> passed. Detected shift 13
 *@test Tpnf fodszqufe ufyu --> passed. Detected shift 1
 */
    {
        int mcl = max_index();
        if ((mcl > 100) && (mcl < 123))
        {
            shift = mcl - 101;
        }
        else
        {
            shift = 26 + (mcl - 101);
        }
        return shift;
    }

void Decryptor::print_analysis_array()
/**Prints how often each letter comes across and prints the most common letter
 *@author Y Buryakov
 *@param[in]
 *@return
 *@date 10.01.2021
 *@test test1.txt -> passed, succesfully displayed the letters and the ammount of them in text and the most common letter.
 *@test test2.txt -> passed, succesfully displayed the letters and the ammount of them in text and the most common letter.
 *@test test3.txt -> passed, succesfully displayed the letters and the ammount of them in text and the most common letter.
 *@test test4.txt -> passed, succesfully displayed the letters and the ammount of them in text and the most common letter.
 *@test test5.txt -> passed, succesfully displayed the letters and the ammount of them in text and the most common letter.
 */
{
    cout << "\nLetter:\t\t" << "Ammount:\n" << endl;
    int cl = 0;
    for (int i = 0; i < 26; i++)
    {
        cout << "\t" << (char)(cl + 65) << "\t\t" << letter[i] << endl;
        cl++;
    }
    cout << "\nMost common character: " << (char)max_index() << endl;
    cout << "\nPress ENTER to continue..." << endl;
}

char to_upper(char character)
/**Transforms the lowercase letter to uppercase letter
 *@author Y Buryakov
 *@param[in] character , character which should be transformed
 *@return uppercase character
 *@date 10.01.2021
 *@test (k) --> passed, returned K
 *@test (g) --> passed, returned G
 *@test (u) --> passed, returned U
 *@test (i) --> passed, returned I
 *@test (o) --> passed, returned O
 */
{
    int result;
    if (((int)character > 96) && ((int)character < 123))
    {
        result = (int)character - 32;
        return (char)result;
    }
    else
    {
        cout << "ERROR! Character already uppercase" <<endl;
        return character;
    }
}

bool is_alpha(char character)
/**Checks if the character is letter
 *@author Y Buryakov
 *@param[in] character, character which should be checked by function
 *@return true if character is letter or false if not
 *@date 10.01.2021
 *@test (a) --> passed, returned true
 *@test (b) --> passed, returned true
 *@test (z) --> passed, returned true
 *@test (2) --> passed, returned false
 *@test (9) --> passed, returned false
 */
{
    if (((int)character < 91) && ((int)character > 64))
    {
        return true;
    }
    else if (((int)character < 123) && ((int)character > 96))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_upper(char character)
/**Checks if the letter upprecase
 *@author Y Buryakov
 *@param[in] character, character which should be checked by function
 *@return true if uppercase or false if not
 *@date 10.01.2021
 *@test (a) --> returned false
 *@test (z) --> returned false
 *@test (Z) --> returned true
 *@test (Z) --> returned true
 *@test (k) --> returned false
 */
{
    if (((int)character < 91) && ((int)character > 64))
    {
        return true;
    }
    else
    {
        return false;
    }
}
