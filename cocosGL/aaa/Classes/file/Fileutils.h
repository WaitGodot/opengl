#ifndef _FILE_UNTILS_H
#define _FILE_UNTILS_H

#include <string>


class FileUtils
{
private:
	FileUtils();

	void checkPath();

	std::string m_rootPath;
	static FileUtils* gs_fileutils;
public:
	~FileUtils();

	std::string getFullPath(const char* file);
	const char* getFullPathNeedRelease(const char* file);
	//mode : r,r+,rb+,rw+,w,w+,a,a+,wb,wb+,ab+
	unsigned char* getFileData(const char* file,const char* mode, unsigned long& length);
	unsigned char* getFileData(const char* file,const char* mode);

	unsigned char* getFileDataNotFullPath(const char* file,const char* mode, unsigned long& length);
	void setRootPath(const char* path);

	bool fileExist(const char* file);

	static FileUtils* shareFileUtils();
};

#define gsShareFileUtils() FileUtils::shareFileUtils()

#endif