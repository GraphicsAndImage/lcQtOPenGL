#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QObject>

class QOpenGLFunctions_4_5_Core;
class lcTexture2D;

class Triangle : public QObject
{
    Q_OBJECT
public:
    Triangle(QOpenGLFunctions_4_5_Core *function, QObject *parent = nullptr);
    void render();
    void cleanup();
private:
    void init(QOpenGLFunctions_4_5_Core *function);
    void initShader();
    void initTexture();
private:
    QOpenGLFunctions_4_5_Core   *mp_GlFuncs;
    QOpenGLShaderProgram        *mp_Shader;
    lcTexture2D                 *mp_TextureA;
    lcTexture2D                 *mp_TextureB;
    lcTexture2D                 *mp_TextureC;
    GLuint                      m_VAO;
    GLuint                      m_EBO;
};

#endif // TRIANGLE_H
