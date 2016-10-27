#ifndef CLTOOLS_H
#define CLTOOLS_H

#include <boost/filesystem.hpp>

class ClParser
{
public:
	ClParser(int, char**);
	~ClParser();
	int8_t FileFormat() const;
	std::string InPath() const;
	std::string OutPath() const;

protected:
	char** mInput;
	std::string* mDirectory;
	boost::filesystem::path* mInPath;
	boost::filesystem::path* mOutPath;
	int8_t mOptions;

	void SetPath(boost::filesystem::path**, char*) const;
	void SetOptions(char*);
};

#endif // CLTOOLS_H


/*
 * mOptions = b00000000
 * 
 * bit 0: <fbx type>
 *   0 = binary
 *   1 = ascii
 *   
 * bit 1: <unused>
 *   0 = 
 *   1 = 
 *   
 * bit 2: <unused>
 *   0 =
 *   1 =
 *   
 * bit 3: <unused>
 *   0 =
 *   1 =
 *   
 * bit 4: <unused>
 *   0 =
 *   1 =
 *   
 * bit 5: <unused>
 *   0 =
 *   1 =
 *   
 * bit 6: <unused>
 *   0 =
 *   1 =
 *   
 * bit 7: <unused>
 *   0 =
 *   1 =
 *   
 * bit 8: <unused>
 *   0 =
 *   1 =
 */