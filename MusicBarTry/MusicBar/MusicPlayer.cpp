#include "MusicPlayer.h"

MusicPlayer::MusicPlayer()
{

    //建立音频输出对象
    audioOutPut = new QAudioOutput;

    //建立媒体播放对象
    mediaPlayer = new QMediaPlayer;
    mediaPlayer->setAudioOutput(audioOutPut);

    //音频输入设备列表
    outPut_device_list =  QMediaDevices::audioOutputs();

    //获取当前媒体的时常
    QObject::connect(mediaPlayer,&QMediaPlayer::durationChanged,this,&MusicPlayer::durationChangedSlots);

    //获取当前播放时长
    QObject::connect(mediaPlayer,&QMediaPlayer::positionChanged,this,&MusicPlayer::positionChangedSlots);


    QObject::connect(mediaPlayer,&QMediaPlayer::mediaStatusChanged,this,&MusicPlayer::mediaStatusChangedSlots);





   for(QList<QAudioDevice>::iterator itr=outPut_device_list.begin();itr!=outPut_device_list.end();++itr)
   {
       qDebug() << itr->description();
   }
}

void MusicPlayer::setVolume(float vol)
{
    audioOutPut->setVolume(vol);
    qDebug()<< "volume" << audioOutPut->volume();
}

void MusicPlayer::play(int row)
{
    if(play_list.empty())
    {
        qDebug()<< "here 1";
        return;
    }

    switch (mediaPlayer->playbackState()) {
    case QMediaPlayer::PlaybackState::StoppedState:
    {
        current_row = row % play_list.size();//防止越界处理
        mediaPlayer->setSource(play_list[current_row]);
        mediaPlayer->play();
        break;
    }
    case QMediaPlayer::PlaybackState::PlayingState:
    {
        mediaPlayer->pause();
        break;
    }
    case QMediaPlayer::PlaybackState::PausedState:
    {
        mediaPlayer->play();
        break;
    }
    default:
        break;
    }
}

void MusicPlayer::choose_play(int row)
{
    current_row = row % play_list.size();


    mediaPlayer->pause();
    mediaPlayer->setSource(play_list[current_row]);
    mediaPlayer->play();
}

void MusicPlayer::play_last()
{
    current_row = (play_list.size() + current_row - 1) % play_list.size();
    mediaPlayer->setSource(play_list[current_row]);
    mediaPlayer->play();
}

void MusicPlayer::play_next()
{
    current_row = (current_row + 1) % play_list.size();
    mediaPlayer->setSource(play_list[current_row]);
    mediaPlayer->play();
}

void MusicPlayer::setPosition(qint64 duration)
{
    mediaPlayer->setPosition(duration);
}

void MusicPlayer::setOutPutDevice(int index)
{
    //防止越界
    outPutDeviceRefresh();

    device_id = index % outPut_device_list.size();
    audioOutPut->setDevice(outPut_device_list[device_id]);
}

void MusicPlayer::toNextOutPutDevice()
{
    setOutPutDevice(device_id + 1);
}

void MusicPlayer::outPutDeviceRefresh()
{
    outPut_device_list = QMediaDevices::audioOutputs();
}

QString MusicPlayer::getOutPutDeviceDescription()
{
    return outPut_device_list[device_id].description();
}

void MusicPlayer::durationChangedSlots(qint64 duration)
{
    //qDebug() << "total="<<duration;
    emit durationChanged(duration);
}

void MusicPlayer::positionChangedSlots(qint64 duration)
{
    //qDebug() << "pos="<<duration;
    emit positionChanged(duration);
}

void MusicPlayer::mediaStatusChangedSlots(QMediaPlayer::MediaStatus status)
{
    qDebug() << status;
    //如果播放结束了 则发出信号
    if(status == QMediaPlayer::EndOfMedia)
    {
        qDebug() << "end of media";
        emit mediaEnd();

    }
}

