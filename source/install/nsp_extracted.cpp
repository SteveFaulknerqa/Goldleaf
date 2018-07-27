#include "install/nsp_extracted.hpp"

#include <memory>
#include "nx/fs.hpp"
#include "error.hpp"

namespace tin::install::nsp
{
    ExtractedDirSession::ExtractedDirSession() {}
    ExtractedDirSession::~ExtractedDirSession()
    {
        fsDirClose(&m_dir);
    }

    Result ExtractedDirSession::OpenDir(FsFileSystem& fileSystem, std::string path)
    {
        PROPAGATE_RESULT(fsFsOpenDirectory(&fileSystem, path.c_str(), FS_DIROPEN_FILE, &m_dir), "Failed to open directory");
        return 0;
    }

    ExtractedNSPContainer::ExtractedNSPContainer() {}

    ExtractedNSPContainer::~ExtractedNSPContainer()
    {
        this->CloseContainer();
    }

    Result ExtractedNSPContainer::OpenContainer(std::string path)
    {
        PROPAGATE_RESULT(fsMountSdcard(&m_fileSystem), "Failed to mount sd card");
        m_baseDirPath = path;
        return 0;
    }

    void ExtractedNSPContainer::CloseContainer()
    {
        fsFsClose(&m_fileSystem);
    }
    
    Result ExtractedNSPContainer::ReadFile(std::string name, u8* buff, size_t size, size_t offset)
    {
        nx::fs::IFile file;
        PROPAGATE_RESULT(file.OpenFile(m_fileSystem, m_baseDirPath + name), "Failed to open file");

        size_t actualReadSize = 0;

        PROPAGATE_RESULT(file.Read(offset, buff, size, &actualReadSize), "Failed to read extracted file");

        if (actualReadSize != size)
        {
            printf("readExtractedInstallFile: Size read 0x%lx doesn't match expected size 0x%lx", actualReadSize, size);
            return -1;
        }

        return 0;
    }

    Result ExtractedNSPContainer::GetFileSize(std::string name, size_t* sizeOut)
    {
        nx::fs::IFile file;
        PROPAGATE_RESULT(file.OpenFile(m_fileSystem, m_baseDirPath + name), "Failed to open file");
        PROPAGATE_RESULT(file.GetSize(sizeOut), "Failed to get file size");
        return 0;
    }

    bool ExtractedNSPContainer::HasFile(std::string name)
    {
        nx::fs::IFile file;
        if (R_FAILED(file.OpenFile(m_fileSystem, m_baseDirPath + name)))
            return false;
        return true;
    }

    std::string ExtractedNSPContainer::GetFileNameFromExtension(std::string extension)
    {
        Result rc = 0;
        ExtractedDirSession dirSession;

        if (R_FAILED(rc = dirSession.OpenDir(m_fileSystem, m_baseDirPath)))
        {
            fprintf(nxlinkout, "%s:%u: %s.  Error code: 0x%08x\n", __func__, __LINE__, "Failed to open dir", rc);
            return "";
        }

        size_t numEntriesRead;
        auto dirEntries = std::make_unique<FsDirectoryEntry[]>(256);

        if (R_FAILED(rc = fsDirRead(&dirSession.m_dir, 0, &numEntriesRead, 256, dirEntries.get())))
        {
            fprintf(nxlinkout, "%s:%u: %s.  Error code: 0x%08x\n", __func__, __LINE__, "Failed to read dir", rc);
            return "";
        }

        for (unsigned int i = 0; i < numEntriesRead; i++)
        {
            FsDirectoryEntry dirEntry = dirEntries[i];
            std::string dirEntryName = dirEntry.name;

            if (dirEntry.type != ENTRYTYPE_FILE)
                continue;

            auto foundExtension = dirEntryName.substr(dirEntryName.find(".") + 1); 

            if (foundExtension == extension)
                return dirEntryName;
        }

        return "";
    }
}