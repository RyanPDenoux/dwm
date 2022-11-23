/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define BROWSER "brave"
#define MODKEY Mod4Mask
#define SESSION_FILE "/tmp/dwm-session"
#define STATUSBAR "dwmblocks"

/* appearance */
#include <X11/X.h>
static unsigned int borderpx		 = 2;      /* border pixel of windows */
static unsigned int snap			 = 32;     /* snap pixel */
static const unsigned int gappih	 = 12;	   /* horizontal inner gap between windows */
static const unsigned int gappiv	 = 12;	   /* vertical inner gap between windows */
static const unsigned int gappoh	 = 12;	   /* horizontal outer gap between windows and screen edge */
static const unsigned int gappov	 = 32;	   /* vertical outer gap between windows and screedn edge */
static int smartgaps				 = 0;      /* 1 means no outer gap when there is only one window */
static int swallowfloating			 = 0;      /* 1 means swallow floating windows by default */
static int showbar					 = 1;      /* 0 means no bar */
static int topbar					 = 1;      /* 0 means bottom bar */
static const int horizpadbar		 = 4;      /* horizontal padding for statusbar */
static const int vertpadbar			 = 8;      /* vertical padding for statusbar */
static char font[]					 = "monospace:size=12";
static char dmenufont[]				 = "monospace:size=12";
static const char *fonts[]			 = { font };
static char normbgcolor[]			 = "#002b36";
static char normbordercolor[]		 = "#073642";
static char normfgcolor[]			 = "#93a1a1";
static char selfgcolor[]			 = "#eee8d5";
static char selbordercolor[]		 = "#268bd2";
static char selbgcolor[]			 = "#268bd2";
static char *colors[][3]			 = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "💽", "💬", "📨", "📷", "☁", "🎶", "📄", "🔤", "🌐" };
static const int taglayouts[] = { 0, 2, 0, 0, 0, 0, 0, 0, 0 };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	     instance    title    tags mask  isfloating  CenterThisWindow?  isterminal  noswallow  monitor float x,y,w,h   floatborderpx */
	{ "St",              NULL,       NULL,    0,         0,          1,                 1,          0,         -1, 	   50,50,500,500,  5 },
	{ "Emacs",           NULL,       NULL,    0,         0,          1,                 1,          0,         -1, 	   50,50,500,500,  5 },
	{ "Nextcloud",       "nextcloud",NULL,    0,         1,          0,                 0,          0,         -1, 	   2700,50,500,800,  5 },
	{ NULL,          NULL, "Event Tester",    0,         0,          1,                 1,          1,         -1, 	   50,50,500,500,  5 },
	{ NULL,          NULL,   "pulsemixer",    0,         1,          0,                 1,          0,         -1, 	   2800,50,600,300,  5 },
	{ "mpv",             NULL,       NULL,    0,         0,          1,                 1,          0,         -1, 	   50,50,500,500,  5 },
	{ "Anki",            NULL,       NULL,    0,         0,          1,                 1,          0,         -1, 	   50,50,500,500,  5 },
	{ "Signal",          NULL,       NULL,    1 << 1,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ "discord",         NULL,       NULL,    1 << 1,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ "whatsapp-nativefier-d40211", NULL, NULL, 1 << 1,  0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ NULL,              NULL,  "neomutt",    1 << 2,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ NULL,              NULL, "calcurse",    1 << 2,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ "Gimp",            NULL,       NULL,    1 << 3,    1,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ "spotify",         NULL,       NULL,    1 << 5,    0,          1,                 1,          0,         -1, 	   50,50,500,500,  5 },
	{ "pocket-casts-linux", NULL,    NULL,    1 << 5,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ "libreoffice-writer", NULL,    NULL,    1 << 6,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ NULL, NULL,       "Mozilla Firefox",    1 << 7,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
	{ "Brave-browser",   NULL,       NULL,    1 << 8,    0,          1,                 0,          0,         -1, 	   50,50,500,500,  5 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "color0",             STRING,  &normbgcolor },
		{ "color0",             STRING,  &normbordercolor },
		{ "color8",             STRING,  &normfgcolor },
		{ "color4",             STRING,  &selbgcolor },
		{ "color4",             STRING,  &selbordercolor },
		{ "color0",             STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|Mod1Mask,              XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("passmenu") },
	{ MODKEY,                       XK_grave,  spawn,          SHCMD("dmenuunicode") },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("dmenusarcastify") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
	{ MODKEY,                       XK_f,      spawn,          SHCMD(TERMINAL " -e lfenv") },
	{ MODKEY,                       XK_m,      spawn,          SHCMD(TERMINAL " -e neomutt; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
	{ MODKEY|ControlMask,           XK_m,      spawn,          SHCMD(TERMINAL " -e calcurse") },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD(TERMINAL " -e newsboat-surf; pkill -RTMIN+6 dwmblocks") },
	{ 0,                            XK_Print,  spawn,          SHCMD("screengrab") },
	{ 0|ShiftMask,                  XK_Print,  spawn,          SHCMD("windowgrab") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " -e $VISUAL") },
	{ MODKEY,                       XK_c,      spawn,          SHCMD(TERMINAL " -e pulsemixer") },
	{ 0,                            XF86XK_AudioMute, spawn,   SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("pamixer --allow-boost -i 2; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("pamixer --allow-boost -d 2; kill -44 $(pidof dwmblocks)") },
	{ 0,                            XF86XK_AudioPrev, spawn,   SHCMD("playerctl previous") },
	{ 0,                            XF86XK_AudioNext, spawn,   SHCMD("playerctl next") },
	{ 0,                            XF86XK_AudioPause, spawn,  SHCMD("playerctl play-pause") },
	{ 0,                            XF86XK_AudioPlay, spawn,   SHCMD("playerctl play-pause") },
	{ 0,                            XF86XK_AudioStop, spawn,   SHCMD("playerctl stop") },
	{ 0,                            XF86XK_AudioRewind, spawn, SHCMD("playerctl position -10") },
	{ 0,                            XF86XK_AudioForward, spawn, SHCMD("playerctl position +10") },
	{ 0,                            XF86XK_AudioMedia, spawn,  SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0,                            XF86XK_AudioMicMute, spawn, SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set 10%+") },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 10%-") },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      spawn,          SHCMD("sysact") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

