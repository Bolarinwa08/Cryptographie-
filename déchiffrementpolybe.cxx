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

  std::string polybiusDecrypt(const std::string& encryptedMessage, const std::string& keyword) {
    std::string grid = createSubstitutionGrid(keyword);
    std::string decryptedMessage = "";

    for (size_t i = 0; i < encryptedMessage.length(); i += 2) {
        if (std::isdigit(encryptedMessage[i]) && std::isdigit(encryptedMessage[i + 1])) {
            int row = encryptedMessage[i] - '0';
            int col = encryptedMessage[i + 1] - '0';
            int position = (row - 1) * 5 + (col - 1);
            
            if (position == 9) {
                decryptedMessage += "I";
            } else if (position < 9) {
                decryptedMessage += grid[position];
            } else {
                decryptedMessage += grid[position - 1];
            }
        } else {
            decryptedMessage += encryptedMessage.substr(i, 2);
        }
    }

    return decryptedMessage;
}

int main() {
    std::string keyword;
    std::string encryptedMessage;

    std::cout << "Enter the keyword: ";
    std::cin >> keyword;

    std::cout << "Enter the message to decrypt: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, encryptedMessage);

    std::string decryptedMessage = polybiusDecrypt(encryptedMessage, keyword);
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

    return 0;
}
