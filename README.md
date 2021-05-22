# BluepadiOS
To use one of the supported accessories in your application, follow these steps:
    - Go to Frameworks and add the ExternalAccessory framework
    - Edit the program's plist file, add a new item and select "Supported External Accessory Protocols" from the list, then add the names of the accessory protocols you want to connect to:<br> for Pinpad: com.datecs.pinpad
To add a framework, you need:
- Drag the "BluePad50v2.framework" folder and select "Copy items if needed"
- Go to General-> Frameworks, Libraries and Embedded Content and select "Embed and Sign" for BluePad50v2.framework
Use the framework
import  BluePad50v2
