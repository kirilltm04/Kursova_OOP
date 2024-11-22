#include "sentencecounter.h"

// Конструктор за замовчуванням
SentenceCounter::SentenceCounter() : text(""), sentenceCount(0) {}

// Конструктор з параметрами
SentenceCounter::SentenceCounter(const std::string &inputText) : text(inputText), sentenceCount(0) {
    countSentences();
}

// Конструктор копіювання
SentenceCounter::SentenceCounter(const SentenceCounter &other)
        : text(other.text), sentenceCount(other.sentenceCount) {}

// Метод для підрахунку речень
void SentenceCounter::countSentences() {
    sentenceCount = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        char ch = text[i];
        if (ch == '.' || ch == '!' || ch == '?') {
            // Перевіряємо, чи це закінчення речення (останній символ або після нього пробіл чи новий рядок)
            if (i + 1 == text.size() || text[i + 1] == ' ' || text[i + 1] == '\n') {
                ++sentenceCount;
            }
        }
    }
}

// Метод для встановлення тексту
void SentenceCounter::setText(const std::string &newText) {
    text = newText;
    countSentences();
}

// Метод для отримання кількості речень
int SentenceCounter::getSentenceCount() const {
    return sentenceCount;
}

// Метод для отримання тексту
std::string SentenceCounter::getText() const {
    return text;
}
