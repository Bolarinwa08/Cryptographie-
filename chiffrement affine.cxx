#include <iostream>
#include <string>
#include <cmath>

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

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool are_coprime(int a, int b) {
    return gcd(a, b) == 1;
}

std::string encrypt_affine_cipher(const std::string& plaintext, int a, int b) {
    std::string encrypted_text = "";
    int m = 26;

    for (char c : plaintext) {
        if (std::isalpha(c)) {
            char encrypted_char = ((a * (c - 'A') + b) % m + m) % m + 'A';
            encrypted_text += encrypted_char;
        } else {
            encrypted_text += c;
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

        if (!are_coprime(a, 26)) {
            std::cout << "Erreur : a n'est pas premier avec 26. Veuillez recommencer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!are_coprime(a, 26));

    std::cout << "Entrez la deuxième partie de la clé (b) : ";
    std::cin >> b;

    std::string encrypted_text = encrypt_affine_cipher(plaintext, a, b);
    std::cout << "Texte chiffré : " << encrypted_text << std::endl;

    return 0;
}
