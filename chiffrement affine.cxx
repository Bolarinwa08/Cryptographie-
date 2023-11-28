#include <iostream>
#include <string>

int mod_inverse(int a, int m) {
    // Fonction pour calculer l'inverse modulaire de a modulo m
    int m0 = m, x0 = 0, x1 = 1;

    while (a > 1) {
        int q = a / m;
        int temp = m;
        m = a % m, a = temp;
        int temp2 = x0;
        x0 = x1 - q * x0;
        x1 = temp2;
    }

    return x1 + m0 * (x1 < 0 ? 1 : 0);
}

std::string encrypt_affine_cipher(const std::string& plaintext, int a, int b) {
    // Fonction de chiffrement affine
    std::string encrypted_text = "";
    int m = 26;  // Taille de l'alphabet (pour l'anglais)

    for (char c : plaintext) {
        if (std::isalpha(c)) {
            // Chiffrement de la lettre
            char encrypted_char = ((a * (c - 'A') + b) % m + m) % m + 'A';
            encrypted_text += encrypted_char;
        } else {
            // Ne touche pas aux caractères non alphabétiques
            encrypted_text += c;
        }
    }

    return encrypted_text;
}

int main() {
    // Demander à l'utilisateur d'entrer le message
    std::cout << "Entrez le message à chiffrer (en majuscules) : ";
    std::string plaintext;
    std::getline(std::cin, plaintext);

    // Demander à l'utilisateur d'entrer les paramètres de la clé
    int a, b;
    std::cout << "Entrez la première partie de la clé (a) : ";
    std::cin >> a;
    std::cout << "Entrez la deuxième partie de la clé (b) : ";
    std::cin >> b;

    // Chiffrer le message et afficher le résultat
    std::string encrypted_text = encrypt_affine_cipher(plaintext, a, b);
    std::cout << "Texte chiffré : " << encrypted_text << std::endl;

    return 0;
}
