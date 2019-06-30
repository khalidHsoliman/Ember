#include "Epch.h"
#include "FileSystem.h"
#include <filesystem>
#include <regex>
#include <fstream>
#include <sstream>
#include "Log.h"
#include <Windows.h>
#include <shellapi.h>

namespace Ember
{
	std::vector<std::string> FileSystem::m_supportedImageFormats;
	std::vector<std::string> FileSystem::m_supportedAudioFormats;
	std::vector<std::string> FileSystem::m_supportedModelFormats;
	std::vector<std::string> FileSystem::m_supportedShaderFormats;
	std::vector<std::string> FileSystem::m_supportedScriptFormats;
	std::vector<std::string> FileSystem::m_supportedFontFormats;

	void FileSystem::Initialize()
	{
		// Supported image formats
		m_supportedImageFormats =
		{
			".jpg",
			".png",
			".bmp",
			".tga",
			".dds",
			".exr",
			".raw",
			".gif",
			".hdr",
			".ico",
			".iff",
			".jng",
			".jpeg",
			".koala",
			".kodak",
			".mng",
			".pcx",
			".pbm",
			".pgm",
			".ppm",
			".pfm",
			".pict",
			".psd",
			".raw",
			".sgi",
			".targa",
			".tiff",
			".tif", // tiff can also be tif
			".wbmp",
			".webp",
			".xbm",
			".xpm"
		};

		// Supported audio formats
		m_supportedAudioFormats =
		{
			".aiff",
			".asf",
			".asx",
			".dls",
			".flac",
			".fsb",
			".it",
			".m3u",
			".midi",
			".mod",
			".mp2",
			".mp3",
			".ogg",
			".pls",
			".s3m",
			".vag", // PS2/PSP
			".wav",
			".wax",
			".wma",
			".xm",
			".xma" // XBOX 360
		};

		// Supported model formats
		m_supportedModelFormats =
		{
			".3ds",
			".obj",
			".fbx",
			".blend",
			".dae",
			".lwo",
			".c4d",
			".ase",
			".dxf",
			".hmp",
			".md2",
			".md3",
			".md5",
			".mdc",
			".mdl",
			".nff",
			".ply",
			".stl",
			".x",
			".smd",
			".lxo",
			".lws",
			".ter",
			".ac3d",
			".ms3d",
			".cob",
			".q3bsp",
			".xgl",
			".csm",
			".bvh",
			".b3d",
			".ndo"
		};

		// Supported shader formats
		/*m_supportedShaderFormats =
		{
			".hlsl"
		};*/

		// Supported script formats
		/*m_supportedScriptFormats =
		{
			".as"
		};*/

		// Supported font formats
		m_supportedFontFormats =
		{
			".ttf",
			".ttc",
			".cff",
			".woff",
			".otf",
			".otc",
			".pfa",
			".pfb",
			".fnt",
			".bdf",
			".pfr"
		};
	}

	bool FileSystem::CreateDirectory_(const std::string& path)
	{
		try
		{
			return std::filesystem::create_directories(path);
		}
		catch (std::filesystem::filesystem_error& e)
		{
			EMBER_ERROR("FileSystem::CreateDirectory: %s, %s", e.what(), path.c_str());
			return true;
		}
	}

	bool FileSystem::DeleteDirectory(const std::string& directory)
	{
		try
		{
			return std::filesystem::remove_all(directory);
		}
		catch (std::filesystem::filesystem_error e)
		{
			EMBER_ERROR("FileSystem::DeleteDirectory: %s, %s", e.what(), directory.c_str());
			return true;
		}
	}

	bool FileSystem::DirectoryExists(const std::string& directory)
	{
		try
		{
			return std::filesystem::exists(directory);
		}
		catch (std::filesystem::filesystem_error e)
		{
			EMBER_ERROR("FileSystem::DeleteDirectory: %s, %s", e.what(), directory.c_str());
			return true;
		}
	}

	bool FileSystem::IsDirectory(const std::string& directory)
	{
		try
		{
			return std::filesystem::is_directory(directory);
		}
		catch (std::filesystem::filesystem_error e)
		{
			EMBER_ERROR("FileSystem::DeleteDirectory: %s, %s", e.what(), directory.c_str());
			return true;
		}
	}

	void FileSystem::OpenDirectoryWindow(const std::string& directory)
	{
		ShellExecute(nullptr, nullptr, FileSystem::StringToWstring(directory).c_str(), nullptr, nullptr, SW_SHOW);
	}

	bool FileSystem::FileExists(const std::string & filePath)
	{
		try
		{
			return std::filesystem::exists(filePath);
		}
		catch (std::filesystem::filesystem_error e)
		{
			EMBER_ERROR("FileSystem::DeleteDirectory: %s, %s", e.what(), filePath.c_str());
			return true;
		}
	}

	bool FileSystem::DeleteFile_(const std::string & filePath)
	{
		// If this is a directory path, return
		if(std::filesystem::is_directory(filePath))
			return false;

		try
		{
			return std::filesystem::remove(filePath.c_str()) == 0;
		}
		catch (std::filesystem::filesystem_error e)
		{
			EMBER_ERROR("FileSystem::DeleteDirectory: %s, %s", e.what(), filePath.c_str());
			return true;
		}
	}

	bool FileSystem::CopyFileFromTo(const std::string & source, const std::string & destination)
	{
		if (source == destination)
			return true;
		// In case the destination path doesn't exist, create it
		if (!DirectoryExists(GetDirectoryFromFilePath(destination)))
		{
			FileSystem::CreateDirectory_(GetDirectoryFromFilePath(destination));
		}

		try
		{
			return std::filesystem::copy_file(source, destination, std::filesystem::copy_options::overwrite_existing);
		}
		catch (std::filesystem::filesystem_error& e)
		{
			EMBER_ERROR("FileSystem: Could not copy \"" + source + "\". " + std::string(e.what()));
			return true;
		}
	}

	std::string FileSystem::GetFileNameFromFilePath(const std::string & path)
	{
		auto lastIndex = path.find_last_of("\\/");
		auto fileName = path.substr(lastIndex + 1, path.length());
		return fileName;
	}

	std::string FileSystem::GetFileNameNoExtensionFromFilePath(const std::string & filepath)
	{
		auto fileName = GetFileNameFromFilePath(filepath);
		auto lastIndex = fileName.find_last_of('.');
		auto fileNameNoExt = fileName.substr(0, lastIndex);
		return fileNameNoExt;
	}

	std::string FileSystem::GetDirectoryFromFilePath(const std::string & filePath)
	{
		auto lastindex = filePath.find_last_of("\\/");
		auto directory = filePath.substr(0, lastindex + 1);
		return directory;
	}

	std::string FileSystem::GetFilePathWithoutExtension(const std::string & filePath)
	{
		auto directory = GetDirectoryFromFilePath(filePath);
		auto fileNameNoExt = GetFileNameNoExtensionFromFilePath(filePath);
		return directory + fileNameNoExt;
	}

	std::string FileSystem::GetExtensionFromFilePath(const std::string & filePath)
	{
		if (filePath.empty() || filePath == NOT_ASSIGNED)
			return NOT_ASSIGNED;

		auto lastIndex = filePath.find_last_of('.');
		if (std::string::npos != lastIndex)
		{
			// extension with dot included
			return filePath.substr(lastIndex, filePath.length());
		}

		return NOT_ASSIGNED;
	}

	// Returns a file path which is relative to the engine's executable
	std::string FileSystem::GetRelativeFilePath(const std::string & absoluteFilePath)
	{
		std::filesystem::path p = std::filesystem::absolute(absoluteFilePath);
		std::filesystem::path r = std::filesystem::absolute(GetWorkingDirectory());

		// if root paths are different, return absolute path
		if (p.root_path() != r.root_path())
			return p.generic_string();

		// initialize relative path
		std::filesystem::path result;

		// find out where the two paths diverge
		std::filesystem::path::const_iterator itr_path = p.begin();
		std::filesystem::path::const_iterator itr_relative_to = r.begin();
		while (*itr_path == *itr_relative_to && itr_path != p.end() && itr_relative_to != r.end())
		{
			++itr_path;
			++itr_relative_to;
		}

		// add "../" for each remaining token in relative_to
		if (itr_relative_to != r.end())
		{
			++itr_relative_to;
			while (itr_relative_to != r.end())
			{
				result /= "..";
				++itr_relative_to;
			}
		}

		// add remaining path
		while (itr_path != p.end())
		{
			result /= *itr_path;
			++itr_path;
		}

		return result.generic_string();
	}

	// Returns a file path which is where the engine's executable is located
	std::string FileSystem::GetWorkingDirectory()
	{
		return std::filesystem::current_path().generic_string() + "/";
	}
	std::string FileSystem::GetParentDirectory(const std::string & directory)
	{
		auto found = directory.find_last_of("/\\");
		auto result = directory;

		// If no slash was found, return provided string
		if (found == std::string::npos)
			return directory;

		// If the slash was find at the last position, remove it and try again
		if (found == directory.length() - 1)
		{
			result = result.substr(0, found - 1);
			return GetParentDirectory(result);
		}

		// Return parent directory including a slash at the end
		return result.substr(0, found) + "/";
	}
	std::vector<std::string> FileSystem::GetDirectoriesInDirectory(const std::string & directory)
	{
		std::vector<std::string> subDirs;
		std::filesystem::directory_iterator end_itr; // default construction yields past-the-end
		for (std::filesystem::directory_iterator itr(directory); itr != end_itr; ++itr)
		{
			if (!std::filesystem::is_directory(itr->status()))
				continue;
			subDirs.emplace_back(itr->path().generic_string());
		}
		return subDirs;
	}
	std::vector<std::string> FileSystem::GetFilesInDirectory(const std::string & directory)
	{
		std::vector<std::string> filePaths;
		std::filesystem::directory_iterator end_itr; // default construction yields past-the-end
		for (std::filesystem::directory_iterator itr(directory); itr != end_itr; ++itr)
		{
			if (!std::filesystem::is_regular_file(itr->status()))
				continue;
			filePaths.emplace_back(itr->path().generic_string());
		}
		return filePaths;
	}
	std::string FileSystem::GetStringAfterExpression(const std::string & str, const std::string & expression)
	{
		auto position = str.find(expression);
		auto remaining = position != std::string::npos ? str.substr(position + expression.length()) : str;
		return remaining;
	}
	std::string FileSystem::GetStringBetweenExpressions(const std::string & str, const std::string & firstExpression, const std::string & secondExpression)
	{
		std::regex base_regex(firstExpression + "(.*)" + secondExpression);
		std::smatch base_match;

		if (std::regex_search(str, base_match, base_regex))
		{
			// The first sub_match is the whole string; the next
			// sub_match is the first parenthesized expression.
			if (base_match.size() == 2)
			{
				return base_match[1].str();
			}
		}
		return str;
	}
	std::string FileSystem::ConvertToUppercase(const std::string & lower)
	{
		std::locale loc;
		std::string upper;

		for (const auto& character : lower)
		{
			upper += std::toupper(character, loc);
		}
		return upper;
	}
	std::string FileSystem::ReplaceExpression(const std::string & str, const std::string & from, const std::string & to)
	{
		return std::regex_replace(str, std::regex(from), to);
	}
	std::wstring FileSystem::StringToWstring(const std::string & str)
	{
		const auto slength = static_cast<int>(str.length()) + 1;
		const auto len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, nullptr, 0);
		const auto buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
		std::wstring result(buf);
		delete[] buf;
		return result;
	}
}