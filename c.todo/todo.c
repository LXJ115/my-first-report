#include <stdio.h> //引入头文件
#include <string.h>

#define MAX 100 //MAX 等价100

int main() {
    char todos[MAX][100];
    int count = 0;
    int choice;
    FILE *fp; // 启动时读取文件
    fp = fopen("todos.txt", "r");
    if (fp != NULL) {
        while (fgets(todos[count], 100, fp) != NULL) {
            // 去掉换行符
            todos[count][strcspn(todos[count], "\n")] = '\0';
            count++;
        }
        fclose(fp);
    }

    while (1) {
        printf("\n===== 待办清单 =====\n");
        printf("1. 添加待办\n");
        printf("2. 查看待办\n");
        printf("3. 保存并退出\n");
        printf("请选择：");
        scanf("%d", &choice);
        getchar(); // 吃掉回车

        if (choice == 1) {
            if (count >= MAX) {
                printf("待办已满！\n");
                continue;
            }
            printf("输入待办内容：");
            fgets(todos[count], 100, stdin);
            todos[count][strcspn(todos[count], "\n")] = '\0'; //删掉读进来的换行符
            count++; //任务组数加1
            printf("添加成功！\n");
        }
        else if (choice == 2) {
            if (count == 0) {
                printf("暂无待办。\n");
            } else {
                printf("\n--- 待办列表 ---\n");
                for (int i = 0; i < count; i++) {
                    printf("%d. %s\n", i + 1, todos[i]);
                }
            }
        }
        else if (choice == 3) {
            fp = fopen("todos.txt", "w");
            if (fp == NULL) {
                printf("保存失败！\n");
                return 1;
            }
            for (int i = 0; i < count; i++) {
                fprintf(fp, "%s\n", todos[i]);
            }
            fclose(fp);
            printf("已保存，退出。\n");
            break;
        }
        else { //输入不正确
            printf("无效选择，请重新输入。\n");
        }
    }

    return 0;
}
