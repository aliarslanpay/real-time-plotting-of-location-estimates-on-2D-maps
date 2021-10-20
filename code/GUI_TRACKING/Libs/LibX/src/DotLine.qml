import QtQuick 2.0
import QtLocation 5.9

MapQuickItem
{
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height/2
    property real factor: 1

    sourceItem: Image
    {
        id: image
        width: 0.35*factor; height: 0.35*factor
        source: "qrc:/line.png"
    }

}
