var coordinates = []
var allCoordinates = []
var arrayLines = []
var lineComplete = false
var circleCoordinates = []

function writeCoordinates(){
    for(var i =0; i<coordinates.length; i++){
        console.log(coordinates[i])
    }
    console.log("------------------------------------------")
}

function createElements(point) {
    var componentMarker = Qt.createComponent("Marker.qml");

    if (componentMarker.status === Component.Ready) {
        var markerFirstCorner = componentMarker.createObject(mapOfWorld);
        markerFirstCorner.coordinate = mapOfWorld.toCoordinate(point)
        coordinates.push(mapOfWorld.toCoordinate(point))
        allCoordinates.push(mapOfWorld.toCoordinate(point))
        /*
		for(var i =0; i<3; i++){
            console.log(coordinates[i])
        }
        console.log("coordinates[i]")
		*/
        mapOfWorld.addMapItem(markerFirstCorner)
    }else{
        console.log("Marker not created")
    }

    var theLine

    if(mode===0){
        //Polyline mode
		
        if(arrayLines.length===0){
            createLine(point)
        }else{
            theLine = arrayLines[arrayLines.length-1]
            theLine.mainPolyline.addCoordinate(mapOfWorld.toCoordinate(point))
        }

    }else if (mode===1){
        //Array of lines

        if(arrayLines.length===0 || !lineComplete){
            createLine(point)
            lineComplete=true
        }else{
            theLine = arrayLines[arrayLines.length-1]
            theLine.mainPolyline.addCoordinate(mapOfWorld.toCoordinate(point))
            lineComplete=false
        }
    }
}

function createLine(point){
    var componentLine = Qt.createComponent("Line.qml")

    if (componentLine.status === Component.Ready) {
        var lineFirstCorner = componentLine.createObject(mapOfWorld);
        lineFirstCorner.mainPolyline.addCoordinate(mapOfWorld.toCoordinate(point))

        mapOfWorld.addMapItem(lineFirstCorner)
        arrayLines.push(lineFirstCorner)
    }else{
        console.log("Line not created")
    }
}
