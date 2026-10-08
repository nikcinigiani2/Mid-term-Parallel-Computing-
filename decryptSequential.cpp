#include "decryptSequential.h"
#include <unistd.h> 

int checkPwdSequential(const std::string& crypted_password, const std::string& salt, const std::vector<std::string>& passwordList) {
    int pos = 1;
    for (const auto& word : passwordList) {
        // Cifra la parola corrente usando l'algoritmo DES
        char* hashed_word_ptr = crypt(word.c_str(), salt.c_str());

        if (hashed_word_ptr != nullptr) {
            std::string hashed_word(hashed_word_ptr);

            // Se l'hash coincide con quello cercato, esci dal ciclo (early termination)
            if (hashed_word == crypted_password) {
                return pos;
            }
        }
        pos++;
    }
    return -1; // Password non trovata
}