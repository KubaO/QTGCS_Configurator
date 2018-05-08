#include "configureproperty.h"

using C = ConfigureProperty;
QVector<C::Mapping> const ConfigureProperty::mappings{
    {&C::GCSAppPath, "GCS"},
    {&C::CFGAppPath, "CFG"},
    {&C::MMAppPath, "Map Manager"},

    {&C::ResourcePath, "Resource"},
    {&C::mapImagePath, "Map Resource"},
    {&C::mapIndexPath, "Map Index"},
    {&C::xbeeAddrPath, "XBEE Address"},
    {&C::logFilePath, "Log"},

    {&C::mapType, "Map Type"},
    {&C::zoomLevel, "Zoom Level"},
    {&C::mapKey, "Map Key"}
};

void ConfigureProperty::setToJsonObject(QJsonObject &obj) const
{
    for (auto &mapping : mappings)
        obj.insert(mapping.key, (*this).*(mapping.member));
}

ConfigureProperty &ConfigureProperty::setFromJsonObject(const QJsonObject &obj)
{
    for (auto &mapping : mappings) {
        auto it = obj.find(mapping.key);
        if (it != obj.end())
            (*this).*(mapping.member) = it.value().toString();
    }
    return *this;
}
