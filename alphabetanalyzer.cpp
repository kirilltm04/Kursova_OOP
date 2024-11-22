#include "alphabetanalyzer.h"
#include <sstream>
#include <iomanip>

// Конструктор за замовчуванням
AlphabetAnalyzer::AlphabetAnalyzer() : latinCount(0), cyrillicCount(0) {}

// Конструктор з параметрами
AlphabetAnalyzer::AlphabetAnalyzer(const std::string &text) : latinCount(0), cyrillicCount(0) {
    analyzeText(text);
}

// Конструктор копіювання
AlphabetAnalyzer::AlphabetAnalyzer(const AlphabetAnalyzer &other)
        : latinCount(other.latinCount), cyrillicCount(other.cyrillicCount) {}

// Метод встановлення тексту
void AlphabetAnalyzer::setText(const std::string &text) {
    latinCount = 0;
    cyrillicCount = 0;
    analyzeText(text);
}

// Метод аналізу тексту
void AlphabetAnalyzer::analyzeText(const std::string &text) {
    for (char ch : text) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            ++latinCount;
        } else if ((unsigned char)ch >= 0xC0 && (unsigned char)ch <= 0xFF) {
            ++cyrillicCount;
        }
    }
}

// Отримання кількості латинських літер
int AlphabetAnalyzer::getLatinCount() const {
    return latinCount;
}

// Отримання кількості кириличних літер
int AlphabetAnalyzer::getCyrillicCount() const {
    return cyrillicCount;
}

// Відсоток латинських літер
double AlphabetAnalyzer::getLatinPercentage() const {
    int totalLetters = latinCount + cyrillicCount;
    return (totalLetters > 0) ? (latinCount * 100.0 / totalLetters) : 0.0;
}

// Відсоток кириличних літер
double AlphabetAnalyzer::getCyrillicPercentage() const {
    int totalLetters = latinCount + cyrillicCount;
    return (totalLetters > 0) ? (cyrillicCount * 100.0 / totalLetters) : 0.0;
}

// Отримання результату як рядка
std::string AlphabetAnalyzer::getResult() const {
    std::ostringstream result;
    result << std::fixed << std::setprecision(2);
    result << "Кількість латинських літер: " << latinCount << " (" << getLatinPercentage() << "%)\n";
    result << "Кількість кириличних літер: " << cyrillicCount << " (" << getCyrillicPercentage() << "%)\n";
    return result.str();
}

