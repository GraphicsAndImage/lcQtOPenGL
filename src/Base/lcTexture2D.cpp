#include "lcTexture2D.h"

#include <QString>
#include <QImage>

lcTexture2D::lcTexture2D(QOpenGLFunctions_4_5_Core *function, const QString &name)
    : m_IsValid(true)
    , m_ttObj(0)
    , mp_GlFuncs(function)
{
    // 第一步：先读取图片
    QImage image(name);
    if(image.isNull()) {
        m_IsValid = false;
        return;
    }

    // 第二步：转换图片格式，并垂直翻转
    QImage glImage = image.convertToFormat(QImage::Format_RGBA8888);
    if(glImage.isNull()) {
        m_IsValid = false;
        return;
    }
    glImage = glImage.mirrored(false, true);  // 参数 (false, true) 表示不水平翻转但垂直翻转

    // 第三步：生成纹理对象，激活纹理单元，绑定纹理单元，绑定纹理对象
    mp_GlFuncs->glGenTextures(1, &m_ttObj); // 生成纹理对象
    mp_GlFuncs->glActiveTexture(GL_TEXTURE0); // 激活纹理单元
    /*
     * 注意下面这一句的作用：
     *  1. 绑定纹理对象到GL状态机的对应卡槽上（ GL_TEXTURE_2D卡槽 ）
     *  2. 绑定纹理对象到上面（上次）激活的纹理单元上（默认纹理单元0）
    */
    mp_GlFuncs->glBindTexture(GL_TEXTURE_2D, m_ttObj);

    // 第四步：将纹理图片数据上传到显存（此时才在显存上开辟存储空间）
    /*
     * glTexImage2D 参数说明：target, level, internalformat, width, height, border, format, type, pixels
     *  target : 数据通过哪个卡槽上传到显存
     *  level : 纹理的详细级别 (mipmap 级别)
     *  internalformat : GPU 中存储纹理数据的格式（ RGB RGBA 等）
     *  width : 纹理的宽度
     *  height : 纹理的高度
     *  border : 边框宽度 (必须为 0)
     *  format : 原始图像数据的格式（ RGB RGBA 等）
     *  type : 原始图像数据的数据类型，或者说每个通道的数据类型（ 比如 0 ~ 255 是 GL_UNSIGNED_BYTE）
     *  pixels : 图像的数据，其实就是一个 char*
    */
    mp_GlFuncs->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glImage.width(), glImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glImage.bits());


    // 第五步：设置纹理的过滤方式
    mp_GlFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    mp_GlFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // 第六步：设置纹理的包裹方式
    // 设置边框颜色
    GLfloat borderColor[] = {1.0f, 0.0f, 0.0f, 1.0f}; // 红色边框
    mp_GlFuncs->glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    mp_GlFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    mp_GlFuncs->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // 至此，纹理图像数据上传到了 显存，而它的纹理对象是 m_ttObj
}

lcTexture2D::~lcTexture2D()
{
    if (m_ttObj != 0) {
        mp_GlFuncs->glDeleteTextures(1, &m_ttObj);
    }
}

void lcTexture2D::bind(GLenum unit) const
{
    mp_GlFuncs->glActiveTexture(GL_TEXTURE0 + unit);
    mp_GlFuncs->glBindTexture(GL_TEXTURE_2D, m_ttObj);
}

void lcTexture2D::release()
{
    mp_GlFuncs->glBindTexture(GL_TEXTURE_2D, 0);
}
