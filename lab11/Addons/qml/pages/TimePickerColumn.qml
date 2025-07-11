import QtQuick 2.0 // Or a higher version like 2.12 if your project uses it
import Sailfish.Silica 1.0
import QtGraphicalEffects 1.0 // For FastBlur effect

// TimePicker.qml
// This component defines a scrollable list of numbers for selecting time units.
// It uses PathView for cyclical scrolling and FastBlur for visual distinction of non-selected items.

Item {
    id: picker
    // Property to define the starting number of the list
    property int from: 0
    // Property to define the ending number of the list
    property int to: 59
    // Property to hold the currently selected value in the picker
    property int currentValue: from
    // Signal emitted when the selected value changes
    signal valueChanged(int value)

    // Define the width of the picker component
    width: Theme.itemSizeLarge * 1.5
    // Define the height of the picker component (e.g., to show 5 items)
    height: Theme.itemSizeLarge * 5
    // Clip children to the bounds of this item
    clip: true

    PathView {
        id: pathView
        anchors.fill: parent // PathView fills the picker item

        // The model determines the number of items in the list.
        model: picker.to - picker.from + 1

        // Delegate defines how each item in the model is visually represented.
        delegate: Item {
            id: delegateRoot
            width: pathView.width // Delegate item takes the full width of the PathView
            height: Theme.itemSizeLarge // Delegate item has a standard height

            // The Label displays the number.
            Label {
                id: numberLabel
                anchors.centerIn: parent // Center the label within the delegate item

                // Display the number. 'index' is the model index for PathView delegates.
                // Add 'picker.from' to get the actual value.
                text: (index + picker.from) < 10 ? "0" + (index + picker.from) : (index + picker.from)
                font.pixelSize: Theme.fontSizeLarge

                // Change color and opacity based on whether this is the current item.
                // PathView.isCurrentItem is an attached property available to delegates.
                color: delegateRoot.PathView.isCurrentItem ? Theme.highlightColor : Theme.primaryColor
                opacity: delegateRoot.PathView.isCurrentItem ? 1.0 : 0.4 // Faded effect for non-current items

                // Enable layering for applying graphical effects
                layer.enabled: true
                // Apply FastBlur effect. Current item has no blur (radius 0).
                layer.effect: FastBlur {
                    // Blur radius: 0 for current item, a positive value for others.
                    // Adjust '16' for desired blur intensity.
                    radius: delegateRoot.PathView.isCurrentItem ? 0 : 16
                    // Caching can improve performance if the source (label text) doesn't change.
                    cached: true
                }
            }
        }

        // Define the path for the items to follow.
        // A simple vertical line centered in the PathView.
        path: Path {
            // StartX positions the path horizontally in the center of the PathView.
            startX: pathView.width / 2
            // StartY positions the path vertically.
            startY: 0 // Path starts at the top edge of the PathView.

            // A line segment defining the vertical path.
            PathLine {
                x: pathView.width / 2 // Stays centered horizontally.
                y: pathView.height   // Path ends at the bottom edge of the PathView.
            }
        }

        // pathItemCount: Number of delegate items to create.
        // Should be an odd number and slightly more than can be visible to ensure smooth scrolling.
        // If picker.height shows 5 items, 7 or 9 allows items to scroll in/out smoothly.
        pathItemCount: 7 // Adjust as needed

        // Highlight range and snapping behavior.
        // This helps to center the current item.
        highlightRangeMode: PathView.StrictlyEnforceRange // Ensures one item is primarily highlighted.
        // preferredHighlightBegin/End are normalized (0.0 to 1.0) positions along the path.
        // 0.5 means the middle of the path.
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5

        // Set the initial current index based on the 'currentValue' property.
        currentIndex: picker.currentValue - picker.from

        // Handler for when the current index of the PathView changes (e.g., due to user scrolling).
        onCurrentIndexChanged: {
            // Update the picker's 'currentValue' property.
            picker.currentValue = currentIndex + picker.from
            // Emit the 'valueChanged' signal with the new current value.
            picker.valueChanged(picker.currentValue)
        }
    }

    // This Rectangle provides a visual border around the highlighted (current) item's slot.
    // It is drawn on top of the PathView to indicate the selection area.
    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter // Center horizontally in the picker
        anchors.verticalCenter: parent.verticalCenter   // Center vertically in the picker
        width: parent.width                             // Match the width of the picker
        height: Theme.itemSizeLarge                     // Match the height of a single item
        color: "transparent"                            // Make the rectangle itself transparent
        border.color: Theme.highlightColor              // Use the theme's highlight color for the border
        border.width: 1                                 // Thin border
        // Ensure this is drawn on top of the PathView items
        z: 1
    }
}
