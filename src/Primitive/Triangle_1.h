#ifndef TRIANGLE_1_H
#define TRIANGLE_1_H

#include <QObject>
#include <QOpenGLVertexArrayObject>

class QOpenGLFunctions_4_5_Core;
class QOpenGLShaderProgram;
class lcTexture2D;

class Triangle_1 : public QObject
{
    Q_OBJECT
public:
    Triangle_1(QOpenGLFunctions_4_5_Core *function, QObject *parent = nullptr);
    void render();
    void cleanup();

private:
    void init();
    void initShader();
    void initTexture();

private:
    QOpenGLFunctions_4_5_Core   *mp_GlFuncs;
    QOpenGLShaderProgram        *mp_Shader;
    lcTexture2D                 *mp_TextureA;
    GLuint                      m_VAO;                              // 顶点数组对象
    GLuint                      m_EBO;                              // 顶点索引数据
};

#endif // TRIANGLE_1_H
