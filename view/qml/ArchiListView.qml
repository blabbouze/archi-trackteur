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
            color: "red"
            width: parent.width ; height: 30
            Text {
                text: "Etape " + section
            }
        }
    }
}
