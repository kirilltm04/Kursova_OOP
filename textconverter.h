#ifndef TEXTCONVERTER_H
#define TEXTCONVERTER_H

#include <QString>
#include <QMap>

class TextConverter {
private:
    QString text;
    QMap<QChar, QString> cyrToLatMap;
    QMap<QString, QChar> latToCyrMap;

    void initializeMaps(); // Ініціалізація карт для конвертації

public:
    // Конструктор за замовчуванням
    TextConverter();

    // Конструктор з параметрами
    explicit TextConverter(const QString& inputText);

    // Конструктор копіювання
    TextConverter(const TextConverter& other);

    // Метод для заміни кирилиці на латиницю
    QString convertCyrToLat(QString text_) const;

    // Метод для заміни латиниці на кирилицю
    QString convertLatToCyr(QString text_) const;

    // Гетер для тексту
    QString getText() const;

    // Сетер для тексту
    void setText(const QString& newText);
};

#endif // TEXTCONVERTER_H
