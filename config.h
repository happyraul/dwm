/* See LICENSE file for copyright and license details. */

/* -*--*-*-*-*-*-*-*-*- GAPS -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
#define GAPS_START 38
#define BORDERPX_START 0

/* -*-*-*-*-*-*-*-*- FLOATING BAR -*-*-*-*-*-*-*-*-*-*-*-*-*-* */
static const int vertpad = GAPS_START - GAPS_START / 3; // vertical padding of bar
static const int sidepad = GAPS_START - GAPS_START / 3; // horizontal padding of bar

/* appearance */
static const unsigned int borderpx  = BORDERPX_START;  /* border pixel of windows */
static const unsigned int gappx     = GAPS_START;      /* gaps between windows */
static const unsigned int snap      = 32;              /* snap pixel */
static const int showbar            = 1;               /* 0 means no bar */
static const int topbar             = 1;               /* 0 means bottom bar */
/* static const char *fonts[]          = { "monospace:size=16" }; */
static const char *fonts[]          = { "ShureTechMono Nerd Font:size=12" };
/* static const char dmenufont[]       = "monospace:size=16"; */
static const char dmenufont[]       = "ShureTechMono Nerd Font:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* */
/*
 * cool emojis to use for tags:
 *
 * "", "爵", "", "", "ﭮ", "", "", "", "","", "﬐", "ﳨ"
 * "ﯙ", "", "", "", "", "", "", "", "", "", "", ""
 * "", "", "", "", "", "", "", "", "", "", "", "", "ﭮ"
 * "", "", "", "", "", "", "", "", "", "聆", "", "阮"
 * "", "", "", "", "", "",
 */
/* tagging */
static const char *tags[] = { "", "", "", "", "聆", "", "", "", "" };
/* static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance        title       tags mask     isfloating   monitor */
	{ "st-256color",   "st-256color",   NULL,       0,            0,           -1 },
	{ "firefox",       NULL,            NULL,       1 << 1,       0,           -1 },
	{ "Sublime_text",  "sublime_text",  NULL,       1 << 2,       0,           -1 },
	{ "Slack",         "slack",         NULL,       1 << 3,       0,           -1 },
	{ "Chromium",      "chromium",      NULL,       1 << 3,       0,           -1 },
	{ "Franz",         "franz",         NULL,       1 << 4,       0,           -1 },
	{ "Signal",        "signal",        NULL,       1 << 4,       0,           -1 },
	{ "Spotify",       "spotify",       NULL,       1 << 5,       0,           -1 },
	{ "Authy desktop", "authy desktop", NULL,       1 << 6,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

// #include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "| ",      tile },    /* first entry is default */
	{ "| 缾",      NULL },    /* no layout function means floating behavior */
	{ "| ",      monocle },
	// { "TTT",      bstack },
	// { "===",      bstackhoriz },
	{ "| M",      centeredmaster },
	{ "| >M>",    centeredfloatingmaster },
	// { "| [@]",      spiral },
	// { "| [\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
/* #define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", "-f", "mono:size=18", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },

	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
	{ MODKEY|ControlMask,           XK_k,      pushup,         {0} },

	/* { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, */
	/* { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } }, */
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = -1 } },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },

	/* { MODKEY|ShiftMask,             XK_c,      killclient,     {0} }, */
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	/* { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_u,      setlayout,      {.v = &layouts[4]} },
	// { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	// { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	/* { MODKEY,                       XK_f,      togglefullscr,  {0} }, */

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* { MODKEY,                       XK_n,      togglealttag,   {0} }, */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* from Luke Smith */
	/* STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push) */

	/* Close Xorg prompt */
	{ MODKEY|ShiftMask,				XK_Escape,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Close Xorg?\")\" = Yes ] && killall Xorg") },

	/* Sleep prompt */
	{ MODKEY|ShiftMask,				XK_s,			spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Sleep?\")\" = Yes ] && systemctl suspend") },

	/* Reboot prompt */
	{ MODKEY|ShiftMask,				XK_BackSpace,	spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot computer?\")\" = Yes ] && sudo -A reboot") },

	/* Shutdown prompt */
	{ MODKEY|ShiftMask,				XK_x,			spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },

	/* Hibernate prompt */
	{ MODKEY,						XK_F4,			spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo -A zzz") },

	/* Lock */
	/* { MODKEY,						XK_x,			spawn,		SHCMD("slock & xset dpms force off; mpc pause ; pauseallmpv") }, */
	{ MODKEY,						XK_x,			spawn,		SHCMD("slock") },

	/* Volume controls
	{ MODKEY,						XK_minus,		spawn,		SHCMD("lmc down") },
	{ MODKEY|ShiftMask,				XK_minus,		spawn,		SHCMD("lmc down 15") },
	{ MODKEY,						XK_equal,		spawn,		SHCMD("lmc up") },
	{ MODKEY|ShiftMask,				XK_equal,		spawn,		SHCMD("lmc up 15") }, */

	/* Start browser */
	{ MODKEY,						XK_w,			spawn,		SHCMD("$BROWSER") },

	/* Start network manager tui */
	{ MODKEY|ShiftMask,				XK_w,			spawn,		SHCMD("st -e sudo nmtui") },

	/* Start neomutt
	{ MODKEY,						XK_e,			spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") }, */

	/* Tutorial vids */
	{ MODKEY|ShiftMask,				XK_e,			spawn,		SHCMD("tutorialvids") },

	/* Start lf file manager
	{ MODKEY,						XK_r,			spawn,		SHCMD("st -e lf") }, */

	/* Camera */
	{ MODKEY|ShiftMask,				XK_c,			spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=mpvfloat $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },

	/* Show display select */
	{ MODKEY,						XK_F3,			spawn,		SHCMD("displayselect") },

	/* Show Mount / Unmount menu */
	{ MODKEY,						XK_F9,			spawn,		SHCMD("dmenumount") },
	{ MODKEY,						XK_F10,			spawn,		SHCMD("dmenuumount") },

	/* Brightness controls
	{ 0, 				XF86XK_MonBrightnessUp,		spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, 				XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

