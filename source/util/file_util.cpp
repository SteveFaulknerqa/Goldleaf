#include "util/file_util.hpp"

#include <memory>

#include "install/simple_filesystem.hpp"
#include "nx/fs.hpp"
#include "util/byte_buffer.hpp"
#include "util/title_util.hpp"

namespace tin::util
{
    std::tuple<std::string, nx::ncm::ContentRecord> GetCNMTNCAInfo(std::string nspPath)
    {
        // Open filesystem
        nx::fs::IFileSystem fileSystem;
        fileSystem.OpenFileSystemWithId(nspPath, FsFileSystemType_ApplicationPackage, 0);
        tin::install::nsp::SimpleFileSystem simpleFS(fileSystem, "/", nspPath + "/");

        // Create the path of the cnmt NCA
        auto cnmtNCAName = simpleFS.GetFileNameFromExtension("", "cnmt.nca");
        auto cnmtNCAFile = simpleFS.OpenFile(cnmtNCAName);
        auto cnmtNCAFullPath = simpleFS.m_absoluteRootPath + cnmtNCAName;
        u64 cnmtNCASize = cnmtNCAFile.GetSize();

        // Prepare cnmt content record
        nx::ncm::ContentRecord contentRecord;
        contentRecord.ncaId = tin::util::GetNcaIdFromString(cnmtNCAName);
        *(u64*)contentRecord.size = cnmtNCASize & 0xFFFFFFFFFFFF;
        contentRecord.contentType = NcmContentType_CNMT;

        return { cnmtNCAFullPath, contentRecord };
    }

    nx::ncm::ContentMeta GetContentMetaFromNCA(std::string ncaPath)
    {
        // Create the cnmt filesystem
        nx::fs::IFileSystem cnmtNCAFileSystem;
        cnmtNCAFileSystem.OpenFileSystemWithId(ncaPath, FsFileSystemType_ContentMeta, 0);
        tin::install::nsp::SimpleFileSystem cnmtNCASimpleFileSystem(cnmtNCAFileSystem, "/", ncaPath + "/");
        
        // Find and read the cnmt file
        auto cnmtName = cnmtNCASimpleFileSystem.GetFileNameFromExtension("", "cnmt");
        auto cnmtFile = cnmtNCASimpleFileSystem.OpenFile(cnmtName);
        u64 cnmtSize = cnmtFile.GetSize();

        tin::util::ByteBuffer cnmtBuf;
        cnmtBuf.Resize(cnmtSize);
        cnmtFile.Read(0x0, cnmtBuf.GetData(), cnmtSize);

        return nx::ncm::ContentMeta(cnmtBuf.GetData(), cnmtBuf.GetSize());
    }

    std::vector<std::string> GetNSPList()
    {
        std::vector<std::string> nspList;
        nx::fs::IFileSystem fileSystem;
        fileSystem.OpenSdFileSystem();
        nx::fs::IDirectory dir = fileSystem.OpenDirectory("/tinfoil/nsp/", FS_DIROPEN_FILE);

        u64 entryCount = dir.GetEntryCount();

        auto dirEntries = std::make_unique<FsDirectoryEntry[]>(entryCount);

        dir.Read(0, dirEntries.get(), entryCount);

        for (unsigned int i = 0; i < entryCount; i++)
        {
            FsDirectoryEntry dirEntry = dirEntries[i];
            std::string dirEntryName(dirEntry.name);
            std::string ext = ".nsp";

            if (dirEntry.type != ENTRYTYPE_FILE || dirEntryName.compare(dirEntryName.size() - ext.size(), ext.size(), ext) != 0)
                continue;

            nspList.push_back(dirEntry.name);
        }

        return nspList;
    }
}