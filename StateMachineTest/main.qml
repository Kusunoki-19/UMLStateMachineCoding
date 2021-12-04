import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import CustomComponents 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    
    StateMachine {
        id:stateMachine
        onEventOutput: {
            console.log("onEventOutput " + outEvent)
        }
        onStateChanged: {
            console.log("onEventOutput " + outEvent)
        }
    }

    ColumnLayout {
        Button {
            width:200
            height:50
            onClicked: {
                stateMachine.trigger(StateMachine.InEvent1)
            }
        }
        Button {
            width:200
            height:50
            onClicked: {
                stateMachine.trigger(StateMachine.InEvent2)
            }
        }
    }

}
