#include "Triangle_1.h"
#include "CommonUtils.h"
#include "lcTexture2D.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>

Triangle_1::Triangle_1(QOpenGLFunctions_4_5_Core *function, QObject *parent)
    : QObject(parent)
    , mp_GlFuncs(function)
    , mp_Shader(nullptr)
    , mp_TextureA(nullptr)
    , m_VAO(0)
    , m_EBO(0)
{
    init();
}

void Triangle_1::render()
{
    mp_Shader->bind();
    mp_TextureA->bind(0);
    mp_Shader->setUniformValue("samplerA",0);
    mp_GlFuncs->glBindVertexArray(m_VAO);
    mp_GlFuncs->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);  // 使用 EBO 绘制三角形
    mp_GlFuncs->glBindVertexArray(0);
    mp_Shader->release();
}

void Triangle_1::cleanup()
{
    // 清理 OpenGL 资源
    mp_GlFuncs->glDeleteVertexArrays(1, &m_VAO);
    mp_GlFuncs->glDeleteBuffers(1, &m_VAO);
    mp_GlFuncs->glDeleteBuffers(1, &m_VAO);
}

void Triangle_1::init()
{
    // 初始化着色器
    initShader();
    //  初始化纹理
    initTexture();

    // 准备顶点数据
    // 顶点数据：位置 (x,y,z) + UV 坐标 (u,v)（共4个顶点）
    float vertices[] = {
        -0.7f, -0.7f, 0.0f,  0.0f, 0.0f, // 左下角 (索引0)
         0.7f, -0.7f, 0.0f,  2.0f, 0.0f, // 右下角 (索引1)
         0.7f,  0.7f, 0.0f,  2.0f, 2.0f, // 右上角 (索引2)
        -0.7f,  0.7f, 0.0f,  0.0f, 2.0f  // 左上角 (索引3)
    };

    // 索引数据（定义两个三角形）
    unsigned int indices[] = {
        0, 1, 2, // 第一个三角形（左下→右下→右上）
        2, 3, 0  // 第二个三角形（右上→左上→左下）
    };

    // 1. 创建并绑定 VBO，并将顶点数据上传到显存
    GLuint vertexVBO;
    mp_GlFuncs->glGenBuffers(1, &vertexVBO); // 创建vbo
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertexVBO); // 绑定vbo
    mp_GlFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将顶点数据上传

    // 2. 创建并绑定 VAO
    mp_GlFuncs->glGenVertexArrays(1, &m_VAO);
    mp_GlFuncs->glBindVertexArray(m_VAO);

    // 3. 创建并绑定 EBO
    mp_GlFuncs->glGenBuffers(1, &m_EBO);
    mp_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    mp_GlFuncs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. 绑定 VBO 到 VAO
    // 4.1 启用位置属性 ，也就是加入位置属性描述信息
    int positionLocation = mp_Shader->attributeLocation(QString("inPosition"));
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    mp_GlFuncs->glEnableVertexAttribArray(positionLocation);
    mp_GlFuncs->glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

    int uvLocation = mp_Shader->attributeLocation(QString("inUV"));
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    mp_GlFuncs->glEnableVertexAttribArray(uvLocation);
    mp_GlFuncs->glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    // 4.3 加入 EBO 到 VAO ，也就是加入位置属性描述信息
    mp_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    // 5. 清理工作
    // 解绑 VAO 和 VBO
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    mp_GlFuncs->glBindVertexArray(0);
}

void Triangle_1::initShader()
{
    QString vertexShaderCode = CommonUtils::loadFile(":/shaders/vertexShader02.glsl");
    QString fragmentShaderCode = CommonUtils::loadFile(":/shaders/fragmentShader01.glsl");
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

void Triangle_1::initTexture()
{
    mp_TextureA = new lcTexture2D(mp_GlFuncs, QString(":/textures/longbb.jpg"));
    mp_TextureA->bind(0);
}
