#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

// Controlla se la password è lunga 8 caratteri e contiene solo i caratteri consentiti
bool isValidPassword(const std::string& pwd) {
    if (pwd.length() != 8) return false;

    // Alfabeto consentito: [a-zA-Z0-9./]
    const std::string valid_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

    // find_first_not_of restituisce std::string::npos se tutti i caratteri sono validi
    return pwd.find_first_not_of(valid_chars) == std::string::npos;
}

int main() {
    std::string input_file = "data/RockYou.txt";       // Il dataset originale scaricato
    std::string output_file = "data/rockyou_clean.txt"; // Il dataset pronto per i test

    std::ifstream infile(input_file);
    if (!infile.is_open()) {
        std::cerr << "Errore: impossibile aprire " << input_file << "\nScarica il file e mettilo nella cartella data/" << std::endl;
        return 1;
    }

    std::unordered_set<std::string> unique_passwords;
    std::string line;

    std::cout << "Inizio lettura e sanitizzazione di " << input_file << "..." << std::endl;

    while (std::getline(infile, line)) {
        // Rimuove eventuali carriage return (utile se il file ha terminatori di riga Windows \r\n)
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Validazione e Deduplicazione
        if (isValidPassword(line)) {
            unique_passwords.insert(line);
        }
    }
    infile.close();

    std::cout << "Filtraggio completato. Trovate " << unique_passwords.size() << " password valide e univoche." << std::endl;

    // Scrittura sul nuovo file
    std::ofstream outfile(output_file);
    if (!outfile.is_open()) {
        std::cerr << "Errore: impossibile creare " << output_file << std::endl;
        return 1;
    }

    for (const auto& pwd : unique_passwords) {
        outfile << pwd << "\n";
    }
    outfile.close();

    std::cout << "File pulito salvato in: " << output_file << std::endl;
    return 0;
}