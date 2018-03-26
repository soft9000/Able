#include "MudLib1.hpp"

using namespace MudLib1;

// The MUD file conatins a map to all of the Multiply Updated Documents
bool Protocol::Get(const Url& url, MudFile& mudFile)
{return false;}
bool Protocol::Put(const Url& url, MudFile& mudFile, const FtpInfo& ftpUser)
{return false;}

// The DIRT file contains a bunch of DIRT tags;
bool Protocol::Get(const Url& url, DirtFile& dirtFile)
{return false;}
bool Protocol::Put(const Url& url, DirtFile& dirtFile, const FtpInfo& ftpUser)
{return false;}

// Commons
bool Protocol::Get(UpDownFile& refCommon)
{return false;}
bool Protocol::Put(UpDownFile& refCommon, const FtpInfo& ftpUser)
{return false;}
