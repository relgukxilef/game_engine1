TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += object_parallel_to_source

DEFINES += GLEW_STATIC

LIBS += -lglfw3dll -lglew32s -lopengl32

SOURCES += \
	main.cpp \
    pass.cpp \
    composition.cpp \
    program.cpp \
    draw_call.cpp \
    vertex_array.cpp

HEADERS += \
    pass.h \
    composition.h \
    renderable.h \
    program.h \
    vertex_array.h \
    resources.h \
    vertex_attribute_struct.h \
    draw_call.h \
	typed/interfaces.h \
    typed/primitive_types.h \
    typed/glm_types.h \
    span.h

DISTFILES += \
    shaders/solid.fs \
    shaders/solid.vs \
    shaders/utils.fs
