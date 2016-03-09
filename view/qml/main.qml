import QtQuick 2.5
import QtQuick.Controls 1.4

import archi.monstre 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

   Controller {
        id: controller

        onError: errorMessage.text = errorMessage.errorDesc
   }

   Text {
        id: errorMessage

   }

   ListView {
       anchors.fill: parent
       model: controller.archiList
       delegate: Text { text: archiName + "(" + monsterName + ")"}

   }
}

