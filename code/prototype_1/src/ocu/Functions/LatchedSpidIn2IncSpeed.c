#include "../Functions.h"
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
}
