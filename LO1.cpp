#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция для шифрования/дешифровки по таблице Виженера с использованием всех 256 символов
std::string vigenere(const std::string& text, const std::string& key, bool encrypt) {
    std::string result;
    size_t key_len = key.size();

    for (size_t i = 0; i < text.size(); ++i) {
        // Берем текущий символ текста и ключа
        // Считыване
        unsigned char text_char = static_cast<unsigned char>(text[i]);
        unsigned char key_char = static_cast<unsigned char>(key[i % key_len]);

        // Шифрование: прибавляем значение ключа к тексту по модулю 256
        if (encrypt) {
            result += static_cast<char>((text_char + key_char) % 256);
        }
        // Дешифровка: вычитаем значение ключа из текста по модулю 256
        else {
            result += static_cast<char>((text_char - key_char + 256) % 256);
        }
    }

    return result;
}
// Функция для работы с файлами и выполнения шифрования/дешифровки
void processFile(const std::string& input_file, const std::string& output_file, const std::string& key, bool encrypt) {
    // Открытие входного файла
    std::ifstream infile(input_file, std::ios::binary);
    if (!infile) {
        std::cerr << "Ошибка: невозможно открыть файл для чтения " << input_file << '\n';
        return;
    }

    // Чтение входного файла в строку
    std::string text((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    // Шифрование или дешифровка
    std::string result = vigenere(text, key, encrypt);

    // Запись результата в выходной файл
    std::ofstream outfile(output_file, std::ios::binary);
    if (!outfile) {
        std::cerr << "Ошибка: невозможно открыть файл для записи " << output_file << '\n';
        return;
    }

    outfile.write(result.c_str(), result.size());
    outfile.close();

    std::cout << (encrypt ? "Кодирование" : "Раскодирование") << " выполнено. Записано в файл " << output_file << '\n';
}

int main() {
    std::string input_file, output_file, key;
    int choice;
    system("chcp 1251");

    while (true) {
        // Меню
        std::cout << "Шифр Вижинера (256 символов)\n";
        std::cout << "1. Закодировать файл\n";
        std::cout << "2. Раскодировать файл\n";
        std::cout << "3. Выход\n";
        std::cout << "Выберите пункт меню (1-3): ";
        std::cin >> choice;

        // Обработка выбора
        if (choice == 1 || choice == 2) {
            std::cout << "Введите файл для считывания: ";
            std::cin >> input_file;

            std::cout << "Введите файл для записи: ";
            std::cin >> output_file;

            std::cout << "Введите ключ: ";
            std::cin >> key;

            // Определяем режим (шифрование или дешифровка)
            bool encrypt = (choice == 1);

            // Выполняем процесс шифрования/дешифровки
            processFile(input_file, output_file, key, encrypt);
        }
        else if (choice == 3) {
            std::cout << "Выход...\n";
            break;
        }
        else {
            std::cout << "Невалидный ввод. Пожалуйста введите 1, 2, или 3.\n";
        }
    }

    return 0;
}

