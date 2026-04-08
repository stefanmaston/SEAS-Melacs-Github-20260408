/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2014 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
*                           ALL RIGHTS RESERVED
*
*   This computer program is the property of RoweBots Research Inc.,
*   Kitchener, Ontario Canada. and may not be copied or redistributed in any
*   form or by any means, whether in part or in whole, except under license
*   granted by RoweBots Research Inc.
*
*   All copies of this program, whether in part or in whole, and whether
*   modified or not, must display this and all other embedded copyright and
*   ownership notices in full.  This notice may not be modified.
*
*   All source code is protected by international copyright laws and license
*   agreements.  Do not break the law.  You can obtain a license and source
*   code at rowebots.com subject to licensing conditions and restrictions.
*   Free development, free source code and free non commercial licenses may
*   be obtained in a few seconds on line without any difficult process.
*
*   All demonstration programs may be redistributed as source code to others
*   as a small part of a Unison or DSPnano application.
*
* ******************************************************************************
*
*
*   Save Time and Money.  If you need modifications to the software to support
*   specific processors or peripherals, RoweBots Research can do this for you
*   quickly and easily at low cost.  If you need help with application develop-
*   ment, again we can solve your embedded development problems quickly and
*   easily at very attractive prices.  We are tiny tiny embedded Linux* experts,
*   let us reduce your risk, accelerate your development and slash your time
*   to market.  See rowebots.com - contact us.
*
*
*******************************************************************************/

#ifndef _pfctl_h_
#define _pfctl_h_

#ifdef __cplusplus
extern "C" {
#endif



#define PF_OPT_NOACTION		0x0001		// Do not actually load rules, just parse them.
#define PF_OPT_QUIET		0x0002		// Only print errors and warnings.


int  pfctl_setup(int, int (*)(const char *, ...), int);	// Set printout function

int	 pfctl_enable(void);				// Enable the packet filter.
int	 pfctl_disable(void);				// Disable the packet filter.

int  pfctl_rules_begin(void);			// Clears the inactive filter rule set.
int  pfctl_rules_parse(char *);			// Adds filter rule at the end of the inactive filter rule set.
int  pfctl_rules_commit(void);			// Switch inactive to active filter rule set.

int  pfctl_nat_begin(void);				// Clears the inactive filter NAT set.
int  pfctl_nat_parse(char *);			// Adds filter rule at the end of the inactive filter NAT set.
int  pfctl_nat_commit(void);			// Switch inactive to active filter NAT set.

int	 pfctl_clear_rules(void);			// Flush the filter rules.
int	 pfctl_clear_nat(void);				// Flush the NAT rules.
int	 pfctl_clear_states(void);			// Flush the state table (NAT and filter).

int	 pfctl_kill_states(const char *, const char *);	// Kill all of the state entries from the specified host.

int	 pfctl_log(char *);						// Enable collection of packet and byte count statistics for interface.
int	 pfctl_clear_stats(void);				// Flush the filter information (statistics that are not bound to rules).
int  pfctl_get_status(struct pf_status *);	// Gets filter information (statistics and counters).

int	 pfctl_gettimeout(const char *);		// Gets a timeout or interval value.
int	 pfctl_settimeout(const char *, int);	// Sets a timeout or interval value.

int	 pfctl_getlimit(const char *);					// Gets hard limits on the memory pools used by the packet filter.
int	 pfctl_setlimit(const char *, unsigned int);	// Sets hard limits on the memory pools used by the packet filter.

int	 pfctl_debug(u_int32_t);			// Set the debug level.


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _pfctl_h_ */
