//
//  Protocol.h
//  RPI_iOS_Bluetooth_Client
//
//  Created by William Clark on 11/21/14.
//
//

#ifndef RPI_iOS_Bluetooth_Client_Protocol_h
#define RPI_iOS_Bluetooth_Client_Protocol_h

// shared with server //

#define PACKET_SIZE 3 // opcode, x, y

typedef enum Opcodes {
    SET_POSITION = 0xff
};

#endif
