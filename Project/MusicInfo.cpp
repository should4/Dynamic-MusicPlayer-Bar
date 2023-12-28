#include "MusicInfo.h"

MusicInfo::MusicInfo()
{

}

MusicInfo::MusicInfo(QList<Music> music_list)
{
    this->music_list = music_list;

    TableInit();
}

QVector<QString> MusicInfo::searchSinger(QString search_str)
{
    QVector<QString> singer_list;

    //遍历 singer_to_music_table 表
    for(auto itr=singer_to_music_table.begin();itr!=singer_to_music_table.end();++itr)
    {
        //对查找词进行模糊查找
        QString singer = itr.key();
        if(singer.startsWith(search_str,Qt::CaseInsensitive))//找到和搜索词相同前缀的 歌手名，并且不区分大小写
        {
            singer_list.push_back(singer);
        }
    }

    return singer_list;
}

QVector<Music> MusicInfo::searchMusic(QString search_str)
{
    QVector<Music> list;

    for(auto itr=music_list.begin();itr!=music_list.end();++itr)
    {
        QString name = itr->name;
        if(name.startsWith(search_str,Qt::CaseInsensitive))
        {
            list.push_back(*itr);
        }
    }

    return list;
}

QList<Music>::iterator MusicInfo::searchMusic_itr(QString search_str)
{
    QList<Music>::iterator itr;
    for(itr=music_list.begin();itr!=music_list.end();++itr)
    {
        QString name = itr->name;
        if(name.startsWith(search_str,Qt::CaseInsensitive))
        {
            break;
        }
    }

    return itr;
}

int MusicInfo::searchMusic_index(QString search_str)
{
    int index=-1;//如果 index == -1 则表示未找到
    int i=0;

    for(auto itr=music_list.begin();itr!=music_list.end();++itr,++i)
    {
        QString name = itr->name;
        if(name.startsWith(search_str,Qt::CaseInsensitive))
        {
            index = i;
            break;
        }
    }

    return index;
}

void MusicInfo::TableInit()
{
    //遍历原始 music_list
    for(QList<Music>::iterator itr1=music_list.begin();itr1!=music_list.end();++itr1)
    {

        //[1]歌手 ->音乐 表 的构建
        for(QString singer:itr1->singer_list)
        {
            QVector<QString> songs;
            //判断 hash 表中是否已存在
            if(!singer_to_music_table.contains(singer))
            {
                songs.append(itr1->name);
                singer_to_music_table.insert(singer,songs);
            }
            else
            {
                QHash<QString,QVector<QString>>::iterator itr2 = singer_to_music_table.find(singer);
                itr2->append(itr1->name);
            }
        }

        //[2]歌曲分词->歌手 倒排索引表
        QStringList seperate_word_list;//分词列表
        seperate_word_list = itr1->name.split(" ");
        for(auto word:seperate_word_list)
        {
            //判断 hash 表中是否已存在
            if(!inverted_index_table.contains(word))
            {
                inverted_index_table.insert(word,itr1->singer_list);
            }
            else
            {
                QHash<QString,QVector<QString>>::iterator itr2 = inverted_index_table.find(word);
                //判断歌手表中是否已经有该歌手
                for(QString singer:itr1->singer_list)
                {
                    if(!itr2->contains(singer))
                    {
                        itr2->append(singer);
                    }
                }

            }
        }

    }

    qDebug() << "########################";
    for(auto itr=singer_to_music_table.begin();itr!=singer_to_music_table.end();++itr)
    {
        QString singer = itr.key();
        QVector<QString> songs = itr.value();

        qDebug() << singer << " "<< songs;
    }
    qDebug() << "########################";
    for(auto itr=inverted_index_table.begin();itr!=inverted_index_table.end();++itr)
    {
        QString word = itr.key();
        QVector<QString> singers = itr.value();

        qDebug() << word << " "<< singers;
    }
}
