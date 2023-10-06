#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

/*
* Terminal uses:
* 
* crypt u <FILE> <KEY>
* Unencrypts the file with the specified password
* 
* crypt e <FILE> <KEY>
* Encrypts the file with the specified password
* 
*/

std::vector<unsigned char> xorEncryptDecrypt(const std::vector<unsigned char>& data, const std::string& key) {
    std::vector<unsigned char> result(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}


int main(int argc, char* argv[])
{

    if (argc == 1) {
        std::cout << "Note: This program is not intended for high-security usage.\n";
        std::cout << "Thank you for using this example cryptography program.\n";
        
        std::cout << "Press 1 and ENTER for Encryption, or 2 and ENTER for Decryption.\n";
        char choice;
        std::cin >> choice;

        if (choice == '1') {
            std::cout << "Please specify which file you would like to encrypt: ";

            std::ifstream unencrypted;
            std::ofstream encrypted;
            std::string fileName;
            std::cin >> fileName;

            unencrypted.open(fileName, std::ios::binary);

            if (!unencrypted.is_open()) {
                std::cerr << "Error: Unable to open the file '" + fileName + ".' Please try again." << std::endl;
                return 1;
            }

            std::string line;

            std::cout << "Please enter the password you would like to use to encrypt the file: ";
            std::string password;

            std::cin >> password;


            encrypted.open("encrypted_" + fileName, std::ios::binary);

            // Read the entire file content as bytes
            std::vector<unsigned char> fileContent(
                (std::istreambuf_iterator<char>(unencrypted)),
                std::istreambuf_iterator<char>()
            );

            // Encrypt the file content
            std::vector<unsigned char> encryptedContent = xorEncryptDecrypt(fileContent, password);
       
            encrypted.write(reinterpret_cast<char*>(encryptedContent.data()), encryptedContent.size());

            unencrypted.close();
            encrypted.close();

            remove(fileName.c_str());
            std::string oldName = "encrypted_" + fileName;

            if (rename(oldName.c_str(), fileName.c_str()) == 1) {
                std::cout << "Error renaming file.";
            }

            std::cout << "Your file has been encrypted. Thank you.";

            return 0;
        }
        else if (choice == '2') {
            std::cout << "Please specify which file you would like to decrypt: ";

            std::ifstream unencrypted;
            std::ofstream encrypted;
            std::string fileName;
            std::cin >> fileName;

            unencrypted.open(fileName, std::ios::binary);

            if (!unencrypted.is_open()) {
                std::cerr << "Error: Unable to open the file '" + fileName + ".' Please try again." << std::endl;
                return 1;
            }

            std::string line;

            std::cout << "Please enter the password you would like to use to encrypt the file: ";
            std::string password;

            std::cin >> password;


            encrypted.open("decrypted_" + fileName, std::ios::binary);

            // Read the entire file content as bytes
            std::vector<unsigned char> fileContent(
                (std::istreambuf_iterator<char>(unencrypted)),
                std::istreambuf_iterator<char>()
            );

            // Encrypt the file content
            std::vector<unsigned char> encryptedContent = xorEncryptDecrypt(fileContent, password);

            encrypted.write(reinterpret_cast<char*>(encryptedContent.data()), encryptedContent.size());

            unencrypted.close();
            encrypted.close();

            remove(fileName.c_str());
            std::string oldName = "decrypted_" + fileName;

            if (rename(oldName.c_str(), fileName.c_str()) == 1) {
                std::cout << "Error renaming file.";
            }

            std::cout << "Your file has been decrypted. Thank you.";

            return 0;
        }

        

    } 
    if (argc == 4) {
        // Do console-command things
        std::cout << "Note: This program is not intended for high-security usage.";
       
        std::ifstream unencrypted;
        std::ofstream encrypted;
        std::string fileName = argv[2];

        unencrypted.open(fileName, std::ios::binary);

        if (!unencrypted.is_open()) {
            std::cerr << "Error: Unable to open the file '" + fileName + ".' Please try again." << std::endl;
            return 1;
        }

        std::string line;

        std::string password = argv[3];



        encrypted.open("decrypted_" + fileName, std::ios::binary);

        // Read the entire file content as bytes
        std::vector<unsigned char> fileContent(
            (std::istreambuf_iterator<char>(unencrypted)),
            std::istreambuf_iterator<char>()
        );

        // Encrypt the file content
        std::vector<unsigned char> encryptedContent = xorEncryptDecrypt(fileContent, password);

        encrypted.write(reinterpret_cast<char*>(encryptedContent.data()), encryptedContent.size());

        unencrypted.close();
        encrypted.close();

        remove((char*)&fileName);
        std::string oldName = "encrypted_" + fileName;
        if (rename((char*)&oldName, (char*)&fileName) == 1) {
            std::cout << "Error renaming file.";
        }

        std::cout << "Your file has been encrypted. Thank you.";

        return 0;
    }
    else {
        std::cout << "Invalid number of arguments specified. Review the program for the intended usage, thank you." << std::endl;
    }
    return 0;
}
