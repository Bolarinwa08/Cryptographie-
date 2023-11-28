#include <iostream>
#include <cctype>
#include <algorithm>

std::string createSubstitutionGrid(const std::string& keyword) {
     std::string alphabet =
     "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::string grid = keyword;

    // Supprime les lettres du mot-clé de l'alphabet
    for (char letter : keyword) {
        alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), letter), alphabet.end());
    }

    // Ajoute le reste de l'alphabet dans l'ordre alphabétique
    grid += alphabet;

    return grid;
}

std::string polybiusEncrypt(const std::string& message, const std::string& keyword) {
    std::string grid = createSubstitutionGrid(keyword);
    std::string encryptedMessage = "";

    for (char letter : message) {
        if (std::isalpha(letter)) {
            letter = std::toupper(letter);
            if (letter == 'J') {
                encryptedMessage += "24";  // J est remplacé par les coordonnées de I
            } else {
                int position = grid.find(letter) + 1;
                int row = position / 5 + 1;
                int col = position % 5 + 1;
                encryptedMessage += std::to_string(row) + std::to_string(col);
            }
        } else {
            encryptedMessage += letter;
        }
    }

    return encryptedMessage;
}

int main() {
    std::string keyword;
    std::string message;

    std::cout << "Enter the keyword: ";
    std::cin >> keyword;

    std::cout << "Enter the message to encrypt: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, message);

    std::string encryptedMessage = polybiusEncrypt(message, keyword);
    std::cout << "Encrypted Message: " << encryptedMessage << std::endl;

    return 0;
}
