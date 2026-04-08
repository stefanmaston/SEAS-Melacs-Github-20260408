# MelacsTop
Folder tree looks like this: <br />

Top						This document + default HEX-files<br />

+---docs					Documentation<br />

+---include					RTOS<br />

+---iolib					RTOS<br />

+---kernel					RTOS<br />

+---Melacs					Projects<br />

|   +---App_Automation_EthernetAndSD.X<br />

|   +---App_Portable_Automation.X<br />

|   +---App_TestrigMelacs2_Ethernet.X<br />

|   +---App_TestrigMelacs2_Ethernet_4.X<br />

|   +---Application_OEM.X<br />

|   +---Application_TestrigMelacs2.X<br />

+---MelacsDisplay.X				Display code<br />

+---servers					RTOS<br />

+---stdio					RTOS<br />


HEX-file defaultMelacsMain.hex for Melacs copied from<br />

	Download\Melacs_Files_Use this library for Melacs inverter and generator controller\Melacs\MelacsMain\dist\ESK\production\InresolMelacsMain.production.hex<br />

HEX-file defaultDisplay.hex for Display copied from<br />

	Download\workspace_before_git\Display\ColorDispGeneric\hex_scancraft.hex<br />


Changes to display source for xc8 compiler <br />

	const rom 		-> const <br />

	signed short long	-> __int24 <br />

	unsigned short long	-> __uint24 <br />

	rom			-> (removed) <br />

	far			-> (removed) <br />





