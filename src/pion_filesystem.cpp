
#include <pion/config.hpp>
#include <pion/utils/pion_filesystem.hpp>

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

template<class COND>
std::vector<std::string> split_if( const std::string &s, COND &c )
{
	std::vector<std::string> res;
	std::string::size_type a = 0;
	for ( std::string::size_type i = 0; i < s.length(); ++i )
	{
		if ( c( s[i] ) )
		{
			if ( (i - a) > 0 )
				res.push_back( s.substr( a, i - a ) );
			a = i + 1;
		}
	}
	if ( (s.length()-a) > 0 )
		res.push_back( s.substr( a, s.length() - a ) );
	return res;
}

std::string join( const std::vector<std::string> &i_list, std::string::value_type sep )
{
	std::string result;
	auto it = i_list.begin();
	if ( it != i_list.end() )
	{
		result.append( *it );
		++it;
		while ( it != i_list.end() )
		{
			result.append( 1, sep );
			result.append( *it );
			++it;
		}
	}
	return result;
}

}

namespace pion { namespace filesystem
{

path::path( const std::string &i_path )
	: _path( i_path )
{
}

path path::filename() const
{
	if ( _path.empty() )
		return path();
	
	auto pos = _path.find_last_of( all_separators );
	if ( pos == std::string::npos )
		return *this;
	
	return path( _path.substr( pos + 1 ) );
}

path path::parent_path() const
{
	if ( _path.empty() )
		return path();
	
	auto pos = _path.find_last_of( all_separators );
	if ( pos == std::string::npos )
		return *this;
	
	return _path.substr( 0, pos );
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

path &path::normalize()
{
    if ( _path.empty() )
      return *this;
	
	auto comps = split_if( _path, is_separator );

#ifdef PION_WIN32
	_path.clear();
	if ( comps.empty() )
		return;
	if ( comps.size() == 1 and comps.front().back() == ':' )
	{
		_path = comps.front() + '\\';
		return *this;
	}
#else
	if ( _path.front() == '/' )
		_path = '/';
	else
		_path.clear();
#endif
	
	std::vector<std::string> newComps;
	auto it = comps.begin();
	while ( it != comps.end() )
	{
		if ( *it == "." )
			continue;
		if ( (it+1) != comps.end() and *(it+1) == ".." )
		{
			it += 2;
			continue;
		}
		newComps.push_back( *it );
	}
	_path += join( newComps, preferred_separator );
	if ( _path.empty() )
		_path = ".";
	
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

bool is_directory( const path &i_path )
{
#ifdef PION_WIN32
#error
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 and ((info.st_mode&S_IFDIR)!=0);
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

std::time_t last_write_time( const path &i_path )
{
#ifdef PION_WIN32
#error
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 ? info.st_mtimespec.tv_sec : 0;
#endif
}

size_t file_size( const path &i_path )
{
#ifdef PION_WIN32
#error
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 ? info.st_size : 0;
#endif
}

std::string extension( const path &i_path )
{
	auto name = i_path.filename().string();
	if ( name == "." or name == ".." )
		return std::string();
	auto pos = name.rfind( '.' );
	return pos == std::string::npos
			? std::string() : name.substr( pos );
}

std::string basename( const path &i_path )
{
	auto name = i_path.filename().string();
	if ( name == "." or name == ".." )
		return name;
	auto pos = name.rfind( '.' );
	return pos == std::string::npos
			? name : name.substr( 0, pos );
}

void remove( const path &i_path )
{
#ifdef PION_WIN32
#error
#else
	::unlink( i_path.string().c_str() );
#endif
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
