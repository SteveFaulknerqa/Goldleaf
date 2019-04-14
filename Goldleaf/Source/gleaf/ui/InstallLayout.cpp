#include <gleaf/ui.hpp>

extern gleaf::set::Settings gsets;

namespace gleaf::ui
{
    extern MainApplication *mainapp;

    InstallLayout::InstallLayout() : pu::Layout()
    {
        this->installText = new pu::element::TextBlock(150, 320, set::GetDictionaryEntry(151));
        this->installText->SetHorizontalAlign(pu::element::HorizontalAlign::Center);
        this->installText->SetColor(gsets.CustomScheme.Text);
        this->installBar = new pu::element::ProgressBar(340, 360, 600, 30, 100.0f);
        this->Add(this->installText);
        this->Add(this->installBar);
    }

    InstallLayout::~InstallLayout()
    {
        delete this->installText;
        delete this->installBar;
    }

    void InstallLayout::StartInstall(std::string Path, fs::Explorer *Exp, Storage Location, pu::Layout *Prev)
    {
        if(IsInstalledTitle()) appletBeginBlockingHomeButton(0);
        Result rc = nsp::Install(Path, Exp, Location, [&](ncm::ContentMetaType Type, u64 ApplicationId, std::string IconPath, NacpStruct *NACP, horizon::TicketData *Tik, std::vector<ncm::ContentRecord> NCAs) -> bool
        {
            std::string info = set::GetDictionaryEntry(82) + "\n\n";
            switch(Type)
            {
                case ncm::ContentMetaType::Application:
                    info += set::GetDictionaryEntry(83);
                    break;
                case ncm::ContentMetaType::Patch:
                    info += set::GetDictionaryEntry(84);
                    break;
                case ncm::ContentMetaType::AddOnContent:
                    info += set::GetDictionaryEntry(85);
                    break;
                default:
                    info += set::GetDictionaryEntry(86);
                    break;
            }
            info += "\n";
            horizon::ApplicationIdMask idmask = horizon::IsValidApplicationId(ApplicationId);
            switch(idmask)
            {
                case horizon::ApplicationIdMask::Official:
                    info += set::GetDictionaryEntry(87);
                    break;
                case horizon::ApplicationIdMask::Homebrew:
                    info += set::GetDictionaryEntry(88);
                    break;
                case horizon::ApplicationIdMask::Invalid:
                    info += set::GetDictionaryEntry(89);
                    break;
            }
            info += "\n" + set::GetDictionaryEntry(90) + " " + horizon::FormatApplicationId(ApplicationId);
            info += "\n\n";
            if(NACP != NULL)
            {
                NacpLanguageEntry lent;
                for(u32 i = 0; i < 16; i++)
                {
                    lent = NACP->lang[i];
                    if((strlen(lent.name) != 0) && (strlen(lent.author) != 0)) break;
                }
                info += set::GetDictionaryEntry(91) + " ";
                info += lent.name;
                info += "\n" + set::GetDictionaryEntry(92) + " ";
                info += lent.author;
                info += "\n" + set::GetDictionaryEntry(109) + " ";
                info += NACP->version;
                info += "\n\n" + set::GetDictionaryEntry(93) + " ";
            }
            for(u32 i = 0; i < NCAs.size(); i++)
            {
                ncm::ContentType t = NCAs[i].Type;
                switch(t)
                {
                    case ncm::ContentType::Control:
                        info += set::GetDictionaryEntry(166);
                        break;
                    case ncm::ContentType::Data:
                        info += set::GetDictionaryEntry(165);
                        break;
                    case ncm::ContentType::LegalInformation:
                        info += set::GetDictionaryEntry(168);
                        break;
                    case ncm::ContentType::Meta:
                        info += set::GetDictionaryEntry(163);
                        break;
                    case ncm::ContentType::OfflineHTML:
                        info += set::GetDictionaryEntry(167);
                        break;
                    case ncm::ContentType::Program:
                        info += set::GetDictionaryEntry(164);
                        break;
                    default:
                        break;
                }
                if(i != (NCAs.size() - 1)) info += ", ";
            }
            if(Tik != NULL)
            {
                info += "\n\n" + set::GetDictionaryEntry(94) + "\n\n";
                info += set::GetDictionaryEntry(235) + " " + Tik->TitleKey;
                info += "\n" + set::GetDictionaryEntry(236) + " ";
                switch(Tik->Signature)
                {
                    case horizon::TicketSignature::RSA_4096_SHA1:
                        info += "RSA 4096 (SHA1)";
                        break;
                    case horizon::TicketSignature::RSA_2048_SHA1:
                        info += "RSA 2048 (SHA1)";
                        break;
                    case horizon::TicketSignature::ECDSA_SHA1:
                        info += "ECDSA (SHA256)";
                        break;
                    case horizon::TicketSignature::RSA_4096_SHA256:
                        info += "RSA 4096 (SHA256)";
                        break;
                    case horizon::TicketSignature::RSA_2048_SHA256:
                        info += "RSA 2048 (SHA256)";
                        break;
                    case horizon::TicketSignature::ECDSA_SHA256:
                        info += "ECDSA (SHA256)";
                        break;
                }
                info += "\n" + set::GetDictionaryEntry(95) + " " + std::to_string(Tik->KeyGeneration + 1) + " ";
                switch(Tik->KeyGeneration)
                {
                    case 0:
                        info += "(1.0.0 - 2.3.0)";
                        break;
                    case 1:
                        info += "(3.0.0)";
                        break;
                    case 2:
                        info += "(3.0.1 - 3.0.2)";
                        break;
                    case 3:
                        info += "(4.0.0 - 4.1.0)";
                        break;
                    case 4:
                        info += "(5.0.0 - 5.1.0)";
                        break;
                    case 5:
                        info += "(6.0.0 - 6.1.0)";
                        break;
                    case 6:
                        info += "(6.2.0)";
                        break;
                    case 7:
                        info += "(7.0.0 - 7.1.0)";
                        break;
                    default:
                        info += set::GetDictionaryEntry(96);
                        break;
                }
            }
            else info += "\n\n" + set::GetDictionaryEntry(97);
            int sopt = mainapp->CreateShowDialog(set::GetDictionaryEntry(77), info, { set::GetDictionaryEntry(65), set::GetDictionaryEntry(18) }, true, IconPath);
            return (sopt == 0);
        }, [&]()
        {
            this->installText->SetText(set::GetDictionaryEntry(146));
            mainapp->CallForRender();
            this->installBar->SetVisible(true);
        }, [&](ncm::ContentRecord Record, u32 Content, u32 ContentCount, double Done, double Total, u64 BytesSec)
        {
            this->installBar->SetMaxValue(Total);
            std::string name = set::GetDictionaryEntry(148) + " \'"  + horizon::GetStringFromNCAId(Record.NCAId);
            if(Record.Type == ncm::ContentType::Meta) name += ".cnmt";
            // name += ".nca\'... (NCA " + std::to_string(Content + 1) + " " + set::GetDictionaryEntry(149) + " " + std::to_string(ContentCount) + ")";
            name += ".nca\'... (" + fs::FormatSize(BytesSec) + "/s)";
            this->installText->SetText(name);
            this->installBar->SetProgress(Done);
            mainapp->CallForRender();
        });
        if(IsInstalledTitle()) appletEndBlockingHomeButton();
        this->installBar->SetVisible(false);
        mainapp->CallForRender();
        if(rc != 0) HandleResult(rc, set::GetDictionaryEntry(251));
        else mainapp->ShowNotification(set::GetDictionaryEntry(150));
        mainapp->LoadLayout(Prev);
    }
}