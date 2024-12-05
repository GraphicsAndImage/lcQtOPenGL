#include "TriangleQt.h"


#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>

TriangleQt::TriangleQt(QOpenGLFunctions_4_5_Core *function, QOpenGLShaderProgram *shader)
    : m_VAO()
    , mp_Shader(shader)
    , mp_GlFuncs(function)
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
    m_VBO.create();
    m_VBO.bind();
    m_VBO.allocate(vertices, sizeof(vertices));  // 上传顶点数据

    // 2. 创建并绑定 EBO
    m_EBO.create();
    m_EBO.bind();
    m_EBO.allocate(indices, sizeof(indices));  // 上传索引数据

    // 3. 创建 VAO (顶点数组对象)
    m_VAO.create();
    m_VAO.bind();

    // 4. 绑定 VBO EBO 到 VAO
    // 4.1 加入 VBO 到 VAO ，也就是加入位置属性描述信息
    mp_Shader->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
    mp_Shader->enableAttributeArray(0);  // 启用第 0 个属性（顶点位置）
    // 4.2 加入 EBO 到 VAO ，也就是加入位置属性描述信息
    m_EBO.bind(); // 在 enableAttributeArray(0); 之后一定要绑定一下 EBO

    // 5. 清理工作
    // 解绑 VAO 和 VBO
    m_VAO.release();
    m_VBO.release();
    m_EBO.release();
}

void TriangleQt::render()
{
    m_VAO.bind();
    mp_GlFuncs->glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(int) * 3));
    // 6 ：绘制几个点
    // (void*)(sizeof(int) * 3) 从哪里开始绘制
    m_VAO.release();

    /*
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
        // 在没有使用 EBO 的情况下，直接传入 indices 也是可以的，但是每一帧都会将 indices 从 CPU 传到 GPU
    */
}

void TriangleQt::cleanup()
{
    m_VAO.release();
    m_VBO.release();
    m_EBO.release();
}
