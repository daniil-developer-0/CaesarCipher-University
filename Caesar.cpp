#include "Caesar.h"
#include "./ui_caesar.h"
#include <map>
#include <QString>
#include <cmath>

#define DEBUG

Caesar::Caesar(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Caesar)
{
    ui->setupUi(this);
    // Соединяем кнопку "Зашифровать"
    connect(ui->EncodeButton, &QPushButton::released, this, &Caesar::EncodeTextSlot);
    // Соединяем кнопку "Дешифровать"
    connect(ui->DecodeButton, &QPushButton::released, this, &Caesar::DecodeTextSlot);
}

Caesar::~Caesar()
{
    delete ui;
}

// UI
void Caesar::GetUserTextInput()
{
    Caesar::SetText(ui->plainTextEdit->toPlainText());
}

void Caesar::SetUserTextOutput()
{
    ui->textBrowser->setText(Caesar::GetText());
}

void Caesar::GetShiftInput()
{
    Caesar::SetShift(ui->shiftSpinbox->value());
}

void Caesar::SetUpLanguageEnvironment()
{
    if (ui->RussianLanguageRadio->isChecked())
    {
        // Русский язык
        Caesar::language = 'r';
    }
    else
    {
        // Английский язык
        Caesar::language = 'e';
    }

    // Mapping values
    std::map<QChar, int> lang_map;
    lang_map['r'] = 1;
    lang_map['e'] = 0;

    // Select language
    switch (lang_map[Caesar::language])
    {
        case 0:
            // English language
            Caesar::alphabet = "abcdefghijklmnopqrstuvwxyz";
            Caesar::alphabetAmountOfLetters = 26;
            Caesar::alphabetFrequency = new float[alphabetAmountOfLetters]{8.12f, 1.49f, 2.71f, 4.32f, 12.0f, 2.30f, 2.03f, 5.92f, 7.31f, 3.98f, 0.10f, 0.69f, 2.61f, 6.95f, 7.68f, 1.82f, 6.02f, 0.11f, 6.28f, 9.10f, 2.88f, 1.11f, 2.09f, 0.17f, 2.11f, 0.07f};
            Caesar::alphabetSortedByFrequency = "etainroshdlcfumgpwbyvkqxjz";
            break;

        case 1:
            // Russian language
            Caesar::alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
            Caesar::alphabetAmountOfLetters = 33;
            Caesar::alphabetFrequency = new float[alphabetAmountOfLetters]{7.5f, 1.7f, 4.6f, 1.6f, 3.0f, 8.8f, 8.8f, 0.8f, 1.9f, 7.5f, 1.2f, 3.4f, 4.2f, 3.2f, 6.4f, 10.9f, 2.8f, 4.8f, 5.4f, 6.4f, 2.6f, 0.2f, 1.1f, 0.5f, 1.5f, 0.7f, 0.4f, 1.9f, 1.7f, 1.7f, 0.4f, 0.7f, 2.2f};
            Caesar::alphabetSortedByFrequency = "оеаинтсрвлкмдпуяызъьгчйхжюшцщэф";
            break;

        default:
            throw std::runtime_error("There is no language what you need (support for Russian and English only)");
            break;
    }
}

// Logic
void Caesar::SetText(QString text)
{
    Caesar::text = text;
}

QString Caesar::GetText()
{
    return Caesar::text;
}

void Caesar::SetShift(int shift)
{
    Caesar::shift = shift;
}

int Caesar::GetShift()
{
    return Caesar::shift;
}

QString Caesar::EncodeText(QString text, int shift)
{
    QString result = ""; // Переменная, в которой будет храниться результат
    bool upper;          // Переменная, которая отвечает в каком регистре символ
    for (auto i : text)
    {
        //TODO: toupper on QChar ?
        upper = (i == i.toUpper()) ? true : false; // Проверяем в каком регистре буква сравнением с её большим вариантом
        //TODO: QString find ? : Nope, that's indexOf(whatToFind : String, startIndex : int)
        int ind = Caesar::alphabet.indexOf(i.toLower());
        if (ind != -1)
        {
            // Прибавляем сдвиг к индексу символа в массиве letters и получаем ещё один индекс (уже зашифрованного символа)
            ind += shift;

            // На случай, если сумма будет больше размера массива
            ind -= (ind >= alphabet.size()) ? alphabet.size() : 0;

            // Возвращаем букву в правильном регистре
            result.append((upper) ? alphabet[ind].toUpper() : alphabet[ind]);
        }
        else
        {
            result.append(i);
        }
    }

    // Обработка ошибок
    try
    {
        if (result != "")
            return result;
        else
            throw(result);
    }
    catch (const std::string e)
    {
        std::printf("Ошибка! Возвращаемым выражением не может быть: \"%s\"\n", e);
        exit(1);
    }
}

QString Caesar::MechanicalDecodeText(QString text)
{
    QString result = "";
    for (int temp_shift = 1; temp_shift <= Caesar::alphabetAmountOfLetters; temp_shift++)
    {
        result.append(Caesar::EncodeText(text, temp_shift) + "\n");
    }
    return result;
}

QString Caesar::AlgoDecodeText(QString text)
{
    QString result = "";
    // Подсчёт коэффициентов символов
    float *localAlphabetFrequency = new float[Caesar::alphabetAmountOfLetters]; // Локальные частоты встречаемости символов
    for (int i = 0; i < Caesar::alphabetAmountOfLetters; i++)
    {
        localAlphabetFrequency[i] = (float)text.count(Caesar::alphabet[i], Qt::CaseInsensitive) / text.length(); // Частота встречи определенного символа в исходном тексте
        localAlphabetFrequency[i] = (float)((int)(localAlphabetFrequency[i] * 10000)) / 100; // Отрезаем мантиссу. Оставляем 10^2 (2 числа после запятой).

#ifdef DEBUG
        result.append("===\n");
        result.append("Letter is: " + QString(Caesar::alphabet.at(i)) + "\n");
        result.append("Letter count: " + QString::number(text.count(Caesar::alphabet.at(i))) + "\n");
        result.append("Letter Frequency divided on text len: " + QString::number(localAlphabetFrequency[i]) + "\n");
        result.append("===\n\n");
#endif
    }

    // Копирование алфавита
    QString localAlphabet = "";
    localAlphabet.append(Caesar::alphabet);

    // Сортировка
    for (int i = 0; i < Caesar::alphabetAmountOfLetters; i++) {
        for (int j = 1; j < Caesar::alphabetAmountOfLetters - i; j++) {
            if (localAlphabetFrequency[j] > localAlphabetFrequency[j - 1]) {
                // Меняем местами коэффициенты
                float tempFrequency = localAlphabetFrequency[j];
                localAlphabetFrequency[j] = localAlphabetFrequency[j - 1];
                localAlphabetFrequency[j - 1] = tempFrequency;
                // Меняем местами буквы
                QChar tempChar = localAlphabet[j];
                localAlphabet[j] = localAlphabet[j - 1];
                localAlphabet[j - 1] = tempChar;
            }
        }
    }

    // Поиск разности индексов
    if ()


    return localAlphabet;
}

// Slots
void Caesar::EncodeTextSlot()
{
    Caesar::GetUserTextInput(); // Парсинг текста из поля для ввода
    Caesar::GetShiftInput();    // Парсинг значения сдвига
    Caesar::SetUpLanguageEnvironment();
    QString input = Caesar::GetText();
    int shift = Caesar::GetShift();
    QString output = Caesar::EncodeText(input, shift); // Кодирование текста
    Caesar::SetText(output);                           // Сет текста в переменную Caesar::text
    Caesar::SetUserTextOutput();                       // Вывод результата на экран
}

void Caesar::DecodeTextSlot()
{
    Caesar::GetUserTextInput(); // Парсинг текста из поля для ввода
    Caesar::SetUpLanguageEnvironment();
    QString input = Caesar::GetText();
    QString output = "";
    output = ui->AlgoDecodeCheckbutton->isChecked() ? Caesar::AlgoDecodeText(input) : Caesar::MechanicalDecodeText(input); // Декодирование текста
    Caesar::SetText(output);     // Сет текста в переменную Caesar::text
    Caesar::SetUserTextOutput(); // Вывод результата на экран
}
