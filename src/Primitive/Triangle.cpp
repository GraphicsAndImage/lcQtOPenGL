#include "Triangle.h"

#include <QOpenGLFunctions_4_5_Core>

Triangle::Triangle(QOpenGLFunctions_4_5_Core *function)
    : mp_GlFuncs(function)
    , m_VAO(0)
    , m_VBO(0)
    , m_EBO(0)
{
    // 创建顶点数据（4个顶点：矩形的4个角）
    GLfloat vertices[] = {
        // 顶点位置 (x, y, z)
        -0.5f,  -0.5f, 0.0f,   // 顶点 1 (左上)
        0.5f,  -0.5f, 0.0f,   // 顶点 2 (右上)
        0.0f, 0.5f, 0.0f,   // 顶点 3 (左下)
        0.5f, 0.5f, 0.0f    // 顶点 4 (右下)
    };

    // 创建索引数据（使用 EBO 来绘制 2 个三角形形成矩形）
    GLuint indices[] = {
        0, 1, 2,  // 第一个三角形
        2, 1, 3   // 第二个三角形
    };

    // 1. 创建并绑定 VBO
    mp_GlFuncs->glGenBuffers(1, &m_VBO);
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    mp_GlFuncs->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 2. 创建并绑定 EBO
    mp_GlFuncs->glGenBuffers(1, &m_EBO);
    mp_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    mp_GlFuncs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 3. 创建并绑定 VAO
    mp_GlFuncs->glGenVertexArrays(1, &m_VAO);
    mp_GlFuncs->glBindVertexArray(m_VAO);

    // 4. 绑定 VBO EBO 到 VAO
    // 4.1 加入 VBO 到 VAO ，也就是加入位置属性描述信息
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    mp_GlFuncs->glEnableVertexAttribArray(0);
    mp_GlFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    // 4.2 加入 EBO 到 VAO ，也就是加入位置属性描述信息
    mp_GlFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    // 5. 清理工作
    // 解绑 VAO 和 VBO
    mp_GlFuncs->glBindBuffer(GL_ARRAY_BUFFER, 0);
    mp_GlFuncs->glBindVertexArray(0);
}

void Triangle::render()
{
    // 绑定 VAO 并绘制三角形
    mp_GlFuncs->glBindVertexArray(m_VAO);
    mp_GlFuncs->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);  // 使用 EBO 绘制三角形
    mp_GlFuncs->glBindVertexArray(0);
}

void Triangle::cleanup()
{
    // 清理 OpenGL 资源
    mp_GlFuncs->glDeleteVertexArrays(1, &m_VAO);
    mp_GlFuncs->glDeleteBuffers(1, &m_VAO);
    mp_GlFuncs->glDeleteBuffers(1, &m_VAO);
}
