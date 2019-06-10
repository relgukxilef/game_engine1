
SOURCE_ROOT = $$PWD/source
INCLUDE_ROOT = $$PWD/include/ge1

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$SOURCE_ROOT/pass.cpp \
    $$SOURCE_ROOT/composition.cpp \
    $$SOURCE_ROOT/program.cpp \
    $$SOURCE_ROOT/draw_call.cpp \
    $$SOURCE_ROOT/vertex_array.cpp

HEADERS += \
    $$INCLUDE_ROOT/geometry/primitives.h \
    $$INCLUDE_ROOT/pass.h \
    $$INCLUDE_ROOT/composition.h \
    $$INCLUDE_ROOT/program.h \
    $$INCLUDE_ROOT/draw_call.h \
    $$INCLUDE_ROOT/vertex_array.h \
    $$INCLUDE_ROOT/renderable.h \
    $$INCLUDE_ROOT/resources.h \
    $$INCLUDE_ROOT/span.h
