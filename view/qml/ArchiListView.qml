import QtQuick 2.5
import QtQuick.Controls 1.4

import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Item {
    property alias modelArchi: listView.model
    property bool showSectionOnly: false

    Item {
        id: searchBarComponent
         width: parent.width ; height: 40

         ArchiSvgImage {
             id: iconSearchField
             iconWidth: 26

             anchors {
                 left: parent.left ; leftMargin: 5
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
            id: rootDelegate
            color: captured ? "#0064E6" : "#B4B4B4"
            width: listView.width ; height: 30
            ArchiText {
                id: text
                text: archiName
                anchors {
                    left: parent.left ; leftMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                color: "white"
                font.pointSize: 12
            }
            ArchiText {
                id: text2
                text: monsterName
                anchors {
                    right: parent.right ; rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                color: "white"
                font.pointSize: 12
            }
            MouseArea {
                anchors.fill:parent
                onClicked: controller.toogleArchiCaptured(qModelIndex.row)
            }

            state: State {
                when: listView.showSectionOnly
                PropertyChanges {
                    target: rootDelegate
                    height: 0
                }
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

                width: parent.width; height: 20
                color: "#505050"

                Rectangle {
                    id: progress
                    // Do not use properties for sectionRoot.captured/sectionRoot.total
                    // It causes refresh problems
                    anchors { top: parent.top ; left: parent.left}
                    height: parent.height
                    width : parent.width * sectionRoot.captured/sectionRoot.total
                    color: getProgressColor( sectionRoot.captured/sectionRoot.total)

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
