#include <signal.h>
#include <stdlib.h>

int main() {
    struct sigaction sa = {0};
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, NULL);

    if (fork() == 0) {
        // Дочірній процес
        _exit(0);
    }

    // Батьківський процес не викликає wait(), але зомбі не буде
    sleep(2);
    return 0;
}