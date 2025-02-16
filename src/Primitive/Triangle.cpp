#include "Triangle.h"
#include "lcTexture2D.h"
#include "CommonUtils.h"

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QRandomGenerator>
#include <QImage>


Triangle::Triangle(QOpenGLFunctions_4_5_Core *function, QObject *parent)
    : QObject(parent)
    , mp_GlFuncs(function)
    , mp_Shader(nullptr)
    , mp_TextureA(nullptr)
    , mp_TextureB(nullptr)
    , mp_TextureC(nullptr)
    , m_VAO(0)
    , m_EBO(0)
{
    init(function);

    // 创建顶点数据（4个顶点：矩形的4个角）
    GLfloat vertices[] = {
        // 顶点位置 (x, y, z)
        -0.5f,   0.5f, 0.0f,   // 顶点 1 (左上)
         0.5f,   0.5f, 0.0f,   // 顶点 2 (右上)
        -0.5f,  -0.5f, 0.0f,   // 顶点 3 (左下)
         0.5f,  -0.5f, 0.0f    // 顶点 4 (右下)
    };

    GLfloat uvs[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };

    GLfloat colors[] = {
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    // 创建索引数据（使用 EBO 来绘制 2 个三角形形成矩形）
    GLuint indices[] = {
        0, 2, 3,  // 第一个三角形
        3, 1, 0   // 第二个三角形
    };

    // 1. 创建并绑定 VBO
    GLuint vertexVBO;
    mp_GlFuncs->glGenBuffers(1, &vertexVBO);
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    mp_GlFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint colorVBO;
    mp_GlFuncs->glGenBuffers(1, &colorVBO);
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    mp_GlFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint uvVBO;
    mp_GlFuncs->glGenBuffers(1, &uvVBO);
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    mp_GlFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    // 3. 创建并绑定 VAO
    mp_GlFuncs->glGenVertexArrays(1, &m_VAO);
    mp_GlFuncs->glBindVertexArray(m_VAO);

    // 2. 创建并绑定 EBO
    mp_GlFuncs->glGenBuffers(1, &m_EBO);
    mp_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    mp_GlFuncs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. 绑定 VBO EBO 到 VAO
    // 4.1 加入 vertexVBO 到 VAO ，也就是加入位置属性描述信息
    int positionLocation = mp_Shader->attributeLocation(QString("inPosition"));
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    mp_GlFuncs->glEnableVertexAttribArray(positionLocation);
    mp_GlFuncs->glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 4.2 加入 colorVBO 到 VAO ，也就是加入颜色属性描述信息
    // int colorLocation = mp_Shader->attributeLocation(QString("inColor"));
    // mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    // mp_GlFuncs->glEnableVertexAttribArray(colorLocation);
    // mp_GlFuncs->glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 4.3 加入 uvVBO 到 VAO ，也就是uv坐标属性描述信息
    int uvLocation = mp_Shader->attributeLocation(QString("inUV"));
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    mp_GlFuncs->glEnableVertexAttribArray(uvLocation);
    mp_GlFuncs->glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

    // 4.3 加入 EBO 到 VAO ，也就是加入位置属性描述信息
    //mp_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    // 5. 清理工作
    // 解绑 VAO 和 VBO
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    mp_GlFuncs->glBindVertexArray(0);
}

void Triangle::render()
{
    // 绑定 VAO 并绘制三角形
    mp_Shader->bind();
    mp_TextureA->bind(0);
    mp_TextureB->bind(1);
    mp_TextureC->bind(2);
    mp_Shader->setUniformValue("samplerA",0);
    mp_Shader->setUniformValue("samplerB",1);
    mp_Shader->setUniformValue("samplerC",2);
    mp_GlFuncs->glBindVertexArray(m_VAO);
    mp_GlFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);  // 使用 EBO 绘制三角形
    mp_GlFuncs->glBindVertexArray(0);
    mp_Shader->release();
}

void Triangle::cleanup()
{
    // 清理 OpenGL 资源
    mp_GlFuncs->glDeleteVertexArrays(1, &m_VAO);
    mp_GlFuncs->glDeleteBuffers(1, &m_VAO);
    mp_GlFuncs->glDeleteBuffers(1, &m_VAO);
}

void Triangle::init(QOpenGLFunctions_4_5_Core *function)
{
    initShader();
    initTexture();
}

void Triangle::initShader()
{
    QString vertexShaderCode = CommonUtils::loadFile(":/shaders/vertexShader02.glsl");
    QString fragmentShaderCode = CommonUtils::loadFile(":/shaders/fragmentShader02.glsl");
    if (vertexShaderCode.isEmpty() || fragmentShaderCode.isEmpty()) {
        return;
    }

    mp_Shader = new QOpenGLShaderProgram(this);
    if (!mp_Shader->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderCode)) {
        return;
    }
    if (!mp_Shader->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderCode)) {
        return;
    }
    if (!mp_Shader->link()) {
        return;
    }

    mp_Shader->bind();
}

void Triangle::initTexture()
{
    mp_TextureA = new lcTexture2D(mp_GlFuncs, QString(":/textures/grass1.jpg"));
    mp_TextureA->bind(0);

    mp_TextureB = new lcTexture2D(mp_GlFuncs, QString(":/textures/ground.jpg"));
    mp_TextureB->bind(1);

    mp_TextureC = new lcTexture2D(mp_GlFuncs, QString(":/textures/longbb.jpg"));
    mp_TextureC->bind(2);
}
