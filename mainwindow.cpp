#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPalette>
#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Встановлення заголовку та розміру вікна
    this->setWindowTitle("Text Analyzer");
    this->resize(1800, 1000);

    // Стилізація основного вікна
    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#2C2F33")); // Темний фон
    palette.setColor(QPalette::WindowText, QColor("#FFFFFF")); // Світлий текст
    this->setPalette(palette);

    // Створення полів вводу та виводу
    inputText = new QTextEdit(this);
    inputText->setStyleSheet("background-color: #40444B; color: #DCDDDE; border: 1px solid #636B73; font-size: 14px;");
    outputText = new QTextEdit(this);
    outputText->setStyleSheet("background-color: #40444B; color: #DCDDDE; border: 1px solid #636B73; font-size: 14px;");
    outputText->setReadOnly(true);

    infoLabel = new QLabel("Інформація про текст буде відображена тут.", this);
    infoLabel->setFixedWidth(400);
    infoLabel->setFixedHeight(30);
    infoLabel->setStyleSheet("font-size: 14px; background-color: #40444B; color: #DCDDDE; padding: 5px; border: 1px solid #636B73; text-align: center;");

    // Створення основних кнопок
    loadFileButton = new QPushButton("Завантажити з файлу", this);
    detectLangButton = new QPushButton("Визначити писемність та статистику", this);
    convertCyrToLatButton = new QPushButton("Кирилиця → Латиниця", this);
    convertLatToCyrButton = new QPushButton("Латиниця → Кирилиця", this);
    countDigitsButton = new QPushButton("Кількість цифр", this);
    replaceCharacterButton = new QPushButton("Замінити символ", this);
    analyzeSentencesButton = new QPushButton("Кількість речень", this);
    findLongestWordButton = new QPushButton("Найдовше слово", this);
    findShortestWordButton = new QPushButton("Найкоротше слово", this);
    findSwapWordsButton = new QPushButton("Поміняти найдовше та найкоротше слово", this);
    saveFileButton = new QPushButton("Зберегти у файл", this);
    refreshTextButton = new QPushButton("Актуалізувати текст", this);


    // Стиль для кнопок
    QString buttonStyle = "QPushButton {"
                          "background-color: #5865F2;"
                          "color: #FFFFFF;"
                          "border-radius: 5px;"
                          "padding: 10px;"
                          "font-size: 14px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #4752C4;"
                          "}";

    loadFileButton->setStyleSheet(buttonStyle);
    detectLangButton->setStyleSheet(buttonStyle);
    convertCyrToLatButton->setStyleSheet(buttonStyle);
    convertLatToCyrButton->setStyleSheet(buttonStyle);
    countDigitsButton->setStyleSheet(buttonStyle);
    replaceCharacterButton->setStyleSheet(buttonStyle);
    analyzeSentencesButton->setStyleSheet(buttonStyle);
    findLongestWordButton->setStyleSheet(buttonStyle);
    findShortestWordButton->setStyleSheet(buttonStyle);
    findSwapWordsButton->setStyleSheet(buttonStyle);
    saveFileButton->setStyleSheet(buttonStyle);
    refreshTextButton->setStyleSheet(buttonStyle);

    // Поля вводу для заміни символів
    oldCharInput = new QLineEdit(this);
    oldCharInput->setPlaceholderText("Старий символ");
    newCharInput = new QLineEdit(this);
    newCharInput->setPlaceholderText("Новий символ");

    // Стиль для полів вводу
    oldCharInput->setStyleSheet("background-color: #40444B; color: #DCDDDE; border: 1px solid #636B73; padding: 5px; font-size: 14px;");
    newCharInput->setStyleSheet("background-color: #40444B; color: #DCDDDE; border: 1px solid #636B73; padding: 5px; font-size: 14px;");

    // Лівий макет для кнопок
    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(loadFileButton);
    leftLayout->addWidget(detectLangButton);
    leftLayout->addWidget(convertCyrToLatButton);
    leftLayout->addWidget(convertLatToCyrButton);
    leftLayout->addWidget(countDigitsButton);

    QHBoxLayout *replaceLayout = new QHBoxLayout();
    replaceLayout->addWidget(oldCharInput);
    replaceLayout->addWidget(newCharInput);
    replaceLayout->addWidget(replaceCharacterButton);
    leftLayout->addLayout(replaceLayout);

    leftLayout->addWidget(analyzeSentencesButton);
    leftLayout->addWidget(findLongestWordButton);
    leftLayout->addWidget(findShortestWordButton);
    leftLayout->addWidget(findSwapWordsButton);
    leftLayout->addWidget(saveFileButton);

    QVBoxLayout *refreshLayout = new QVBoxLayout();
    refreshLayout->addWidget(refreshTextButton);


    // Правий макет для текстових полів
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addLayout(refreshLayout);
    rightLayout->addWidget(new QLabel("Введіть текст:", this));
    rightLayout->addWidget(inputText);
    rightLayout->addWidget(new QLabel("Результат:", this));
    rightLayout->addWidget(outputText);


    // Основний горизонтальний макет
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout, 1);   // Ліва частина займає 1/3
    mainLayout->addLayout(rightLayout, 2); // Права частина займає 2/3

    // Створення центрального віджета
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Підключення сигналів до слотів
    connect(loadFileButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);
    connect(saveFileButton, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(detectLangButton, &QPushButton::clicked, this, &MainWindow::detectLanguageStats);
    connect(convertCyrToLatButton, &QPushButton::clicked, this, &MainWindow::convertCyrToLat);
    connect(convertLatToCyrButton, &QPushButton::clicked, this, &MainWindow::convertLatToCyr);
    connect(countDigitsButton, &QPushButton::clicked, this, &MainWindow::countDigits);
    connect(replaceCharacterButton, &QPushButton::clicked, this, &MainWindow::replaceCharacter);
    connect(analyzeSentencesButton, &QPushButton::clicked, this, &MainWindow::analyzeSentences);
    connect(findLongestWordButton, &QPushButton::clicked, this, &MainWindow::findLongestWord);
    connect(findShortestWordButton, &QPushButton::clicked, this, &MainWindow::findShortestWord);
    connect(findSwapWordsButton, &QPushButton::clicked, this, &MainWindow::findAndSwapWords);
    connect(refreshTextButton, &QPushButton::clicked, this, &MainWindow::refreshText);
}

void MainWindow::refreshText() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім для актуалізації.");
        return;
    }

    textAnalyzer.setText(text.toStdString());
    infoLabel->setText("Текст актуалізовано.");
    QMessageBox::information(this, "Успіх", "Текст успішно актуалізовано.");
}


void MainWindow::convertCyrToLat() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }
    textAnalyzer.setText(text.toStdString());
    QString convertedText = QString::fromStdString(textAnalyzer.convertCyrToLat());
    outputText->setText(convertedText);
    infoLabel->setText("Кирилиця успішно переконвертована у латиницю.");
}

void MainWindow::convertLatToCyr() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }
    textAnalyzer.setText(text.toStdString());
    QString convertedText = QString::fromStdString(textAnalyzer.convertLatToCyr());
    outputText->setText(convertedText);
    infoLabel->setText("Латиниця успішно переконвертована у кирилицю.");
}

void MainWindow::countDigits() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }
    textAnalyzer.setText(text.toStdString());
    QString result = QString::fromStdString(textAnalyzer.getDigitAnalysis());
    outputText->setText(result);
    infoLabel->setText("Підрахунок цифр завершено.");
}

void MainWindow::replaceCharacter() {
    QString oldChar = oldCharInput->text();
    QString newChar = newCharInput->text();

    if (oldChar.isEmpty() || newChar.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Введіть старий та новий символи.");
        return;
    }

    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }

    textAnalyzer.setText(text.toStdString());
    try {
        QString replacedText = textAnalyzer.replaceCharacter(oldChar, newChar);
        outputText->setText(replacedText);
        infoLabel->setText("Заміна символів виконана.");
    } catch (const std::invalid_argument &e) {
        QMessageBox::warning(this, "Помилка", e.what());
    }
}

void MainWindow::analyzeSentences() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }
    textAnalyzer.setText(text.toStdString());
    int sentenceCount = textAnalyzer.getSentenceCount();
    outputText->setText(QString("Кількість речень: %1").arg(sentenceCount));
    infoLabel->setText("Підрахунок речень завершено.");
}

void MainWindow::findAndSwapWords() {
    QString text = inputText->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }
    textAnalyzer.setText(text.toStdString());
    QString result = QString::fromStdString(textAnalyzer.replaceLongestAndShortestWords());
    outputText->setText(result);
    infoLabel->setText("Замінено найдовше та найкоротше слова.");
}

void MainWindow::detectLanguageStats() {
    // Отримуємо текст із поля вводу
    QString text = inputText->toPlainText();

    // Перевірка на порожній текст
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Поле вводу не може бути порожнім.");
        return;
    }

    // Використання TextAnalyzer для аналізу
    textAnalyzer.setText(text.toStdString());
    QString analysisResult = QString::fromStdString(textAnalyzer.getResult());

    // Виведення результату у вихідний текстовий редактор
    outputText->setText(analysisResult);
    infoLabel->setText("Аналіз тексту завершено.");
}


void MainWindow::loadFromFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Виберіть файл для завантаження", "", "Текстові файли (*.txt);;Усі файли (*.*)");
    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити файл.");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    inputText->setText(content);
    infoLabel->setText("Текст завантажено з файлу.");
}



void MainWindow::saveToFile() {
    QString filePath = QFileDialog::getSaveFileName(this, "Виберіть місце для збереження файлу", "", "Текстові файли (*.txt);;Усі файли (*.*)");
    if (filePath.isEmpty()) {
        return;
    }
    try {
        textAnalyzer.generateReport(filePath.toStdString());
        QMessageBox::information(this, "Успіх", "Звіт успішно створено!");
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Помилка", e.what());
    }
}


void MainWindow::findLongestWord() {
    QString longestWord = QString::fromStdString(textAnalyzer.findLongestWord());
    if (longestWord.isEmpty()) {
        QMessageBox::information(this, "Результат", "Не вдалося знайти найдовше слово.");
    } else {
        outputText->setText("Найдовше слово: " + longestWord);
        infoLabel->setText("Найдовше слово знайдено.");
    }
}

void MainWindow::findShortestWord() {
    QString shortestWord = QString::fromStdString(textAnalyzer.findShortestWord());
    if (shortestWord.isEmpty()) {
        QMessageBox::information(this, "Результат", "Не вдалося знайти найкоротше слово.");
    } else {
        outputText->setText("Найкоротше слово: " + shortestWord);
        infoLabel->setText("Найкоротше слово знайдено.");
    }
}
