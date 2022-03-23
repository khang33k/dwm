/*  ____ _____  */
/* |  _ \_   _|  Derek Taylor (DistroTube) */
/* | | | || |  	http://www.youtube.com/c/DistroTube */
/* | |_| || |  	http://www.gitlab.com/dwt1/ */
/* |____/ |_|  	*/ 

/* See LICENSE file for copyright and license details. */
/* appearance */

static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappx    = 2;   /* pixel gap between clients */
static const int horizpadbar       = 6;   /* horizontal padding for statusbar */
static const int vertpadbar        = 7;   /* vertical padding for statusbar */
/* Mononoki Nerd Font must be installed from AUR nerd-fonts-complete.
 * Otherwise, your default font will be Hack which is found in the standard
 * Arch repos and is listed as a dependency for this build. JoyPixels is also
 * a hard dependency and makes colored fonts and emojis possible.
 */

static char font[]            = "SauceCodePro Nerd Font Mono:weight=bold:size=14:antialias=true:hinting=true" ;

static char dmenufont[]       = "SauceCodePro Nerd Font Mono:weight=bold:size=13:antialias=true:hinting=true" ;
static const char *fonts[]     = { font, "SauceCodePro Nerd Font Mono:weight=bold:size=13:antialias=true:hinting=true",
	                              "Mononoki:size=13:antialias=true:autohint=true",
                                  "Hack:size=8:antialias=true:autohint=true",
                                  "JoyPixels:size=10:antialias=true:autohint=true"
				     	};
/* bar opacity 
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static const unsigned int baralpha    = 0xff; 
static const unsigned int borderalpha = OPAQUE;

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
 };
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
*/ static const char *tags[] = { "dev", "www", "sys", "doc", "vbox", "chat", "mus", "vid", "gfx" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */

static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */

static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
/* If you are using the dmenu-distrotube-git program, use the following for a cooler dmenu! */
/* static const char *dmenucmd[]    = { "dmenu_run", "-g", "10", "-l", "48", "-p", "Run: ", NULL }; */

/* the st terminal with tabbed */
static const char *termcmd[]     = { "alacritty", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
 { "color0",		STRING,	&normbordercolor },
 		{ "color8",		STRING,	&selbordercolor },
 		{ "color0",		STRING,	&normbgcolor },
 		{ "color4",		STRING,	&normfgcolor },
 		{ "color0",		STRING,	&selfgcolor },
 		{ "color4",		STRING,	&selbgcolor },	{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

/* An alternative way to launch st along with the fish shell */
/* static const char *termcmd[]     = { "st", "-e fish", NULL }; */
static const char *tabtermcmd[]  = { "tabbed", "-r", "2", "st", "-w", "''", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier             chain key  key        function        argument */
	{ MODKEY,     -1,        XK_d, spawn,          {.v = dmenucmd } },
	{ MODKEY,               -1,        XK_Return, spawn,          {.v = termcmd } },
	{ Mod1Mask,             -1,        XK_Return, spawn,          {.v = tabtermcmd } },
	{ MODKEY,               -1,        XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,               -1,        XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,               -1,        XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,               -1,        XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,               -1,        XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,               -1,        XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,               -1,        XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,   -1,        XK_Return, zoom,           {0} },
	{ MODKEY,               -1,        XK_Tab,    view,           {0} },
	{ MODKEY,     -1,      XK_q,      killclient,     {0} },

	{ MODKEY|ShiftMask,     -1,      XK_l,      spawn,     CMD("slock") },
    /* Layout manipulation */
	{ MODKEY,               -1,        XK_Tab,    cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_Tab,    cyclelayout,    {.i = +1 } },
	{ MODKEY,               -1,        XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_space,  togglefloating, {0} },

    /* Switch to specific layouts */
	{ MODKEY,               -1,        XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               -1,        XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               -1,        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               -1,        XK_g,      setlayout,      {.v = &layouts[3]} },

	{ MODKEY,               -1,        XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     -1,        XK_0,      tag,            {.ui = ~0 } },

    /* Switching between monitors */
	{ MODKEY,               -1,        XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,               -1,        XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_period, tagmon,         {.i = +1 } },
	
    /* Keybindings for programs using the format SUPER + ALT + "key" */
	{ MODKEY|Mod1Mask,      -1,        XK_s,      spawn,          CMD("tabbed -r 2 surf -pe x '.surf/html/homepage.html'") },
	{ MODKEY,      -1,        XK_w,      spawn,          CMD("firefox") },
	{ MODKEY|ShiftMask,      -1,        XK_w,      spawn,          CMD("firefox --private-window") },
	{ MODKEY|Mod1Mask,      -1,        XK_m,      spawn,          CMD("mailspring") },
	{ MODKEY,      -1,        XK_n,      spawn,          CMD("pcmanfm") },
	
    /* Dmenu scripts launched with emacs-style keychords SUPER + p followed by "key" */
	{ MODKEY,               XK_p,      XK_e,      spawn,          CMD("./dmscripts/dm-confedit") },
	{ MODKEY,               XK_p,      XK_i,      spawn,          CMD("./dmscripts/dm-maim") },
	{ MODKEY,               XK_p,      XK_k,      spawn,          CMD("./dmscripts/dm-kill") },
	{ MODKEY,               XK_p,      XK_l,      spawn,          CMD("./dmscripts/dm-logout") },
	{ MODKEY,               XK_p,      XK_m,      spawn,          CMD("./dmscripts/dm-man") },
	{ MODKEY,               XK_p,      XK_r,      spawn,          CMD("./dmscripts/dm-reddit") },
	{ MODKEY,               XK_p,      XK_s,      spawn,          CMD("./dmscripts/dm-websearch") },
	{ MODKEY,               XK_p,      XK_p,      spawn,          CMD("passmenu") },
    
    /* Doom emacs keybindings use the keychord CTRL + e followed by "key" */
	{ ControlMask,          XK_e,      XK_e,      spawn,          CMD("emacsclient -c -a 'emacs'") },
	{ ControlMask,          XK_e,      XK_b,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(ibuffer)'") },
	{ ControlMask,          XK_e,      XK_d,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(dired nil)'") },
	{ ControlMask,          XK_e,      XK_m,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(mu4e)'") },
	{ ControlMask,          XK_e,      XK_n,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(elfeed)'") },
	{ ControlMask,          XK_e,      XK_s,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(eshell)'") },
	{ ControlMask,          XK_e,      XK_v,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(+vterm/here nil)'") },

	TAGKEYS(                -1,        XK_1,                      0)
	TAGKEYS(                -1,        XK_2,                      1)
	TAGKEYS(                -1,        XK_3,                      2)
	TAGKEYS(                -1,        XK_4,                      3)
	TAGKEYS(                -1,        XK_5,                      4)
	TAGKEYS(                -1,        XK_6,                      5)
	TAGKEYS(                -1,        XK_7,                      6)
	TAGKEYS(                -1,        XK_8,                      7)
	TAGKEYS(                -1,        XK_9,                      8)
	{ MODKEY|ShiftMask,     -1,        XK_q,	  quit,		      {0} },
    { MODKEY|ShiftMask,     -1,        XK_r,      quit,           {1} }, 

	{ 0, -1, XF86XK_MonBrightnessUp,	spawn,		CMD("xbacklight -inc 10") },
	{ 0, -1, XF86XK_MonBrightnessDown,	spawn,		CMD("xbacklight -dec 5") },

	{ MODKEY|ShiftMask,          -1,      XK_n,      spawn,          CMD("alacritty -e nmtui") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};


