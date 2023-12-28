#ifndef MUSICINFO_H
#define MUSICINFO_H

#include "MyFile.h"
#include <QHash>
#include <QVector>

class MusicInfo
{
public:
    MusicInfo();
    MusicInfo(QList<Music> music_list);

    QList<Music> music_list;//音乐索引表

    QVector<QString> searchSinger(QString search_str);//前缀查找 找到所有符合要求的歌手名
    QVector<Music> searchMusic(QString search_str);//前缀查找 找到所有符合要求的歌曲名
    QList<Music>::iterator searchMusic_itr(QString search_str);
    int searchMusic_index(QString search_str);
    QVector<Music> getMusicBySinger(QString singer);


protected:
    void TableInit();

private:

    QHash<QString,QVector<QString>> singer_to_music_table;//歌手 ->音乐 表
    QHash<QString,QVector<QString>> inverted_index_table;//歌曲歌手分词->歌手 倒排索引表

    QList<Music> play_list;
};

#endif // MUSICINFO_H
