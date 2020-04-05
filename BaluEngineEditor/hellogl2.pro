HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                logo.h \
    dialog.h \
    form.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                logo.cpp \
    dialog.cpp \
    form.cpp

QT           += widgets

# install
target.path = $$PWD/build/installed
INSTALLS += target

INCLUDEPATH += "$$PWD/../BaluEngine/include"
INCLUDEPATH += "$$PWD/../BaluEngine/submodules/BaluRender/BaluLib/Include"

debug {
    win32:LIBS += $$quote($$PWD/../BaluEngine/Output/Debug/BaluEngine.lib)
}
release {
    win32:LIBS += $$quote($$PWD/../BaluEngine/Output/Release/BaluEngine.lib)
}

FORMS += \
    dialog.ui \
    form.ui
