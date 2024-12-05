
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 系统第三方库
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)

# 下面定义了一个函数，获取dir目录下的所有子目录
# SUBDIRLIST 是函数名
# dirs 是返回值
# dir 传入参数
MACRO(SUBDIRLIST dirs dir)
  FILE(GLOB children RELATIVE ${dir} ${dir}/*)
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${dir}/${child})
      LIST(APPEND dirs ${child})
    ENDIF()
  ENDFOREACH()
ENDMACRO()

# 通过使用上面定义的函数，我们可以include_directories目录，这样在include的时候就不用包含路径了
SUBDIRLIST(dirs ${CMAKE_CURRENT_SOURCE_DIR})
foreach(dir ${dirs})
    message(************ ${dir})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${dir})
endforeach()

# 生成目标
file(GLOB_RECURSE GL_HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE GL_CPPS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
qt6_add_resources(GL_QRC ${CMAKE_SOURCE_DIR}/asset/resource.qrc)
qt_add_executable(${PROJECT_NAME}
    ${GL_QRC}
    ${GL_HDRS}
    ${GL_CPPS}
    Primitive/TriangleQt.h Primitive/TriangleQt.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

# 链接子项目库到主项目可执行文件
# target_link_libraries(TestGridUtils PRIVATE MyLibrary)
