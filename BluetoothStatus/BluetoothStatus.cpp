#include <Windows.h>
#include <bthsdpdef.h>
#include <bluetoothapis.h>
#include "../API/RainmeterAPI.h"
#pragma comment(lib, "Bthprops.lib")

struct Measure {
    bool bluetoothState;
};

PLUGIN_EXPORT void Initialize(void** data, void* rm) {
    Measure* measure = new Measure;
    *data = measure;

    measure->bluetoothState = false; 
}

PLUGIN_EXPORT void Reload(void* data, void* rm, double* maxValue) {
    
}

PLUGIN_EXPORT double Update(void* data) {
    Measure* measure = (Measure*)data;


    BLUETOOTH_FIND_RADIO_PARAMS params = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
    HANDLE hRadio = nullptr;
    HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&params, &hRadio);

    measure->bluetoothState = (hFind != nullptr);

   
    if (hFind) {
        BluetoothFindRadioClose(hFind);
        CloseHandle(hRadio);
    }

    return measure->bluetoothState ? 1.0 : 0.0;
}


PLUGIN_EXPORT void Finalize(void* data) {
    Measure* measure = (Measure*)data;
    delete measure;
}
