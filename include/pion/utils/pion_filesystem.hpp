
#ifndef H_PION_FILESYSTEM
#define H_PION_FILESYSTEM

#include <pion/config.hpp>
#include <vector>
#include <string>
#include <ctime>

#ifdef PION_WIN32
#  pragma warning( push )
#  pragma warning( disable: 4251 )
#endif

namespace pion { namespace filesystem
{
	class PION_API path
	{
		public:
			path() = default;
			path( const std::string &i_path );

			inline bool empty() const { return _path.empty(); }
			inline const std::string &string() const { return _path; }
			path filename() const;
			path parent_path() const;

			path &make_preferred();

			path &operator/=( const path &i_comp );

			path &normalize();

		private:
			std::string _path;
	};

	path PION_API operator/( const path &i_path, const path &i_comp );

	path PION_API system_complete( const path &i_path );
	std::string PION_API extension( const path &i_path );
	std::string PION_API basename( const path &i_path );
	bool PION_API exists( const path &i_path );
	bool PION_API is_directory( const path &i_path );
	bool PION_API is_regular( const path &i_path );

	std::time_t PION_API last_write_time( const path &i_path );
	uint64_t PION_API file_size( const path &i_path );

	void PION_API remove( const path &i_path );
}

std::vector<filesystem::path> PION_API get_dir_content( const filesystem::path &i_path );

#ifdef PION_WIN32
std::wstring PION_API filesystem_path( const filesystem::path &i_path );
#else
std::string filesystem_path( const filesystem::path &i_path );
#endif

}

#ifdef PION_WIN32
#  pragma warning( pop )
#endif

#endif
