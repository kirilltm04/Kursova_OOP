#include "wordreplacer.h"
#include <iostream>
#include <QRegularExpression>

// Конструктор за замовчуванням
WordReplacer::WordReplacer() : text("") {}

// Конструктор з параметрами
WordReplacer::WordReplacer(const QString& text) : text(text) {}

// Конструктор копій
WordReplacer::WordReplacer(const WordReplacer& other) : text(other.text) {}

// Деструктор
WordReplacer::~WordReplacer() {}

// Геттер для тексту
QString WordReplacer::getText() const {
    return text;
}

// Сеттер для тексту
void WordReplacer::setText(const QString& text) {
    this->text = text;
}

// Метод для знаходження найдовшого слова
QString WordReplacer::findLongestWord() const {
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QString longestWord = "";
    QRegularExpression onlyLettersRegex("[^\\p{L}]"); // Залишає тільки букви (унікодні)

    for (QString word : words) {
        // Видаляємо всі небуквені символи
        word.remove(onlyLettersRegex);

        // Перевіряємо довжину слова
        if (word.length() > longestWord.length()) {
            longestWord = word;
        }
    }
    return longestWord;
}

// Метод для знаходження найкоротшого слова
QString WordReplacer::findShortestWord() const {
    QStringList words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    if (words.isEmpty()) {
        return "";
    }

    QRegularExpression onlyLettersRegex("[^\\p{L}]"); // Залишає тільки букви (унікодні)
    QString shortestWord = ""; // Найкоротше слово
    QList<QString> candidates; // Список потенційно найкоротших слів

    // Створюємо список кандидатів, очищених від небуквених символів
    for (QString word : words) {
        word.remove(onlyLettersRegex);
        if (!word.isEmpty()) {
            if (shortestWord.isEmpty() || word.length() < shortestWord.length()) {
                candidates.clear();
                shortestWord = word;
            }
            if (word.length() == shortestWord.length()) {
                candidates.append(word);
            }
        }
    }

    // Сортуємо кандидатів: спочатку кирилиця, потім латиниця
    std::sort(candidates.begin(), candidates.end(), [](const QString& a, const QString& b) {
        QRegularExpression isCyrillic("[а-яА-ЯіІїЇєЄґьҐ]");
        bool aIsCyrillic = isCyrillic.match(a).hasMatch();
        bool bIsCyrillic = isCyrillic.match(b).hasMatch();

        if (aIsCyrillic != bIsCyrillic) {
            return aIsCyrillic; // Кирилиця має пріоритет
        }

        return a < b; // Алфавітний порядок
    });

    return candidates.isEmpty() ? "" : candidates.first();
}

QString WordReplacer::replaceLongestAndShortestWords() {
    QString longestWord = findLongestWord();
    QString shortestWord = findShortestWord();

    if (longestWord.isEmpty() || shortestWord.isEmpty()) {
        return text; // Якщо текст порожній або слова не знайдено, повертаємо текст без змін
    }

    QString replacedText = text;
    replacedText.replace(longestWord, "TEMP_PLACEHOLDER");
    replacedText.replace(shortestWord, longestWord);
    replacedText.replace("TEMP_PLACEHOLDER", shortestWord);

    return replacedText;
}





// Перевантаження оператора присвоєння
WordReplacer& WordReplacer::operator=(const WordReplacer& other) {
    if (this != &other) {
        text = other.text;
    }
    return *this;
}

// Перевантаження оператора виведення
std::ostream& operator<<(std::ostream& os, const WordReplacer& replacer) {
    os << "Text: " << replacer.text.toStdString();
    return os;
}
