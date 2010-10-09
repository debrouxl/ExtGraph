===============================================================================
Library ExtGraph (TIGCC-AddOn)               (c) 2001-2010 TICT (TI-Chess Team)
===============================================================================

Read file docs/extgraph.html to get details about the API of the ExtGraph-Lib.
NOTE: in betas of the ExtGraph 2.xx series, the documentation is not fully
updated. The header extgraph.h is up to date, though, and the demos cover most
functions.


ExtGraph is a compile-time library (used functions are fetched from the library
during the linking stage) and it contains various useful graphics related
routines which are missing in the TIGCCLIB or modified routines which are
implemented with high speed in mind (without stupid excessive speed
optimizations, though, except preshifted sprites, which are brute-force).
ExtGraph can be used as is (extgraph.h + tilemap.h + preshift.h + extgraph.a +
tilemap.a in folder lib), building it before using it for the first time is
neither necessary nor recommended. I removed the instructions for building
from this file: not so few did not understand that ExtGraph was ready for use
(this information was missing in this file...), therefore they wanted to
recompile it and they were experiencing trouble.


To use the ExtGraph Library
---------------------------
Copy files from the folder /lib into the directory where the rest of your
sources are. To use extgraph functions now in your project add the following
line:
#include "extgraph.h"
to your sourcecode.

If you are using the commandline compile your project (in this case myprog) this
way:
tigcc myprog.c extgraph.a
If you are using the IDE add extgraph.h and extgraph.a to your project. That's
all.


ExtGraph history
----------------
One of the greatest improvements in ExtGraph 2.xx, compared to ExtGraph 1.xx,
is the introduction of __attribute__((__regparm__)) routines. They are faster
and smaller than equivalent __attribute__((__stkparm__)) routines, which were
rewritten too, and are left for backwards compatibility. Few __stkparm__
routines do not have a __regparm__ version: please use __regparm__ versions
whenever possible, as they are smaller and faster and lead to smaller and
faster code. As a consequence, TIGCC 0.93 is not supported any more, but this
version is no longer the official release and it is REALLY outdated now.
But ExtGraph 2.xx brings much more than that, read the beginning of the
documentation DOCS/extgraph.html.

If you distribute ExtGraph within your projects' distributions, please include
both extgraph.a and extgraph.h (and tilemap.a / tilemap.h if you use the tilemap
engine, preshift.h if you use preshifted sprites). Don't get fooled by the huge
size of those files: they are very redundant data, high compression ratios can
therefore be achieved on them. extgraph.a, is more than six times smaller after
compression with old ZIP format.


The sources of ExtGraph are provided, so that you can customize the functions
to make them best fit your needs, even if you hardly know any assembly:
* customizing clipped sprite routines to different screen sizes can be simply
achieved through replacing all occurrences of 239 (width - 1) and 127
(height - 1) by other values. Several functions have equates (.set ...),
maybe I'll modify all functions to use them, since this should not add bugs.
* customizing non-interlaced sprite routines to use the not-so-infrequent
"block" (M/)L/D sprite format, consisting of h consecutive lines of mask
(applied to both planes) if that applies, h consecutive lines of light, h
consecutive lines of dark (or any other permutation of (M/)L/D) requires
changing a bit the lines where registers a2 to a5 are set. I did this for
Venus, while adding comments. Also, check UpsideDownGrayClipSprite16_MASK_R in
/src/misc and all Gray(Clip)SingleSprite functions.
* customizing slightly the sprite format of the interlaced sprite routines (if
you want to put dark before light) requires swapping the planes, either in the
function call (GrayGetPlane(DARK_PLANE) as light plane, and vice-versa) or in
the function itself (swap all occurrences of a0 and a1 in the drawing loops).
* light gray and dark gray transparencies (TRANL / TRAND) can be made from
TRANW / TRANB ones. I made the GrayClipISprite16 ones, after a user wanted
TRANL / TRAND routines, but the information I had put here turned out to be
wrong. The same goes for the routines in the tilemap engine.
Note that as of ExtGraph 2.00 Beta 5, "32" routines were not optimized, and
this way of doing does not apply to them.
* making non-clipped grayscale interlaced sprite routines just requires removing
the clipping code and loops.

Of course, if you customize a function, it's best to include it directly in
your project, instead of recompiling ExtGraph: it lowers incompatibility and
bug chances due to recompiling, and it avoids spreading modified versions which
don't behave the same way as the original ones do. You can also contribute your
modifications.


If you think you've found a bug, send me information about the faulty functions,
with a complete testcase if possible (I won't disclose your project if you send
me an entire project): I have a small test suite, which suits well to sprite
routines. I'll _try_ to reply within several days, the delay depends on how busy
I am. If I forget to reply after a while, remind me about you !
But first, please:
* download the ExtGraph library (at least the files in the /lib directory) from
the Git repository at http://github.com/debrouxl/ExtGraph , and see if the bug
is still there in the repository version.
Historical note: there used to be a SVN repository at
http://opensvn.csie.org/ExtGraph . This free SVN repository hosting provider
went away mid-May 2010, the Git repository was created in October 2010. Many
bugs were fixed in SVN prior to the 2.00 Beta 5 release, and likewise after the
2.00 Beta 5 release.
* if the problem is Address Error, check whether forcing the pointer alignment
to be even fixes the problem. As a general rule, all planes *must* start at an
even address, but some functions assume, for efficiency, that one of their
arguments has non-default alignment (e.g. word alignment for the addess pointed
to by an unsigned char * pointer).


===============================================================================
thomas.nussbaumer@gmx.net                                          Graz/Austria
lionel_debroux@yahoo.fr                                                  France
===============================================================================
