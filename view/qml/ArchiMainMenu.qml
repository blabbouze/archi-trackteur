import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {

    width: 250;
    anchors { top: parent.top; bottom:parent.bottom}
    color: "#505050"
// LIST

    ListModel {
        id: listModel
        ListElement { displayText: "Non capturés" ; icon: "not_captured" ; section: "filter"}
        ListElement { displayText: "Capturés" ; icon: "captured" ; section: "filter"}
        ListElement { displayText: "Etape seulement" ; icon: "step_only" ; section: "filter"}
        ListElement { displayText: "Avancement étape" ; icon: "sort_step" ; section: "sort"}
    }

    ListView {
        id: listView
        anchors { fill:parent ; margins: 15}

        model: listModel

        delegate: Rectangle {
            id: rootDelegate
            property bool hovered: false
            height: 50; width: listView.width
            color: "transparent"
            ArchiSvgImage {
                id: menuIcon

                iconWidth: 24

                anchors {
                    left: parent.left ; leftMargin: 20
                    verticalCenter: parent.verticalCenter
                }

                source: "qrc:/icons/" + icon
            }

            ArchiText {
                anchors {
                    left: menuIcon.right;  leftMargin: 10
                    verticalCenter: menuIcon.verticalCenter }
                text: displayText
                state: "MenuElement"
            }

            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: rootDelegate.hovered = true
                onExited: rootDelegate.hovered = false
            }

            states: State {
                when: hovered
                PropertyChanges {
                    target: rootDelegate
                    color: "#b4b4b4"
                }
            }
        }

        section.property: "section"
        section.delegate: Item {
            height: section == "filter" ? 30 : 40 ; width: listView.width
            Image {
                id: iconSection
                anchors.verticalCenter: parent.verticalCenter
                width: 24 ; height: 24
                source: "qrc:/icons/" + section
                antialiasing: true
            }

            ArchiText {
                anchors {
                    left: iconSection.right; leftMargin: 10
                    verticalCenter: iconSection.verticalCenter
                }
                text: section == "filter" ? "Filtres" : "Tri"
                state: "MenuSectionTitle"
            }
        }


    }



//       Text {
//           anchors.centerIn: parent
//           color: "white"
//           text: controller.archiListRaw.archiStats.archiCaptured
//       }
}

