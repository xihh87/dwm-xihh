/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=10", "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#ffffff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_black },
	[SchemeSel]  = { col_gray4, col_cyan,  col_white  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

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
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 0;    /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },    /* first entry is default */
	{ "[]=",      tile },
};

/* key definitions */
#define MODKEY Mod4Mask
#define NOMODKEY 0
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "/usr/bin/dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "/usr/bin/env", "SHELL=/usr/bin/fish", "st", "-e", "dvtm", NULL };
static const char *emcscmd[] = {"/usr/bin/emacs", NULL };
static const char *filebwsr2[] = {"/usr/bin/nautilus", NULL };
static const char *filebwsr[] = {"/usr/bin/st", "-t", "Archivos", "-e", "vifm", "/home/joshpar", NULL };
static const char *newscmd[] = {"/usr/bin/st", "-t", "RSS", "-e", "newsbeuter", NULL };
static const char *scrnlck[] = {"/usr/bin/slock", NULL };
static const char *scrshot[] = {"/usr/bin/scrot", "-s", "/home/joshpar/shots/%F-%H%M%S.png", NULL };
static const char *vimcmd[] = {"/usr/bin/st", "-e", "vis", NULL };
static const char *webbwsr[] = {"/usr/bin/iceweasel", NULL };

static const char *taskcmd[] = {"/usr/bin/st", "-t", "Pendientes", "-e", "/home/joshpar/.bin/t", NULL };
static const char *wtaskcmd[] = {"/usr/bin/st", "-t", "Pendientes (trabajo)", "-e", "/home/joshpar/.bin/tw", NULL };

static const char *mpcnext[] = {"/usr/bin/mpc", "-h", "/run/user/1000/mpd/mpd.socket", "next", NULL };
static const char *mpcplay[] = {"/usr/bin/mpc", "-h", "/run/user/1000/mpd/mpd.socket", "toggle", NULL };
static const char *mpcprev[] = {"/usr/bin/mpc", "-h", "/run/user/1000/mpd/mpd.socket", "cdprev", NULL };
static const char *mpcstop[] = {"/usr/bin/mpc", "-h", "/run/user/1000/mpd/mpd.socket", "stop", NULL };

static const char *mutecmd[] = {"/usr/bin/amixer", "set", "Master", "toggle", NULL };
static const char *voldn[] = {"/usr/bin/amixer", "set", "Master", "5%-", NULL };
static const char *volup[] = {"/usr/bin/amixer", "set", "Master", "5%+", NULL };

static const char *brightdn[] = {"/usr/bin/xbacklight", "-dec", "+5", NULL };
static const char *brightup[] = {"/usr/bin/xbacklight", "-inc", "+5", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
    /* modifier                     key                       function           argument */
    { MODKEY|ControlMask,           XK_n,	              spawn,             SHCMD("snotes -s")},
    { MODKEY|ControlMask,           XK_q,                     quit,              {0} },
    { MODKEY|ShiftMask,             XK_0,                     tag,               {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_c,                     killclient,        {0} },
    { MODKEY|ShiftMask,             XK_comma,                 tagmon,            {.i = -1 } },
    { MODKEY|ShiftMask,             XK_e,                     spawn,             {.v = filebwsr2 }},
    { MODKEY|ShiftMask,             XK_n,                     spawn,             SHCMD("snotes-open \"`sselp`\"")},
    { MODKEY|ShiftMask,             XK_o,                     spawn,             {.v = taskcmd } },
    { MODKEY|ShiftMask,             XK_period,                tagmon,            {.i = +1 } },
    { MODKEY|ShiftMask,             XK_space,                 togglefloating,    {0} },
    { MODKEY|ShiftMask,             XK_w,                     spawn,             {.v = termcmd } },
    { MODKEY,                       XF86XK_AudioNext,         spawn,             {.v = mpcnext } },
    { MODKEY,                       XF86XK_AudioPlay,         spawn,             {.v = mpcplay } },
    { MODKEY,                       XF86XK_AudioPrev,         spawn,             {.v = mpcprev } },
    { MODKEY,                       XF86XK_AudioStop,         spawn,             {.v = mpcstop } },
    { MODKEY,                       XK_0,                     view,              {.ui = ~0 } },
    { MODKEY,                       XK_a,                     spawn,             {.v = vimcmd } },
    { MODKEY,                       XK_b,                     togglebar,         {0} },
    { MODKEY,                       XK_comma,                 focusmon,          {.i = -1 } },
    { MODKEY,                       XK_d,                     incnmaster,        {.i = -1 } },
    { MODKEY,                       XK_Escape,                spawn,             {.v = scrnlck }},
    { MODKEY,                       XK_e,                     spawn,             {.v = filebwsr }},
    { MODKEY,                       XK_F4,                    killclient,        {0} },
    { MODKEY,                       XK_h,                     setmfact,          {.f = -0.05} },
    { MODKEY,                       XK_i,                     incnmaster,        {.i = +1 } },
    { MODKEY,                       XK_j,                     focusstack,        {.i = +1 } },
    { MODKEY,                       XK_k,                     focusstack,        {.i = -1 } },
    { MODKEY,                       XK_l,                     setmfact,          {.f = +0.05} },
    { MODKEY,                       XK_m,                     setlayout,         {.v = &layouts[0]} },
    { MODKEY,                       XK_n,	              spawn,             SHCMD("snotes")},
    { MODKEY,                       XK_o,                     spawn,             {.v = wtaskcmd } },
    { MODKEY,                       XK_period,                focusmon,          {.i = +1 } },
    { MODKEY,                       XK_p,                     spawn,             {.v = dmenucmd } },
    { MODKEY,                       XK_q,                     spawn,             {.v = webbwsr } },
    { MODKEY,                       XK_Return,                zoom,              {0} },
    { MODKEY,                       XK_r,                     spawn,             {.v = newscmd } },
    { MODKEY,                       XK_space,                 setlayout,         {0} },
    { MODKEY,                       XK_s,                     spawn,             {.v = emcscmd } },
    { MODKEY,                       XK_Tab,                   view,              {0} },
    { MODKEY,                       XK_t,                     setlayout,         {.v = &layouts[1]} },
    { MODKEY,                       XK_w,                     spawn,             {.v = termcmd } },
    { NOMODKEY,                     XF86XK_AudioLowerVolume,  spawn,             {.v = voldn } },
    { NOMODKEY,                     XF86XK_AudioMute,         spawn,             {.v = mutecmd } },
    { NOMODKEY,                     XF86XK_AudioRaiseVolume,  spawn,             {.v = volup } },
    { NOMODKEY,                     XF86XK_MonBrightnessDown, spawn,             {.v = brightdn } },
    { NOMODKEY,                     XF86XK_MonBrightnessUp,   spawn,             {.v = brightup } },
    { NOMODKEY,                     XK_Print,                 spawn,             {.v = scrshot } },
    TAGKEYS(                        XK_1,                     0)
    TAGKEYS(                        XK_2,                     1)
    TAGKEYS(                        XK_3,                     2)
    TAGKEYS(                        XK_4,                     3)
    TAGKEYS(                        XK_5,                     4)
    TAGKEYS(                        XK_6,                     5)
    TAGKEYS(                        XK_7,                     6)
    TAGKEYS(                        XK_8,                     7)
    TAGKEYS(                        XK_9,                     8)
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
