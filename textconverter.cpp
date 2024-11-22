#include "TextConverter.h"

// Конструктор за замовчуванням
TextConverter::TextConverter() : text("") {
    initializeMaps();
}

// Конструктор з параметрами
TextConverter::TextConverter(const QString& inputText) : text(inputText) {
    initializeMaps();
}

// Конструктор копіювання
TextConverter::TextConverter(const TextConverter& other) : text(other.text), cyrToLatMap(other.cyrToLatMap), latToCyrMap(other.latToCyrMap) {}

// Ініціалізація карт для конвертації
QString TextConverter::convertLatToCyr(QString text) const {
    QString result;
    int i = 0;

    while (i < text.size()) {
        // Обробка багатосимвольних комбінацій, починаючи з найдовших
        if (i + 3 <= text.size() && text.mid(i, 3) == "shch") {
            result += QChar(u'щ');
            i += 3;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "zh") {
            result += QChar(u'ж');
            i += 2;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "sh") {
            result += QChar(u'ш');
            i += 2;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "ch") {
            result += QChar(u'ч');
            i += 2;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "kh") {
            result += QChar(u'х');
            i += 2;
        }
        else if (i + 3 <= text.size() && text.mid(i, 3) == "Shch") {
            result += QChar(u'Щ');
            i += 3;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "Zh") {
            result += QChar(u'Ж');
            i += 2;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "Sh") {
            result += QChar(u'Ш');
            i += 2;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "Ch") {
            result += QChar(u'Ч');
            i += 2;
        } else if (i + 2 <= text.size() && text.mid(i, 2) == "Kh") {
            result += QChar(u'Х');
            i += 2;
        }
        else if (i + 2 <= text.size() && text.mid(i, 2) == "Th") {
            result += QChar(u'З');
            i += 2;
        }
        else if (i + 2 <= text.size() && text.mid(i, 2) == "th") {
            result += QChar(u'з');
            i += 2;
        }
        else if (i + 1 <= text.size() && text.mid(i, 1) == "x") {  // Обробка літери "x" як "кс"
            result += QChar(u'к');
            result += QChar(u'с');
            i += 1;
        }
        else if (i + 1 <= text.size() && text.mid(i, 1) == "X") {  // Обробка літери "x" як "кс"
            result += QChar(u'К');
            result += QChar(u'с');
            i += 1;
        }
        else {
            // Якщо це не комбінація, перевіряємо окрему літеру через мапінг
            QString singleChar = text.mid(i, 1);
            if (latToCyrMap.contains(singleChar)) {
                result += latToCyrMap[singleChar];
            } else {
                result += singleChar; // Символ, який не знайдено, залишаємо без змін
            }
            ++i;
        }
    }

    return result;
}

QString TextConverter::convertCyrToLat(QString text) const {
    QString result;
    for (const QChar& ch : text) {
        if (cyrToLatMap.contains(ch)) {
            result += cyrToLatMap[ch];
        } else {
            result += ch; // Символ, який не знайдено, залишаємо без змін
        }
    }
    return result;
}

void TextConverter::initializeMaps() {
    // Мапінг для кирилиці → латиниці
    cyrToLatMap = {
            {QChar(u'А'), "A"}, {QChar(u'Б'), "B"}, {QChar(u'В'), "V"}, {QChar(u'Г'), "H"}, {QChar(u'Ґ'), "G"},
            {QChar(u'Д'), "D"}, {QChar(u'Е'), "E"}, {QChar(u'Є'), "Ye"}, {QChar(u'Ж'), "Zh"}, {QChar(u'З'), "Z"},
            {QChar(u'И'), "Y"}, {QChar(u'І'), "I"}, {QChar(u'Ї'), "Yi"}, {QChar(u'Й'), "Y"}, {QChar(u'К'), "K"},
            {QChar(u'Л'), "L"}, {QChar(u'М'), "M"}, {QChar(u'Н'), "N"}, {QChar(u'О'), "O"}, {QChar(u'П'), "P"},
            {QChar(u'Р'), "R"}, {QChar(u'С'), "S"}, {QChar(u'Т'), "T"}, {QChar(u'У'), "U"}, {QChar(u'Ф'), "F"},
            {QChar(u'Х'), "Kh"}, {QChar(u'Ц'), "Ts"}, {QChar(u'Ч'), "Ch"}, {QChar(u'Ш'), "Sh"}, {QChar(u'Щ'), "Shch"},
            {QChar(u'Ь'), "'"}, {QChar(u'Ю'), "Yu"}, {QChar(u'Я'), "Ya"},
            {QChar(u'а'), "a"}, {QChar(u'б'), "b"}, {QChar(u'в'), "v"}, {QChar(u'г'), "h"}, {QChar(u'ґ'), "g"},
            {QChar(u'д'), "d"}, {QChar(u'е'), "e"}, {QChar(u'є'), "ye"}, {QChar(u'ж'), "zh"}, {QChar(u'з'), "z"},
            {QChar(u'и'), "y"}, {QChar(u'і'), "i"}, {QChar(u'ї'), "yi"}, {QChar(u'й'), "y"}, {QChar(u'к'), "k"},
            {QChar(u'л'), "l"}, {QChar(u'м'), "m"}, {QChar(u'н'), "n"}, {QChar(u'о'), "o"}, {QChar(u'п'), "p"},
            {QChar(u'р'), "r"}, {QChar(u'с'), "s"}, {QChar(u'т'), "t"}, {QChar(u'у'), "u"}, {QChar(u'ф'), "f"},
            {QChar(u'х'), "kh"}, {QChar(u'ц'), "ts"}, {QChar(u'ч'), "ch"}, {QChar(u'ш'), "sh"}, {QChar(u'щ'), "shch"},
            {QChar(u'ь'), "'"}, {QChar(u'ю'), "yu"}, {QChar(u'я'), "ya"}
    };

    // Мапінг для латиниці → кирилиці
    latToCyrMap = {
            // Великі латинські літери
            {"A", QChar(u'А')}, {"B", QChar(u'Б')}, {"C", QChar(u'К')}, {"D", QChar(u'Д')}, {"E", QChar(u'Е')},
            {"F", QChar(u'Ф')}, {"G", QChar(u'Ґ')}, {"H", QChar(u'Г')}, {"I", QChar(u'І')}, {"J", QChar(u'Й')},
            {"K", QChar(u'К')}, {"L", QChar(u'Л')}, {"M", QChar(u'М')}, {"N", QChar(u'Н')}, {"O", QChar(u'О')},
            {"P", QChar(u'П')}, {"Q", QChar(u'К')}, {"R", QChar(u'Р')}, {"S", QChar(u'С')}, {"T", QChar(u'Т')},
            {"U", QChar(u'У')}, {"V", QChar(u'В')}, {"W", QChar(u'В')}, {"X", QChar(u'К')}, {"Y", QChar(u'И')},
            {"Z", QChar(u'З')},
            // Малі латинські літери
            {"a", QChar(u'а')}, {"b", QChar(u'б')}, {"c", QChar(u'к')}, {"d", QChar(u'д')}, {"e", QChar(u'е')},
            {"f", QChar(u'ф')}, {"g", QChar(u'ґ')}, {"h", QChar(u'г')}, {"i", QChar(u'і')}, {"j", QChar(u'й')},
            {"k", QChar(u'к')}, {"l", QChar(u'л')}, {"m", QChar(u'м')}, {"n", QChar(u'н')}, {"o", QChar(u'о')},
            {"p", QChar(u'п')}, {"q", QChar(u'к')}, {"r", QChar(u'р')}, {"s", QChar(u'с')}, {"t", QChar(u'т')},
            {"u", QChar(u'у')}, {"v", QChar(u'в')}, {"w", QChar(u'в')}, {"x", QChar(u'к')}, {"y", QChar(u'и')},
            {"z", QChar(u'з')}
    };


}

// Гетер для тексту
QString TextConverter::getText() const {
    return text;
}

// Сетер для тексту
void TextConverter::setText(const QString& newText) {
    text = newText;
}
