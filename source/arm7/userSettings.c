/*---------------------------------------------------------------------------------

	Copyright (C) 2005
		Dave Murphy (WinterMute)

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any
	damages arising from the use of this software.

	Permission is granted to anyone to use this software for any
	purpose, including commercial applications, and to alter it and
	redistribute it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you
			must not claim that you wrote the original software. If you use
			this software in a product, an acknowledgment in the product
			documentation would be appreciated but is not required.
	2.	Altered source versions must be plainly marked as such, and
			must not be misrepresented as being the original software.
	3.	This notice may not be removed or altered from any source
			distribution.

---------------------------------------------------------------------------------*/

#include <ndsi/arm7/serial.h>
#include <ndsi/system.h>
#include <string.h>

//---------------------------------------------------------------------------------
void readUserSettings() {
//---------------------------------------------------------------------------------

	PERSONAL_DATA slots[2];

	short slot1count, slot2count;
	short slot1CRC, slot2CRC;

	uint32 userSettingsBase;
	readFirmware( 0x20, &userSettingsBase,2);

	uint32 slot1Address = userSettingsBase * 8;
	uint32 slot2Address = userSettingsBase * 8 + 0x100;

	readFirmware( slot1Address , &slots[0], sizeof(PERSONAL_DATA));
	readFirmware( slot2Address , &slots[1], sizeof(PERSONAL_DATA));
	readFirmware( slot1Address + 0x70, &slot1count, 2);
	readFirmware( slot2Address + 0x70, &slot2count, 2);
	readFirmware( slot1Address + 0x72, &slot1CRC, 2);
	readFirmware( slot2Address + 0x72, &slot2CRC, 2);

	// default to slot 1 user Settings
	int currentSettingsSlot = 0;

	short calc1CRC = swiCRC16( 0xffff, &slots[0], sizeof(PERSONAL_DATA));
	short calc2CRC = swiCRC16( 0xffff, &slots[1], sizeof(PERSONAL_DATA));

	// bail out if neither slot is valid
	if ( calc1CRC != slot1CRC && calc2CRC != slot2CRC) return;

	// if both slots are valid pick the most recent
	if ( calc1CRC == slot1CRC && calc2CRC == slot2CRC ) {
		currentSettingsSlot = (slot2count == (( slot1count + 1 ) & 0x7f) ? 1 : 0);
	} else {
		if ( calc2CRC == slot2CRC )
			currentSettingsSlot = 1;
	}
	*PersonalData = slots[currentSettingsSlot];

}
