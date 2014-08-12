#include <memory>
#include <unordered_map>
#include <iostream>
#include <mysql/mysql.h>

template <typename T, typename F>
std::unique_ptr<T, F> gc(T* p, F f)
{
	  return std::unique_ptr<T, F>(p, f);
}

void ensure_mysql(MYSQL* p)
{
	  if(p== 0)
		      throw std::runtime_error(mysql_error(p));
}

void ensure_query(MYSQL* p, int ret)
{
	  if(ret> 0)
		      throw std::runtime_error(mysql_error(p));
}

int main()
{
	  try
		    {
			        auto mysql= gc(mysql_init(0), mysql_close);
				    ensure_mysql(mysql.get());
				        ensure_mysql(mysql_real_connect(mysql.get(), "server", "username", "password", "database", 3306, 0, CLIENT_COMPRESS| CLIENT_FOUND_ROWS));

					    ensure_query(mysql.get(), mysql_query(mysql.get(), "select table_name, table_type, engine from information_schema.tables"));
					        auto result= gc(mysql_use_result(mysql.get()), mysql_free_result);
						    while(MYSQL_ROW row= mysql_fetch_row(result.get()))
							        {}

						      }
	    catch(std::exception &ex)
		      {
			          std::cerr<< ex.what()<< '\n';
				    }
}
