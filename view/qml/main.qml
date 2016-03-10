import QtQuick 2.5
import QtQuick.Controls 1.4

import archi.monstre 1.0

ApplicationWindow {
    id: app
    property bool saved: false

    visible: true
    width: 640 ; height: 480
    title: qsTr("ArchiTrackteur")



   Controller {
        id: controller

        onError: errorMessage.text = errorMessage.errorDesc
        onReadyToExit: {
            saved = true;
            app.close();
        }
   }


   onClosing: {
       if (!saved) {
           close.accepted = false
           controller.save();
       }
   }



   Text {
        id: errorMessage
   }

   ListView {
       anchors.fill: parent
       model: controller.archiList
       delegate: Rectangle {
           color: captured ? "blue" : "white"
           border { color: "black" ; width: 1 }
           width: 100 ; height: 25
           Text {
               text: archiName + "(" + monsterName + ")"
               anchors.centerIn: parent
           }
           MouseArea {
               anchors.fill:parent
               onClicked: controller.toogleArchiCaptured(index)
           }
       }
   }
}

