/* See LICENSE file for copyright and license details. */
#pragma once

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=12" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_blue[]        = "#437ebb";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_blue,  col_blue },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd0[] = {"alacritty", "-t", "scratchpad", NULL };
const char *spcmd1[] = {"signal-desktop", NULL };
const char *spcmd2[] = {"com.discordapp.Discord", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"Alacritty",   spcmd0},
	{"signal",      spcmd1},
    {"discord",     spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance     title            tags mask     isfloating   monitor  float x,y,w,h  floatborderpx*/
	{ NULL,       "Alacritty", "scratchpad",    SPTAG(0),     1,           -1,      0,0,0.75,0.75, 5 },
	{ NULL,       "signal",    NULL,            SPTAG(1),     1,           -1,      0,0,0.75,0.75, 5 },
    { NULL,       "discord",   NULL,            SPTAG(2),     1,           -1,      0,0,0.75,0.75, 5 },
    { "Vivado",   NULL,        NULL,            NULL,         0,            0,      0,0,0,0,       5 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *firefox_priv[] = { "firefox", "--private-window", NULL };
static const char *volume_toggle[] = { "amixer", "sset", "Master", "toggle", NULL };
static const char *volume_up[] = { "amixer", "sset", "Master", "5%+", NULL };
static const char *volume_down[] = { "amixer", "sset", "Master", "5%-", NULL };
static const char *brightness_up[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brightness_down[] = {"brightnessctl", "set", "10%-", NULL };


static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_w,      spawn,          {.v = firefox } },
    { MODKEY|ShiftMask,             XK_w,      spawn,          {.v = firefox_priv } },
    { MODKEY,                       XK_m,      spawn,          SHCMD("mailsync") },
    { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("matlab -desktop") },
    { MODKEY,                       XK_v,      spawn,          SHCMD("vivado -tempDir ~/.cache/vivado/ -log ~/.cache/vivado/log -jou ~/.cache/vivado/jou") },
    { MODKEY,                       XK_b,      spawn,          SHCMD("pdfread") },
    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,            			XK_grave,  togglescratch,  {.ui = 0 } },
    { MODKEY,            			XK_s,	   togglescratch,  {.ui = 1 } },
    { MODKEY,                       XK_d,      togglescratch,  {.ui = 2 } },
    { 0,                     XF86XK_AudioMute, spawn,          {.v = volume_toggle } },
    { 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volume_up } },
    { 0,              XF86XK_AudioLowerVolume, spawn,          {.v = volume_down } },
    { 0,                       XF86XK_Display, spawn,          SHCMD("slock") },
    { MODKEY,                  XF86XK_Display, spawn,          SHCMD("arandr") },
    { 0,               XF86XK_MonBrightnessUp, spawn,          {.v = brightness_up } },
    { 0,             XF86XK_MonBrightnessDown, spawn,		   {.v = brightness_down } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0] } },
    { ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[2] } },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1] } },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          SHCMD("[ -z $(setxkbmap -query | grep us) ] && setxkbmap us || setxkbmap tr") },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

