#include "ClTools.h"
#include <iostream>
#include "../Exceptions/SdkException.h"
#include <boost/filesystem/fstream.hpp>

using namespace boost::filesystem;


/* Public Members */

ClParser::ClParser(int pNumArgs, char** pInput)
	: mInput(pInput)
{
	size_t i = 0;
	mOptions = 0;
	mOutPath = new path();
	mInPath = new path();

	for (char** lItor = ++pInput; lItor < pInput+pNumArgs-1; ++lItor)
	{
		if (**lItor == '-')
		{
			char* lOpt = *lItor;
			++lOpt;
			SetOptions(lOpt);
		} 
		else
		{
			switch (i)
			{
			case 0:
				SetPath(&mInPath, *lItor);
				break;
			case 1:
				SetPath(&mOutPath, *lItor);
				break;
			default:
				throw new SdkException("Unable to parse command line arguments");
			}
			++i;
		}
	}
}

ClParser::~ClParser()
{
	delete mOutPath;
	delete mInPath;
}

int8_t ClParser::FileFormat() const
{
	return (mOptions & 0x01);
}

std::string ClParser::InPath() const
{
	return mInPath->string();
}

std::string ClParser::OutPath() const
{
	return mOutPath->string();
}



/* Protected Members */

void ClParser::SetPath(path** pPath, char* lPtr) const
{
	try
	{
		path lPath = complete(lPtr);
		**pPath = lPath;
	}
	catch (const filesystem_error& ex)
	{
		std::cerr << ex.what() << "\n";
		throw;
	}
}

void ClParser::SetOptions(char* pOpt)
{
	switch (*pOpt)
	{
	case 'b':
		mOptions = mOptions | 0x00;
		break;
	case 'a':
		mOptions = mOptions | 0x01;
		break;
	default:
		mOptions = mOptions & 0x00;
		break;
	}
}



