#include <unistd.h>
#include "file_operation.h"

File_Operation::File_Operation(){
    initFileOperation();
}

File_Operation::~File_Operation(){

}

void File_Operation::initFileOperation(){

    m_car_speed = 60; // set default Km/h
    m_update_interval = 100; // set default millisecond
    m_start_latitude = 36.136261; // set default coordinate Westgate
    m_start_longitude = -115.151254;
    m_style = QString("https://tile.openstreetmap.jp/styles/openmaptiles/style.json");
    m_map_copyright = QString("MapLibre | © OpenMapTiles © OpenStreetMap contributors");
    m_enable_maplibre = true;

    QFile file(NAVI_CONFIG_FILEPATH);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        fprintf(stderr,"Failed to open mapAccessToken file \"%s\": %m", qPrintable(NAVI_CONFIG_FILEPATH));
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(data));
    QJsonObject jsonObj(jsonDoc.object());

    if(jsonObj.contains("speed")){
        m_car_speed = jsonObj["speed"].toDouble();
    }else{
        fprintf(stderr,"Failed to find speed data \"%s\": %m", qPrintable(NAVI_CONFIG_FILEPATH));
        file.close();
        return;
    }

    if(jsonObj.contains("interval")){
        m_update_interval = jsonObj["interval"].toInt();
    }else{
        fprintf(stderr,"Failed to find interval data \"%s\": %m", qPrintable(NAVI_CONFIG_FILEPATH));
        file.close();
        return;
    }

    if(jsonObj.contains("latitude")){
        m_start_latitude = jsonObj["latitude"].toDouble();
    }else{
        fprintf(stderr,"Failed to find latitude data \"%s\": %m", qPrintable(NAVI_CONFIG_FILEPATH));
        file.close();
        return;
    }

    if(jsonObj.contains("longitude")){
        m_start_longitude = jsonObj["longitude"].toDouble();
    }else{
        fprintf(stderr,"Failed to find longitude data \"%s\": %m", qPrintable(NAVI_CONFIG_FILEPATH));
        file.close();
        return;
    }

    // Check if using maplibre
    if (jsonObj.contains("maplibre")){
        m_enable_maplibre = jsonObj["maplibre"].toBool();
    }

    if(jsonObj.contains("maplibreStyleUrls")){
        if(jsonObj.contains("mapCopyright")){
            m_style = jsonObj["maplibreStyleUrls"].toString();
            m_map_copyright = jsonObj["mapCopyright"].toString();
        } else {
            fprintf(stderr,"Must be set mapCopyright if you set maplibreStyleUrls.\n");
        }
    }

    file.close();

    return;
}

double File_Operation::getCarSpeed(){
    return m_car_speed;
}
int File_Operation::getUpdateInterval(){
    return m_update_interval;
}
double File_Operation::getStartLatitude(){
    return m_start_latitude;
}
double File_Operation::getStartLongitude(){
    return m_start_longitude;
}

QString File_Operation::getMaplibreStyle() {
    return m_style;
}

QString File_Operation::getMapCopyright() {
    return m_map_copyright;
}

QString File_Operation::getCachePath(QString name)
{
    QString path("/var/run/user/");

    path.append(QString::number(getuid()));
    path.append("/usrshr/cache/");
    path.append(name);

    return path;
}
