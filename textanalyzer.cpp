#include "textanalyzer.h"
#include <iomanip>
#include "charreplacer.h"
#include "wordreplacer.h"
#include "textconverter.h"
#include <QString>

// Конструктор за замовчуванням
TextAnalyzer::TextAnalyzer()
        : text(""), modifiedText(""),
          sentenceCounter(""), digitCounter(""), alphabetAnalyzer("") {}

// Конструктор з параметром
TextAnalyzer::TextAnalyzer(const std::string &inputText)
        : text(inputText), modifiedText(inputText),
          sentenceCounter(inputText), digitCounter(inputText), alphabetAnalyzer(inputText) {
    analyzeText();
}

// Конструктор копіювання
TextAnalyzer::TextAnalyzer(const TextAnalyzer &other)
        : text(other.text), modifiedText(other.modifiedText),
          sentenceCounter(other.sentenceCounter), digitCounter(other.digitCounter),
          alphabetAnalyzer(other.alphabetAnalyzer) {}

// Метод для оновлення всіх об'єктів аналізу
void TextAnalyzer::analyzeText() {
    sentenceCounter.setText(text);
    digitCounter.setText(text);
    alphabetAnalyzer.setText(text);
}

// Встановлення нового тексту
void TextAnalyzer::setText(const std::string &newText) {
    text = newText;
    modifiedText = newText;
    analyzeText();
}

// Отримання оригінального тексту
std::string TextAnalyzer::getText() const {
    return text;
}

// Отримання модифікованого тексту
std::string TextAnalyzer::getModifiedText() const {
    return modifiedText;
}

// Аналіз цифр
std::string TextAnalyzer::getDigitAnalysis() const {
    return digitCounter.getDigitAnalysis();
}

// Загальний аналіз тексту
std::string TextAnalyzer::getResult() const {
    std::ostringstream result;
    result << alphabetAnalyzer.getResult();
    return result.str();
}

// Кількість речень у тексті
int TextAnalyzer::getSentenceCount() const {
    return sentenceCounter.getSentenceCount();
}

// Перевизначення оператора вводу
std::istream &operator>>(std::istream &in, TextAnalyzer &analyzer) {
    std::ostringstream ss;
    ss << in.rdbuf(); // Читаємо весь потік
    analyzer.setText(ss.str());
    return in;
}

// Перевизначення оператора виводу
std::ostream &operator<<(std::ostream &out, const TextAnalyzer &analyzer) {
    out << "=== Звіт про аналіз тексту ===\n\n";

    // 1. Оригінальний текст
    out << "1) Оригінальний текст:\n" << analyzer.text << "\n\n";

    // 2. Визначення мови та статистика літер
    out << "2) Визначення мови та статистика літер:\n";
    out << analyzer.alphabetAnalyzer.getResult() << "\n";

    // 3. Транслітерація кирилиці → латиниця
    out << "3) Заміна кирилиці на латиницю:\n";
    out << analyzer.convertCyrToLat() << "\n\n";

    // 4. Транслітерація латиниці → кирилиця
    out << "4) Заміна латиниці на кирилицю:\n";
    out << analyzer.convertLatToCyr() << "\n\n";

    // 5. Аналіз цифр
    out << "5) Аналіз цифр:\n";
    out << analyzer.getDigitAnalysis() << "\n\n";

    // 6. Кількість речень
    out << "6) Кількість речень у тексті:\n";
    out << "Речень: " << analyzer.getSentenceCount() << "\n\n";

    // 7. Найкоротше слово
    out << "7) Найкоротше слово:\n";
    out << analyzer.findShortestWord() << "\n\n";

    // 8. Найдовше слово
    out << "8) Найдовше слово:\n";
    out << analyzer.findLongestWord() << "\n\n";

    // 9. Перестановка найдовшого та найкоротшого слова
    out << "9) Перестановка найдовшого та найкоротшого слова:\n";
    out << analyzer.replaceLongestAndShortestWords() << "\n";

    return out;
}


// Замінює символи у тексті
QString TextAnalyzer::replaceCharacter(const QString &oldChar, const QString &newChar) {
    if (oldChar.isEmpty() || newChar.isEmpty() || oldChar.size() > 1 || newChar.size() > 1) {
        throw std::invalid_argument("Кожне поле повинно містити лише один символ.");
    }

    QString qModifiedText = QString::fromStdString(modifiedText);
    CharReplacer replacer(qModifiedText, oldChar, newChar);
    qModifiedText = replacer.replaceText();
    modifiedText = qModifiedText.toStdString();
    return qModifiedText;
}

// Знаходження найдовшого слова
std::string TextAnalyzer::findLongestWord() const {
    QString qModifiedText = QString::fromStdString(modifiedText);
    WordReplacer replacer(qModifiedText);
    return replacer.findLongestWord().toStdString();
}

// Знаходження найкоротшого слова
std::string TextAnalyzer::findShortestWord() const {
    QString qModifiedText = QString::fromStdString(modifiedText);
    WordReplacer replacer(qModifiedText);
    return replacer.findShortestWord().toStdString();
}

// Замінює найдовше і найкоротше слово
std::string TextAnalyzer::replaceLongestAndShortestWords() const {
    QString qModifiedText = QString::fromStdString(modifiedText);
    WordReplacer replacer(qModifiedText);
    qModifiedText = replacer.replaceLongestAndShortestWords();
    return qModifiedText.toStdString(); // Повертаємо змінений текст без зміни стану об'єкта
}


// Транслітерація кирилиці → латиниця
std::string TextAnalyzer::convertCyrToLat() const {
    QString qModifiedText = QString::fromStdString(modifiedText);
    TextConverter converter;
    return converter.convertCyrToLat(qModifiedText).toStdString();
}

// Транслітерація латиниці → кирилиця
std::string TextAnalyzer::convertLatToCyr() const {
    QString qModifiedText = QString::fromStdString(modifiedText);
    TextConverter converter;
    return converter.convertLatToCyr(qModifiedText).toStdString();
}

// Створення звіту
void TextAnalyzer::generateReport(const std::string &filePath) const {
    std::ofstream reportFile(filePath); // Відкриваємо файл для запису
    if (!reportFile.is_open()) {
        throw std::runtime_error("Не вдалося створити файл звіту.");
    }

    reportFile << *this; // Використовуємо перевизначений оператор для запису всіх даних у файл

    reportFile.close(); // Закриваємо файл
}

