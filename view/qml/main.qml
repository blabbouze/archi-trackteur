import QtQuick 2.5
import QtQuick.Controls 1.4

import archi.monstre 1.0

ApplicationWindow {
    id: app
    property bool saved: false

    function getProgressColor(progress) {
        var color = ""
        if (progress <= 0.2) {
            color = "#FF5050"
        } else if (progress > 0.2 && progress < 0.5) {
            color =  "#ff6400"
        } else if (progress >= 0.5 && progress < 0.85) {
            color = "#ffb400"
        } else if (progress >= 0.85 && progress < 1) {
            color = "#00CD78"
        } else {
            color = "#00BEE6"
        }

        return color;
    }

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
      id: archiListView
       anchors {
           top: topBar.bottom;  topMargin: 10
           right: parent.right; rightMargin: 15
           left: menuStats.right ; leftMargin: 15
           bottom:parent.bottom
       }
       modelArchi: controller.archiList
   }

}

