#ifndef CHARREPLACER_H
#define CHARREPLACER_H

#include <QString>

class CharReplacer {
private:
    QString text;
    QString oldChar; // Символ, який потрібно замінити
    QString newChar; // Символ, на який потрібно замінити

public:
    // Конструктор за замовчуванням
    CharReplacer();

    // Конструктор з параметрами
    CharReplacer(const QString& text, const QString& oldChar, const QString& newChar);

    // Конструктор копій
    CharReplacer(const CharReplacer& other);

    // Деструктор
    ~CharReplacer();

    // Геттери
    [[nodiscard]] QString getText() const;
    [[nodiscard]] QString getOldChar() const;
    [[nodiscard]] QString getNewChar() const;

    // Сеттери
    void setText(const QString& text);
    void setOldChar(const QString& oldChar);
    void setNewChar(const QString& newChar);

    // Метод для заміни символів у тексті
    QString replaceText();

    // Статичний метод для заміни символів
    static QString replace(const QString& text, const QString& oldChar, const QString& newChar);

    // Перевантаження оператора виведення
    friend std::ostream& operator<<(std::ostream& os, const CharReplacer& replacer);
};

#endif // CHARREPLACER_H
