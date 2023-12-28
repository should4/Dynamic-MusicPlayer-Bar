# 类设计

## 音乐播放类

### 结构功能
实现对音乐源文件（.mp3）的输入输出操作:
1. 读取指定路径下的音源文件(.mp3)
2. 输出指定的音源文件
3. 读取指定音源的播放总时长，当前播放时长
4. 指定输出设备（扬声器，耳机） 
5. 调整输出设备的音量 
   
### 程序设计
```c++
class MusicPlayer
{
     public:
    MusicPlayer();

    QList<QUrl> play_list;
    int device_id=0;//记录当前输出设备在列表中的位置
    int current_row=0;//记录当前播放歌曲所对应的行数

    //设置音量
    void setVolume(float vol);

    //播放歌曲
    void play(int row);//指 如果此时媒体播放对象没有指定音源 则将音源指定为播放列表的第 row 行
    void choose_play(int row);//选择指定歌曲播放 row表示音源在播放列表中的索引

    //播放下一首 上一首
    void play_last();
    void play_next();

    //设置当前歌曲的进度
    void setPosition(qint64 duration);

    //设置输出设备
    void setOutPutDevice(int index);
    void toNextOutPutDevice();
    void outPutDeviceRefresh();
    QString getOutPutDeviceDescription();
private:
    QAudioOutput* audioOutPut;//设备输出控制类

    QMediaPlayer* mediaPlayer;//媒体播放类

    QList<QAudioDevice> outPut_device_list;//音乐输出设备列表

}

```




## 文件操作类

### 结构功能
实现对音乐源文件（.mp3）的读取操作，并以 Music 结构体的形式储存在链表中

### 程序设计
```c++
//音乐结构体
//音乐源文件夹中依照以下规则命名 （"歌手" - "歌手1"&"歌手2"&"歌手2"....）
//例 Bewitched - Laufey&Spencer Stewart
struct Music
{
    QString name;//音乐名
    QVector<QString> singer_list;//歌手列表
    QString root_text;//未经处理的音乐名
};

class MyFile
{
public:
    MyFile();

    //将音源文件夹中的音乐信息读取到列表中
    static QList<Music> readAll();
}
```

1. 功能
   * 将音乐源文件中的歌名及其对应的歌手以链表的形式读取出来 
         
        ``` c++
        struct Music
        {
            QString name;//音乐名
            QList<QString> singer_list;//歌手列表
            QImage img;//专辑封面
        }

        // 音源格式 End Game - Taylor Swift&Ed Sheeran&Future
        QList<Music> readAll();
        ``` 
    
## 音乐索引类

### 结构功能
实现对音乐的查找操作：
1. 模糊查找（前缀查找）
2. 哈希查找：找到歌手对应的歌曲集

### 程序设计
```c++
class MusicInfo
{
public:
    MusicInfo();
    MusicInfo(QList<Music> music_list);

    QList<Music> music_list;//音乐索引表

    QVector<QString> searchSinger(QString search_str);//前缀查找 找到所有符合要求的歌手名
    QVector<Music> searchMusic(QString search_str);//前缀查找 找到所有符合要求的歌曲名
    QList<Music>::iterator searchMusic_itr(QString search_str);//返回音乐在音乐列表中的索引指针
    int searchMusic_index(QString search_str);//返回音乐在音乐列表中的索引号
    QVector<Music> getMusicBySinger(QString singer);//找到查找歌手的音乐集


protected:
    void TableInit();//初始化音乐索引表

private:

    QHash<QString,QVector<QString>> singer_to_music_table;//歌手 ->音乐 表
    QHash<QString,QVector<QString>> inverted_index_table;//歌曲歌手分词->歌手 倒排索引表

    QList<Music> play_list;
};
```

1. 成员变量
   
    * 歌手->音乐 表 
      1. 存储结构：通过哈希表将歌手名字作为key值，歌手创作的歌曲作为数据域
      2. 采用该种结构的原因：和歌曲数量相比 歌手数量远远少于歌曲，因而将歌手作为key值构造的哈希表规模较为可控，在空间上的占用时可以接受的
      3. 使用场景：在用户查找歌手对应单曲的场景下适用
   
   ---
    * 歌曲分词->歌手 倒排索引表 
      1. 存储结构：通过哈希表将分词结构作为key值，歌手姓名数组作为数据域
      2. 采用该种结构的原因：在歌曲基数较大的情况下  歌曲的分词结果远远少于和歌曲数量
      3. 使用场景：在用户进行歌曲歌手随机查找时使用

2. 功能（将从文件中读取出来的音乐列表 按不同需求构建对应的索引表）
   * 指定查找：输入歌手名，查找对应歌手名下的所有单曲
        ``` c++
        QVector<Music> getMusicBySinger(QString singer);
        ```
   * 随机查找：输入音乐名  查找符合条件的歌曲 
        ``` c++
        QVector<Music> getMusicByName(QString name)
        ```