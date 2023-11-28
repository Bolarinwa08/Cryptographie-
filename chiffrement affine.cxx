#include <iostream>
#include <string>
#include <cmath>

// Fonction pour calculer l'inverse modulaire de 'a' par rapport à 'm'
int mod_inverse(int a, int m) {
    int m0 = m, x0 = 0, x1 = 1;

    // Algorithme d'Euclide étendu
    while (a > 1) {
        int q = a / m;
        int temp = m;
        m = a % m, a = temp;
        int temp2 = x0;
        x0 = x1 - q * x0;
        x1 = temp2;
    }

    return x1 + m0 * (x1 < 0 ? 1 : 0);  // Assurer un inverse modulaire positif
}

// Fonction pour calculer le plus grand commun diviseur (PGCD) de deux nombres 'a' et 'b'
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Fonction pour vérifier si deux nombres 'a' et 'b' sont premiers entre eux (PGCD est 1)
bool are_coprime(int a, int b) {
    return gcd(a, b) == 1;
}

// Fonction pour chiffrer un texte en clair en utilisant le chiffre affine avec la clé (a, b)
std::string encrypt_affine_cipher(const std::string& plaintext, int a, int b) {
    std::string encrypted_text = "";
    int m = 26;  // Taille de l'alphabet

    for (char c : plaintext) {
        if (std::isalpha(c)) {
            // Formule de chiffrement pour chaque caractère
            char encrypted_char = ((a * (c - 'A') + b) % m + m) % m + 'A';
            encrypted_text += encrypted_char;
        } else {
            encrypted_text += c;  // Conserver les caractères non alphabétiques
        }
    }

    return encrypted_text;
}

int main() {
    std::cout << "Entrez le message à chiffrer (en majuscules) : ";
    std::string plaintext;
    std::getline(std::cin, plaintext);

    int a, b;
    do {
        std::cout << "Entrez la première partie de la clé (a) : ";
        std::cin >> a;

        // Valider que 'a' est premier avec 26
        if (!are_coprime(a, 26)) {
            std::cout << "Erreur : a n'est pas premier avec 26. Veuillez recommencer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!are_coprime(a, 26));

    std::cout << "Entrez la deuxième partie de la clé (b) : ";
    std::cin >> b;

    // Chiffrer le texte en clair en utilisant le chiffre affine
    std::string encrypted_text = encrypt_affine_cipher(plaintext, a, b);
    std::cout << "Texte chiffré : " << encrypted_text << std::endl;

    return 0;
}
