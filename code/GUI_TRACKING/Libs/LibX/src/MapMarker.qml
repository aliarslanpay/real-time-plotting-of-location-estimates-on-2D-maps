import QtQuick 2.0
import QtLocation 5.9

MapQuickItem
{
    id: assetMapItem2
    property string name: "deneme"
    property bool followMe: true
    property real transparency: 0
    anchorPoint.x: receiverIcon.width/2
    anchorPoint.y: receiverIcon.height/2
    visible: true
    sourceItem: Column
    {
        Image
        {
            id: receiverIcon
            width: 40
            height: 50
            source: "qrc:/receiver.png"
        }
        Text
        {
            text: name
            horizontalAlignment: Text.AlignHCenter
            width: receiverIcon.width
        }
    }
}
