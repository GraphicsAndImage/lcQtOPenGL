#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QTextStream>

class CommonUtils
{
public:
    CommonUtils();

    /**
     * @brief loadFile : 加载一个文件
     * @param file : 文件名称
     * @return
     */
    static QString loadFile(const QString &file);
};

#endif // COMMONUTILS_H
