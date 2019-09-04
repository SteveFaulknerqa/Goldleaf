#include <ui/ui_TitleDumperLayout.hpp>
#include <ui/ui_MainApplication.hpp>

extern set::Settings gsets;

namespace ui
{
    extern MainApplication::Ref mainapp;

    TitleDumperLayout::TitleDumperLayout()
    {
        this->dumpText = pu::ui::elm::TextBlock::New(150, 320, set::GetDictionaryEntry(151));
        this->dumpText->SetHorizontalAlign(pu::ui::elm::HorizontalAlign::Center);
        this->dumpText->SetColor(gsets.CustomScheme.Text);
        this->ncaBar = pu::ui::elm::ProgressBar::New(340, 360, 600, 30, 100.0f);
        this->ncaBar->SetVisible(false);
        gsets.ApplyProgressBarColor(this->ncaBar);
        this->Add(this->dumpText);
        this->Add(this->ncaBar);
    }

    void TitleDumperLayout::StartDump(hos::Title &Target)
    {
        EnsureDirectories();
        mainapp->CallForRender();
        FsStorageId stid = static_cast<FsStorageId>(Target.Location);
        pu::String fappid = hos::FormatApplicationId(Target.ApplicationId);
        pu::String outdir = "sdmc:/" + GoldleafDir + "/dump/" + fappid;
        fs::CreateDirectory(outdir);
        this->dumpText->SetText(set::GetDictionaryEntry(192));
        mainapp->CallForRender();
        pu::String tkey = dump::GetTitleKeyData(Target.ApplicationId, true);
        this->dumpText->SetText(set::GetDictionaryEntry(193));
        mainapp->CallForRender();
        NcmContentStorage cst;
        Result rc = ncmOpenContentStorage(stid, &cst);
        if(rc != 0)
        {
            HandleResult(MAKERESULT(222, 2221), set::GetDictionaryEntry(198));
            //HandleResult(err::Make(err::ErrorDescription::CouldNotLocateTitleContents), set::GetDictionaryEntry(198));
            mainapp->LoadLayout(mainapp->GetContentManagerLayout());
            return;
        }
        NcmContentMetaDatabase cmdb;
        rc = ncmOpenContentMetaDatabase(stid, &cmdb);
        if(rc != 0)
        {
            HandleResult(MAKERESULT(222, 2222), set::GetDictionaryEntry(198));
            //HandleResult(err::Make(err::ErrorDescription::CouldNotLocateTitleContents), set::GetDictionaryEntry(198));
            mainapp->LoadLayout(mainapp->GetContentManagerLayout());
            serviceClose(&cst.s);
            return;
        }
        NcmMetaRecord mrec = Target.Record;
        /*
        bool ok = dump::GetMetaRecord(&cmdb, Target.ApplicationId, &mrec);
        if(!ok)
        {
            HandleResult(MAKERESULT(222, 2223), set::GetDictionaryEntry(198));
            //HandleResult(err::Make(err::ErrorDescription::CouldNotLocateTitleContents), set::GetDictionaryEntry(198));
            mainapp->LoadLayout(mainapp->GetContentManagerLayout());
            serviceClose(&cst.s);
            serviceClose(&cmdb.s);
            return;
        }
        */
        NcmNcaId meta;
        bool ok = dump::GetNCAId(&cmdb, &mrec, Target.ApplicationId, dump::NCAType::Meta, &meta);
        if(!ok)
        {
            HandleResult(MAKERESULT(222, 2224), set::GetDictionaryEntry(198));
            //HandleResult(err::Make(err::ErrorDescription::CouldNotLocateTitleContents), set::GetDictionaryEntry(198));
            mainapp->LoadLayout(mainapp->GetContentManagerLayout());
            serviceClose(&cst.s);
            serviceClose(&cmdb.s);
            return;
        }
        pu::String smeta = dump::GetNCAIdPath(&cst, &meta);
        NcmNcaId program;
        ok = dump::GetNCAId(&cmdb, &mrec, Target.ApplicationId, dump::NCAType::Program, &program);
        bool hasprogram = ok;
        pu::String sprogram;
        if(ok) sprogram = dump::GetNCAIdPath(&cst, &program);
        NcmNcaId control;
        ok = dump::GetNCAId(&cmdb, &mrec, Target.ApplicationId, dump::NCAType::Control, &control);
        bool hascontrol = ok;
        pu::String scontrol;
        if(ok) scontrol = dump::GetNCAIdPath(&cst, &control);
        NcmNcaId linfo;
        ok = dump::GetNCAId(&cmdb, &mrec, Target.ApplicationId, dump::NCAType::LegalInfo, &linfo);
        bool haslinfo = ok;
        pu::String slinfo;
        if(ok) slinfo = dump::GetNCAIdPath(&cst, &linfo);
        NcmNcaId hoff;
        ok = dump::GetNCAId(&cmdb, &mrec, Target.ApplicationId, dump::NCAType::OfflineHtml, &hoff);
        bool hashoff = ok;
        pu::String shoff;
        if(ok) shoff = dump::GetNCAIdPath(&cst, &hoff);

        NcmNcaId data;
        ok = dump::GetNCAId(&cmdb, &mrec, Target.ApplicationId, dump::NCAType::Data, &data);
        bool hasdata = ok;
        pu::String sdata;
        if(ok) sdata = dump::GetNCAIdPath(&cst, &data);

        hos::LockAutoSleep();

        pu::String xprogram = sprogram;
        pu::String xmeta = smeta;
        pu::String xcontrol = scontrol;
        pu::String xlinfo = slinfo;
        pu::String xhoff = shoff;
        pu::String xdata = sdata;
        if(stid == FsStorageId_SdCard)
        {
            this->dumpText->SetText(set::GetDictionaryEntry(194));
            xmeta = outdir + "/" + hos::ContentIdAsString(meta) + ".cnmt.nca";
            fs::CreateConcatenationFile(xmeta);
            this->ncaBar->SetVisible(true);
            dump::DecryptCopyNAX0ToNCA(&cst, meta, xmeta, [&](double Done, double Total)
            {
                this->ncaBar->SetMaxValue(Total);
                this->ncaBar->SetProgress(Done);
                mainapp->CallForRender();
            });
            this->ncaBar->SetVisible(false);
            if(hasprogram)
            {
                xprogram = outdir + "/" + hos::ContentIdAsString(program) + ".nca";
                fs::CreateConcatenationFile(xprogram);
                this->ncaBar->SetVisible(true);
                dump::DecryptCopyNAX0ToNCA(&cst, program, xprogram, [&](double Done, double Total)
                {
                    this->ncaBar->SetMaxValue(Total);
                    this->ncaBar->SetProgress(Done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
            }
            if(hascontrol)
            {
                xcontrol = outdir + "/" + hos::ContentIdAsString(control) + ".nca";
                fs::CreateConcatenationFile(xcontrol);
                this->ncaBar->SetVisible(true);
                dump::DecryptCopyNAX0ToNCA(&cst, control, xcontrol, [&](double Done, double Total)
                {
                    this->ncaBar->SetMaxValue(Total);
                    this->ncaBar->SetProgress(Done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
            }
            if(haslinfo)
            {
                xlinfo = outdir + "/" + hos::ContentIdAsString(linfo) + ".nca";
                fs::CreateConcatenationFile(xlinfo);
                this->ncaBar->SetVisible(true);
                dump::DecryptCopyNAX0ToNCA(&cst, linfo, xlinfo, [&](double Done, double Total)
                {
                    this->ncaBar->SetMaxValue(Total);
                    this->ncaBar->SetProgress(Done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
            }
            if(hashoff)
            {
                xhoff = outdir + "/" + hos::ContentIdAsString(hoff) + ".nca";
                fs::CreateConcatenationFile(xhoff);
                this->ncaBar->SetVisible(true);
                dump::DecryptCopyNAX0ToNCA(&cst, hoff, xhoff, [&](double Done, double Total)
                {
                    this->ncaBar->SetMaxValue(Total);
                    this->ncaBar->SetProgress(Done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
            }
            if(hasdata)
            {
                xdata = outdir + "/" + hos::ContentIdAsString(data) + ".nca";
                fs::CreateConcatenationFile(xdata);
                this->ncaBar->SetVisible(true);
                dump::DecryptCopyNAX0ToNCA(&cst, data, xdata, [&](double Done, double Total)
                {
                    this->ncaBar->SetMaxValue(Total);
                    this->ncaBar->SetProgress(Done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
            }
        }
        else
        {
            fs::Explorer *nexp = NULL;
            if(stid == FsStorageId_NandSystem) nexp = fs::GetNANDSystemExplorer();
            else if(stid == FsStorageId_NandUser) nexp = fs::GetNANDUserExplorer();
            else
            {
                HandleResult(err::Make(err::ErrorDescription::CouldNotLocateTitleContents), set::GetDictionaryEntry(198));
                mainapp->LoadLayout(mainapp->GetContentManagerLayout());
                serviceClose(&cst.s);
                serviceClose(&cmdb.s);
                hos::UnlockAutoSleep();
                return;
            }
            this->dumpText->SetText(set::GetDictionaryEntry(195));
            xmeta = nexp->FullPathFor("Contents/" + xmeta.substr(15));
            pu::String txmeta = outdir + "/" + hos::ContentIdAsString(meta) + ".cnmt.nca";
            fs::CreateConcatenationFile(txmeta);
            this->ncaBar->SetVisible(true);
            fs::CopyFileProgress(xmeta, txmeta, [&](double done, double total)
            {
                this->ncaBar->SetMaxValue(total);
                this->ncaBar->SetProgress(done);
                mainapp->CallForRender();
            });
            this->ncaBar->SetVisible(false);
            xmeta = txmeta;
            if(hasprogram)
            {
                xprogram = nexp->FullPathFor("Contents/" + xprogram.substr(15));
                pu::String txprogram = outdir + "/" + hos::ContentIdAsString(program) + ".nca";
                fs::CreateConcatenationFile(txprogram);
                this->ncaBar->SetVisible(true);
                fs::CopyFileProgress(xprogram, txprogram, [&](double done, double total)
                {
                    this->ncaBar->SetMaxValue(total);
                    this->ncaBar->SetProgress(done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
                xprogram = txprogram;
            }
            if(hascontrol)
            {
                xcontrol = nexp->FullPathFor("Contents/" + xcontrol.substr(15));
                pu::String txcontrol = outdir + "/" + hos::ContentIdAsString(control) + ".nca";
                fs::CreateConcatenationFile(txcontrol);
                this->ncaBar->SetVisible(true);
                fs::CopyFileProgress(xcontrol, txcontrol, [&](double done, double total)
                {
                    this->ncaBar->SetMaxValue(total);
                    this->ncaBar->SetProgress(done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
                xcontrol = txcontrol;
            }
            if(haslinfo)
            {
                xlinfo = nexp->FullPathFor("Contents/" + xlinfo.substr(15));
                pu::String txlinfo = outdir + "/" + hos::ContentIdAsString(linfo) + ".nca";
                fs::CreateConcatenationFile(txlinfo);
                this->ncaBar->SetVisible(true);
                fs::CopyFileProgress(xlinfo, txlinfo, [&](double done, double total)
                {
                    this->ncaBar->SetMaxValue(total);
                    this->ncaBar->SetProgress(done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
                xlinfo = txlinfo;
            }
            if(hashoff)
            {
                xhoff = nexp->FullPathFor("Contents/" + xhoff.substr(15));
                pu::String txhoff = outdir + "/" + hos::ContentIdAsString(hoff) + ".nca";
                fs::CreateConcatenationFile(txhoff);
                this->ncaBar->SetVisible(true);
                fs::CopyFileProgress(xhoff, txhoff, [&](double done, double total)
                {
                    this->ncaBar->SetMaxValue(total);
                    this->ncaBar->SetProgress(done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
                xhoff = txhoff;
            }
            if(hasdata)
            {
                xdata = nexp->FullPathFor("Contents/" + xdata.substr(15));
                pu::String txdata = outdir + "/" + hos::ContentIdAsString(data) + ".nca";
                fs::CreateConcatenationFile(txdata);
                this->ncaBar->SetVisible(true);
                fs::CopyFileProgress(xdata, txdata, [&](double done, double total)
                {
                    this->ncaBar->SetMaxValue(total);
                    this->ncaBar->SetProgress(done);
                    mainapp->CallForRender();
                });
                this->ncaBar->SetVisible(false);
                xdata = txdata;
            }
        }
        pu::String fout = "sdmc:/" + GoldleafDir + "/dump/" + fappid + ".nsp";
        fs::CreateConcatenationFile(fout);
        this->ncaBar->SetVisible(true);
        this->dumpText->SetText(set::GetDictionaryEntry(196));
        int qi = nsp::Build(outdir, fout, [&](u64 done, u64 total)
        {
            this->ncaBar->SetMaxValue((double)total);
            this->ncaBar->SetProgress((double)done);
            mainapp->CallForRender();
        });
        hos::UnlockAutoSleep();
        ok = (qi == 0);
        fs::DeleteDirectory("sdmc:/" + GoldleafDir + "/dump/temp");
        fs::DeleteDirectory(outdir);
        if(ok) mainapp->ShowNotification(set::GetDictionaryEntry(197) + " '" + fout + "'");
        else
        {
            HandleResult(err::Make(err::ErrorDescription::CouldNotBuildNSP), set::GetDictionaryEntry(198));
            fs::DeleteDirectory("sdmc:/" + GoldleafDir + "/dump");
            EnsureDirectories();
        }
        serviceClose(&cst.s);
        serviceClose(&cmdb.s);
    }
}