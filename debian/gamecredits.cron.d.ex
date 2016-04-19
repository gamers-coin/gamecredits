#
# Regular cron jobs for the gamecredits package
#
0 4	* * *	root	[ -x /usr/bin/gamecredits_maintenance ] && /usr/bin/gamecredits_maintenance
