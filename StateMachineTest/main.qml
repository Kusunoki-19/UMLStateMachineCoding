import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import CustomComponents 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("")
    
    StateMachine {
        id:stateMachine
        onEventOutput: {
            var eventOutMsg = "onEventOutput " + outEvent
            console.log(eventOutMsg)
            eventLogTest.text += eventOutMsg + "\n"
        }
        onStateChanged: {
            console.log("onStateChanged " + this.state)
        }
    }
    RowLayout {
        anchors.fill:parent
        Item {
            Layout.fillWidth:true
            Layout.fillHeight:true
            ColumnLayout {
                Text {
                    text: "current state:" + stateMachine.state
                }

                Button {
                    width:200
                    height:50
                    text:"StateMachine.InEvent1"
                    onClicked: {
                        stateMachine.trigger(StateMachine.InEvent1)
                    }
                }
                Button {
                    width:200
                    height:50
                    text:"StateMachine.InEvent2"
                    onClicked: {
                        stateMachine.trigger(StateMachine.InEvent2)
                    }
                }
            }
        }
        Item {
            Layout.fillWidth:true
            Layout.fillHeight:true
            Text {
                id:eventLogTest
                text:"eventLog \n"
            }
        }
    }
}
