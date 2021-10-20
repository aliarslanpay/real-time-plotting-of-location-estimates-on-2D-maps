import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtLocation 5.8
import QtPositioning 5.5
import Qt.labs.location 1.0
import "create_points.js" as Create_points
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    width: 1200
    height: 600
    y:30
    x:360
    visibility: "Windowed"
    title: qsTr("Receiver Tracking")
    onClosing: mainmenu.closeProgram()
    property int mode: 0
    property int follow: 1

    Map {
        id: mapOfWorld
        activeMapType: mapOfWorld.supportedMapTypes[1]
        anchors.centerIn: parent
        anchors.fill: parent
        zoomLevel: 10
        //maximumZoomLevel: 17
        plugin: Plugin {
            name: 'osm';
            PluginParameter {
                name: 'osm.mapping.offline.directory'
                value: ':/offline_tiles/'
            }
            PluginParameter {
                        name: "osm.mapping.providersrepository.disabled"
                        value: false
            }
        }

        MapCircle {
            id: first_circle
            visible: false
            center {
                latitude: second_text.text
                longitude: third_text.text
            }
            radius: first_text.text
            color: 'green'
            border.width: 3
        }
        center: QtPositioning.coordinate(41.115604, 29.070932)
        /*
        Button {
            id: marker_0
            text: "o-o"
            onClicked: mode = 0
            height: 40
            width: 40
            anchors.left: parent.left
            anchors.top: parent.top
        }
        */
        /*Button {
            id: marker_1
            text: "|"
            onClicked: {
                Create_points.lineComplete = true
                mode = 1
                Create_points.arrayLines = []
            }
            height: 40
            width: 40
            anchors.right: parent.left+1
            anchors.top: marker_0.bottom
        }*/
        /*Button {
            id: marker_2
            text: "o"
            onClicked: {
                Create_points.lineComplete = true
                mode = 2
                Create_points.arrayLines = []
            }
            anchors.left: parent.left
            anchors.top: marker_delete.bottom
            height: 40
            width: 40
        }
        */
        Text {
            id: map_circle
            topPadding: 5
            text: "Circle"
            //font.family: "Helvetica"
            font.pointSize: 12
            font.bold: true
            //color: "red"
            anchors.left: parent.left
            anchors.top: marker_delete.bottom
        }
        Text {
            id: radius_text
            visible: false
            text: "Radius: "
            anchors.left: parent.left
            anchors.top: circle_visibility.bottom
        }
        TextInput {
            id:first_text
            visible: false
            text: "1000"
            cursorVisible: false
            anchors.left: radius_text.right
            anchors.top: circle_visibility.bottom
        }
        Text {
            id: latitude_text
            visible: false
            text: "Latitude: "
            anchors.left: parent.left
            anchors.top: radius_text.bottom
        }
        TextInput {
            id: second_text
            visible: false
            text: "41.118604"
            cursorVisible: false
            anchors.left: latitude_text.right
            anchors.top: radius_text.bottom
        }
        Text {
            id: longitude_text
            visible: false
            text: "Longitude: "
            anchors.left: parent.left
            anchors.top: latitude_text.bottom
        }
        TextInput {
            id: third_text
            visible: false
            text: "29.000932"
            cursorVisible: false
            anchors.left: longitude_text.right
            anchors.top: latitude_text.bottom
        }
        Button {
            id: route_circle
            text: "C"
            visible: false
            onClicked: {
                /*for(var i =0; i<12; i++){
                   Create_points.circleCoordinates.push(QtPositioning.coordinate(41.115604, 29.070932))
                }*/
                messageDialog.text = ""
                for(var i =0; i<12; i++){
                   Create_points.circleCoordinates.push(QtPositioning.coordinate(second_text.text, third_text.text).atDistanceAndAzimuth(first_text.text, i*30))
                }
                for(var i =0; i<12; i++){
                    messageDialog.text += (i*30) + "° - " + Create_points.circleCoordinates[i].latitude + ", " + Create_points.circleCoordinates[i].longitude + "\n"
                }
                messageDialog.visible = true

                Create_points.lineComplete = true
                Create_points.circleCoordinates = []
            }
            anchors.left: parent.left
            anchors.top: third_text.bottom
            height: 40
            width: 40
        }
        Button {
            id: circle_visibility
            text: "V"
            onClicked: {
                if (first_circle.visible == true){
                    first_circle.visible = false
                    route_circle.visible = false
                    radius_text.visible = false
                    first_text.visible = false
                    latitude_text.visible = false
                    second_text.visible = false
                    longitude_text.visible = false
                    third_text.visible = false
                }
                else{
                    first_circle.visible = true
                    route_circle.visible = true
                    radius_text.visible = true
                    first_text.visible = true
                    latitude_text.visible = true
                    second_text.visible = true
                    longitude_text.visible = true
                    third_text.visible = true
                }

            }

            height: 40
            width: 40
            anchors.left: parent.left
            anchors.top: map_circle.bottom
        }
        Button {
            id: marker_f
            text: "R"

            onClicked: {
                messageDialog.text = ""
                for(var i =0; i<Create_points.coordinates.length; i++){
                    messageDialog.text += (i+1) + "- " + Create_points.coordinates[i].latitude + ", " + Create_points.coordinates[i].longitude + "\n"
                }
                messageDialog.visible = true

                Create_points.lineComplete = true
                //Create_points.arrayLines = []
                //Create_points.coordinates = []
            }
            anchors.left: parent.left
            anchors.top: parent.top
            height: 40
            width: 40
        }
        Button {
            id: marker_delete
            text: "D"
            onClicked: {
                Create_points.lineComplete = true
                Create_points.arrayLines = []
                Create_points.coordinates = []

                for(var i = mapOfWorld.mapItems.length-1; i>1; i--){
                    mapOfWorld.removeMapItem(mapOfWorld.mapItems[i])
                }
            }
            anchors.left: parent.left
            anchors.top: marker_f.bottom
            height: 40
            width: 40
        }
        CheckBox {
                id: follow_box
                style: CheckBoxStyle {
                        label: Text {
                            text: "Follow"
                            font.pointSize: 10
                        }
                }
                height: 20
                checked: true
                anchors.right: parent.right
                anchors.top: parent.top
                onCheckedChanged: follow *= -1
        }
        Button {
            id: zoom_in
            text: "+"
            onClicked: {
                if(mapOfWorld.zoomLevel < mapOfWorld.maximumZoomLevel)
                    mapOfWorld.zoomLevel += 1;
            }
            height: 40
            width: 40
            anchors.right: parent.right
            anchors.top: follow_box.bottom
        }
        Button {
            id: zoom_out
            text: "-"
            onClicked: mapOfWorld.zoomLevel -= 1;
            anchors.right: parent.right
            anchors.top: zoom_in.bottom
            height: 40
            width: 40
        }
        Button {
            id: home
            text: "F"
            onClicked: mapOfWorld.fitViewportToVisibleMapItems()
            anchors.right: parent.right
            anchors.top: zoom_out.bottom
            height: 40
            width: 40
        }
        Button {
            id: screenshot
            text: "SS"
            onClicked: {
                mapOfWorld.grabToImage(function(result) {
                    var d = new Date();

                    result.saveToFile("map_"+d.getTime()+".png")
                });
            }
            anchors.right: parent.right
            anchors.top: home.bottom
            height: 40
            width: 40
        }
        Button {
            id: quit_button
            text: "Quit"
            onClicked:mainmenu.closeProgram()
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: 40
            width: 50
        }
        Text {
            id: cursor_position
            text: ""
            anchors.right: zoom_in.left
            anchors.top: parent.top
        }
        Text {
            id: angle_text2
            text: "Angle: "
            anchors.right: angle_text.left
            anchors.bottom: parent.bottom
        }
        Text {
            id: angle_text
            text: ""
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }

        Text {
            id: coordinate_text
            visible: false
            text: ""
            anchors.right: parent.right
            anchors.bottom: angle_text.top
        }
        MapItemView {
            id:ali
            model: assetmodel
            delegate: MapMarker{
                coordinate: assetData
                name: nameData
                followMe: true
                transformOrigin: Item.Center
                rotation: angle_text.text*(-1)
                onCoordinateChanged: {
                    angle_text.text = angleData
                    if(follow == 1)
                        mapOfWorld.center = assetData
                }
                z:100
            }
        }
    }
    statusBar: StatusBar {
        id: statusbar
        RowLayout {
            anchors.fill: parent
            Label{
                text: "Haritanın merkezi: "+mapOfWorld.center/* + "\tAlıcının konumu: "+coordinate_text.text */+ "\tZoom: "+mapOfWorld.zoomLevel
            }
        }
    }
    Canvas {
            id: root
            anchors.fill : parent
            property int wgrid: 10
            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 1
                ctx.strokeStyle = "gray"
                ctx.beginPath()

                var nrows = height/wgrid;
                ctx.moveTo(0, wgrid*(nrows/2));
                ctx.lineTo(width, wgrid*(nrows/2));

                var ncols = width/wgrid
                ctx.moveTo(wgrid*(ncols/2), 0);
                ctx.lineTo(wgrid*(ncols/2), height);

                ctx.closePath()
                ctx.stroke()
            }
    }
    MouseArea{
            anchors.fill: parent
            z:1
            acceptedButtons:Qt.RightButton
            onClicked: if (mouse.button === Qt.RightButton){
                Create_points.createElements(Qt.point(mouse.x,mouse.y))
            }
        }
    MessageDialog {
        id: messageDialog
        title: "Route"
        //text: "It's so cool that you are using Qt Quick."
        Component.onCompleted: visible = false
    }
}
