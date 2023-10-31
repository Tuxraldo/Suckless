/* See LICENSE file for copyright and license details. */

/* Default color scheme */
#include "/home/tdr/.dwm/dwm-themes/dark_pastel.h"

/* appearance */
static const unsigned int borderpx  	  = 2;        /* border pixel of windows */
static const unsigned int gappx     	  = 8;        /* gaps between windows */
static const unsigned int snap      	  = 32;       /* snap pixel */
static const unsigned int systraypinning  = 0;  	  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;        /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 2;        /* systray spacing */
static const unsigned int systrayiconsize = 16;       /* systray icon size in px */
static const int systraypinningfailfirst  = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        	  = 1;        /* 0 means no systray */
static const int showbar            	  = 1;        /* 0 means no bar */
static const int topbar             	  = 1;        /* 0 means bottom bar */
static const int user_bh            	  = 24;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          	  = { "JetBrainsMono Nerd Font:size=9" };
static const char dmenufont[]       	  = "JetBrainsMono Nerd Font:size=9";
static const char *colors[][3]      	  = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fgn, col_bgn, col_bn},
    [SchemeSel]  = { col_fgs, col_bgs, col_bs},
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 * SwitchTag: 0 is default behaviour, view is not changed
     *            1 automatically moves you to the tag of the newly opened application
     *            2 enables the tag of the newly opened application in addition to your existing enabled tags
     *            3 as 1, but closing that window reverts the view back to what it was before opening the client *
     *            4 as 2, but closing that window reverts the view back to what it was before opening the client *
     */
	/* class                        instance    title       tags mask     switchtag    isfloating   monitor */
    { "Galculator",                 NULL,       NULL,       0,            0,            1,           -1 },
    { "firefox",                    NULL,       NULL,       0,            0,            0,           -1 },
	{ "Firefox-esr",                NULL,       NULL,       1 << 1,       0,            0,           -1 },
    { "Thunar",                     NULL,       NULL,       1 << 3,       1,            0,           -1 },
    { "Evince",                     NULL,       NULL,       1 << 6,       1,            0,           -1 },
    { "Gimp-2.10",                  NULL,       NULL,       1 << 6,       1,            0,           -1 },
    { "libreoffice-startcenter",    NULL,       NULL,       1 << 6,       0,            0,           -1 },
    { "libreoffice-writer",         NULL,       NULL,       1 << 6,       0,            0,           -1 },
    { "Mousepad",                   NULL,       NULL,       1 << 6,       1,            0,           -1 },
    { "Mednaffe",                   NULL,       NULL,       1 << 7,       1,            0,           -1 },
    { "mGBA",                       NULL,       NULL,       1 << 7,       0,            0,           -1 },
    { "ResidualVM",                 NULL,       NULL,       1 << 7,       0,            0,           -1 },
    { "scummVM",                    NULL,       NULL,       1 << 7,       0,            0,           -1 },
    { "KeePassXC",                  NULL,       NULL,       1 << 8,       1,            0,           -1 },
    { "qBittorrent",                NULL,       NULL,       1 << 8,       1,            0,           -1 },
    { "SiriKali",                   NULL,       NULL,       1 << 8,       1,            0,           -1 },
    { "Virt-manager",               NULL,       NULL,       1 << 8,       1,            0,           -1 },
};

/* layout(s) */
static const float mfact     	= 0.50;      	     /* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;         	     /* number of clients in master area */
static const int resizehints 	= 0;         	     /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;         	     /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                            /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },                            /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu", NULL };
static const char *termcmd[]  = { "xfce4-terminal", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        	     function            argument */
	{ MODKEY,	                    XK_Return, 	     spawn,              {.v = termcmd } },		    /* Defaul terminal emulator */
	{ MODKEY,                       XK_b,      	     togglebar,          {0} },			            /* Toggle dwm bar */
	{ MODKEY,                       XK_Left,   	     focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_Right,  	     focusstack,         {.i = -1 } },
	{ Mod1Mask,                     XK_Tab,  	     focusstack,         {.i = -1 } },		        /* Focus on next window */
	{ MODKEY,                       XK_v,      	     incnmaster,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_v,            incnmaster,         {.i = -1 } },
	{ MODKEY,                       XK_h,      	     setmfact,           {.f = -0.05} },            /* Decrease window size */
	{ MODKEY,                       XK_l,      	     setmfact,           {.f = +0.05} },            /* Increase window size */
    { MODKEY|ShiftMask,             XK_h,            setmfact,           {.f = 1.0 + mfact } },     /* Restore window size */
	{ MODKEY,                       XK_k,            setcfact,           {.f = +0.25} },            /* Increase window cfacts */            
	{ MODKEY,                       XK_j,            setcfact,           {.f = -0.25} },            /* Decrease window cfacts */
	{ MODKEY|ShiftMask,             XK_j,            setcfact,           {.f =  0.00} },            /* Restore wndow cfacts */
	{ MODKEY|ShiftMask,             XK_Left,         movestack,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,        movestack,          {.i = -1 } },
	{ MODKEY,                       XK_Return, 	     zoom,               {0} },
	{ MODKEY,                       XK_Tab,    	     view,               {0} },
	{ MODKEY,	                    XK_q,      	     killclient,         {0} },			            /* Kill focused window */
	{ MODKEY,                       XK_e,      	     setlayout,          {.v = &layouts[0]} },	    /* Default Master/Stacking */
	{ MODKEY|ShiftMask,             XK_m,      	     setlayout,          {.v = &layouts[1]} },	    /* Monocle Mode */
	{ MODKEY|ShiftMask,             XK_f,      	     setlayout,          {.v = &layouts[2]} },	    /* Float */
	{ MODKEY,                       XK_m,     	     setlayout,          {0} },
	{ MODKEY|ShiftMask,             XK_space,  	     togglefloating,     {0} },
	{ MODKEY,	                    XK_f,      	     togglefullscr,      {0} },			            /* Fullscreen */
	{ MODKEY,                       XK_minus,  	     setgaps,            {.i = -1 } },		        /* Decrease gaps */
	{ MODKEY,                       XK_equal,  	     setgaps,            {.i = +8 } },		        /* Increase gaps */
	{ MODKEY|ShiftMask,             XK_equal,  	     setgaps,            {.i = 0  } },		        /* No gaps */
	{ ControlMask|Mod1Mask,         XK_Left,   	     viewtoleft,         {0} },			            /* Move to left tag */	
    { ControlMask|Mod1Mask,         XK_Right,  	     viewtoright,        {0} },			            /* Move to right tag */
    { ControlMask|MODKEY,           XK_Left,   	     tagtoleft,          {0} },			            /* Move window to left tag */
    { ControlMask|MODKEY,           XK_Right,  	     tagtoright,         {0} },			            /* Move window to right tag */
	{ MODKEY|ControlMask,           XK_comma,  	     focusmon,           {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, 	     focusmon,           {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  	     tagmon,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 	     tagmon,             {.i = +1 } },
	TAGKEYS(                        XK_1,      	                         0)
	TAGKEYS(                        XK_2,      	                         1)
	TAGKEYS(                        XK_3,      	                         2)
	TAGKEYS(                        XK_4,      	                         3)
	TAGKEYS(                        XK_5,      	                         4)
	TAGKEYS(                        XK_6,      	                         5)
	TAGKEYS(                        XK_7,      	                         6)
	TAGKEYS(                        XK_8,      	                         7)
	TAGKEYS(                        XK_9,      	                         8)
	{ MODKEY|ShiftMask,             XK_e,      	     quit,               {0} },			            /* Exit dwm */

/* Sem uso 
* 	{ MODKEY|ShiftMask,             XK_o,      	     view,               {.ui = ~0 } },
*	{ MODKEY|ShiftMask,             XK_p,      	     tag,                {.ui = ~0 } },
 */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

