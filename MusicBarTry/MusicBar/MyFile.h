#ifndef MYFILE_H
#define MYFILE_H

#include <QDir>
#include <QList>
#include <QImage>
#include <QDebug>
#include <QVector>

struct Music
{
    QString name;//音乐名
    QVector<QString> singer_list;//歌手列表
//    QImage img;//专辑封面
    QString root_text;
};

class MyFile
{
public:
    MyFile();

    //将音源文件夹中的音乐信息读取到列表中
    static QList<Music> readAll();
};

#endif // MYFILE_H
