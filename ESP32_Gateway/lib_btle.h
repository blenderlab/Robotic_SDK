
#include "BLEDevice.h"
// UUID of service (BT16 default)
static BLEUUID serviceUUID("0000ffe0-0000-1000-8000-00805f9b34fb");
// UUID of read characteristic :
static BLEUUID charUUID("0000ffe2-0000-1000-8000-00805f9b34fb");
// UUID of write  & notify characteristic :
static BLEUUID writeUUID("0000ffe1-0000-1000-8000-00805f9b34fb");

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic* pWriteCharacteristic;
static BLERemoteCharacteristic* pReadCharacteristic;

// CAllback of notification (when Well sent)
static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  Serial.print("Notify callback ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
}

// Callbacks for device found :
class BTCallbacks: public BLEAdvertisedDeviceCallbacks {
    // When
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.print("BLE Advertised Device found: ");
      Serial.println(advertisedDevice.toString().c_str());
      // We have found a device, let us now see if it contains the service we are looking for.
      if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) {
        Serial.print("Found our device!  address: ");
        advertisedDevice.getScan()->stop();
        pServerAddress = new BLEAddress(advertisedDevice.getAddress());
        doConnect = true;

      }
    }
};
void BTLE_init() {
  BLEDevice::init("");
  // Create scanner :
  BLEScan* pBLEScan = BLEDevice::getScan();
  // Attach callbacks :
  pBLEScan->setAdvertisedDeviceCallbacks(new BTCallbacks());
  // Start scanner :
  pBLEScan->setActiveScan(true);
  // Timeout = 30s
  pBLEScan->start(30);
}

void send_data(String d) {
  if (connected) {
    pReadCharacteristic->writeValue(d.c_str(), d.length());
  }
}
// Connection to the robot's BT server :
bool connectToServer(BLEAddress pAddress) {

  Serial.print("Forming a connection to ");
  Serial.println(pAddress.toString().c_str());

  BLEClient*  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  Serial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    return false;
  }
  Serial.println(" - Found our service");
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pReadCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pReadCharacteristic == nullptr) {
    Serial.print("Failed to find READ our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    return false;
  }
  Serial.println(" - Found our READ characteristic");

  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pWriteCharacteristic = pRemoteService->getCharacteristic(writeUUID);
  if (pWriteCharacteristic == nullptr) {
    Serial.print("Failed to find our WRITE characteristic UUID: ");
    Serial.println(writeUUID.toString().c_str());
    return false;
  }
  Serial.println(" - Found our  WRITE characteristic");

  // Read the value of the characteristic.
  std::string value = pWriteCharacteristic->readValue();
  Serial.print("The characteristic value was: ");
  Serial.println(value.c_str());

  pWriteCharacteristic->registerForNotify(notifyCallback);

  return true;
}

void bt_loop(){
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }
}
