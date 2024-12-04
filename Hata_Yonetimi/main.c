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
        perror("fork olusturlamadi");
        exit(1);
    } else if (pid == 0) {
        FILE *file = fopen("dosya.txt", "r");
        if (file == NULL) {
            perror("Dosya açılamadı. abort() çağrılıyor...");
            abort();
        } else {
            printf("Dosya başarıyla açıldı.\n");
            fclose(file);
            exit(0);
        }
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process başarıyla tamamlandı, çıkış kodu: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process sinyal ile sonlandı, sinyal kodu: %d\n", WTERMSIG(status));
        } else {
            printf("Child process beklenmeyen bir şekilde sonlandı.\n");
        }
    }

    return 0;
}
