cmake_minimum_required(VERSION 3.16)

# Назва проекту
project(Kursova_OOP VERSION 1.0 LANGUAGES CXX)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Вказуємо шлях до Qt6
set(Qt6_DIR "/Users/kirilltm04/Qt/6.8.0/macos/lib/cmake/Qt6")

# Знаходимо пакети Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Автоматично обробляємо moc, uic, rcc для Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Додаємо директорії, де шукати заголовки
include_directories(${CMAKE_SOURCE_DIR})

# Додаємо джерела
set(SOURCES
        main.cpp
        mainwindow.cpp
        textanalyzer.cpp
        charreplacer.cpp
        wordreplacer.cpp
        textconverter.cpp
        sentencecounter.cpp
        digitcounter.cpp
        alphabetanalyzer.cpp
        )

set(HEADERS
        mainwindow.h
        textanalyzer.h
        charreplacer.h
        wordreplacer.h
        textconverter.h
        sentencecounter.h
        digitcounter.h
        alphabetanalyzer.h
        )

# Створюємо виконуваний файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Підключаємо необхідні модулі Qt
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
