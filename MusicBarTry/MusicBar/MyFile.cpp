#include "MyFile.h"

MyFile::MyFile()
{

}

QList<Music> MyFile::readAll()
{
    QList<Music> music_list;

    QString path = QDir::currentPath();
    path += "/music";
//    qDebug() << "here " << path;
    QDir dir(path);
    QStringList nameFilters;//筛选条件
    nameFilters << "*.mp3";

    QStringList musicStrList = dir.entryList(nameFilters);
    //music_list.resize(musicStrList.size());//设置音乐源大小

//    qDebug() << musicList;

    for(QString music_str : musicStrList)
    {
        Music music;
        //例 End Game - Taylor Swift&Ed Sheeran&Future
        music_str.remove(".mp3");

        music.root_text = music_str;

        QString split_1 = " - ";//歌名与歌手的分隔符
        QString split_2 = "&";//歌手之间的分隔符
        QStringList music_after_split1 = music_str.split(split_1);

        music.name = music_after_split1[0];
        music.singer_list = music_after_split1[1].split(split_2);

        qDebug() << music.name << " " << music.singer_list;

        music_list.push_back(music);
    }

    return music_list;
}
