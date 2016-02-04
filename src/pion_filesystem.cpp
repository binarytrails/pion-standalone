
#include <pion/config.hpp>
#include <pion/utils/pion_filesystem.hpp>

#ifdef ASIO_STANDALONE

#ifdef PION_WIN32
#else
#include <unistd.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <dirent.h>
#endif

namespace
{

bool is_separator( char c )
{
#ifdef PION_WIN32
	return c == '/' or c == '\\';
#else
	return c == '/';
#endif
}

#ifdef PION_WIN32
const char preferred_separator = '\\';
const char all_separators[] = "\\/";
#else
const char preferred_separator = '/';
const char all_separators[] = "/";
#endif

bool is_absolute( const pion::filesystem::path &i_path )
{
#ifdef PION_WIN32
#error
#else
	return not i_path.string().empty() and i_path.string().front() == '/';
#endif
}

std::string filename( const pion::filesystem::path &i_path )
{
	if ( i_path.string().empty() )
		return std::string();
	
	auto pos = i_path.string().find_last_of( all_separators );
	if ( pos == std::string::npos )
		return i_path.string();
	
	return i_path.string().substr( pos + 1 );
}

}

namespace pion { namespace filesystem
{

path::path( const std::string &i_path )
	: _path( i_path )
{
}

path &path::operator/=( const path &i_comp )
{
	if ( i_comp.string().empty() )
		return *this;
	if ( not is_separator( i_comp.string().front() ) )
	{
		if ( not _path.empty() and
#ifdef PION_WIN32
				_path.back() != ':' and
#endif
				not is_separator( _path.back() ) )
		{
			_path += preferred_separator;
		}
	}
	_path += i_comp.string();
	
	return *this;
}

path operator/( const path &i_path, const path &i_comp )
{
	path p( i_path );
	p /= i_comp;
	return p;
}

path system_complete( const path &i_path )
{
#ifdef PION_WIN32
#error GetFullPathNameW ?
#else
	if ( i_path.string().empty() or is_absolute(i_path) )
		return i_path;
	else
	{
		char cwd[MAXPATHLEN];
		path p( getcwd( cwd, MAXPATHLEN ) );
		p /= i_path;
		return p;
	}
#endif
}

bool exists( const path &i_path )
{
#ifdef PION_WIN32
#error
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0;
#endif
}

bool is_regular( const path &i_path )
{
#ifdef PION_WIN32
#error
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 and ((info.st_mode&S_IFREG)!=0);
#endif
}

std::string extension( const path &i_path )
{
	auto name = filename(i_path);
	if ( name == "." or name == ".." )
		return std::string();
	auto pos = name.rfind( '.' );
	return pos == std::string::npos
			? std::string() : name.substr( pos );
}

std::string basename( const path &i_path )
{
	auto name = filename(i_path);
	if ( name == "." or name == ".." )
		return name;
	auto pos = name.rfind( '.' );
	return pos == std::string::npos
			? name : name.substr( 0, pos );
}

}

std::vector<filesystem::path> get_dir_content( const filesystem::path &i_path )
{
	std::vector<filesystem::path> dirlist;
#ifdef PION_WIN32
#error
#else
	auto dirpath = filesystem::system_complete(i_path);
	auto dirp = ::opendir( dirpath.string().c_str() );
	if ( dirp != nullptr )
	{
		struct dirent entry, *result;
		while ( readdir_r( dirp, &entry, &result ) == 0 and result != nullptr )
		{
			dirlist.emplace_back( dirpath.string() + "/" + result->d_name );
		}
		closedir( dirp );
	}
#endif
	return dirlist;
}

}

#else

namespace pion
{

std::vector<boost::filesystem::path> get_dir_content( const boost::filesystem::path &i_path )
{
	std::vector<boost::filesystem::path> result;
	
	boost::filesystem::directory_iterator end;
	for ( boost::filesystem::directory_iterator it( i_path ); it != end; ++it )
		result.push_back( *it );

	return result;
}

#ifdef PION_WIN32
std::wstring filesystem_path( const filesystem::path &i_path )
{
#error
}
#else
std::string filesystem_path( const filesystem::path &i_path )
{
	return i_path.string();
}
#endif

}

#endif
