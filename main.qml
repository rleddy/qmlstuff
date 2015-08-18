import QtQuick 2.2
import QtQuick.Controls 1.1

TableView {
    objectName:cputable
    model: cpuInfoModel
    anchors.fill: parent
    anchors.margins: 12

    width:  500
    height: 500


    TableViewColumn {
        role: "credit"
        title: "Maker"
        width: 120
    }
    TableViewColumn {
        role: "runrate"
        title: "HRZ"
        width: 200
        visible: true
    }

    TableViewColumn {
        role: "moredata"
        title: "MORE DATA"
        width: 200
        visible: true
    }


    itemDelegate: Item {
               Text {
                   anchors.left: parent.left
                   anchors.verticalCenter: parent.verticalCenter
                   renderType: Text.NativeRendering
                   text: styleData.value
               }
           }

    frameVisible: frameCheckbox.checked
    headerVisible: headerCheckbox.checked
    sortIndicatorVisible: sortableCheckbox.checked
    alternatingRowColors: alternateCheckbox.checked
}
