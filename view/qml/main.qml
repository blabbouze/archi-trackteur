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


  ArchiListView {
       anchors.fill: parent
       modelArchi: controller.archiList
   }

}

