import QtQuick 2.5
import QtQuick.Controls 1.4

import QtQuick.Layouts 1.1

Item {
    property alias modelArchi: listView.model

    TextField {
        id: searchField
        width: parent.width ; height: 25
       placeholderText: "Chercher..."
       onTextChanged: controller.searchArchi(searchField.text)
    }

    ListView {
        id: listView
        width: parent.width ; height: 200
        anchors { top: searchField.bottom ; bottom: parent.bottom }
        clip: true

        delegate: Rectangle {
            color: captured ? "blue" : "white"
            border { color: "black" ; width: 1 }
            width: parent.width ; height: 25
            Text {
                text: archiName + "(" + monsterName + ")"
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill:parent
                onClicked: controller.toogleArchiCaptured(index)
            }
        }

        section.property:  "step"
        section.delegate: Rectangle {
            id: sectionRoot
            // This var are refreshed when the model emits that StepRole have changed
            property int captured: controller.archiListRaw.archiStats.getArchiCapturedInStep(section)
            property int total: controller.archiListRaw.archiStats.getTotalArchiCountInStep(section)


            Rectangle {
                id: progress
                anchors { top: parent.top ; left: parent.left}
                height: parent.height
                width : parent.width * sectionRoot.captured/sectionRoot.total
                color: "red"
            }

            color: "gray"
            width: parent.width ; height: 30
            Text {
                text: "Etape " + section + "(" + captured +  "/" + total + ")"
            }
        }
    }
}
