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

    FontLoader { id: appFont; name: "Segoe UI" }

   Controller {
        id: controller

        onReadyToExit: {
            saved = true;
            app.close();
        }
   }


   ArchiMainMenu {
       id: menuStats
   }


   ArchiTopBar {
       id: topBar
       anchors {
           right: parent.right
           left: menuStats.right ; leftMargin: 1
       }
   }

  ArchiListView {
       anchors {
           top: topBar.bottom;  topMargin: 10
           right: parent.right; bottom:parent.bottom
           left: menuStats.right ; leftMargin: 10
       }
       modelArchi: controller.archiList
   }

}

