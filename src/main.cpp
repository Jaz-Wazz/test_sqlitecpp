#include <SQLiteCpp/Database.h>
#include <exception>
#include <fmt/core.h>

int main() try
{
	SQLite::Database db {"db.db"};
	fmt::print("sas.\n");
	return 0;
}
catch(const std::exception & exception)
{
	fmt::print("exception: '{}'.\n", exception.what());
}
