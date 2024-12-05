#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLFunctions_4_5_Core;

class Triangle
{
public:
    Triangle(QOpenGLFunctions_4_5_Core *function);
    void render();
    void cleanup();
private:
    QOpenGLFunctions_4_5_Core   *mp_GlFuncs;
    GLuint                      m_VAO;
    GLuint                      m_VBO;
    GLuint                      m_EBO;
};

#endif // TRIANGLE_H
