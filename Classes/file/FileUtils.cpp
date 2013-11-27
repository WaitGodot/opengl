#include "Fileutils.h"
#include "_MacroConfig.h"
#include <windows.h>


#define MAX_PATH 256

FileUtils::FileUtils():
	m_rootPath("")
{

}

FileUtils::~FileUtils()
{

}

std::string FileUtils::getFullPath( const char* file )
{
	return m_rootPath + file;
}

const char* FileUtils::getFullPathNeedRelease( const char* file )
{
	char* path = new char[MAX_PATH];
	std::string newPath = m_rootPath+file;
	memcpy(path,newPath.c_str(),newPath.size());
	path[newPath.size()] = '\0';
	return path;
}

unsigned char* FileUtils::getFileData( const char* file,const char* mode, unsigned long& length )
{
	std::string str = file;
	
	if( std::string::npos == str.find(m_rootPath) )
	{
		str = getFullPath(file).c_str();
	}
	unsigned char* result = NULL;
	do 
	{
		FILE* fp = fopen(str.c_str(),mode);
		BREAK_IF_LOG(!fp,"fopen fail!");
		
		fseek(fp,0,SEEK_END);
		length = ftell(fp);
		fseek(fp,0,SEEK_SET);
		result = new unsigned char[length];
		length = fread(result , sizeof(unsigned char),length,fp);
		fclose(fp);
		//BREAK_IF_LOG(length == 0 ,"fopen fail! length = 0!");
	} while (0);

	return result;
}

unsigned char* FileUtils::getFileData( const char* file,const char* mode )
{
	unsigned long length = 0;
	return getFileData(file,mode,length);
}

void FileUtils::checkPath()
{
	char path[256] = {0};
	if (! path[0])
	{
		WCHAR  wszPath[MAX_PATH] = {0};
		int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath, 
			GetCurrentDirectoryW(sizeof(wszPath), wszPath), 
			path, MAX_PATH, NULL, NULL);
		path[nNum] = '\\'; 
	}
	setRootPath(path);
}

void FileUtils::setRootPath( const char* path )
{
	m_rootPath = path;
}

FileUtils* FileUtils::shareFileUtils()
{
	if(!gs_fileutils){
		gs_fileutils = new FileUtils();
		gs_fileutils->checkPath();
	}
	return gs_fileutils;
}

FileUtils* FileUtils::gs_fileutils = 0;

