#include <gleaf/ui.hpp>

extern gleaf::set::Settings gsets;

namespace gleaf::ui
{
    extern MainApplication *mainapp;

    SystemInfoLayout::SystemInfoLayout() : pu::Layout()
    {
        horizon::FwVersion fwv = horizon::GetFwVersion();
        this->fwText = new pu::element::TextBlock(30, 630, "Firmware: " + fwv.ToString() + " (" + fwv.DisplayName + ")");
        this->fwText->SetColor(gsets.CustomScheme.Text);
        this->sdText = new pu::element::TextBlock(280, 300, set::GetDictionaryEntry(19), 35);
        this->sdText->SetColor(gsets.CustomScheme.Text);
        this->sdBar = new pu::element::ProgressBar(220, 345, 300, 30);
        this->sdFreeText = new pu::element::TextBlock(225, 385, "0 bytes " + set::GetDictionaryEntry(221));
        this->sdFreeText->SetColor(gsets.CustomScheme.Text);
        this->nandText = new pu::element::TextBlock(600, 300, set::GetDictionaryEntry(79), 35);
        this->nandText->SetColor(gsets.CustomScheme.Text);
        this->nandBar = new pu::element::ProgressBar(660, 345, 300, 30);
        this->nandFreeText = new pu::element::TextBlock(655, 385, "0 bytes " + set::GetDictionaryEntry(221));
        this->nandFreeText->SetColor(gsets.CustomScheme.Text);
        this->safeText = new pu::element::TextBlock(105, 480, set::GetDictionaryEntry(27));
        this->safeText->SetColor(gsets.CustomScheme.Text);
        this->safeBar = new pu::element::ProgressBar(100, 515, 300, 30);
        this->userText = new pu::element::TextBlock(455, 480, set::GetDictionaryEntry(28));
        this->userText->SetColor(gsets.CustomScheme.Text);
        this->userBar = new pu::element::ProgressBar(450, 515, 300, 30);
        this->systemText = new pu::element::TextBlock(805, 480, set::GetDictionaryEntry(29));
        this->systemText->SetColor(gsets.CustomScheme.Text);
        this->systemBar = new pu::element::ProgressBar(800, 515, 300, 30);
        this->AddChild(this->fwText);
        this->AddChild(this->sdText);
        this->AddChild(this->sdBar);
        this->AddChild(this->sdFreeText);
        this->AddChild(this->nandText);
        this->AddChild(this->nandBar);
        this->AddChild(this->nandFreeText);
        this->AddChild(this->safeText);
        this->AddChild(this->safeBar);
        this->AddChild(this->userText);
        this->AddChild(this->userBar);
        this->AddChild(this->systemText);
        this->AddChild(this->systemBar);
    }

    void SystemInfoLayout::UpdateElements()
    {
        u64 sdctotal = fs::GetTotalSpaceForPartition(fs::Partition::SdCard);
        u64 sdcfree = fs::GetFreeSpaceForPartition(fs::Partition::SdCard);
        u64 nsftotal = fs::GetTotalSpaceForPartition(fs::Partition::NANDSafe);
        u64 nsffree = fs::GetFreeSpaceForPartition(fs::Partition::NANDSafe);
        u64 nsutotal = fs::GetTotalSpaceForPartition(fs::Partition::NANDUser);
        u64 nsufree = fs::GetFreeSpaceForPartition(fs::Partition::NANDUser);
        u64 nsstotal = fs::GetTotalSpaceForPartition(fs::Partition::NANDSystem);
        u64 nssfree = fs::GetFreeSpaceForPartition(fs::Partition::NANDSystem);
        u8 sdval = ((100 * (sdctotal - sdcfree)) / sdctotal);
        u8 nsfval = ((100 * (nsftotal - nsffree)) / nsftotal);
        u8 nsuval = ((100 * (nsutotal - nsufree)) / nsutotal);
        u8 nssval = ((100 * (nsstotal - nssfree)) / nsstotal);
        this->sdBar->SetProgress(sdval);
        this->safeBar->SetProgress(nsfval);
        this->userBar->SetProgress(nsuval);
        this->systemBar->SetProgress(nssval);
        u64 nandtotal = (nsftotal + nsutotal + nsstotal);
        u64 nandfree = (nsffree + nsufree + nssfree);
        u8 nandval = ((100 * (nandtotal - nandfree)) / nandtotal);
        this->nandBar->SetProgress(nandval);
        this->nandFreeText->SetText(fs::FormatSize(nandfree) + " " + set::GetDictionaryEntry(221));
        this->sdFreeText->SetText(fs::FormatSize(sdcfree) + " " + set::GetDictionaryEntry(221));
    }
}