#ifndef LCTEXTURE2D_H
#define LCTEXTURE2D_H

#include <QOpenGLFunctions_4_5_Core>

class QString;
class QOpenGLFunctions_4_5_Core;

class lcTexture2D
{
public:
    lcTexture2D(QOpenGLFunctions_4_5_Core *function, const QString &name);
    ~lcTexture2D();
    // 禁用拷贝和赋值
    lcTexture2D(const lcTexture2D&) = delete;
    lcTexture2D& operator=(const lcTexture2D&) = delete;

    void bind(GLenum unit = 0) const;
    void release();
private:
    bool                        m_IsValid;
    GLuint                      m_ttObj;
    QOpenGLFunctions_4_5_Core   *mp_GlFuncs;
};

#endif // LCTEXTURE2D_H
