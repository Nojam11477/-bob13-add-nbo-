#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

uint32_t my_ntohl(uint32_t netlong) {
    return ((netlong & 0xFF000000) >> 24) |
           ((netlong & 0x00FF0000) >> 8)  |
           ((netlong & 0x0000FF00) << 8)  |
           ((netlong & 0x000000FF) << 24);
}

int main(int argc, char *argv[]) {
    uint32_t a, b;
    FILE *file1, *file2;

    if (argc < 2) {
        printf("덧셈할 두 개의 파일을 입력해 주세요.\n");
        return 0;
    }

    file1 = fopen(argv[1], "rb");
    file2 = fopen(argv[2], "rb");

    if (file1 == NULL || file2 == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 0;
    }

    fread(&a, sizeof(uint32_t), 1, file1);
    fread(&b, sizeof(uint32_t), 1, file2);
    
    fclose(file1);
    fclose(file2);

    a = my_ntohl(a);
    b = my_ntohl(b);


    if(a>65535||b>65535){
        printf("숫자가 너무 큽니다.\n");
        return 0;
    }

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n",a,a,b,b,a+b,a+b);

    return 0;
}

