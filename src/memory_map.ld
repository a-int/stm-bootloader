MEMORY{
	BootloaderROM (rx) : ORIGIN = 0x08000000, LENGTH = 20K
	FirmwareROM (rx) : ORIGIN = ORIGIN(BootloaderROM) + LENGTH(BootloaderROM), LENGTH = 492K
	RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
}

_sbootloader = ORIGIN(BootloaderROM);
_ebootloader = ORIGIN(BootloaderROM) + LENGTH(BootloaderROM);
_sfirmware = ORIGIN(FirmwareROM);
_efirmware = ORIGIN(FirmwareROM) + LENGTH(FirmwareROM);