#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(void)
{

	openlog("test syslog", LOG_CONS | LOG_NDELAY, LOG_LOCAL0);

	// syslog(LOG_EMERG, "%i %s", 1, "emerg");
	syslog(LOG_ALERT, "%i %s", 2, "alert");
	syslog(LOG_CRIT, "%i %s", 3, "crit");
	syslog(LOG_ERR, "%i %s", 4, "err");
	syslog(LOG_WARNING, "%i %s", 5, "warning");
	syslog(LOG_NOTICE, "%i %s", 6, "notice");
	syslog(LOG_INFO, "%i %s", 7, "info");
	syslog(LOG_DEBUG, "%i %s", 8, "debug");

	return 0;
}
