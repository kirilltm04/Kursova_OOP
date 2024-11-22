#ifndef SENTENCECOUNTER_H
#define SENTENCECOUNTER_H

#include <string>

class SentenceCounter {
private:
    std::string text;     // Текст, що аналізується
    int sentenceCount;    // Кількість речень

    void countSentences(); // Метод для підрахунку речень

public:
    SentenceCounter(); // Конструктор за замовчуванням
    explicit SentenceCounter(const std::string &inputText); // Конструктор з параметрами
    SentenceCounter(const SentenceCounter &other); // Конструктор копіювання

    // Методи доступу
    void setText(const std::string &newText);
    [[nodiscard]] int getSentenceCount() const;
    [[nodiscard]] std::string getText() const;
};

#endif // SENTENCECOUNTER_H
