#include <Arduino.h>
//#include <vector>
#include "MoppyConfig.h"
#include "MoppyInstruments/MoppyInstrument.h"

/**********
 * MoppyInstruments handle the sound-creation logic for your setup.  The
 * instrument class provides a systemMessage handler function and a deviceMessage
 * handler function for handling messages received by the network and a tick
 * function for precise timing events.
 *
 * Configure the appropriate instrument class for your setup in MoppyConfig.h
 */


//#include "MoppyInstruments/ShiftedFloppyDrives.h"
#include "MoppyInstruments/Stepper.h"
#include "MoppySystem/MoppySystemController.h"
#include "MoppySystem/MoppyOutputShift.h"
MoppySystemController *controller = new MoppySystemController();
//MoppyInstrument *instrument = new instruments::ShiftedFloppyDrives();

/**********
 * MoppyNetwork classes receive messages sent by the Controller application,
 * parse them, and use the data to call the appropriate handler as implemented
 * in the instrument class defined above.
 *
 * Configure the appropriate networking class for your setup in MoppyConfig.h
 */

// Standard Arduino HardwareSerial implementation
#ifdef NETWORK_SERIAL
#include "MoppyNetworks/MoppySerial.h"
MoppySerial *network;// = MoppySerial(instrument);
#endif

//// UDP Implementation using some sort of network stack?  (Not implemented yet)
#ifdef NETWORK_UDP
#include "MoppyNetworks/MoppyUDP.h"
MoppyUDP *network;// = MoppyUDP(instrument);
#endif

//std::vector<MoppyInstrument *> instrument_list;

//The setup function is called once at startup of the sketch
void setup()
{
	controller->addDevice(new instruments::Stepper(1, 3, 158, 71, STEPPER_STEPDIR)); // 3 floppies
	controller->addOutput(new MoppyOutputShift(8, 1));
	//instrument_list.push_back(new instruments::ShiftedFloppyDrives());
	//network = new MoppySerial(instrument_list[0]);
	network = new MoppySerial(controller);

	// Call setup() on the instrument to allow to to prepare for action
	//instrument_list[0]->setup();
	controller->begin(); // Start the timer and initialize the instruments

	// Tell the network to start receiving messages
	network->begin();
}

// The loop function is called in an endless loop
void loop()
{
	// Endlessly read messages on the network.  The network implementation
	// will call the system or device handlers on the intrument whenever a message is received.
	network->readMessages();
}
