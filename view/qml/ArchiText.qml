import QtQuick 2.0

Text {
    id: text

    font.family: appFont.name

    states: [ State {
            name: 'MenuSectionTitle'
            PropertyChanges {
                target: text
                font {
                    pointSize: 10
                    capitalization: Font.AllUppercase
                }
                color: "white"
            }
        },
        State {
            name: 'MenuElement'
            PropertyChanges {
                target: text
                font {
                    pointSize: 12
                }
                color: "white"
            }
        },
        State {
            name: 'MenuSectionStep'
            PropertyChanges {
                target: text
                font {
                    pointSize: 8
                    capitalization: Font.AllUppercase
                    bold: true
                }
                color: "white"
            }
        }

 ]
}

