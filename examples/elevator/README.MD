 
## **Elevator Example**
Following is an example of a real world system that might use IPC to connect multiple networked systems.

![Class Diagram](elevator_system_highlevel.drawio.png)

Above is a basic block diagram that illustrates the object structure for a Passenger Elevator System. The structure is often described to *qcpp2ipc* using json or qml.

The design consists of a main system controller, an elevator Car controller, an elevator Motor controller, and 1 to many elevator Floor controllers.

### Output Structure - (optional) **PassengerElevatorStructure.qml**
```js
    ElevatorSystem{ // top level domain
        floorCount:6    // Constant floorCount (6)
        restingFloor:1  // Rest on Lobby floor

        ElevatorCar{ // car controller
            id: carController
            Doors{
                id:elevatorDoors
            }
            FloorRequestTerminal{
                id:floorRequestTerminal
            }
        }

        ElevatorMotor{ // motor controller
            id:motorController
        }

        ElevatorFloor{ // basement floor controller
            id:basement  
            name:"Basement Floor"          
            Doors{
                id: basementDoors
            }
            CallTerminal{
                id:basementTerminal
            }
            StatusDisplay{
                id:basementStatus
            }
        }

        ElevatorFloor{ // lobby floor controller
            id:lobby            
            name:"Lobby Floor" 
            Doors{
                id:lobbyDoors
            }
            CallTerminal{
                id:lobbyTerminal
            }
            StatusDisplay{
                id:lobbyStatus
            }
        }
        // ...
    }
```

### **Elevator Details**
    Inside the controller exists further object structure. For instance, both the elevator car and each floor has a set of doors. The elevator system controller will coordinate between systems, bringing the elevator to a complete stop at the target floor. Then, synchronizing the opening of the elevator and floor doors to allow passengers to enter or exit the car.

### **Object Interfaces**
Each individual controller is connected to a networked bus. The controller API (object interface) is described and accessed through the bus. The system will utilize the generated code to communicate asynchronously between devices. Each device knows about the API and the IPC type (protocol + transport).

- ` ElevatorSystem.h => ElevatorSystem `
- ` FloorRequestTerminal.h => FloorRequestTerminal `
- ` CallTerminal.h => CallTerminal `
- ` ElevatorCar.h => ElevatorCar `
- ` ElevatorFloor.h => ElevatorFloor ` 
- ` Doors.h => Doors ` 
- ` etc... `

### **Properties**
The Object interface describes its properties using the Q_PROPERTY macro. This example is simple but the macro can define the details of a property, like read/write access or even flags for the protocol (plugin) to utilize for generation.

![Elevator System Properties](Elevator_System_Properties.png)

Properties marked with a NOTIFY signal the property can change at any moment. Systems interested in monitoring this change can register a callback.

### **Remote Procedure Calls**
Often an interface cannot be described by properties alone. The qccp2ipc turns signal and slot definitions into bidirectional RPC. Signals are relayed to anyone listening for them, public slots are local functions, protected slots are turned into remote procedure calls (invoked remotely).

![Floor Terminal Procedures](call_terminal_rpc.png)

The methods are marked virtual so this interface can be inherited from and used for a derived solution. The concrete class will contain real code to perform when a remote procedure is called.