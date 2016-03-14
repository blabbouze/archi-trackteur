import QtQuick 2.0

Rectangle {
    color: "#505050"
    height: 30

    ArchiSvgImage {
        id: icon
        iconWidth: 26
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/overview"
    }

    ArchiText {
        anchors {left: icon.right ; leftMargin: 10}
        text:

    }
}

