import QtQuick 2.1
import QtQuick.Controls 1.2

Rectangle {
    width: 100
    height: 62
    color: "gray"

    //property time current_time

    Timer {
        id: presentTimer

        interval: 1000

        onTriggered: {
            //current_time + 1
        }
    }

    Column {
        Button {
            text: "start"

            onClicked: {
                presentTimer.start()
            }
        }


        Text {
            id: txtTime
            text: "test"

        }
    }

}
