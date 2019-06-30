#include <vector>
#include <string>

static const std::string NOT_ASSIGNED = "N/A";
static const int NOT_ASSIGNED_HASH = -1;
// Metadata extensions
static const char* METADATA_EXTENSION = ".xml";
static const char* METADATA_TYPE_TEXTURE = "Texture";
static const char* METADATA_TYPE_AUDIOCLIP = "Audio_Clip";
// Engine file extensions
static const char* EXTENSION_WORLD = ".world";
static const char* EXTENSION_MATERIAL = ".mat";
static const char* EXTENSION_MODEL = ".model";
static const char* EXTENSION_PREFAB = ".prefab";
static const char* EXTENSION_SHADER = ".shader";
static const char* EXTENSION_TEXTURE = ".texture";
static const char* EXTENSION_MESH = ".mesh";

namespace Ember
{
	class FileSystem
	{
	public:
		static void Initialize();

		//Directories
		static bool CreateDirectory_(const std::string& path);
		static bool DeleteDirectory(const std::string& directory);
		static bool DirectoryExists(const std::string& directory);
		static bool IsDirectory(const std::string& directory);
		static void OpenDirectoryWindow(const std::string& directory);

		//Files
		static bool FileExists(const std::string& filePath);
		static bool DeleteFile_(const std::string& filePath);
		static bool CopyFileFromTo(const std::string& source, const std::string& destination);

		//Directory Parsing
		static std::string GetFileNameFromFilePath(const std::string& path);
		static std::string GetFileNameNoExtensionFromFilePath(const std::string& filepath);
		static std::string GetDirectoryFromFilePath(const std::string& filePath);
		static std::string GetFilePathWithoutExtension(const std::string& filePath);
		static std::string GetExtensionFromFilePath(const std::string& filePath);
		static std::string GetRelativeFilePath(const std::string& absoluteFilePath);
		static std::string GetWorkingDirectory();
		static std::string GetParentDirectory(const std::string& directory);
		static std::vector<std::string> GetDirectoriesInDirectory(const std::string& directory);
		static std::vector<std::string> GetFilesInDirectory(const std::string& directory);

		//Supported Files In Directory
		static std::vector<std::string> GetSupportedFilesInDirectory(const std::string& directory);
		static std::vector<std::string> GetSupportedImageFilesFromPaths(const std::vector<std::string>& paths);
		static std::vector<std::string> GetSupportedAudioFilesFromPaths(const std::vector<std::string>& paths);
		static std::vector<std::string> GetSupportedScriptFilesFromPaths(const std::vector<std::string>& paths);
		static std::vector<std::string> GetSupportedModelFilesFromPaths(const std::vector<std::string>& paths);
		static std::vector<std::string> GetSupportedModelFilesInDirectory(const std::string& directory);
		static std::vector<std::string> GetSupportedSceneFilesInDirectory(const std::string& directory);

		//--> Supported File Checks
		static bool IsSupportedAudioFile(const std::string& path);
		static bool IsSupportedImageFile(const std::string& path);
		static bool IsSupportedModelFile(const std::string& path);
		static bool IsSupportedShaderFile(const std::string& path);
		static bool IsSupportedFontFile(const std::string& path);
		static bool IsEngineScriptFile(const std::string& path);
		static bool IsEnginePrefabFile(const std::string& filePath);
		static bool IsEngineMaterialFile(const std::string& filePath);
		static bool IsEngineMeshFile(const std::string& filePath);
		static bool IsEngineModelFile(const std::string& filePath);
		static bool IsEngineSceneFile(const std::string& filePath);
		static bool IsEngineTextureFile(const std::string& filePath);
		static bool IsEngineShaderFile(const std::string& filePath);
		static bool IsEngineMetadataFile(const std::string& filePath);

		//--> String Parsing
		static std::string GetStringAfterExpression(const std::string& str, const std::string& expression);
		static std::string GetStringBetweenExpressions(const std::string& str, const std::string& firstExpression, const std::string& secondExpression);
		static std::string ConvertToUppercase(const std::string& lower);
		static std::string ReplaceExpression(const std::string& str, const std::string& from, const std::string& to);
		static std::wstring StringToWstring(const std::string& str);
		static std::string ResolveIncludeDirectives(const std::string& source, const std::string& directory);

		//--> Supported Asset File Formats
		static std::vector<std::string> GetSupportedImageFormats() { return m_supportedImageFormats; }
		static std::vector<std::string> GetSupportedAudioFormats() { return m_supportedAudioFormats; }
		static std::vector<std::string> GetSupportedModelFormats() { return m_supportedModelFormats; }
		static std::vector<std::string> GetSupportedShaderFormats() { return m_supportedShaderFormats; }
		static std::vector<std::string> GetSupportedScriptFormats() { return m_supportedScriptFormats; }
		static std::vector<std::string> GetSupportedFontFormats() { return m_supportedFontFormats; }

		//--> Private Vectors
	private:
		static std::vector<std::string> m_supportedImageFormats;
		static std::vector<std::string> m_supportedAudioFormats;
		static std::vector<std::string> m_supportedModelFormats;
		static std::vector<std::string> m_supportedShaderFormats;
		static std::vector<std::string> m_supportedScriptFormats;
		static std::vector<std::string> m_supportedFontFormats;
	};
}