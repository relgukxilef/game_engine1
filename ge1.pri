
SOURCE_ROOT = $$PWD/source
INCLUDE_ROOT = $$PWD/include/ge1

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$SOURCE_ROOT/editor/editor_camera.cpp \
    $$SOURCE_ROOT/opengl/pass.cpp \
    $$SOURCE_ROOT/opengl/composition.cpp \
    $$SOURCE_ROOT/opengl/program.cpp \
    $$SOURCE_ROOT/opengl/draw_call.cpp \
    $$SOURCE_ROOT/opengl/vertex_array.cpp \
    $$SOURCE_ROOT/opengl/framebuffer.cpp \
    $$SOURCE_ROOT/editor/backends/glfw.cpp

HEADERS += \
    $$INCLUDE_ROOT/geometry/primitives.h \
    $$INCLUDE_ROOT/pass.h \
    $$INCLUDE_ROOT/composition.h \
    $$INCLUDE_ROOT/program.h \
    $$INCLUDE_ROOT/draw_call.h \
    $$INCLUDE_ROOT/vertex_array.h \
    $$INCLUDE_ROOT/renderable.h \
    $$INCLUDE_ROOT/resources.h \
    $$INCLUDE_ROOT/span.h \
    $$INCLUDE_ROOT/framebuffer.h \
    $$INCLUDE_ROOT/editor/editor_camera.h \
    $$INCLUDE_ROOT/editor/editor_io.h \
    $$INCLUDE_ROOT/editor/backends/glfw.h
