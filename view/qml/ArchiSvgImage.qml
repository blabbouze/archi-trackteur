import QtQuick 2.5

Image {
    id: icon
    property int iconWidth: 24
    property int iconHeight: iconWidth

    anchors {
        left: parent.left ; leftMargin: 20
        verticalCenter: parent.verticalCenter
    }

    width: iconWidth ; height: iconHeight
    sourceSize { width: iconWidth ; height: iconHeight}

    antialiasing: true
}

