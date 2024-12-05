#include "LCOpenGLWidget.h"
#include "Triangle.h"
#include "TriangleQt.h"

#include <QFile>

LCOpenGLWidget::LCOpenGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
    , mp_Shader(nullptr)
    , mp_Triangle(nullptr)
    , mp_TriangleQt(nullptr)
{
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

    // 初始化着色器
    mp_Shader = initShaderProgram();

    // 创建三角形
    mp_Triangle = new Triangle(this);
    mp_TriangleQt = new TriangleQt(this, mp_Shader);
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

    mp_Shader->bind();
    mp_Triangle->render();
    mp_TriangleQt->render();
    mp_Shader->release();
}

QOpenGLShaderProgram* LCOpenGLWidget::initShaderProgram()
{
    QString vertexShaderCode = readGlsl(":/glsl/vertexShader.glsl");
    QString fragmentShaderCode = readGlsl(":/glsl/fragmentShader.glsl");
    if (vertexShaderCode.isEmpty() || fragmentShaderCode.isEmpty()) {
        return nullptr;
    }

    QOpenGLShaderProgram *shaderProgram = new QOpenGLShaderProgram(this);
    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCode)) {
        return nullptr;
    }
    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCode)) {
        return nullptr;
    }
    if (!shaderProgram->link()) {
        return nullptr;
    }

    shaderProgram->bind();
    return shaderProgram;
}

QString LCOpenGLWidget::readGlsl(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();  // 如果文件无法打开，直接返回空字符串
    }

    QTextStream in(&file);
    return in.readAll();  // 直接返回文本内容，无需使用 std::move
}


