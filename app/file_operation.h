#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H
#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

/******************************************************
 * Please set mapAccessToken, mapStyleUrl, speed,
 * interval, latitude and longitude in JSON format
 * in /etc/naviconfig.ini
 ******************************************************/
#define NAVI_CONFIG_FILEPATH "/etc/naviconfig.ini"

class File_Operation: public QObject{

    Q_OBJECT

    double m_car_speed;         // set Km/h
    int m_update_interval;      // set millisecond
    double m_start_latitude;
    double m_start_longitude;
    QString m_style;
    QString m_map_copyright;
    bool m_enable_maplibre;

public:
    File_Operation();
    virtual ~File_Operation();

    Q_INVOKABLE double getCarSpeed();
    Q_INVOKABLE int getUpdateInterval();
    Q_INVOKABLE double getStartLatitude();
    Q_INVOKABLE double getStartLongitude();
    Q_INVOKABLE bool isMaplibre() { return m_enable_maplibre; };
    Q_INVOKABLE QString getMaplibreStyle();
    Q_INVOKABLE QString getMapCopyright();
    Q_INVOKABLE QString getCachePath(QString name);

private:
    void initFileOperation();
};

#endif // FILE_OPERATION_H
