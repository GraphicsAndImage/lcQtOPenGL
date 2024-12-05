#ifndef TRIANGLEQT_H
#define TRIANGLEQT_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLFunctions_4_5_Core;
class QOpenGLShaderProgram;

class TriangleQt
{
public:
    TriangleQt(QOpenGLFunctions_4_5_Core *function, QOpenGLShaderProgram *shader);
    void render();
    void cleanup();

private:
    QOpenGLVertexArrayObject    m_VAO;                               // 顶点数组对象
    QOpenGLShaderProgram        *mp_Shader;
    QOpenGLFunctions_4_5_Core   *mp_GlFuncs;
    QOpenGLBuffer               m_VBO{QOpenGLBuffer::VertexBuffer};  // 顶点缓冲对象
    QOpenGLBuffer               m_EBO{QOpenGLBuffer::IndexBuffer};   // 索引缓冲对象
};

#endif // TRIANGLEQT_H
