#include <gleaf/ui.hpp>

extern gleaf::set::Settings gsets;

namespace gleaf::ui
{
    extern MainApplication *mainapp;

    MainMenuLayout::MainMenuLayout() : pu::Layout()
    {
        this->optionMenu = new pu::element::Menu(0, 160, 1280, gsets.CustomScheme.Base, gsets.MenuItemSize, (560 / gsets.MenuItemSize));
        this->optionMenu->SetOnFocusColor(gsets.CustomScheme.BaseFocus);
        this->exploreMenuItem = new pu::element::MenuItem("Explore content");
        this->exploreMenuItem->SetIcon(gsets.PathForResource("/Common/SdCard.png"));
        this->exploreMenuItem->SetColor(gsets.CustomScheme.Text);
        this->exploreMenuItem->AddOnClick(std::bind(&MainMenuLayout::exploreMenuItem_Click, this));
        this->titleMenuItem = new pu::element::MenuItem(set::GetDictionaryEntry(3));
        this->titleMenuItem->SetIcon(gsets.PathForResource("/Common/Storage.png"));
        this->titleMenuItem->SetColor(gsets.CustomScheme.Text);
        this->titleMenuItem->AddOnClick(std::bind(&MainMenuLayout::titleMenuItem_Click, this));
        this->ticketMenuItem = new pu::element::MenuItem(set::GetDictionaryEntry(4));
        this->ticketMenuItem->SetIcon(gsets.PathForResource("/Common/Ticket.png"));
        this->ticketMenuItem->SetColor(gsets.CustomScheme.Text);
        this->ticketMenuItem->AddOnClick(std::bind(&MainMenuLayout::ticketMenuItem_Click, this));
        this->webMenuItem = new pu::element::MenuItem(set::GetDictionaryEntry(5));
        this->webMenuItem->SetIcon(gsets.PathForResource("/Common/Browser.png"));
        this->webMenuItem->SetColor(gsets.CustomScheme.Text);
        this->webMenuItem->AddOnClick(std::bind(&MainMenuLayout::webMenuItem_Click, this));
        this->accountMenuItem = new pu::element::MenuItem(set::GetDictionaryEntry(6));
        this->accountMenuItem->SetIcon(gsets.PathForResource("/Common/Accounts.png"));
        this->accountMenuItem->SetColor(gsets.CustomScheme.Text);
        this->accountMenuItem->AddOnClick(std::bind(&MainMenuLayout::accountMenuItem_Click, this));
        this->sysinfoMenuItem = new pu::element::MenuItem(set::GetDictionaryEntry(7));
        this->sysinfoMenuItem->SetIcon(gsets.PathForResource("/Common/Settings.png"));
        this->sysinfoMenuItem->SetColor(gsets.CustomScheme.Text);
        this->sysinfoMenuItem->AddOnClick(std::bind(&MainMenuLayout::sysinfoMenuItem_Click, this));
        this->updateMenuItem = new pu::element::MenuItem("Update");
        this->updateMenuItem->SetIcon(gsets.PathForResource("/Common/Update.png"));
        this->updateMenuItem->SetColor(gsets.CustomScheme.Text);
        this->updateMenuItem->AddOnClick(std::bind(&MainMenuLayout::updateMenuItem_Click, this));
        this->aboutMenuItem = new pu::element::MenuItem(set::GetDictionaryEntry(8));
        this->aboutMenuItem->SetIcon(gsets.PathForResource("/Common/Info.png"));
        this->aboutMenuItem->SetColor(gsets.CustomScheme.Text);
        this->aboutMenuItem->AddOnClick(std::bind(&MainMenuLayout::aboutMenuItem_Click, this));
        this->optionMenu->AddItem(this->exploreMenuItem);
        this->optionMenu->AddItem(this->titleMenuItem);
        this->optionMenu->AddItem(this->ticketMenuItem);
        this->optionMenu->AddItem(this->webMenuItem);
        this->optionMenu->AddItem(this->accountMenuItem);
        this->optionMenu->AddItem(this->sysinfoMenuItem);
        this->optionMenu->AddItem(this->updateMenuItem);
        this->optionMenu->AddItem(this->aboutMenuItem);
        this->Add(this->optionMenu);
    }

    MainMenuLayout::~MainMenuLayout()
    {
        delete this->optionMenu;
    }

    void MainMenuLayout::exploreMenuItem_Click()
    {
        mainapp->LoadMenuData("Mounted content", "Storage", "Explore mounted contents");
        mainapp->LoadLayout(mainapp->GetExploreMenuLayout());
    }

    void MainMenuLayout::titleMenuItem_Click()
    {
        mainapp->LoadMenuData(set::GetDictionaryEntry(32), "Storage", set::GetDictionaryEntry(33));
        EnsureDirectories();
        mainapp->LoadLayout(mainapp->GetContentManagerLayout());
    }

    void MainMenuLayout::ticketMenuItem_Click()
    {
        mainapp->LoadMenuData(set::GetDictionaryEntry(34), "Ticket", set::GetDictionaryEntry(35));
        mainapp->GetTicketManagerLayout()->UpdateElements();
        mainapp->LoadLayout(mainapp->GetTicketManagerLayout());
    }

    void MainMenuLayout::webMenuItem_Click()
    {
        if(!IsInstalledTitle()) mainapp->CreateShowDialog(set::GetDictionaryEntry(36), set::GetDictionaryEntry(37), { set::GetDictionaryEntry(234) }, false);
        std::string out = AskForText(set::GetDictionaryEntry(38), "https://");
        if(out == "") return;
        else
        {
            bool nothttp = (out.substr(0, 6) != "http:/");
            bool nothttps = (out.substr(0, 7) != "https:/");
            if(nothttp && nothttps)
            {
                mainapp->CreateShowDialog(set::GetDictionaryEntry(36), set::GetDictionaryEntry(39), { set::GetDictionaryEntry(234) }, false);
                return;
            }
        }
        if(IsInstalledTitle())
        {
            WebCommonConfig web;
            webPageCreate(&web, out.c_str());
            WebCommonReply wout;
            webConfigShow(&web, &wout);  
        }
        else
        {
            WebWifiConfig wwf;
            webWifiCreate(&wwf, NULL, out.c_str(), 0, 0);
            WebWifiReturnValue vret;
            Result rc = webWifiShow(&wwf, &vret);
            if(rc != 0) HandleResult(rc, set::GetDictionaryEntry(40));
        }
    }

    void MainMenuLayout::accountMenuItem_Click()
    {
        u128 uid = AskForUser();
        if(uid == 0) return;
        mainapp->LoadMenuData(set::GetDictionaryEntry(41), "Accounts", set::GetDictionaryEntry(42));
        mainapp->GetAccountLayout()->Load(uid);
        mainapp->LoadLayout(mainapp->GetAccountLayout());
    }

    void MainMenuLayout::sysinfoMenuItem_Click()
    {
        mainapp->LoadMenuData(set::GetDictionaryEntry(43), "Settings", set::GetDictionaryEntry(44));
        mainapp->GetSystemInfoLayout()->UpdateElements();
        mainapp->LoadLayout(mainapp->GetSystemInfoLayout());
    }

    void MainMenuLayout::updateMenuItem_Click()
    {
        mainapp->LoadMenuData("Update", "Update", "Update Goldleaf");
        mainapp->LoadLayout(mainapp->GetUpdateLayout());
        mainapp->GetUpdateLayout()->StartUpdateSearch();
    }

    void MainMenuLayout::aboutMenuItem_Click()
    {
        std::string rmode = set::GetDictionaryEntry(45);
        if(IsNRO()) rmode = set::GetDictionaryEntry(46);
        else if(IsInstalledTitle()) rmode = set::GetDictionaryEntry(47);
        else if(IsQlaunch()) rmode = set::GetDictionaryEntry(78);
        mainapp->LoadMenuData("Goldleaf v" + GetVersion(), "Info", rmode);
        mainapp->LoadLayout(mainapp->GetAboutLayout());
    }
}