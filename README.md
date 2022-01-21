
# Table of Contents

1.  [Background](#orgaf9ad27)
2.  [Patches](#orged96993)
3.  [Patches Removed](#org06f06d9)
    1.  [autostart](#org68c9bc4)
4.  [Specifics](#orgbf5d862)
    1.  [vanitygaps](#org2606b98)
    2.  [center first window](#org2ff9a1b)



<a id="orgaf9ad27"></a>

# Background

DWM is the Dynamic Window Manager from [suckless.org](https://dwm.suckless.org/).

This build should work on any system that can run Xserver and replace `libxft` with `libxft-bgra` (unless they finally merge it upstream)

Installations are managed through `make`


<a id="orged96993"></a>

# Patches

This is my personal build which adds these additional patches

-   [hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/)
-   [center first window](https://dwm.suckless.org/patches/center_first_window/)
-   [statuscmd-signal](https://dwm.suckless.org/patches/statuscmd/)
-   [vanitygaps](https://dwm.suckless.org/patches/vanitygaps/)
-   [Xresources](https://dwm.suckless.org/patches/xresources/)
-   [swallow](https://dwm.suckless.org/patches/swallow/)

Where possible I will try to maintain the original file structure of dwm in favor of reorganizing current functions into new files (looking at you vanitygaps)


<a id="org06f06d9"></a>

# Patches Removed

I used to have theese patches as part of the build, but have since removed them for the listed reasons


<a id="org68c9bc4"></a>

## [autostart](https://dwm.suckless.org/patches/autostart/)

As the name implied, I was running my background utilities using this patch to get away from .xprofile for some reason. But this stopped making sense once I realized I was either going to run dwm as a standalone window manager (xproile can just be concerned with DWM) or with a display manager (lightDM in my case) that provides a helpful `DESKTOP_SESSION` variable.


<a id="orgbf5d862"></a>

# Specifics


<a id="org2606b98"></a>

## vanitygaps

The patch I used for vanitygaps had moved the tile layout and a couple of other things into a new `vanitygaps.c` file. I found this was causing me grief when patching down the line so I yanked everything out of that file and placed it in the `dwm.c` source file.


<a id="org2ff9a1b"></a>

## center first window

Originally, this patch would only place a small client in the center of the screen and would not resize for any reason. I&rsquo;ve replaced the constants that did this so that the client fills the vertical space and uses `mfact` to determine the horizontal size.

