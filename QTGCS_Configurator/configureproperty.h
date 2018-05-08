#ifndef CONFIGUREPROPERTY_H
#define CONFIGUREPROPERTY_H

#include <QString>
#include <QJsonObject>
#include <QVector>

struct ConfigureProperty
{
    QString productType;
    QString productVersion;
    QString GCSAppPath;
    QString CFGAppPath;
    QString MMAppPath;
    QString cfgFilePath;
    QString ResourcePath;
    QString mapImagePath;
    QString mapIndexPath;
    QString xbeeAddrPath;
    QString logFilePath;
    QString mapType = "hybrid";
    QString zoomLevel = "19";
    QString mapKey;
    QString originLat;
    QString originLon;
    void setToJsonObject(QJsonObject &) const;
    ConfigureProperty &setFromJsonObject(const QJsonObject &);
private:
    struct Mapping {
        using member_t = QString ConfigureProperty::*;
        member_t member;
        QLatin1String key;
        Mapping(member_t member, const char *key) : member(member), key(key) {}
    };
    static QVector<Mapping> const mappings;
};

#endif // CONFIGUREPROPERTY_H
