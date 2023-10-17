#include <cstring>
#include <cctype>

extern "C" {
char* encrypt(char* rawText, int key);
char* decrypt(char* encryptedText, int key);
}

char* encrypt(char* rawText, int key) {
    int length = strlen(rawText);
    char* encryptedText = new char[length + 1];

    for (int i = 0; i < length; i++) {
        char currentChar = rawText[i];

        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            encryptedText[i] = (currentChar - base + key) % 26 + base;
        } else {
            encryptedText[i] = currentChar;
        }
    }
    encryptedText[length] = '\0';
    return encryptedText;
}

char* decrypt(char* encryptedText, int key) {
    int length = strlen(encryptedText);
    char* decryptedText = new char[length + 1];

    for (int i = 0; i < length; i++) {
        char currentChar = encryptedText[i];

        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            decryptedText[i] = (currentChar - base - key + 26) % 26 + base;
        } else {
            decryptedText[i] = currentChar;
        }
    }
    decryptedText[length] = '\0';
    return decryptedText;
}
