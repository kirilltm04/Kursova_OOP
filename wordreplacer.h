#ifndef WORDREPLACER_H
#define WORDREPLACER_H

#include <QString>
#include <QStringList>

class WordReplacer {
private:
    QString text; // Текст, в якому будуть знайдені та замінені слова

public:
    // Конструктор за замовчуванням
    WordReplacer();

    // Конструктор з параметрами
    WordReplacer(const QString& text);

    // Конструктор копій
    WordReplacer(const WordReplacer& other);

    // Деструктор
    ~WordReplacer();

    // Геттер для тексту
    QString getText() const;

    // Сеттер для тексту
    void setText(const QString& text);

    // Метод для заміни найдовшого та найкоротшого слова
    QString replaceLongestAndShortestWords();

    // Метод для знаходження найдовшого слова
    QString findLongestWord() const;

    // Метод для знаходження найкоротшого слова
    QString findShortestWord() const;

    // Перевантаження оператора присвоєння
    WordReplacer& operator=(const WordReplacer& other);

    // Перевантаження оператора виведення
    friend std::ostream& operator<<(std::ostream& os, const WordReplacer& replacer);
};

#endif // WORDREPLACER_H
