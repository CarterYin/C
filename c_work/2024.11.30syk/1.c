#include <stdio.h>
#include <time.h>

// 计算两个日期之间的天数
int days_between_dates(struct tm start, struct tm end) {
    time_t start_time = mktime(&start);
    time_t end_time = mktime(&end);
    double difference = difftime(end_time, start_time);
    return difference / (60 * 60 * 24);
}

int main() {
    struct tm start_date = {0};
    struct tm end_date = {0};

    // 输入开始日期
    printf("请输入开始日期 (年 月 日): ");
    scanf("%d %d %d", &start_date.tm_year, &start_date.tm_mon, &start_date.tm_mday);
    start_date.tm_year -= 1900; // 年份从1900开始
    start_date.tm_mon -= 1; // 月份从0开始

    // 输入结束日期
    printf("请输入结束日期 (年 月 日): ");
    scanf("%d %d %d", &end_date.tm_year, &end_date.tm_mon, &end_date.tm_mday);
    end_date.tm_year -= 1900; // 年份从1900开始
    end_date.tm_mon -= 1; // 月份从0开始

    // 计算天数差
    int days = days_between_dates(start_date, end_date);
    printf("两个日期之间相隔的天数: %d\n", days);

    return 0;
}