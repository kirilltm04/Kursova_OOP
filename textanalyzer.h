#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include <string>
#include <fstream>
#include <sstream>
#include "sentencecounter.h"
#include "digitcounter.h"
#include "alphabetanalyzer.h"
#include <QString>
#include <iomanip>

class TextAnalyzer {
private:
    std::string text;             // Оригінальний текст
    std::string modifiedText;     // Модифікований текст після обробки

    SentenceCounter sentenceCounter;   // Підрахунок речень
    DigitCounter digitCounter;         // Підрахунок цифр
    AlphabetAnalyzer alphabetAnalyzer; // Аналіз літер (латиниця/кирилиця)

    // Оновлення внутрішнього стану аналізатора
    void analyzeText();

public:
    // Конструктори
    TextAnalyzer();
    explicit TextAnalyzer(const std::string &inputText);
    TextAnalyzer(const TextAnalyzer &other);

    // Оператори для вводу/виводу
    friend std::istream &operator>>(std::istream &in, TextAnalyzer &analyzer);
    friend std::ostream &operator<<(std::ostream &out, const TextAnalyzer &analyzer);

    // Методи доступу до тексту
    void setText(const std::string &newText);
    [[nodiscard]] std::string getText() const;
    [[nodiscard]] std::string getModifiedText() const;

    // Методи аналізу тексту
    [[nodiscard]] std::string getResult() const; // Результат аналізу
    [[nodiscard]] std::string getDigitAnalysis() const; // Аналіз цифр
    [[nodiscard]] int getSentenceCount() const; // Кількість речень

    // Методи роботи зі словами
    [[nodiscard]] std::string findLongestWord() const;
    [[nodiscard]] std::string findShortestWord() const;
    std::string replaceLongestAndShortestWords() const;


    // Методи транслітерації
    [[nodiscard]] std::string convertCyrToLat() const;
    [[nodiscard]] std::string convertLatToCyr() const;

    // Метод для створення звіту
    void generateReport(const std::string &filePath) const;

    // Замінює символи в тексті
    QString replaceCharacter(const QString &oldChar, const QString &newChar);
};

#endif // TEXTANALYZER_H
