
# Table of Contents

1.  [Background](#org9f4383a)
2.  [Patches](#org5cbd35c)
3.  [Patches Removed](#orgb1ede47)
    1.  [autostart](#orgd5c65de)
4.  [Specifics](#org3986fcf)
    1.  [vanitygaps](#org1a8426c)
    2.  [center first window](#org78c023f)
    3.  [statuscmd-signal](#orgc817f12)



<a id="org9f4383a"></a>

# Background

DWM is the Dynamic Window Manager from [suckless.org](https://dwm.suckless.org/).

This build should work on any system that can run Xserver and replace `libxft` with `libxft-bgra` (unless they finally merge it upstream)

Installations are managed through `make`


<a id="org5cbd35c"></a>

# Patches

This is my personal build which adds these additional patches

-   [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
-   [center first window](https://dwm.suckless.org/patches/center_first_window/)
-   [statuscmd-signal](https://dwm.suckless.org/patches/statuscmd/)
-   [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
-   [Xresources](https://dwm.suckless.org/patches/xresources/)
-   [swallow](https://dwm.suckless.org/patches/swallow/)
-   [stacker](https://dwm.suckless.org/patches/stacker/)

Where possible I try to maintain the original file structure of dwm in favor of reorganizing current functions into new files (looking at you vanitygaps)


<a id="orgb1ede47"></a>

# Patches Removed

I used to have these patches as part of my build, but have since removed them for the listed reasons


<a id="orgd5c65de"></a>

## [autostart](https://dwm.suckless.org/patches/autostart/)

As the name implied, I was running my background utilities using this patch to get away from `.xprofile` for some reason. But this stopped making sense once I realized I was either going to run DWM as a stand-alone window manager (`.xprofile` can just be concerned with DWM) or with a display manager (lightDM in my case) that provides a helpful `DESKTOP` variable.


<a id="org3986fcf"></a>

# Specifics


<a id="org1a8426c"></a>

## vanitygaps

The patch I used for vanitygaps had moved the tile layout and a couple of other things into a new `vanitygaps.c` file. I found this was causing me grief when patching down the line so I yanked everything out of that file and placed it in the `dwm.c` source file.


<a id="org78c023f"></a>

## center first window

Originally, this patch would only place a small client in the center of the screen and would not resize for any reason. I&rsquo;ve replaced the constants that did this so that the client fills the vertical space and uses `mfact` to determine the horizontal size.


<a id="orgc817f12"></a>

## statuscmd-signal

This patch is applied to give clickable buttons for use with [Luke Smith&rsquo;s dwmblocks](https://github.com/lukesmithxyz/dwmblocks).

