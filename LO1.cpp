#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция для шифрования текста с использованием таблицы Виженера
string vigenereCipher(const string& text, const string& key, bool decrypt = false) {
    string result;
    int keyLength = key.size();

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        // Приведение символа к типу unsigned char
        if (isalpha(static_cast<unsigned char>(c))) {
            char base = isupper(static_cast<unsigned char>(c)) ? 'A' : 'a';
            int keyIndex = (i % keyLength);
            char keyChar = key[keyIndex];
            int keyShift = (tolower(static_cast<unsigned char>(keyChar)) - 'a') * (decrypt ? -1 : 1);
            result += char(int(base + (c - base + keyShift + 26) % 26));
        }
        else {
            result += c; // Не шифровать символы, не являющиеся буквами
        }
    }

    return result;
}

// Функция для чтения файла в строку
string readFile(const string& filename) {
    ifstream file(filename, ios::in | ios::binary);
    if (!file) {
        throw runtime_error("Error with open file to read: " + filename);
    }

    string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();
    return content;
}

// Функция для записи строки в файл
void writeFile(const string& filename, const string& content) {
    ofstream file(filename, ios::out | ios::binary);
    if (!file) {
        throw runtime_error("Error with open file to write: " + filename);
    }

    file.write(content.c_str(), content.size());
    file.close();
}

// Меню программы
void displayMenu() {
    cout << "Main\n";
    cout << "1. Encode file\n";
    cout << "2. Decode file\n";
    cout << "3. Exit\n";
    cout << "Choose the variant: ";
}

int main() {
    int choice;
    string inputFile, outputFile, key;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter file to encode: ";
            cin >> inputFile;
            cout << "Enter file to write in: ";
            cin >> outputFile;
            cout << "Enter the key of encoding: ";
            cin >> key;

            try {
                string content = readFile(inputFile);
                string encrypted = vigenereCipher(content, key, false);
                writeFile(outputFile, encrypted);
                cout << "Succes " << outputFile << endl;
            }
            catch (const exception& e) {
                cerr << "Error " << e.what() << endl;
            }
            break;
        }
        case 2: {
            cout << "Enter file to decode: ";
            cin >> inputFile;
            cout << "Enter file to write in: ";
            cin >> outputFile;
            cout << "Enter the key of decoding: ";
            cin >> key;

            try {
                string content = readFile(inputFile);
                string decrypted = vigenereCipher(content, key, true);
                writeFile(outputFile, decrypted);
                cout << "Succes " << outputFile << endl;
            }
            catch (const exception& e) {
                cerr << "Error " << e.what() << endl;
            }
            break;
        }
        case 3:
            cout << "Execution...\n";
            break;
        default:
            cout << "Wrong choice. Try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
