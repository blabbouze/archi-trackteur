import QtQuick 2.0

Rectangle {
    color: "#505050"
    height: 40

    ArchiSvgImage {
        id: icon
        iconWidth: 28
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/icons/overview"
    }

    ArchiText {
        id: text
        property int archiCaptured: controller.archiListRaw.archiStats.archiCaptured
        property int archiCount: controller.archiListRaw.archiStats.archiCount

        readonly property int archiLeft: archiCount - archiCaptured

        anchors {
            top: parent.top; topMargin: 3
            horizontalCenter: progress.horizontalCenter
        }
        text: "%2 capturés / %3 restants / %1\% complété".arg((archiCaptured / archiCount * 100).toFixed(0)).arg(archiCaptured).arg(archiLeft)
        color: "white"
        font.pointSize: 11
    }
    Rectangle {
        id: progress
        height: 10
        anchors {
            left: icon.right ; leftMargin: 20
            right: parent.right ; rightMargin: 20
            bottom:  parent.bottom ; bottomMargin :5
        }
        color: "#B4B4B4"

        Rectangle {
            height: parent.height;
            width: parent.width * text.archiCaptured / text.archiCount
            color: getProgressColor(text.archiCaptured / text.archiCount)
        }
    }
}

