#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void Dosyaya_Olustur() {
    int fd = open("dosya.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("Dosya oluşturulamadı");
        exit(1);
    }
    write(fd, "", 0);
    close(fd);
    exit(0);
}

void Dosyaya_Yaz() {
    int fd = open("dosya.txt", O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("Dosya açılamadı");
        exit(1);
    }
    char *data = "Bu bir test yazısıdır.\n";
    write(fd, data, strlen(data));
    close(fd);
    exit(0);
}

void Dosyayi_Oku() {
    int fd = open("dosya.txt", O_RDONLY);
    if (fd < 0) {
        perror("Dosya açılamadı");
        exit(1);
    }
    char buffer[1024];
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("Dosya içeriği:\n%s", buffer);
    }
    close(fd);
    exit(0);
}

int main() {
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if (pid1 == 0) {
        Dosyaya_Olustur();
    }

    pid2 = fork();
    if (pid2 == 0) {
        Dosyaya_Yaz();
    }

    pid3 = fork();
    if (pid3 == 0) {
        Dosyayi_Oku();
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
