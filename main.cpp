#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono> // Per i timer ad alta risoluzione
#include <unistd.h>
#include "decryptSequential.h"

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

int main() {
    std::cout << "--- Avvio DecryptionPassword (Benchmarking Sequenziale) ---" << std::endl;

    // 1. Caricamento del dataset pulito (Escluso dal timer delle performance)
    std::string dict_path = "data/rockyou_clean.txt";
    std::cout << "Caricamento dizionario in corso..." << std::endl;
    std::vector<std::string> passwordList = loadDictionary(dict_path);

    if (passwordList.empty()) {
        return 1;
    }
    std::cout << "Dizionario caricato con " << passwordList.size() << " password." << std::endl;

    // 2. Setup del target di test
    // Prendiamo una password situata a metà del dataset per avere un tempo di ricerca significativo
    int target_index = passwordList.size() / 2;
    std::string target_plain = passwordList[target_index];
    std::string salt = "ab";
    std::string target_hash = crypt(target_plain.c_str(), salt.c_str());

    std::cout << "Target Hash generato (per la password all'indice " << target_index << "): " << target_hash << std::endl;

    // 3. Esecuzione e Misurazione del Tempo
    std::cout << "Ricerca sequenziale in corso..." << std::endl;

    // Inizio timer
    auto start_time = std::chrono::high_resolution_clock::now();

    int position = checkPwdSequential(target_hash, salt, passwordList);

    // Fine timer
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> execution_time = end_time - start_time;

    // 4. Stampa dei Risultati
    if (position != -1) {
        std::cout << "\nSUCCESS! Password trovata alla riga: " << position << std::endl;
        std::cout << "La password in chiaro e': " << passwordList[position - 1] << std::endl;
    } else {
        std::cout << "\nFAILED! Password non trovata." << std::endl;
    }

    std::cout << "Tempo di esecuzione sequenziale: " << execution_time.count() << " secondi." << std::endl;

    return 0;
}