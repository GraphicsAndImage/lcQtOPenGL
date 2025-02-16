#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QObject>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QObject>

class QOpenGLFunctions_4_5_Core;
class QOpenGLShaderProgram;

class Primitive : public QObject
{
public:
    explicit Primitive(QOpenGLFunctions_4_5_Core *function, QObject *parent = nullptr);
    void render();
    void cleanup();
protected:
    void init(QOpenGLFunctions_4_5_Core *function);
    void initShader();
private:
    QOpenGLVertexArrayObject    m_VAO;                               // 顶点数组对象
    QOpenGLShaderProgram        *mp_Shader;
    QOpenGLFunctions_4_5_Core   *mp_GlFuncs;
    QOpenGLBuffer               m_VBO{QOpenGLBuffer::VertexBuffer};  // 顶点缓冲对象
    QOpenGLBuffer               m_EBO{QOpenGLBuffer::IndexBuffer};   // 索引缓冲对象
};

#endif // PRIMITIVE_H
