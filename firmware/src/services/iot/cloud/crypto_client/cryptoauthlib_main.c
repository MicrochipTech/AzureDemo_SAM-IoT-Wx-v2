#include "cryptoauthlib_main.h"
#include "crypto_client.h"
#include "cryptoauthlib.h"
#include "definitions.h"



extern ATCAIfaceCfg atecc608_0_init_data;
        
ATCAIfaceCfg* device_cfg = &atecc608_0_init_data;

void cryptoauthlib_init(void)
{
    uint8_t rv;
    
   // atcab_init_device(&_gMyDevice);
    
    rv = atcab_init(device_cfg);
    if (rv != ATCA_SUCCESS)
    {
       cryptoDeviceInitialized = false;
    } else {
       atcab_lock_data_slot(0);
       cryptoDeviceInitialized = true;
    }
}
