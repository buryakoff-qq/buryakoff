#ifndef enc_library_bs
#define enc_library_bs

using namespace std;
class Decryptor
{
private:
public:
    string file_name;
    int letter[26];
    int shift;
    Decryptor(string arg1);
    void character_count();
    int max_index();
    void decrypt(char* character, int shift);
    int detect_shift();
    void print_analysis_array();
};
bool isAlpha(char character);
bool is_upper(char character);
char to_upper(char character);

#endif
