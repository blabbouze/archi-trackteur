import QtQuick 2.5
import QtQuick.Controls 1.4

import archi.monstre 1.0

ApplicationWindow {
    id: app
    property bool saved: false

    onClosing: {
        if (!saved) {
            close.accepted = false
            controller.save();
        }
    }

    visible: true
    width: 1024 ; height: 768
    title: qsTr("ArchiTrackteur")


   Controller {
        id: controller

        onError: errorMessage.text = errorMessage.errorDesc
        onReadyToExit: {
            saved = true;
            app.close();
        }
   }


   Rectangle {
    id: menuStats
       width: 100;
       anchors { top: parent.top; bottom:parent.bottom}
       color: "black"
       Text {
           anchors.centerIn: parent
           color: "white"
           text: controller.archiListRaw.archiStats.archiCaptured
       }
   }

  ArchiListView {
       anchors {
           top: parent.top; right: parent.right; bottom:parent.bottom
           left: menuStats.right
       }
       modelArchi: controller.archiList
   }

}

