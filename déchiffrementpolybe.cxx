#include <iostream>
#include <cctype>
#include <algorithm>

// Fonction pour créer une grille de substitution basée sur le mot-clé fourni
std::string createSubstitutionGrid(const std::string& keyword) {
    // Définir l'alphabet complet en excluant 'J'
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::string grid = keyword;

    // Supprimer les lettres du mot-clé dans l'alphabet
    for (char letter : keyword) {
        alphabet.erase(std::remove(alphabet.begin(), alphabet.end(), letter), alphabet.end());
    }

    // Ajouter le reste de l'alphabet au mot-clé dans l'ordre alphabétique
    grid += alphabet;

    return grid;
}

// Fonction pour décrypter un message chiffré avec le carré de Polybe en utilisant un mot-clé
std::string polybiusDecrypt(const std::string& encryptedMessage, const std::string& keyword) {
    // Créer une grille de substitution basée sur le mot-clé fourni
    std::string grid = createSubstitutionGrid(keyword);
    std::string decryptedMessage = "";

    // Parcourir le message chiffré deux caractères à la fois
    for (size_t i = 0; i < encryptedMessage.length(); i += 2) {
        // Vérifier si les caractères représentent une coordonnée valide du carré de Polybe
        if (std::isdigit(encryptedMessage[i]) && std::isdigit(encryptedMessage[i + 1])) {
            int row = encryptedMessage[i] - '0';
            int col = encryptedMessage[i + 1] - '0';

            // Calculer la position dans la grille de substitution
            int position = (row - 1) * 5 + (col - 1);

            // Gérer le cas spécial de la lettre 'I'
            if (position == 9) {
                decryptedMessage += "I";
            } else if (position < 9) {
                decryptedMessage += grid[position];
            } else {
                decryptedMessage += grid[position - 1];
            }
        } else {
            // Ajouter les caractères inchangés s'ils ne représentent pas une coordonnée valide
            decryptedMessage += encryptedMessage.substr(i, 2);
        }
    }

    return decryptedMessage;
}

// Fonction principale pour la saisie de l'utilisateur et l'appel de la fonction de décryptage
int main() {
    std::string keyword;
    std::string encryptedMessage;

    // Obtenir le mot-clé de l'utilisateur
    std::cout << "Entrez le mot-clé : ";
    std::cin >> keyword;

    // Obtenir le message chiffré de l'utilisateur
    std::cout << "Entrez le message à décrypter : ";
    std::cin.ignore(); // Vider le tampon d'entrée
    std::getline(std::cin, encryptedMessage);

    // Décrypter le message en utilisant la fonction de décryptage du carré de Polybe
    std::string decryptedMessage = polybiusDecrypt(encryptedMessage, keyword);

    // Afficher le message décrypté à l'utilisateur
    std::cout << "Message Décrypté : " << decryptedMessage << std::endl;

    return 0;
}
