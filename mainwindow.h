#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "textanalyzer.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void refreshText();
    void loadFromFile();
    void saveToFile();
    void detectLanguageStats();
    void convertCyrToLat();
    void convertLatToCyr();
    void countDigits();
    void replaceCharacter();
    void analyzeSentences();
    void findAndSwapWords();
    void findLongestWord();
    void findShortestWord();

private:
    QTextEdit *inputText;
    QTextEdit *outputText;

    QPushButton *loadFileButton;
    QPushButton *saveFileButton;

    QPushButton *detectLangButton;
    QPushButton *convertCyrToLatButton;
    QPushButton *convertLatToCyrButton;
    QPushButton *countDigitsButton;
    QPushButton *replaceCharacterButton;
    QPushButton *analyzeSentencesButton;
    QPushButton *findSwapWordsButton;
    QPushButton *findLongestWordButton;
    QPushButton *findShortestWordButton;
    QPushButton *refreshTextButton;


    QLabel *infoLabel;
    QLineEdit *oldCharInput;
    QLineEdit *newCharInput;

    TextAnalyzer textAnalyzer;
};

#endif // MAINWINDOW_H
