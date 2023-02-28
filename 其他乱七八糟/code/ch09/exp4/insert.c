#include <stdlib.h>
#include <stdio.h>

#include <mysql.h>

int main(int argc, char *argv[]) {
   MYSQL my_connection;
   mysql_init(&my_connection);  
   if (mysql_real_connect(&my_connection, "localhost", "root", "v587", "db_chat", 0, NULL, 0)) {
      printf("连接成功\n");

      int res = mysql_query(&my_connection, "INSERT INTO tb_user(name,sex,birthday,status) VALUES ('Lee',true,'1997-01-05',1)");
      if (!res) 
         printf("插入 %lu 行\n", (unsigned long)mysql_affected_rows(&my_connection));
      else
         fprintf(stderr, "插入操作错误 error %d: %s\n", mysql_errno(&my_connection),mysql_error(&my_connection));

      mysql_close(&my_connection);
   }
   else {
      fprintf(stderr, "连接失败\n");
      if (mysql_errno(&my_connection))
         fprintf(stderr, "连接错误 error %d: %s\n",mysql_errno(&my_connection), mysql_error(&my_connection));
   }

   return EXIT_SUCCESS;
}

