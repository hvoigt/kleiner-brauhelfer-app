import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Drawer {
    id: drawer
    property alias model: repeater.model

    z: 1
    Material.elevation: 4
    width: layout.width
    height: parent.height
    topPadding: 0
    rightPadding: 0

    Flickable {
        anchors.fill: parent
        boundsBehavior: Flickable.OvershootBounds
        contentHeight: layout.height
        clip: true

        ColumnLayout {
            id: layout
            focus: false
            anchors.top: parent.top
            anchors.left: parent.left
            spacing: 0

            Rectangle {
                Layout.preferredWidth: childrenRect.width
                Layout.preferredHeight: childrenRect.height
                topRightRadius: 12
                color: Material.primary
                MouseArea {
                   anchors.fill: parent
                   onClicked: close()
                }
                RowLayout {
                    Image {
                        Layout.topMargin: drawer.SafeArea.margins.top + 4
                        Layout.bottomMargin: 4
                        width: 48 * app.settings.scalingfactor
                        height: width
                        source: "qrc:/images/logo.png"
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Layout.margins: 4
                        Label {
                            text: Qt.application.name
                            font.pointSize: 14 * app.settings.scalingfactor
                            font.weight: Font.Bold
                            color: Material.background
                        }
                        Label {
                            text: "v" + Qt.application.version
                            font.pointSize: 12 * app.settings.scalingfactor
                            color: Material.background
                        }
                    }
                }
            }

            Repeater {
                id: repeater
                Loader {
                    Layout.fillWidth: true
                    source: model.type
                }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator {}
    }
}
