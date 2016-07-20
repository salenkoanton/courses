LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-graphics -lsfml-main -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-graphics-d -lsfml-main-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include
SOURCES += \
    main.cpp

HEADERS += \
    dllmanager.h \
    main_ui.h \
    map.h \
    player.h \
    enums.h \
    list.h
