#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

/***************************************
 * To enable/disable debugging,you can
 * comment/uncomment the following line,
 * or (not define)/(define) it in Makefile.
**************************************/
#define NDEBUG

#undef pr_debug		/* undef it, just in case */

#ifdef NDEBUG

/* not debugging: print nothing */
#define pr_debug(fmt, args...)

#else

#ifdef __KERNEL__
		/* if debugging is enable, and on kernel space, do this one */
#define pr_debug(fmt, args...) printk( KERN_ERR fmt, ## args)

#else
		 /* if on user space, do this one */
#define pr_debug(fmt, args...) fprintf(stderr, fmt, ## args)
#endif

#endif


#endif

