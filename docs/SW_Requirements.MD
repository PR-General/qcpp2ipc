# **qcpp2ipc Software Requirements** [DRAFT]
### **Background and Strategy**
The qcpp2ipc tool is an evolution of existing software generation methods existing within the Qt ecosystem ([qdbuscpp2xml](https://doc.qt.io/qt-6/qdbusxml2cpp.html) for example). The qcpp2ipc tool is intended to be used manually from commandline or ideally as part of a software build process (CMake). Instead of focusing specifically on one inter-process communication (IPC) protocol, qcpp2ipc describes the object interface and meta-information through a generic json object model. This generic object model is used by an IPC generator plugin to create a protocol specific implementation (class derivation). The generator can produce code for any language, but will most likely output C++ or Qt/C++ native object code. 

![IPO diagram for illustration](diagrams/ipo_qcpp2ipc.drawio.png)

### **Use Case**
The existing toolset works for simple use cases and is targeted at Qt **developers**. However, the code generated is limited and does not work for more advanced needs like custom types.

A well documented example is seen in a series of [KDE tutorials on DBUS](https://techbase.kde.org/Development/Tutorials/D-Bus).

[The XML output from the generator must be altered to support custom types](https://techbase.kde.org/Development/Tutorials/D-Bus/CustomTypes#Edit_the_XML); if necessary, the gain in generation is nearly lost. The qccp2ipc tool will overcome this limitation through an "output structure" meta input. This input file (json, xml, or qml) will communicate the object structure to the generator plugin. Interface objects are referenced by type name and are matched against virtual interface objects scanned, allowing use of custom types.

The qdbuscpp2xml and qdbusxml2cpp tools both target the QtDbus library as the output implementation. Using multiple runtime plugins, the same input can be used to generate multiple IPC solutions. The generator plugin will be selected using a commandline argument to qcpp2ipc.


## **Functional Requirements**
### Commandline parameters (**CMDP**)
The qcpp2ipc tool allows commandline input to configure the generation plugin and output
- **(CMDP-1)** Developer can specify the output generator plugin to use by name.
- **(CMDP-2)** Developer can specify the output generator plugin to use by file path.
- **(CMDP-3)** Developer can specify a single file as an object interface input.
- **(CMDP-4)** Developer can specify a folder to be scanned for (multiple) object interface inputs.
- **(CMDP-5)** Developer can specify a json format output structure input file.
- **(CMDP-6)** Developer can specify a xml format output structure input file.
- **(CMDP-7)** Developer can specify a qml format output structure input file.
- **(CMDP-8)** Developer can specify a protocol plugin configuration input file.
- **(CMDP-9)** Developer can specify a command parameter to request help instructions

### Software Processing (**PROC**)
- **(PROC-1)** the software shall validate the json output structure
- **(PROC-2)** the software shall validate the xml output structure
- **(PROC-3)** the software shall validate the qml output structure
- **(PROC-4)** the software shall validate the interface objects input
- **(PROC-5)** the software shall validate the output generator plugin selection
- **(PROC-6)** the software shall scan and validate a folder of object interfaces
- **(PROC-7)** the software shall output status and result of generator process
- **(PROC-8)** the software shall output status and result of generator process
- **(PROC-9)** the software shall produce a json intermediate representation of object model
- **(PROC-10)** the software shall (optionally) produce a generation report

### Generator Plugin Management (**PLUG**)
- **(PLUG-1)** the software shall load the plugin specified by name or path.
- **(PLUG-2)** the software shall instantiate the plugins root generator object.
- **(PLUG-3)** the software shall configure the generator object with the developers input
- **(PLUG-4)** the software shall use the intermediate representation (json) to initiate the plugin generator process
- **(PLUG-5)** the software shall report errors observed in the generation process
- **(PLUG-6)** the software shall forward progress communication from the plugin to the developer
- **(PLUG-7)** the software shall cleanup the plugin when the process is finishing



