#include "digitcounter.h"
#include <sstream>

// Конструктор за замовчуванням
DigitCounter::DigitCounter() : digitCount(0), digitDistribution{} {}

// Конструктор з параметрами
DigitCounter::DigitCounter(const std::string &text) : digitCount(0), digitDistribution{} {
    countDigits(text);
}

// Конструктор копіювання
DigitCounter::DigitCounter(const DigitCounter &other)
        : digitCount(other.digitCount), digitDistribution(other.digitDistribution) {}

// Метод встановлення тексту
void DigitCounter::setText(const std::string &text) {
    digitCount = 0;
    digitDistribution.fill(0); // Очищаємо попередні дані
    countDigits(text);
}

// Метод підрахунку цифр у тексті
void DigitCounter::countDigits(const std::string &text) {
    for (char ch : text) {
        if (ch >= '0' && ch <= '9') {
            ++digitCount;
            ++digitDistribution[ch - '0'];
        }
    }
}

// Отримання загальної кількості цифр
int DigitCounter::getDigitCount() const {
    return digitCount;
}

// Отримання розподілу цифр
const std::array<int, 10> &DigitCounter::getDigitDistribution() const {
    return digitDistribution;
}

// Аналіз цифр у вигляді рядка
std::string DigitCounter::getDigitAnalysis() const {
    if (digitCount == 0) {
        return "No digits found in the text.\n";
    }

    std::ostringstream result;
    result << "Загальна кількість цифр: " << digitCount << "\n";
    for (int i = 0; i < 10; ++i) {
        if (digitDistribution[i] > 0) {
            result << "Кількість цифр '" << i << "': " << digitDistribution[i] << "\n";
        }
    }
    return result.str();
}
