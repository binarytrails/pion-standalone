
#ifndef H_PION_FILESYSTEM
#define H_PION_FILESYSTEM

#include <vector>

#ifdef ASIO_STANDALONE

#include <string>
#include <ctime>

namespace pion { namespace filesystem
{
	class path
	{
		public:
			path() = default;
			path( const std::string &i_path );
		
			inline bool empty() const { return _path.empty(); }
			inline const std::string &string() const { return _path; }
			path filename() const;
			path parent_path() const;
		
			path &operator/=( const path &i_comp );
		
			path &normalize();
		
		private:
			std::string _path;
	};
	
	path operator/( const path &i_path, const path &i_comp );
	
	path system_complete( const path &i_path );
	std::string extension( const path &i_path );
	std::string basename( const path &i_path );
	bool exists( const path &i_path );
	bool is_directory( const path &i_path );
	bool is_regular( const path &i_path );
	
	std::time_t last_write_time( const path &i_path );
	size_t file_size( const path &i_path );
	
	bool remove( const path &i_path );
}

std::vector<filesystem::path> get_dir_content( const filesystem::path &i_path );

#ifdef PION_WIN32
std::wstring filesystem_path( const filesystem::path &i_path );
#else
std::string filesystem_path( const filesystem::path &i_path );
#endif

}

#else

#include <boost/filesystem.hpp>

// bring filesystem in the pion namespace
namespace pion
{
	namespace filesystem = boost::filesystem;

	std::vector<boost::filesystem::path> get_dir_content( const boost::filesystem::path &i_path );

#ifdef PION_WIN32
	std::wstring filesystem_path( const boost::filesystem::path &i_path );
#else
	std::string filesystem_path( const boost::filesystem::path &i_path );
#endif
}

#endif

#endif
