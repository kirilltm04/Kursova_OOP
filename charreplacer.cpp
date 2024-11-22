#include "charreplacer.h"
#include <iostream>

// Конструктор за замовчуванням
CharReplacer::CharReplacer()
        : text(""), oldChar(""), newChar("") {
}

// Конструктор з параметрами
CharReplacer::CharReplacer(const QString& text, const QString& oldChar, const QString& newChar)
        : text(text), oldChar(oldChar), newChar(newChar) {
}

// Конструктор копій
CharReplacer::CharReplacer(const CharReplacer& other)
        : text(other.text), oldChar(other.oldChar), newChar(other.newChar) {
}

// Деструктор
CharReplacer::~CharReplacer() {
    // Не потребує спеціальної реалізації
}

// Геттери
QString CharReplacer::getText() const {
    return text;
}

QString CharReplacer::getOldChar() const {
    return oldChar;
}

QString CharReplacer::getNewChar() const {
    return newChar;
}

// Сеттери
void CharReplacer::setText(const QString& text) {
    this->text = text;
}

void CharReplacer::setOldChar(const QString& oldChar) {
    this->oldChar = oldChar;
}

void CharReplacer::setNewChar(const QString& newChar) {
    this->newChar = newChar;
}

// Метод для заміни символів у тексті
QString CharReplacer::replaceText() {
    return text.replace(oldChar, newChar);
}

// Статичний метод для заміни символів
QString CharReplacer::replace(const QString& text, const QString& oldChar, const QString& newChar) {
    return QString(text).replace(oldChar, newChar);
}

// Перевантаження оператора виведення
std::ostream& operator<<(std::ostream& os, const CharReplacer& replacer) {
    os << "Text: " << replacer.text.toStdString()
       << ", OldChar: " << replacer.oldChar.toStdString()
       << ", NewChar: " << replacer.newChar.toStdString();
    return os;
}
