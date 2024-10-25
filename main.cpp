#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



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

int main()
{
    fstream file;

    string filePath;

    cout << "Enter the path of the file to encrypt or decrypt: ";
    getline(cin, filePath);

    file.open(filePath, ios::in | ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "Error opening file: ";
        return 0;
    }

    int choice, key;

    cout << "Enter 0 to encrypt, 1 to decrypt: ";
    cin >> choice;

    if (choice != 0 && choice != 1) {
        cout << "Invalid choice.";
        file.close();
        return 0;
    }

    vector<char> data;
    char c;
    while (file.get(c)) {
        data.push_back(c);
    }

    if (choice == 0) {
        for (char& currentChar : data) {
            encrypt(key, &currentChar);
        }
    } else {
        for (char& currentChar : data) {
            decrypt(key, &currentChar);
        }
    }

    file.seekp(0);
    for (char c : data) {
        file.put(c);
    }

    file.close();

    return 0;
}