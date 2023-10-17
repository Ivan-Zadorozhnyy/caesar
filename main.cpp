#include <iostream>
#include <dlfcn.h>

typedef char* (*encrypt_ptr_t)(char*, int);
typedef char* (*decrypt_ptr_t)(char*, int);

int main() {
    void* handle = dlopen("./libcaesar.dylib", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error: " << dlerror() << std::endl;
        return 1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t) dlsym(handle, "encrypt");
    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t) dlsym(handle, "decrypt");

    int choice, key;
    char message[1024];
    while (true) {
        std::cout << "1. Encrypt\n2. Decrypt\n3. Exit\nEnter choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:{
                std::cout << "Enter message to encrypt: ";
                std::cin.getline(message, sizeof(message));
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cin.ignore();
                char* encrypted = encrypt_ptr(message, key);
                std::cout << "Encrypted: " << encrypted << std::endl;
                delete[] encrypted;
                break;
            }
            case 2:{
                std::cout << "Enter message to decrypt: ";
                std::cin.getline(message, sizeof(message));
                std::cout << "Enter key: ";
                std::cin >> key;
                std::cin.ignore();
                char* decrypted = decrypt_ptr(message, key);
                std::cout << "Decrypted: " << decrypted << std::endl;
                delete[] decrypted;
                break;
            }
            case 3:
                dlclose(handle);
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }
    return 0;
}
