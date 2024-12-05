#ifndef LCOPENGLWIDGET_H
#define LCOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>

class Triangle;
class TriangleQt;

class LCOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
public:
    LCOpenGLWidget(QWidget *parent = nullptr);
    virtual ~LCOpenGLWidget();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    /**
     * @brief initShaderProgram : 读取Shader程序
     */
    QOpenGLShaderProgram *initShaderProgram();

    /**
     * @brief readGlsl : 读取glsl文件
     * @param fileName : glsl 文件
     * @return 返回文本
     */
    QString readGlsl(const QString &fileName);

private:
    QOpenGLShaderProgram        *mp_Shader;
    Triangle                    *mp_Triangle;
    TriangleQt                  *mp_TriangleQt;
};

#endif // LCOPENGLWIDGET_H
