/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// in_null.c -- for systems without a mouse

#include "quakedef.h"

#ifdef FLASH
byte _asToQKey[256];

float	mouse_x, mouse_y;
float	old_mouse_x, old_mouse_y;

cvar_t	m_filter = {"m_filter","0"};

#endif

void IN_Init (void)
{
#ifdef FLASH
	Cvar_RegisterVariable (&m_filter);

	//Use mouse look by default
	in_mlook.state = 1;

	//Set the Actionscript to Quake keyboard mappings

	_asToQKey[9] = K_TAB;

	//Copied from http://flash-creations.com/notes/asclass_key.php
	//Ascii()  	String  	Code
/*27 	.(esc) 	*/ _asToQKey[27] = K_ESCAPE;
/*8 	.(backspace) 	*/ _asToQKey[8] = K_BACKSPACE;
///*0 	(capslock) 	*/ _asToQKey[20] = 
/*0 	(shift) 	*/ _asToQKey[16] = K_SHIFT;
/*	(alt) 	*/ _asToQKey[18] = K_ALT;
/*0 	(ctrl) 	*/ _asToQKey[17] = K_CTRL;
/*13 	(enter) 	*/ _asToQKey[13] = K_ENTER;
/*32 	(space) 	*/ _asToQKey[32] = K_SPACE;
/*function keys
/*0 	(F1) 	*/ _asToQKey[112] = K_F1;
/*0 	(F2) 	*/ _asToQKey[113] = K_F2;
/*0 	(F3) 	*/ _asToQKey[114] = K_F3;
/*0 	(F4) 	*/ _asToQKey[115] = K_F4;
/*0 	(F5) 	*/ _asToQKey[116] = K_F5;
/*0 	(F6) 	*/ _asToQKey[117] = K_F6;
/*0 	(F7) 	*/ _asToQKey[118] = K_F7;
/*0 	(F8) 	*/ _asToQKey[119] = K_F8;
/*0 	(F9) 	*/ _asToQKey[120] = K_F9;
/*0 	(F10) 	*/ _asToQKey[121] = K_F10;
/*0 	(F11) 	*/ _asToQKey[122] = K_F11;
/*0 	(F12) 	*/ _asToQKey[123] = K_F12;
/*letters and other main keybd w/shift key on
/*126 	~ 	*/ _asToQKey[192] = '~';
/*33 	! 	*/ _asToQKey[49] = '!';
/*64 	@ 	*/ _asToQKey[50] = '@';
/*35 	# 	*/ _asToQKey[51] = '#';
/*36 	$ 	*/ _asToQKey[52] = '$';
/*37 	% 	*/ _asToQKey[53] = '%';
/*94 	^ 	*/ _asToQKey[54] = '^';
/*38 	& 	*/ _asToQKey[55] = '&';
/*42 	* 	*/ _asToQKey[56] = '*';
/*40 	( 	*/ _asToQKey[57] = '(';
/*41 	) 	*/ _asToQKey[48] = ')';
/*95 	_ 	*/ _asToQKey[189] = '_';
/*43 	+ 	*/ _asToQKey[187] = '+';
/*124 	| 	*/ _asToQKey[220] = '|';
/*81 	Q 	*/ _asToQKey[81] = 'Q';
/*87 	W 	*/ _asToQKey[87] = 'W';
/*69 	E 	*/ _asToQKey[69] = 'E';
/*82 	R 	*/ _asToQKey[82] = 'R';
/*84 	T 	*/ _asToQKey[84] = 'T';
/*89 	Y 	*/ _asToQKey[89] = 'Y';
/*85 	U 	*/ _asToQKey[85] = 'U';
/*73 	I 	*/ _asToQKey[73] = 'I';
/*79 	O 	*/ _asToQKey[79] = 'O';
/*80 	P 	*/ _asToQKey[80] = 'P';
/*123 	{ 	*/ _asToQKey[219] = '{';
/*125 	} 	*/ _asToQKey[221] = '}';
/*65 	A 	*/ _asToQKey[65] = 'A';
/*83 	S 	*/ _asToQKey[83] = 'S';
/*68 	D 	*/ _asToQKey[68] = 'D';
/*70 	F 	*/ _asToQKey[70] = 'F';
/*71 	G 	*/ _asToQKey[71] = 'G';
/*72 	H 	*/ _asToQKey[72] = 'H';
/*74 	J 	*/ _asToQKey[74] = 'J';
/*75 	K 	*/ _asToQKey[75] = 'K';
/*76 	L 	*/ _asToQKey[76] = 'L';
/*58 	: 	*/ _asToQKey[186] = ':';
/*34 	" 	*/ _asToQKey[222] = '"';
/*90 	Z 	*/ _asToQKey[90] = 'Z';
/*88 	X 	*/ _asToQKey[88] = 'X';
/*67 	C 	*/ _asToQKey[67] = 'C';
/*86 	V 	*/ _asToQKey[86] = 'V';
/*66 	B 	*/ _asToQKey[66] = 'B';
/*78 	N 	*/ _asToQKey[78] = 'N';
/*77 	M 	*/ _asToQKey[77] = 'M';
/*60 	< 	*/ _asToQKey[188] = '<';
/*62 	> 	*/ _asToQKey[190] = '>';
/*63 	? 	*/ _asToQKey[191] = '?';
/*letters and other main keybd, no shift
/*96 	` 	*/ _asToQKey[223] = '`';
/*49 	1 	*/ _asToQKey[49] = '1';
/*50 	2 	*/ _asToQKey[50] = '2';
/*51 	3 	*/ _asToQKey[51] = '3';
/*52 	4 	*/ _asToQKey[52] = '4';
/*53 	5 	*/ _asToQKey[53] = '5';
/*54 	6 	*/ _asToQKey[54] = '6';
/*55 	7 	*/ _asToQKey[55] = '7';
/*56 	8 	*/ _asToQKey[56] = '8';
/*57 	9 	*/ _asToQKey[57] = '9';
/*48 	0 	*/ _asToQKey[48] = '0';
/*45 	- 	*/ _asToQKey[189] = '-';
/*61 	= 	*/ _asToQKey[187] = '=';
/*92 	\ 	*/ _asToQKey[220] = '\\';
/*113 	q 	*/ _asToQKey[81] = 'q';
/*119 	w 	*/ _asToQKey[87] = 'w';
/*101 	e 	*/ _asToQKey[69] = 'e';
/*114 	r 	*/ _asToQKey[82] = 'r';
/*116 	t 	*/ _asToQKey[84] = 't';
/*121 	y 	*/ _asToQKey[89] = 'y';
/*117 	u 	*/ _asToQKey[85] = 'u';
/*105 	i 	*/ _asToQKey[73] = 'i';
/*111 	o 	*/ _asToQKey[79] = 'o';
/*112 	p 	*/ _asToQKey[80] = 'p';
/*91 	[ 	*/ _asToQKey[219] = '[';
/*93 	] 	*/ _asToQKey[221] = ']';
/*97 	a 	*/ _asToQKey[65] = 'a';
/*115 	s 	*/ _asToQKey[83] = 's';
/*100 	d 	*/ _asToQKey[68] = 'd';
/*102 	f 	*/ _asToQKey[70] = 'f';
/*103 	g 	*/ _asToQKey[71] = 'g';
/*104 	h 	*/ _asToQKey[72] = 'h';
/*106 	j 	*/ _asToQKey[74] = 'j';
/*107 	k 	*/ _asToQKey[75] = 'k';
/*108 	l 	*/ _asToQKey[76] = 'l';
/*59 	; 	*/ _asToQKey[186] = ';';
/*39 	' 	*/ _asToQKey[222] = '\'';
/*122 	z 	*/ _asToQKey[90] = 'z';
/*120 	x 	*/ _asToQKey[88] = 'x';
/*99 	c 	*/ _asToQKey[67] = 'c';
/*118 	v 	*/ _asToQKey[86] = 'v';
/*98 	b 	*/ _asToQKey[66] = 'b';
/*110 	n 	*/ _asToQKey[78] = 'n';
/*109 	m 	*/ _asToQKey[77] = 'm';
/*44 	, 	*/ _asToQKey[188] = ',';
/*46 	. 	*/ _asToQKey[190] = '.';
/*47 	/ 	*/ _asToQKey[191] = '/';
/*keypad keys w/numlock on
/*47 	/ 	*/ _asToQKey[111] = '/';
/*42 	* 	*/ _asToQKey[106] = '*';
/*45 	- 	*/ _asToQKey[109] = '-';
/*55 	7 	*/ _asToQKey[103] = '7';
/*56 	8 	*/ _asToQKey[104] = '8';
/*57 	9 	*/ _asToQKey[105] = '9';
/*52 	4 	*/ _asToQKey[100] = '4';
/*53 	5 	*/ _asToQKey[101] = '5';
/*54 	6 	*/ _asToQKey[102] = '6';
/*49 	1 	*/ _asToQKey[97] = '1';
/*50 	2 	*/ _asToQKey[98] = '2';
/*51 	3 	*/ _asToQKey[99] = '3';
/*48 	0 	*/ _asToQKey[96] = '0';
/*46 	. 	*/ _asToQKey[110] = '.';
/*13 		*/ _asToQKey[13] = '3';
/*43 	+ 	*/ _asToQKey[107] = '+';
/*keypad keys w/numlock off
/*47 	/ 	*/ _asToQKey[111] = '/';
/*42 	* 	*/ _asToQKey[106] = '*';
/*45 	- 	*/ _asToQKey[109] = '-';
/*0 	(Home) 	*/ _asToQKey[36] = K_HOME;
/*0 	(up arrow) 	*/ _asToQKey[38] = K_UPARROW;
/*0 	(PgUp) 	*/ _asToQKey[33] = K_PGUP;
/*0 	(left arrow) 	*/ _asToQKey[37] = K_LEFTARROW;
///*0 		*/ _asToQKey[12] = 
/*0 	(right arrow) 	*/ _asToQKey[39] = K_RIGHTARROW;
/*0 	(End) 	*/ _asToQKey[35] = K_END;
/*0 	(down arrow) 	*/ _asToQKey[40] = K_DOWNARROW;
/*0 	(PgDown) 	*/ _asToQKey[34] = K_PGUP;
/*0 	(Ins) 	*/ _asToQKey[45] = K_INS;
/*127 	(Del) 	*/ _asToQKey[46] = K_DEL;
/*13 	(Enter) 	*/ _asToQKey[13] = K_ENTER;
/*43 	+ 	*/ _asToQKey[107] = '+';
/*middlekeys
///*0 	(ScrollLock) 	*/ _asToQKey[145] = 
/*0 	(Pause) 	*/ _asToQKey[19] = K_PAUSE;
/*0 	(Ins) 	*/ _asToQKey[45] = K_INS;
/*0 	(Home) 	*/ _asToQKey[36] = K_HOME;
/*0 	(PageUp) 	*/ _asToQKey[33] = K_PGUP;
/*127 	(Delete) 	*/ _asToQKey[46] = K_DEL;
/*0 	(End) 	*/ _asToQKey[35] = K_END;
/*0 	(PageDown) 	*/ _asToQKey[34] = K_PGDN;
/*arrowkeys
/*0 	(left) 	*/ _asToQKey[37] = K_LEFTARROW;
/*0 	(up) 	*/ _asToQKey[38] = K_UPARROW;
/*0 	(down) 	*/ _asToQKey[40] = K_DOWNARROW;
/*0 	(right) */ _asToQKey[39]  = K_RIGHTARROW;
#endif //ifdef FLASH
}

void IN_Shutdown (void)
{
}

void IN_Commands (void)
{
}

#ifdef FLASH
void IN_MouseMove (usercmd_t *cmd)
{
	float mx = mouse_x;
	float my = mouse_y;

	if (m_filter.value)
	{
		mouse_x = (mouse_x + old_mouse_x) * 0.5;
		mouse_y = (mouse_y + old_mouse_y) * 0.5;
	}
	old_mouse_x = mx;
	old_mouse_y = my;

	mouse_x *= sensitivity.value;
	mouse_y *= sensitivity.value;

// add mouse X/Y movement to cmd
	if ( (in_strafe.state & 1) || (lookstrafe.value && (in_mlook.state & 1) ))
		cmd->sidemove += m_side.value * mouse_x;
	else
		cl.viewangles[YAW] -= m_yaw.value * mouse_x;
	
	if (in_mlook.state & 1)
		V_StopPitchDrift ();
		
	if ( (in_mlook.state & 1) && !(in_strafe.state & 1))
	{
		cl.viewangles[PITCH] += m_pitch.value * mouse_y;
		if (cl.viewangles[PITCH] > 80)
			cl.viewangles[PITCH] = 80;
		if (cl.viewangles[PITCH] < -70)
			cl.viewangles[PITCH] = -70;
	}
	else
	{
		if ((in_strafe.state & 1) && noclip_anglehack)
			cmd->upmove -= m_forward.value * mouse_y;
		else
			cmd->forwardmove -= m_forward.value * mouse_y;
	}

	mouse_x = 0.0f;
	mouse_y = 0.0f;
}
#endif

void IN_Move (usercmd_t *cmd)
{
#ifdef FLASH
	IN_MouseMove(cmd);
#endif
}

