#include <iostream>
#include <cctype>
#include <algorithm>

// Fonction pour créer la grille de substitution en utilisant le mot-clé
std::string createSubstitutionGrid(const std::string& keyword) {
    // L'alphabet de base (sans 'J' qui est combiné avec 'I')
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::string grid = keyword;

    // Supprime les lettres du mot-clé de l'alphabet
    for (char letter : keyword) {
        alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), letter), alphabet.end());
    }

    // Ajoute le reste de l'alphabet dans l'ordre alphabétique
    grid += alphabet;

    return grid;
}

// Fonction pour chiffrer un message en utilisant le chiffre de Polybe
std::string polybiusEncrypt(const std::string& message, const std::string& keyword) {
    // Crée la grille de substitution en utilisant le mot-clé
    std::string grid = createSubstitutionGrid(keyword);
    std::string encryptedMessage = "";

    for (char letter : message) {
        if (std::isalpha(letter)) {
            letter = std::toupper(letter);

            // Remplace 'J' par les coordonnées de 'I'
            if (letter == 'J') {
                encryptedMessage += "24";
            } else {
                // Trouve la position de la lettre dans la grille et calcule les coordonnées
                int position = grid.find(letter) + 1;
                int row = position / 5 + 1;
                int col = position % 5 + 1;
                encryptedMessage += std::to_string(row) + std::to_string(col);
            }
        } else {
            // Conserve les caractères non alphabétiques inchangés
            encryptedMessage += letter;
        }
    }

    return encryptedMessage;
}

int main() {
    std::string keyword;
    std::string message;

    // Saisie du mot-clé
    std::cout << "Entrez le mot-clé : ";
    std::cin >> keyword;

    // Saisie du message à chiffrer
    std::cout << "Entrez le message à chiffrer : ";
    std::cin.ignore(); // Vide le tampon d'entrée
    std::getline(std::cin, message);

    // Chiffre le message en utilisant le chiffre de Polybe
    std::string encryptedMessage = polybiusEncrypt(message, keyword);
    std::cout << "Message chiffré : " << encryptedMessage << std::endl;

    return 0;
}
