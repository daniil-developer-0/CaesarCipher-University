#ifndef CAESAR_H
#define CAESAR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Caesar; }
QT_END_NAMESPACE

class Caesar : public QMainWindow
{
    Q_OBJECT

public:
    Caesar(QWidget *parent = nullptr);
    ~Caesar();
    // Logic
    /**
     * @brief Шифрование текста
     * 
     * @param text Текст для шифрования
     * @param shift Сдвиг
     * @return QString Зашифрованный текст
     */
    QString EncodeText(QString text, int shift);
    void EncodeTextSlot(); // Функция для взаимодействия с интерфейсом

    QString MechanicalDecodeText(QString text);
    void DecodeTextSlot(); // Функция для взаимодействия с интерфейсом


            // Геттеры и сеттеры
    /**
     * @brief Сеттер для текста
     * 
     * @param text Текст
     */
    void SetText(QString text);

    /**
     * @brief Геттер для текста
     * 
     * @return QString Текст
     */
    QString GetText();

    /**
     * @brief Сеттер значения сдвига
     * 
     * @param shift Значение сдвига
     */
    void SetShift(int shift);

    /**
     * @brief Геттер значения сдвига
     * 
     * @return int Значение сдвига
     */
    int GetShift();

    //! Для языковых параметров я не вижу смысла делать геттеры и сеттеры, так как эти параметры неизменны.
    /**
     * @brief Устанавливает нужные свойства объекту класса Caesar, которые связаны с языковыми параметрами пользователя. \
     * Данные будут использоваться в рабочем окружении логических функций и не будут влиять на внешние языковые параметры
     * 
     */
    void SetUpLanguageEnvironment();


    // UI
    /**
     * @brief Сеттер для поля для вывода (UI)
     * 
     */
    void SetUserTextOutput();

    /**
     * @brief Геттер для текста из поля для ввода (UI)
     * 
     */
    void GetUserTextInput();

    /**
     * @brief Геттер для поля ввода значения сдвига (UI)
     * 
     */
    void GetShiftInput();


private:
    Ui::Caesar *ui;

    /**
     * @brief Текст, который обрабатывается
     * 
     */
    QString text;

    /**
     * @brief Количественная характеристика сдвига
     * 
     */
    int shift;

    /**
     * @brief Алфавит используемого языка
     * 
     */
    QString alphabet;

    /**
     * @brief Количество букв в алфавите
     * 
     */
    int alphabetAmountOfLetters;

    /**
     * @brief Массив с частотами встречаемости каждого символа в алфавите
     * 
     */
    float* alphabetFrequency;

    /**
     * @brief Символ, который охарактеризовывает используемый язык
     * 
     */
    QChar language;
};
#endif // CAESAR_H
