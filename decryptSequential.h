#ifndef DECRYPT_SEQUENTIAL_H
#define DECRYPT_SEQUENTIAL_H

#include <vector>
#include <string>

// Funzione core per la ricerca sequenziale
int checkPwdSequential(const std::string& crypted_password, const std::string& salt, const std::vector<std::string>& passwordList);

#endif