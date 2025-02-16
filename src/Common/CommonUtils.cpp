#include "CommonUtils.h"


CommonUtils::CommonUtils() {}

QString CommonUtils::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();  // 如果文件无法打开，直接返回空字符串
    }

    QTextStream in(&file);
    return in.readAll();  // 直接返回文本内容，无需使用 std::move
}
