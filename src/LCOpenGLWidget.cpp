#include "LCOpenGLWidget.h"
#include "Triangle.h"
#include "Triangle_1.h"

#include <QFile>
#include <QTimer>
#include <QObject>

LCOpenGLWidget::LCOpenGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
    , mp_Triangle(nullptr)
{
    // 定时器更新，每隔16ms触发一次（大约60FPS）
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&](){
        update();
    });
    timer->start(16); // 约每16ms更新一次，即每秒60帧
}

LCOpenGLWidget::~LCOpenGLWidget()
{

}

void LCOpenGLWidget::initializeGL()
{
    // 初始化opengl接口
    initializeOpenGLFunctions();

    // 设置清除颜色缓冲区时使用的颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // 创建三角形
    mp_Triangle = new Triangle_1(this);
}

void LCOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void LCOpenGLWidget::paintGL()
{
    // 实际执行清除操作，使用 glClearColor 设置的颜色清除颜色缓冲区。
    // GL_COLOR_BUFFER_BIT 是标志位，表示清除的是颜色缓冲区。
    glClear(GL_COLOR_BUFFER_BIT);
    mp_Triangle->render();
}


