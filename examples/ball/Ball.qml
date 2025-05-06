import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: ball
    
    readonly property bool wellPositioned: (x > 0 && x + width < parent.width) && (y > 0 && y + height < parent.height)
    readonly property real xStepFactor: 10.0
    readonly property real yStepFactor: 10.0
    readonly property point center: Qt.point((canva.width / 2) - (ball.width / 2), (canva.height / 2) - (ball.height / 2))
    
    function moveToCenter() {
        moveToCenterAnimation.start();
    }
    
    function moveLeft(steps = 1.0) {
        var totalSteps = steps * xStepFactor;
        if (x >= totalSteps)
            x -= totalSteps;
        else
            x = 0;
    }
    
    function moveRight(steps = 1.0) {
        var totalSteps = steps * xStepFactor;
        if (x + width + totalSteps <= parent.width)
            x += totalSteps;
        else
            x = parent.width - width
    }
    
    function moveUp(steps = 1.0) {
        var totalSteps = steps * yStepFactor;
        if (y >= totalSteps)
            y -= steps * yStepFactor;
        else
            y = 0;
    }
    
    function moveDown(steps = 1.0) {
        var totalSteps = steps * yStepFactor;
        if (y + height + totalSteps <= parent.height)
            y += totalSteps;
        else
            y = parent.height - height;
    }
    
    color: (wellPositioned ? "transparent" : "red")
    radius: width / 2
    width: 0
    height: 0

    Image {
        source: "qrc:/Ball.png"
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
    }
    
    PropertyAnimation {
        target: ball
        properties: "width,height"
        
        from: 0
        to: 64
        duration: 1000
        easing.type: Easing.InOutQuad
        running: true
    }
    
    ParallelAnimation {
        id: moveToCenterAnimation
        
        PropertyAnimation {
            target: ball
            property: "x"
            
            duration: 300
            easing.type: Easing.InOutQuad
            
            to: ball.center.x
        }
        
        PropertyAnimation {
            target: ball
            property: "y"
            
            duration: 300
            easing.type: Easing.InOutQuad
            
            to: ball.center.y
        }
    }
}
