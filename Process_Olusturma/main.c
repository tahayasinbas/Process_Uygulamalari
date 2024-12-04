#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork calistirilamadi");
        exit(1);
    } else if (pid == 0) {
        printf("Child process başlatıldı. Dosya içeriği yazdırılıyor:\n");
        execlp("cat", "cat", "dosya.txt", NULL);
        perror("Calistirilamadi");
        exit(1);
    } else {
        printf("Parent process, child process'i bekliyor...\n");
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process başarıyla tamamlandı, çıkış kodu: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process beklenmeyen bir şekilde sonlandı.\n");
        }
    }

    return 0;
}
