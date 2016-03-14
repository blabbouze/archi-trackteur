import QtQuick 2.5
import QtQuick.Controls 1.4

import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Item {
    property alias modelArchi: listView.model

    Item {
        id: searchBarComponent
         width: parent.width ; height: 40

         ArchiSvgImage {
             id: iconSearchField
             iconWidth: 26

             anchors {
                 left: parent.left ; leftMargin: 20
                 verticalCenter: parent.verticalCenter
             }

             source: "qrc:/icons/search"

         }

         TextField {
            id: searchField
            height: parent.height
            anchors {
                left: iconSearchField.right; leftMargin: 10
                right: parent.right
            }
            placeholderText: "Rechercher..."
            onTextChanged: controller.searchArchi(searchField.text)
            style: TextFieldStyle {
                placeholderTextColor:'#b4b4b4'
                textColor: "#505050"
                background: Rectangle {
                    color: '#f0f0f0'
                }

                font {
                    family: appFont.name
                    pointSize: 12
                }
            }
         }

    }


    ListView {
        id: listView
        width: parent.width ; height: 200
        anchors { top: searchBarComponent.bottom ; bottom: parent.bottom }
        clip: true

        spacing: 5
        delegate: Rectangle {
            color: captured ? "#0064E6" : "#B4B4B4"
            width: text.implicitWidth + 20 ; height: 30
            ArchiText {
                id: text
                text: archiName + " (" + monsterName + ")"
                anchors {
                    left: parent.left ; leftMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                color: "white"
                font.pointSize: 12
            }
            MouseArea {
                anchors.fill:parent
                onClicked: controller.toogleArchiCaptured(index)
            }
        }

        section.property:  "step"
        section.delegate: Item {
            height: sectionRoot.height +10 ; width: parent.width
            Rectangle {
                id: sectionRoot
                // Those vars are refreshed when the model emits that StepRole have changed
                property int captured: controller.archiListRaw.archiStats.getArchiCapturedInStep(section)
                property int total: controller.archiListRaw.archiStats.getTotalArchiCountInStep(section)

                function getColor(progress) {
                    var color = ""
                    if (progress <= 0.2) {
                        color = "#FF5050"
                    } else if (progress > 0.2 && progress < 0.5) {
                        color =  "#ff6400"
                    } else if (progress >= 0.5 && progress < 0.85) {
                        color = "#ffb400"
                    } else if (progress >= 0.85 && progress < 1) {
                        color = "#00CD78"
                    } else {
                        color = "#00BEE6"
                    }

                    return color;
                }

                width: parent.width - 10 ; height: 20
                color: "#505050"

                Rectangle {
                    id: progress
                    // Do not use properties for sectionRoot.captured/sectionRoot.total
                    // It causes refresh problems
                    anchors { top: parent.top ; left: parent.left}
                    height: parent.height
                    width : parent.width * sectionRoot.captured/sectionRoot.total
                    color: sectionRoot.getColor( sectionRoot.captured/sectionRoot.total)

                }

                ArchiSvgImage {
                    id: iconStep
                    iconWidth: 16

                    anchors {
                        left: parent.left ; leftMargin: 5
                        verticalCenter: parent.verticalCenter
                    }

                    source: "qrc:/icons/step_only"
                }

                ArchiText {
                    anchors {
                        left: iconStep.right ; leftMargin: 5
                        verticalCenter: parent.verticalCenter
                    }
                    text: "étape " + section + " (" + sectionRoot.captured +  "/" + sectionRoot.total + ")"

                    state: "MenuSectionStep"
                }
            }
        }
    }
}
