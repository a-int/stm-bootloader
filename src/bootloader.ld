INCLUDE memory_map.ld

ENTRY(Reset_Handler)
_estack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} >BootloaderROM

	.text :
	{
		. = ALIGN(4);
		_stext = .;
		*(.text)
		*(.text*)
		. = ALIGN(4);
		_etext = .;
	} > BootloaderROM
	
	.rodata :
   	{
   		. = ALIGN(4);
    	*(.rodata)         /* .rodata sections (constants, strings, etc.) */
    	*(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
		. = ALIGN(4);
  	} >BootloaderROM

	_sidata = LOADADDR(.data);
	.data :
	{
		. = ALIGN(4);
		_sdata = .;
		
		*(.data)
		*(.data*)
		
		. = ALIGN(4);
		_edata = .;
	} >RAM AT> BootloaderROM

	.bss :
	{
		. = ALIGN(4);
		_sbss = .;

		*(.bss)
		*(.bss*)
		*(COMMON)
		
		. = ALIGN(4);
		_ebss = .;
	}
}