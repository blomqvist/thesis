
/*---------------------------------------------------------------------------*/
/*!
    LatchedSpidIn2IncSpeed = Latched high speed rabbit button.
    Normal condition is reduced drive speed by means of OptionMaxSpeedHiRange
    and/or OptionMaxSpeedLoRange. If the designated button is pressed and
    released while driving, and as long as the belly button or arm brake is
    unaffected, the machine will travel in maximum speed controlled by parameter
    ParMaxSpeedHiRange and ParMaxSpeedLoRange.

    If OptSpeed = 0, drive is inhibited and the brake does not get lifted. Can
    be used for a drive restriction option.

    \param SpidAddr Spider address          0 SEU 0
                                            1 SEU 1
                                            2 ACT
    \param DigIn Spider digital in          0..7 for SEU
                                            0..11 for ACT
    \param OptSpeed Speed                   0..125 [km/h / 10]
    \param Range Function range             0 high speed range
                                            1 low speed range
                                            2 both ranges

    \param BuffIndex which option function 0..7 (MSB also used for setup)
*/
/*---------------------------------------------------------------------------*/
void latchedSpidIn2IncSpeed(UByte SpidAddr, UByte DigIn, UByte OptSpeed, UByte Range, UByte BuffIndex)
{
    #define FOPTION_PRESSED_RABBIT  (1 << 0)
    #define FOPTION_LATCHED_RABBIT  (1 << 1)
    #define FOPTION_RABBIT_ALLOWED  (1 << 2)
    UByte OptionIndex = BuffIndex & 0x7F;   // MSB used as init flag. Remove for the option index.

    // Setup
    if (BuffIndex & BUFF_INDEX_SETUP) {
        // Shall input be from ACT or SEU?
        if (SpidAddr >= 2) {
            // Input is in ACT/ACC, no need for special initialization
        }
        else {
            // Check if application uses the input
            if (checkRequestSpiderDigitalIn(SpidAddr, (tSpiderDigitalInType)DigIn) != FALSE) {
                // Request option trigger
                setSpiderOption(SpidAddr);
            }
            else {
                // Disable this option function
                RamParOpt[OptionIndex].ptr = optionDummy;
                errSet(ARG_ERR_SPIDER);
            }
        }
    }
    // Option function
    else {

        /* Increase speed when: * Belly button is unaffected and
                                * Arm brake not activated and
                                * Button connected to Spider digital input is
                                  pressed and released and
                                * Throttle command given and
                                * No instantaneous direction change detected
                                  (throttle may change sign without passing zero) */
        if (hal_isBellyButtonActivated() == FALSE && isOptionBellyButtonActive() == FALSE &&
                getTillerStatus() != FALSE && isBflyNotZero() &&
                (((hal_getBflyPos() > 0) == ((SByte)RamParOpt[OptionIndex].stat.Byte.LoByte > 0)))) {

            // Check if rabbit button has been pressed and released.
            // Driving - Button pressed
            if (getOptionDigitalIn(SpidAddr, DigIn) == FALSE) {
                if ((RamParOpt[OptionIndex].stat.Byte.HiByte & FOPTION_RABBIT_ALLOWED) != FALSE) {
                    // Only detect button if seen released once after entering drive
                    RamParOpt[OptionIndex].stat.Byte.HiByte |= FOPTION_PRESSED_RABBIT;
                }
            }
            else { // Driving - Button released
                // Detection of rabbit button is allowed next time
                RamParOpt[OptionIndex].stat.Byte.HiByte |= FOPTION_RABBIT_ALLOWED;
                if ((RamParOpt[OptionIndex].stat.Byte.HiByte & FOPTION_PRESSED_RABBIT) != FALSE) {
                    // If button was pressed before release, toggle rabbit mode
                    RamParOpt[OptionIndex].stat.Byte.HiByte &= ~FOPTION_PRESSED_RABBIT;

                    RamParOpt[OptionIndex].stat.Byte.HiByte =
                            RamParOpt[OptionIndex].stat.Byte.HiByte ^ FOPTION_LATCHED_RABBIT;
                }
            }
        }
        else {
            // Not driving, clear flags to exit rabbit mode
            RamParOpt[OptionIndex].stat.Byte.HiByte = 0;
        }

        // Store throttle reading for sign check at next call
        RamParOpt[OptionIndex].stat.Byte.LoByte = (UByte)hal_getBflyPos();

        // Set low speed when NOT in rabbit mode
        if ((RamParOpt[OptionIndex].stat.Byte.HiByte & FOPTION_LATCHED_RABBIT) == FALSE) {
            if (Range == 0) {
                // high speed range
                setMaxOptionSpeedHiRangeKmph(OptSpeed);
            }
            else if (Range == 1) {
                // low speed range
                setMaxOptionSpeedLoRangeKmph(OptSpeed);
            }
            else {
                // high and low speed ranges
                setMaxOptionSpeedHiRangeKmph(OptSpeed);
                setMaxOptionSpeedLoRangeKmph(OptSpeed);
            }
        }
    }
}
