#pragma once

#include "install/remote_nsp.hpp"

namespace tin::install::nsp
{
    class HTTPNSP : public RemoteNSP
    {
        public:
            tin::network::HTTPDownload m_download;

            HTTPNSP(std::string url);

            virtual void RetrieveHeader() override;
            virtual void StreamToPlaceholder(nx::ncm::ContentStorage& contentStorage, NcmNcaId placeholderId) override;
    };
}