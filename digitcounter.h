#ifndef DIGITCOUNTER_H
#define DIGITCOUNTER_H

#include <string>
#include <array>

class DigitCounter {
private:
    int digitCount;                   // Загальна кількість цифр
    std::array<int, 10> digitDistribution; // Розподіл цифр (0-9)

    void countDigits(const std::string &text); // Підрахунок цифр у тексті

public:
    DigitCounter(); // Конструктор за замовчуванням
    explicit DigitCounter(const std::string &text); // Конструктор з параметрами
    DigitCounter(const DigitCounter &other); // Конструктор копіювання

    void setText(const std::string &text);

    [[nodiscard]] int getDigitCount() const;
    [[nodiscard]] const std::array<int, 10> &getDigitDistribution() const;
    [[nodiscard]] std::string getDigitAnalysis() const;
};

#endif // DIGITCOUNTER_H
