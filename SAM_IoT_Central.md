# Connecting the SAM-IoT Wx v2 Development Board (Part No. EV62V87A) to Azure IoT Central

NOTE: Should you encounter any issues/obstacles with the following procedure, check out the [FAQ section](./FAQ.md)

## Introduction

[Azure IoT Central](https://docs.microsoft.com/en-us/azure/iot-central/core/overview-iot-central) is an IoT application platform that reduces the burden and cost of developing, managing, and maintaining enterprise-grade IoT solutions. Choosing to build with IoT Central gives you the opportunity to focus time, money, and energy on transforming your business with IoT data, rather than just maintaining and updating a complex and continually evolving IoT infrastructure.

The web UI lets you quickly connect devices, monitor device conditions, create rules, and manage millions of devices and their data throughout their life cycle. Furthermore, it enables you to act on device insights by extending IoT intelligence into line-of-business applications.

[IoT Plug and Play](https://docs.microsoft.com/en-us/azure/iot-develop/overview-iot-plug-and-play) enables solution builders to integrate IoT devices with their solutions without any manual configuration. At the core of IoT Plug and Play, is a device model that a device uses to advertise its capabilities to an IoT Plug and Play-enabled application. This model is structured as a set of elements that define:

- `Properties` that represent the read-only or writable state of a device or other entity. For example, a device serial number may be a read-only property and a target temperature on a thermostat may be a writable property

- `Telemetry` which is the data emitted by a device, whether the data is a regular stream of sensor readings, an occasional error, or an information message

- `Commands` that describe a function or operation that can be done on a device. For example, a command could reboot a gateway or take a picture using a remote camera

As a solution builder, you can use IoT Central to develop a cloud-hosted IoT solution that uses IoT Plug and Play devices. IoT Plug and Play devices connect directly to an IoT Central application where you can use customizable dashboards to monitor and control your devices. You can also use device templates in the IoT Central web UI to create and edit [Device Twins Definition Language (DTDL)](https://github.com/Azure/opendigitaltwins-dtdl) models.

## Program the Plug and Play Demo

1. Clone/download the MPLAB X demo project by issuing the following commands in a `Command Prompt` or `PowerShell` window

    ```bash
    git clone https://github.com/MicrochipTech/AzureDemo_SAM-IoT-Wx-v2.git
    cd AzureDemo_SAM-IoT-Wx-v2
    git submodule update --init
    ```

2. Connect the board to the PC using a micro USB cable, then make sure a device named `CURIOSITY` shows up as a Mass Storage Device (MSD) on the `Desktop` or in a `File Explorer` window. Drag and drop (i.e. copy) the pre-built `*.hex` file (located in the folder at `Microchip-SAM-IoT-Wx` > `firmware` > `AzurePnPDps.X` > `dist` > `SAMD21_WG_IOT` > `production`) to the `CURIOSITY` drive 

    <img src=".//media/image115.png">

    NOTE: If this file copy operation fails for any reason, [Make and Program Device](./AzurePnP_MPLABX.md) by building the MPLAB X source code project that was used to generate the `*.hex` file

3. Set up a Command Line Interface (CLI) to the board

    - Open a serial terminal (e.g. PuTTY, TeraTerm, etc.) and connect to the COM port corresponding to your board at `9600 baud` (e.g. open PuTTY Configuration window &gt; choose `session` &gt; choose `Serial`&gt; Enter the right COMx port). You can find the COM info by opening your PC’s `Device Manager` &gt; expand `Ports(COM & LPT)` &gt; take note of `Curiosity Virtual COM Port` 

        <img src=".//media/image27.png">

 4. Before typing anything in the terminal emulator window, **disable** the local echo feature in the terminal settings for best results.  In the terminal window, hit `[RETURN]` to bring up the Command Line Interface prompt (which is simply the `>` character). Type `help` and then hit `[RETURN]` to get the list of available commands for the CLI.  The Command Line Interface allows you to send simple ASCII-string commands to set or get the user-configurable operating parameters of the application while it is running

    <img src=".//media/image44.png" style="width:5.in;height:3.18982in" alt="A screenshot of a cell phone Description automatically generated" />

5. In the terminal emulator window, set the debug messaging level to 0 to temporarily disable the output messages. The debug level can be set anywhere from 0 to 4.  Use the `debug <level>` command by manually typing it into the CLI.  The complete command must be followed by hitting `[RETURN]`
    ```bash
    >debug 0
    ```

6. Perform a Wi-Fi scan to see the list of Access Points that are currently being detected by the board's Wi-Fi network controller.  Use  the `wifi` command's `scan` option by manually typing it into the CLI.  The complete command must be followed by hitting `[RETURN]`
    ```bash
    >wifi -scan
    ```

7. Configure the SAM-IoT board's internal Wi-Fi settings with your wireless router’s SSID and password using the `wifi` command's `set` option by manually typing it into the CLI.  The complete command must be followed by hitting `[RETURN]` (there cannot be any spaces used in the SSID or password)
    ```bash
    >wifi -set <NETWORK_SSID>,<PASSWORD>,<SECURITY_OPTION[1=Open|2=WPA|3=WEP]>
    ```
    For example, if the SSID of the router is "MyWirelessRouter" and the WPA/WPA2 key is "MyRoutersPassword", the exact command to type into the CLI (followed by `[RETURN]`) would be
    ```bash
    >wifi -set MyWirelessRouter,MyRoutersPassword,2
    ```

8. At the CLI prompt, type in the command `reset` and hit `[RETURN]` to restart the host application.  The Blue LED should eventually stay solidly ON to signify that the SAM-IoT board has successfully connected to the wireless router.
    ```bash
    >reset
    ```

9. In the terminal emulator window, set the debug messaging level to 0 to temporarily disable the output messages. The debug level can be set anywhere from 0 to 4.  Use the `debug <level>` command by manually typing it into the CLI.  The complete command must be followed by hitting `[RETURN]`
    ```bash
    >debug 0
    ```

10. At this point, the board is connected to Wi-Fi, but has not yet established a connection with the cloud (the green and red LEDs may be flashing). The `cloud` command can be used at any time to confirm the cloud connection status (which as of right now should be false).  The complete command must be followed by hitting `[RETURN]`
    ```bash
    >cloud -status
    ```

## Create an IoT Central Application

IoT Central allows you to create an application dashboard to monitor the telemetry and take appropriate actions based on customized rules.  To access all of your custom applications, you must be signed into the [Azure IoT Central Portal](https://apps.azureiotcentral.com) (it is recommended to bookmark this link for later use).

1. Review the below recomendations for creating the IoT Central application using the [Azure IoT Central Builder](https://apps.azureiotcentral.com/build) and then create your IoT Central application by clicking [here](https://docs.microsoft.com/en-us/azure/iot-central/core/quick-deploy-iot-central).

    NOTE: **Only** perform the steps in the first 2 sections titled "Prerequisites" and "Create an application"; once the application is created, stop and return to this page (i.e. **DO NOT** do the section titled "Register a device" as that will be done in a future step).

    If you are not currently logged into your [Microsoft account](https://account.microsoft.com/account), you will be prompted to sign in with your credentials to proceed.  
 
    - Choose a unique `Application name` which (will result in a unique `URL`) for accessing your application. Azure IoT Builder will populate a suggested unique `Application name` which can/should be leveraged, resulting in a unique `URL`. Take note of the unique/customizable portion of the `URL` (e.g. "custom-120683lb8ae") as it will be needed in a future step (suggest copy and pasting the exact text into a temporary doc file)

        <img src=".//media/image80a.png">

    - If you select the **Free** plan, you can connect up to 5 devices for free.  However, the free trial period will expire after 7 days which means a [paid pricing plan](https://azure.microsoft.com/en-us/pricing/details/iot-central/) will need to be selected to continue using the application.  Of course, there is nothing to stop you from creating a new free trial application but the device will need to be configured for the app from scratch.  Since the **Standard** plans each allow 2 free devices with no time-restricted trial period, if you only plan on evaluating 1 or 2 devices for connecting to the IoT Central app, then it's best to choose the **Standard 2** plan to get the highest total allowable number of messages (30K per month)

        <img src=".//media/image80b.png">

    - `Billing info` section: If there is an issue with selecting an existing subscription in the drop-down list (or no subscriptions appear in the list at all), click on the `Create subscription` link to create a new subscription to use for the creation of this application.  Take note of the exact subscription name (e.g. "Azure subscription 1") which was selected as it will be needed in a future step (suggest typing the exact text into a temporary doc file)
    
        <img src=".//media/image80c.png">

    - NOTE: If the message `Something went wrong` appears underneath the `Azure subscription` field, open up a web browser and log into your account using the [Azure portal](https://portal.azure.com) then retry selecting (or creating) a valid subscription

        <img src=".//media/image80d.png">

2. Once the application has been created, the application will be automatically saved and accessible in your [IoT Central Portal](https://apps.azureiotcentral.com) (it might be a good idea to bookmark this link now).

3. Whenever specific settings are needed to be read (typically the custom URL to access the application in the future), look up the settings for your application by using the left-hand navigation pane to select `Settings` &gt; `Application` &gt; `Management`

4. To access any of your IoT Central applications in the future, you can also go to [Azure IoT Central](https://apps.azureiotcentral.com) and click on `My apps`

    <img src=".//media/image108.png" style="width:5.in;height:1.98982in" alt="A screenshot of a cell phone Description automatically generated" />

## Create an Enrollment Group

1. Using the left-hand side navigation pane of your IoT Central application, select `Security` &gt; `Permissions` &gt; `Device connection groups`

   <img src=".//media/image81a.png" style="width:6.5.in;height:3.63506in" />

2. Click on the `+ New` button and create a new enrollment group using any name (with Group type = `IoT devices` and attestation type = `Certificates (X.509)`).  Hit the `Save` icon when finished

   <img src=".//media/image81b.png" style="width:6.5.in;height:3.63506in" />

3. Now that the new enrollment group has been created, click on `Manage Primary`

   <img src=".//media/image82.png" style="width:5.5.in;height:2.53506in" />

4. Click on `+ Add certificate` and browse to the **root** certificate file (`root-ca.crt` which should be located in the hidden `.microchip_iot` sub-folder that was created by the IoT Provisioning Tool). The IoT Provisioning Tool should have created the `.microchip_iot` hidden folder in the home directory (e.g. `/Users/<username>/.microchip_iot`). Click the `Upload` button (then click on `Close` when the certificate has been accepted)

   <img src=".//media/image75.png" style="width:5.5.in;height:2.13506in" />

5. Click on `Manage Secondary` and then click on `+ Add certificate`. Browse to the **signer** certificate file (`signer-ca.crt` which should be located in the hidden `.microchip_iot` sub-folder that was created by the IoT Provisioning Tool). The IoT Provisioning Tool should have created the `.microchip_iot` hidden folder in the home directory (e.g. `/Users/<username>/.microchip_iot`). Click the `Upload` button (then click on `Close` when the certificate has been accepted)

   <img src=".//media/image76.png" style="width:5.5.in;height:2.13506in" />

6. Click on the `Save` icon at the top of the page, and note the ID Scope which was created for the enrollment group. The X.509 enrollment group has been successfully created and should be ready to go!

    <img src=".//media/image83.png" style="width:5.in;height:2.18982in" alt="A screenshot of a cell phone Description automatically generated" />

## Test SAM-IoT Device with the IoT Central Application

1. Launch a terminal emulator window and connect to the COM port corresponding to the SAM-IoT board at `9600` baud (**disable** local echo for the terminal settings for best results).  If there are continuous non-stop messages being displayed on the terminal, disable them by typing `debug 0` followed by `[RETURN]`. Hit `[RETURN]` a couple of times to bring up the Command Line Interface prompt (which is simply the `>` character). Type `help` and then hit `[RETURN]` to get the list of available commands for the CLI.  The Command Line Interface allows you to send simple ASCII-string commands to set or get the user-configurable operating parameters of the application while it is running

    <img src=".//media/image44.png" style="width:5.in;height:3.18982in" alt="A screenshot of a cell phone Description automatically generated" />

2.	Look up the `ID Scope` for your IoT Central application (navigate to your application's web page and using the left-hand navigation pane, select `Permissions` > `Device connection groups`).  The `ID Scope` will be programmed/saved into the [ATECC608A](https://www.microchip.com/wwwproducts/en/atecc608a) secure element on the board in the next step

    <img src=".//media/image84a.png" style="width:5.in;height:3.18982in" alt="A screenshot of a cell phone Description automatically generated" />

3. In the terminal emulator window, hit `[RETURN]` to bring up the Command Line Interface prompt (which is simply the `>` character>). At the CLI prompt, type in the `idscope <your_ID_scope>` command to set it (which gets saved in the [ATECC608A](https://www.microchip.com/wwwproducts/en/atecc608a) secure element on the board) and then hit `[RETURN]`.  The ID Scope can be read out from the board by issuing the `idscope` command without specifying any parameter on the command line - confirm that the ID Scope has been read back correctly before proceeding to the next step

    <img src=".//media/image85.png" style="width:5.in;height:3.18982in" alt="A screenshot of a cell phone Description automatically generated" />

    NOTE: Make sure the ID scope reads back correctly. If not, keep repeating the write/read sequence until the correct ID scope has been read back from the board

4. In the terminal emulator window, hit `[RETURN]` to bring up the CLI prompt. Type in the command `reset` and hit `[RETURN]`

5. Wait for the SAM-IoT board to connect to your IoT Central application’s DPS; the Blue and Green LEDs will be flashing and/or staying on at different times/rates (which could take up to a few minutes).  Eventually the Blue and Green LEDs should both remain constantly ON.

    NOTE: If the Red LED comes on, then something may have been incorrectly programmed (e.g. wrong firmware, ID scope was entered incorrectly, etc.)

6. At this point, the board should have established a valid cloud connection (this can be confirmed visually by the Green LED staying on constantly).  The `cloud` command can be used at any time to confirm the cloud connection status using the CLI.  The complete command must be followed by hitting `[RETURN]`
    ```bash
    >cloud -status
    ```

7. Go back to your web browser to access the Azure IoT Central application.  Use the left-hand side pane and select `Devices` > `All Devices`.  Confirm that your device is listed – the device name & ID is the Common Name of the device certificate (which should be `sn + {17-digit device ID}`).  Click on the device name to see the additional details available for viewing

    <img src=".//media/image86.png" style="width:5.in;height:1.38982in" alt="A screenshot of a cell phone Description automatically generated" />

8. If desired, change the Device name by clicking on `Manage device` > `Rename`

    <img src=".//media/image87.png" style="width:5.in;height:1.18982in" alt="A screenshot of a cell phone Description automatically generated" />

9. Click on the `Commands` tab; type `PT5S` in the `Delay before rebooting SAM-IoT` field and then click on `Run` to send the command to the device to reboot in 5 seconds

    <img src=".//media/image88.png" style="width:5.in;height:1.58982in" alt="A screenshot of a cell phone Description automatically generated" />

10. Within 5 seconds of sending the Reboot command, the SAM-IoT development board should reset itself.  Once the Blue and Green LED's **both** stay constantly ON, press the SW0 and SW1 buttons (the Red LED may toggle with each button press)

    <img src=".//media/image89.png" style="width:5.in;height:1.28982in" alt="A screenshot of a cell phone Description automatically generated" />

11. Click on the `Properties (Writable)` tab and type `0` (zero) in the `Disable Telemetry` field, then hit `Save`

    <img src=".//media/image89a.png"/>

12. Click on the `Raw data` tab and confirm that the button press telemetry messages were received (scroll the page to the right to view the `SW0/SW1 button push event` column)

    <img src=".//media/image90.png"/>

13. Click on the `Refresh` icon to display all messages received since the previous page refresh operation.  Confirm that periodic telemetry messages are being continuously received approximately every 10 seconds (the default interval value for the `telemetryInterval` property)

    <img src=".//media/image91.png" style="width:5.in;height:1.58982in" alt="A screenshot of a cell phone Description automatically generated" />

    <img src=".//media/image92.png" style="width:5.in;height:2.12982in" alt="A screenshot of a cell phone Description automatically generated" />

14. Increase the ambient light source shining on top of the board. Wait approximately 30 seconds.  Click on the `Refresh` icon to confirm that the light sensor value has increased

    <img src=".//media/image93.png" style="width:5.in;height:2.18982in" alt="A screenshot of a cell phone Description automatically generated" />

15. Click [here](./DeviceTemplate_CreatingViews.md) to create an additional "Properties" view that allows you to change any of the Cloud-writable properties. Once this new view has been added to the device template, click on the Properties view and type in a new value for the Telemetry Interval. Click on the **Save** icon to send the property update request to the physical device. You should see the status of the property listed as "Pending" until a confirmation has been received from the physical device that the property was successfully updated. At this point in time, the status of the property should revert back to the "Accepted" state.

    Depending how quickly the write property response is received, it is possible that IoT Central will show the value as "Pending". If the device is offline or doesn't respond to a writable property request, the value can display as "Pending" indefinitely in IoT Central until a valid property update acknowledge has been received from the device.

16. Click on the `Properties` tab and try changing the property of the `Yellow LED state` between On, Off, & Blinking (remember to hit the `Save` icon for each property write operation to take effect). Confirm that the Yellow LED on the board corresponds to the state which was selected.

17. Click on the `About` tab to conveniently view all of the device's property settings/states on a single page.

## Creating a Dashboard for Custom Data Visualization

Try creating an IoT Central dashboard by clicking [here](https://docs.microsoft.com/en-us/azure/iot-central/core/howto-add-tiles-to-your-dashboard) and following the procedure outlined in the online guide. The below screen captures show the possibilities of dashboard components that can highlight the telemetry data and properties facilitated by the `IoT Plug and Play` interface.  Note that multiple devices can be selected for each tile to allow groups of devices to be visualized within a single tile. 

<img src=".//media/image95.png" style="width:5.in;height:3.34982in" alt="A screenshot of a cell phone Description automatically generated" />

<img src=".//media/image96.png" style="width:5.in;height:4.4182in" alt="A screenshot of a cell phone Description automatically generated" />

<img src=".//media/image97.png" style="width:5.in;height:3.34982in" alt="A screenshot of a cell phone Description automatically generated" />

<img src=".//media/image98.png" style="width:5.in;height:3.34982in" alt="A screenshot of a cell phone Description automatically generated" />
