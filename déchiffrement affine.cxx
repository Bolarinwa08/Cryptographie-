 #include <iostream>
#include <string>

// Fonction pour calculer l'inverse modulaire de a modulo m
int mod_inverse(int a, int m) {
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

// Fonction pour calculer le plus grand commun diviseur (PGCD) de deux nombres 'a' et 'b'
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Fonction de déchiffrement affine
std::string decrypt_affine_cipher(const std::string& ciphertext, int a, int b) {
    std::string decrypted_text = "";
    int m = 26;  // Taille de l'alphabet (pour l'anglais)
    int a_inv = mod_inverse(a, m);

    for (char c : ciphertext) {
        if (std::isalpha(c)) {
            // Déchiffrement de la lettre
            char decrypted_char = ((a_inv * (c - 'A' - b)) % m + m) % m + 'A';
            decrypted_text += decrypted_char;
        } else {
            // Ne touche pas aux caractères non alphabétiques
            decrypted_text += c;
        }
    }

    return decrypted_text;
}

int main() {
    // Demander à l'utilisateur d'entrer le message chiffré
    std::cout << "Entrez le message à déchiffrer (en majuscules) : ";
    std::string ciphertext;
    std::getline(std::cin, ciphertext);

    // Demander à l'utilisateur d'entrer les paramètres de la clé
    int a, b;

    do {
        std::cout << "Entrez la première partie de la clé (a) : ";
        std::cin >> a;

        // Valider que 'a' est premier avec 26
        if (gcd(a, 26) != 1) {
            std::cout << "Erreur : a doit être premier avec 26. Veuillez recommencer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (gcd(a, 26) != 1);

    std::cout << "Entrez la deuxième partie de la clé (b) : ";
    std::cin >> b;

    // Déchiffrer le message et afficher le résultat
    std::string decrypted_text = decrypt_affine_cipher(ciphertext, a, b);
    std::cout << "Texte déchiffré : " << decrypted_text << std::endl;

    return 0;
}
   
