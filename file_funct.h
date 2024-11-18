#ifndef FILE_FUNCT_H
#define FILE_FUNCT_H

#include <QString>

bool createFile(QString& filePath);
bool openFile(QString& filePath, QString& content);
bool saveFile(const QString& filePath, const QString& content);

#endif // FILE_FUNCT_H
