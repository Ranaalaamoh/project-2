
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

const string EEXTENSION = ".encrypt";
string filePath;

bool isEncryptedFile(const string& filename) {
    return filesystem::path(filename).extension() == EEXTENSION;
}

void encrypt(int key, char* currentChar) {
    while (*currentChar) {
        if (*currentChar >= 'a' && *currentChar + key > 'z') {
            *currentChar = (*currentChar + key) - 'z' + 'a' - 1;
        } else if (*currentChar >= 'A' && *currentChar + key > 'Z') {
            *currentChar = (*currentChar + key) - 'Z' + 'A' - 1;
        } else {
            *currentChar += key;
        }
        currentChar++;
    }
}

void decrypt(int key, char* currentChar) {
    while (*currentChar) {
        if (*currentChar >= 'a' && *currentChar - key < 'a') {
            *currentChar = (*currentChar - key) + 'z' - 'a' + 1;
        } else if (*currentChar >= 'A' && *currentChar - key < 'A') {
            *currentChar = (*currentChar - key) + 'Z' - 'A' + 1;
        } else {
            *currentChar -= key;
        }
        currentChar++;
    }
}

int main() {
    fstream file;

    cout << "Enter the path of the file to encrypt or decrypt: ";
    getline(cin, filePath);


    filesystem::path encryptedFilePath;
    if (isEncryptedFile(filePath)) {
        encryptedFilePath = filePath;
    } else {
        encryptedFilePath = filePath.append(EEXTENSION);
    }

    file.open(filePath, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file: ";
        return 0;
    }

    int key;
    cout << "Enter the numeric key: ";
    cin >> key;

    vector<char> data;
    char c;
    while (file.get(c)) {
        data.push_back(c);
    }

    if (isEncryptedFile(filePath)) {
        for (char& currentChar : data) {
            decrypt(key, &currentChar);
        }
    } else {
        for (char& currentChar : data) {
            encrypt(key, &currentChar);
    }

    file.seekp(0);
    for (char c : data) {
        file.put(c);
    }

    file.close();


        filesystem::rename(filePath, encryptedFilePath);
    }

    return 0;
}