<!--
Format:


File:
mcu.c

Algorithm:
main()
{
...
}

Description:
...



-->

File:
mcu.c

Algorithm:

void gw_initializeMcu(void)
{
    // Initialize the MCU PDO sub id 1 CAN msg
    McuData.Pdo.CanMsg1.Receive.Can = 1;
    McuData.Pdo.CanMsg1.Receive.Dlc = 8;
    McuData.Pdo.CanMsg1.Receive.Id = MCU_PDO_MOSI_ID;
    McuData.Pdo.CanMsg1.Send.Can = 1;
    McuData.Pdo.CanMsg1.Send.Dlc = 8;
    McuData.Pdo.CanMsg1.Send.Id = MCU_PDO_MISO_ID;
    McuData.Pdo.CanMsg1.Master = FALSE;
    McuData.Pdo.CanMsg1.EnableSend = TRUE;
    McuData.Pdo.CanMsg1.EnableReceive = FALSE; //EXJOBB
    McuData.Pdo.CanMsg1.EnableSubId = TRUE;
    McuData.Pdo.CanMsg1.SubIdValue = 1;
    if (hal_registerCanGoldwingPdo(&McuData.Pdo.CanIndex1, &McuData.Pdo.CanMsg1) != COMM_OK) {
        ASSERT(0, "MCU PDO 1 CAN message could not be registered");
    }
}

Description:
Removed unneccesary Interfaces like the one above. Only need Tx1, Tx2 & Rx1 in
Option Control Unit. TODO: Cleanup.




