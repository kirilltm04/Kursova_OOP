#ifndef ALPHABETANALYZER_H
#define ALPHABETANALYZER_H

#include <string>
#include <iostream>

class AlphabetAnalyzer {
private:
    int latinCount;      // Кількість латинських літер
    int cyrillicCount;   // Кількість кириличних літер

    void analyzeText(const std::string &text); // Аналіз тексту

public:
    AlphabetAnalyzer(); // Конструктор за замовчуванням
    explicit AlphabetAnalyzer(const std::string &text); // Конструктор з параметрами
    AlphabetAnalyzer(const AlphabetAnalyzer &other); // Конструктор копіювання

    void setText(const std::string &text);

    [[nodiscard]] int getLatinCount() const;
    [[nodiscard]] int getCyrillicCount() const;
    [[nodiscard]] double getLatinPercentage() const;
    [[nodiscard]] double getCyrillicPercentage() const;
    [[nodiscard]] std::string getResult() const;

};

#endif // ALPHABETANALYZER_H
