import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle {

    width: 250;
    anchors { top: parent.top; bottom:parent.bottom}
    color: "#505050"

    ListModel {
        id: listModel
        ListElement { displayText: "Non capturés" ; icon: "not_captured" ; section: "filter"}
        ListElement { displayText: "Capturés" ; icon: "captured" ; section: "filter"}
        ListElement { displayText: "Etape seulement" ; icon: "step_only" ; section: "filter"}
        ListElement { displayText: "Avancement étape" ; icon: "sort_step" ; section: "sort"}
    }

    ListView {
        id: listView

        property int currentFilter: -1
        property int currentSort: -1

        onCurrentFilterChanged: {
            archiListView.showSectionOnly = false
            controller.archiList.resetCapturedFilters()
            switch(currentFilter) {
            case 0:
                controller.archiList.showNotCapturedOnly();
                break;
            case 1:
                controller.archiList.showCapturedOnly();
                break;
            case 2:
                archiListView.showSectionOnly = true
                break;
            }
        }

        onCurrentSortChanged: {
            controller.archiList.resetSortFilters()
            switch(currentSort) {
            case 3:
                controller.archiList.sortByStepProgress();
                break;
            }
        }

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
                onClicked: {
                    if (index < 3) {
                        if (listView.currentFilter  == index)  {
                            listView.currentFilter  = -1
                            rootDelegate.hovered = false
                        } else {
                            listView.currentFilter  = index
                        }
                    } else {
                        if (listView.currentSort  == index)  {
                            listView.currentSort  = -1
                            rootDelegate.hovered = false
                        } else {
                            listView.currentSort  = index
                        }
                    }
                }
            }

            states: State {
                when: hovered || listView.currentFilter == index || listView.currentSort == index
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

}

