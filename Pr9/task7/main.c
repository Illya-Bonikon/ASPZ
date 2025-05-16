#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	uid_t target_uid = 1001;
	gid_t target_gid = 1001;

	if (setgid(target_gid) != 0)
	{
		perror("setgid");
		return 1;
	}

	if (setuid(target_uid) != 0)
	{
		perror("setuid");
		return 1;
	}

	execlp("whoami", "whoami", NULL);

	perror("execlp");
	return 1;
}
