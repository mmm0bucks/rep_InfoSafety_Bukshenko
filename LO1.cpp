//#include <iostream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//// Функция для шифрования/дешифровки по таблице Виженера с использованием всех 256 символов
//std::string vigenere(const std::string& text, const std::string& key, bool encrypt) {
//    std::string result;
//    size_t key_len = key.size();
//
//    for (size_t i = 0; i < text.size(); ++i) {
//        // Берем текущий символ текста и ключа
//        // Считыване
//        unsigned char textChar = static_cast<unsigned char>(text[i]);
//        unsigned char keyChar = static_cast<unsigned char>(key[i % key_len]);
//
//        // Шифрование: прибавляем значение ключа к тексту по модулю 256
//        if (encrypt) {
//            result += static_cast<char>((textChar + keyChar) % 256);
//        }
//        // Дешифровка: вычитаем значение ключа из текста по модулю 256
//        else {
//            result += static_cast<char>((textChar - keyChar + 256) % 256);
//        }
//    }
//
//    return result;
//}
//// Функция для работы с файлами и выполнения шифрования/дешифровки
//void processFile(const std::string& input_file, const std::string& output_file, const std::string& key, bool encrypt) {
//    // Открытие входного файла
//    std::ifstream infile(input_file, std::ios::binary);
//    if (!infile) {
//        std::cerr << "Ошибка: невозможно открыть файл для чтения " << input_file << '\n';
//        return;
//    }
//
//    // Чтение входного файла в строку
//    std::string text((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
//    infile.close();
//
//    // Шифрование или дешифровка
//    std::string result = vigenere(text, key, encrypt);
//
//    // Запись результата в выходной файл
//    std::ofstream outfile(output_file, std::ios::binary);
//    if (!outfile) {
//        std::cerr << "Ошибка: невозможно открыть файл для записи " << output_file << '\n';
//        return;
//    }
//
//    outfile.write(result.c_str(), result.size());
//    outfile.close();
//
//    std::cout << (encrypt ? "Кодирование" : "Раскодирование") << " выполнено. Записано в файл " << output_file << '\n';
//}
//
//int main() {
//    std::string input_file, output_file, key;
//    int choice;
//    system("chcp 1251");
//
//    while (true) {
//        // Меню
//        std::cout << "Шифр Вижинера (256 символов)\n";
//        std::cout << "1. Закодировать файл\n";
//        std::cout << "2. Раскодировать файл\n";
//        std::cout << "3. Выход\n";
//        std::cout << "Выберите пункт меню (1-3): ";
//        std::cin >> choice;
//
//        // Обработка выбора
//        if (choice == 1 || choice == 2) {
//            std::cout << "Введите файл для считывания: ";
//            std::cin >> input_file;
//
//            std::cout << "Введите файл для записи: ";
//            std::cin >> output_file;
//
//            std::cout << "Введите ключ: ";
//            std::cin >> key;
//
//            // Определяем режим (шифрование или дешифровка)
//            bool encrypt = (choice == 1);
//
//            // Выполняем процесс шифрования/дешифровки
//            processFile(input_file, output_file, key, encrypt);
//        }
//        else if (choice == 3) {
//            std::cout << "Выход...\n";
//            break;
//        }
//        else {
//            std::cout << "Невалидный ввод. Пожалуйста введите 1, 2, или 3.\n";
//        }
//    }
//
//    return 0;
//}



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Функция для подсчета частоты символов
vector<int> getEntry(vector<unsigned char>& text) {
    vector<int> entry(256, 0);
    for (auto j : text) {
        entry[j]++;
    }
    return entry;
}

// Вывод n самых частых символов эталонного текста
void printFirstN(vector<unsigned char>& text, int n) {
    vector<int> entry = getEntry(text);
    unordered_map<int, int> entryPairs;
    for (int i = 0; i < 256; i++)
        entryPairs.insert({ entry[i], i });

    sort(entry.begin(), entry.end(), std::greater<int>());

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". '" << char(entryPairs[entry[i]]) << "', количество вхождений: " << entry[i] << endl;
    }
}

// Нахождение индекса совпадения
float getIndex(vector<unsigned char>& text) {
    vector<int> entry = getEntry(text);
    float index = 0;
    float sumInd = 0;

    for (int j = 0; j < entry.size(); j++) {
        sumInd += (float)entry[j] * (float)(entry[j] - 1);
    }

    index = sumInd / (float)(text.size() * (text.size() - 1));
    return index;
}

// Нахождение самого часто встречающегося символа
unsigned char theMostFrequent(vector<int>& text) {
    unsigned char frChar;
    int max = -1;
    for (int i = 0; i < 256; i++) {
        if (text[i] > max) {
            frChar = i;
            max = text[i];
        }
    }
    return frChar;
}

// Определение длины ключа
int keyLength(vector<unsigned char>& textEncode) {
    cout << "Введите диапазон длины ключа через пробел: ";
    int left, right;
    cin >> left >> right;

    int lengthKey = left;
    double maxIndex = 0;

    for (int length = left; length <= right; length++) {
        cout << "Анализ " << length << "-значного ключа" << endl;

        vector<unsigned char> groupSameLetter;
        for (int i = 0; i < textEncode.size(); i++) {
            if (i % length == 0)
                groupSameLetter.push_back(textEncode[i]);
        }

        double index = getIndex(groupSameLetter);
        cout << "Индекс совпадения: " << index << endl;

        if (index > maxIndex) {
            maxIndex = index;
            lengthKey = length;
        }
    }

    cout << "Предполагаемая длина ключа: " << lengthKey << endl;
    return lengthKey;
}

// Поиск ключа
string keySearch(vector<unsigned char>& textEncode, vector<unsigned char>& textEtalon, const int& lengthKey) {
    vector<int> entry = getEntry(textEtalon);
    unsigned char frecCharEtalon = theMostFrequent(entry);

    vector<vector<unsigned char>> groups(lengthKey);

    for (int i = 0; i < textEncode.size(); i++) {
        groups[i % lengthKey].push_back(textEncode[i]);
    }

    string key;
    for (int j = 0; j < lengthKey; j++) {
        vector<int> temp = getEntry(groups[j]);
        unsigned char frecCharText = theMostFrequent(temp);
        key.push_back(frecCharText - frecCharEtalon);
    }

    cout << "Найденный ключ: " << key << endl;
    return key;
}

// Расшифровка текста по таблице Виженера
void vizhenerDecode(const string& fileIn, const string& keyWord) {
    basic_ifstream<unsigned char> fin(fileIn, ios::binary);
    cout << "Введите имя файла для записи: ";
    string fileOut;
    cin >> fileOut;
    fileOut += ".txt";
    basic_ofstream<unsigned char> fout(fileOut, ios::binary);

    int memberkey = 0;
    unsigned char code;
    while (true) {
        code = fin.get();
        if (fin.eof()) break;
        fout << (unsigned char)(code - keyWord[memberkey % keyWord.size()]);
        memberkey++;
    }

    fin.close();
    fout.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool exit;
    int lengthKey;
    string inputEncodeFile, inputEtalon;
    string key;

    while (true) {
        cout << "Введите имя файла закодированного текста (без расширения): ";
        cin >> inputEncodeFile;
        inputEncodeFile += ".txt";
        cout << "Введите имя эталонного текста: ";
        cin >> inputEtalon;
        inputEtalon += ".txt";

        ifstream inputTextEncode(inputEncodeFile, ios::binary);
        ifstream inputTextEtalon(inputEtalon, ios::binary);

        vector<unsigned char> textEtalon((istreambuf_iterator<char>(inputTextEtalon)), istreambuf_iterator<char>());
        vector<unsigned char> textEncode((istreambuf_iterator<char>(inputTextEncode)), istreambuf_iterator<char>());

        printFirstN(textEtalon, 5);

        lengthKey = keyLength(textEncode);

        key = keySearch(textEncode, textEtalon, lengthKey);

        vizhenerDecode(inputEncodeFile, key);

        cout << "Хотите расшифровать еще один файл? (для выхода нажмите 0): ";
        cin >> exit;
        if (!exit)
            break;
    }
    return 0;
}



