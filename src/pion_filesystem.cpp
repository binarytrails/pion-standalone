
#include <pion/config.hpp>
#include <pion/utils/pion_filesystem.hpp>

#ifdef PION_WIN32
#include <codecvt>
#include <algorithm>
#include <windows.h>
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
	return c == '/' || c == '\\';
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
	if ( ! is_separator( i_comp.string().front() ) )
	{
		if ( ! _path.empty() &&
#ifdef PION_WIN32
				_path.back() != ':' &&
#endif
				! is_separator( _path.back() ) )
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
		return *this;
	if ( comps.size() == 1 && comps.front().back() == ':' )
	{
		_path = comps.front() + preferred_separator;
		return *this;
	}
#else
	if ( _path.front() == preferred_separator)
		_path = preferred_separator;
	else
		_path.clear();
#endif
	
	std::vector<std::string> newComps;
	auto it = comps.begin();
	while ( it != comps.end() )
	{
		if ( *it == "." )
			continue;
		if ( (it+1) != comps.end() && *(it+1) == ".." )
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

path &path::make_preferred()
{
#ifdef PION_WIN32
	std::replace( _path.begin(), _path.end(), '/', preferred_separator );
#endif
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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
	return conversion.to_bytes( filesystem_path( i_path ) );
#else
	if ( i_path.string().empty() or i_path.string().front() == '/' )
		return i_path; // already absolute
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
	return GetFileAttributesW(filesystem_path(i_path).c_str()) != INVALID_FILE_ATTRIBUTES;
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0;
#endif
}

bool is_directory( const path &i_path )
{
#ifdef PION_WIN32
	return GetFileAttributesW(filesystem_path(i_path).c_str()) == FILE_ATTRIBUTE_DIRECTORY;
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 and ((info.st_mode&S_IFDIR)!=0);
#endif
}

bool is_regular( const path &i_path )
{
#ifdef PION_WIN32
	return GetFileAttributesW(filesystem_path(i_path).c_str()) == FILE_ATTRIBUTE_NORMAL;
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 and ((info.st_mode&S_IFREG)!=0);
#endif
}

std::time_t last_write_time( const path &i_path )
{
#ifdef PION_WIN32
	std::time_t res = -1;
	auto h = CreateFileW(filesystem_path(i_path).c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr );
	if (h != INVALID_HANDLE_VALUE)
	{
		FILETIME createTime, accessTime, writeTime;
		if (GetFileTime(h, &createTime, &accessTime, &writeTime))
		{
			int64_t t = (static_cast<int64_t>(writeTime.dwHighDateTime) << 32)
				+ writeTime.dwLowDateTime;
			t -= 116444736000000000LL;
			t /= 10000000;
			res= static_cast<std::time_t>(t);
		}
		CloseHandle(h);
	}
	return res;
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 ? info.st_mtim.tv_sec : -1;
#endif
}

uint64_t file_size( const path &i_path )
{
#ifdef PION_WIN32
	WIN32_FILE_ATTRIBUTE_DATA fad;

	if ( GetFileAttributesExW(filesystem_path(i_path).c_str(), GetFileExInfoStandard, &fad) &&
				(fad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 )
	{
		return (static_cast<uint64_t>(fad.nFileSizeHigh)
			<< (sizeof(DWORD) * 8)) + fad.nFileSizeLow;
	}
	return static_cast<size_t>(-1);
#else
	struct stat info;
	return stat( i_path.string().c_str(), &info ) == 0 ? info.st_size : static_cast<uint64_t>(-1);
#endif
}

std::string extension( const path &i_path )
{
	auto name = i_path.filename().string();
	if ( name == "." || name == ".." )
		return std::string();
	auto pos = name.rfind( '.' );
	return pos == std::string::npos
			? std::string() : name.substr( pos );
}

std::string basename( const path &i_path )
{
	auto name = i_path.filename().string();
	if ( name == "." || name == ".." )
		return name;
	auto pos = name.rfind( '.' );
	return pos == std::string::npos
			? name : name.substr( 0, pos );
}

void remove( const path &i_path )
{
#ifdef PION_WIN32
	DeleteFileW(filesystem_path(i_path).c_str());
#else
	::unlink( i_path.string().c_str() );
#endif
}

}

std::vector<filesystem::path> get_dir_content( const filesystem::path &i_path )
{
	std::vector<filesystem::path> dirlist;
#ifdef PION_WIN32
	WIN32_FIND_DATAW fdata;
	auto dirpath = filesystem_path( i_path );
	auto h = FindFirstFileW( dirpath.c_str(), &fdata );
	if ( h != INVALID_HANDLE_VALUE )
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
		do
		{
			auto e = dirpath + L"\\" + fdata.cFileName;
			dirlist.emplace_back( conversion.to_bytes( e ) );
		}
		while (FindNextFileW( h, &fdata ) != 0 );
		FindClose( h );
	}
#else
	auto dirpath = filesystem::system_complete( i_path );
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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
	auto p = conversion.from_bytes( i_path.string() );
	std::replace( p.begin(), p.end(), L'/', L'\\' );

	auto len = GetFullPathNameW( p.c_str(), 0, nullptr, nullptr );
	if ( len == 0 )
		return p;
	std::wstring result( len, L' ' );
	GetFullPathNameW( p.c_str(), len, (LPWSTR)result.data(), nullptr );
	return result;
}
#else
std::string filesystem_path( const filesystem::path &i_path )
{
	return i_path.string();
}
#endif

}
