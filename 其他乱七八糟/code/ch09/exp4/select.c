#include <stdlib.h>
#include <stdio.h>

#include "mysql.h"

MYSQL my_connection;//连接
MYSQL_RES *res_ptr;//结果集指针
MYSQL_ROW sqlrow;//行结构

void display_header();
void display_row();

int main(int argc, char *argv[]) {
   int first_row = 1; //用于确保只显示一次表头

   //连接数据库
   mysql_init(&my_connection);  
   if (mysql_real_connect(&my_connection, "localhost", "root", "v587", "db_chat", 0, NULL, 0)) {
       printf("连接成功\n");
       //查询
       int res = mysql_query(&my_connection, "SELECT * FROM tb_user WHERE sex=1");
       if (res) 
          printf("查询错误: %s\n", mysql_error(&my_connection));
       else {
          //提取数据
          /* res_ptr = mysql_store_result(&my_connection); */
          res_ptr = mysql_use_result(&my_connection);
          if (res_ptr) {
             /* printf("检索到 %lu 条记录\n", (unsigned long)mysql_num_rows(res_ptr)); */
             //遍历数据
             while ((sqlrow = mysql_fetch_row(res_ptr))){
                /* printf("获取数据...\n"); */
                if (first_row) { //显示表头信息
                   display_header();
                   first_row = 0;
                }
                display_row();
             }
             if (mysql_errno(&my_connection))
                fprintf(stderr, "获取数据错误: %s\n", mysql_error(&my_connection)); 
             //清理工作
             mysql_free_result(res_ptr);
          }
       }
       mysql_close(&my_connection);
   } 
   else {
       fprintf(stderr, "连接失败\n");
       if (mysql_errno(&my_connection))
          fprintf(stderr, "连接错误 %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection));
   }

   return EXIT_SUCCESS;
}

//显示表头信息
void display_header() {
   MYSQL_FIELD *field_ptr;

   printf("表头信息:\n");
 
   while ((field_ptr = mysql_fetch_field(res_ptr)) != NULL) {
      printf("\t 字段名: %s\n", field_ptr->name);
      printf("\t 字段类型: ");
      if (IS_NUM(field_ptr->type)) {
         printf("数字字段\n");
      } else {
         switch(field_ptr->type) {
            case FIELD_TYPE_VAR_STRING:
               printf("VARCHAR\n");
            break;
            case FIELD_TYPE_LONG: 
               printf("LONG\n");
            break;
            default:
              printf("其他类型 %d \n", field_ptr->type);
         }
      }

      printf("\t 最大宽度 %ld\n", field_ptr->length); 
      if (field_ptr->flags & AUTO_INCREMENT_FLAG)printf("\t 自增长 \n");
      printf("\n");
   }
}

//显示一行原始数据
void display_row() {
   unsigned int field_count=0;
   while (field_count < mysql_field_count(&my_connection)) {
      if (sqlrow[field_count])
          printf("%s ", sqlrow[field_count]);
      else
          printf("NULL");
      field_count++;
   }
   printf("\n");
}
