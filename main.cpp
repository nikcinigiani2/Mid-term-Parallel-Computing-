#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h> // per la funzione crypt() su sistemi Unix/macOS

//carica il file di testo in memoria (nel ector)
std::vector<std::string> loadDictionary(const std::string& filename) {
    std::vector<std::string> dict;
    std::ifstream file(filename);
    std::string word;

    if (!file.is_open()) {
        std::cerr << "Errore: impossibile aprire il file " << filename << std::endl;
        return dict;
    }

    while (file >> word) {
        dict.push_back(word);
    }
    file.close();
    return dict;
}

// Funzione core per la ricerca sequenziale
// Restituisce la posizione (1-based) se trova la password, altrimenti -1
int checkPwd(const std::string& crypted_password, const std::string& salt, const std::vector<std::string>& passwordList) {
    int pos = 1;
    for (const auto& word : passwordList) {
        // Cifra la parola corrente usando l'algoritmo DES (tramite crypt)
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

int main() {
    std::cout << "--- Avvio DecryptionPassword (Sequenziale Baseline) ---" << std::endl;

    // 1. Carica il dizionario fittizio
    std::string dict_path = "../data/dummy_dict.txt"; // Aggiusta il path se necessario in CLion
    std::vector<std::string> passwordList = loadDictionary(dict_path);

    if (passwordList.empty()) {
        return 1; // Termina se il dizionario è vuoto o non trovato
    }
    std::cout << "Dizionario caricato con " << passwordList.size() << " password." << std::endl;

    // 2. Setup del test
    // Immaginiamo di voler cercare la password "password" il cui salt è "ab"
    std::string target_plain = "password";
    std::string salt = "ab";

    // Generiamo l'hash target direttamente per il test (in un caso reale questo ci viene fornito)
    std::string target_hash = crypt(target_plain.c_str(), salt.c_str());
    std::cout << "Target Hash generato (per '" << target_plain << "'): " << target_hash << std::endl;

    // 3. Esecuzione della ricerca
    std::cout << "Ricerca in corso..." << std::endl;
    int position = checkPwd(target_hash, salt, passwordList);

    // 4. Risultato
    if (position != -1) {
        std::cout << "SUCCESS! Password trovata alla riga: " << position << std::endl;
        std::cout << "La password in chiaro e': " << passwordList[position - 1] << std::endl;
    } else {
        std::cout << "FAILED! Password non trovata nel dizionario." << std::endl;
    }

    return 0;
}