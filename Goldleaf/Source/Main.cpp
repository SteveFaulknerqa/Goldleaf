#include <gleaf/Goldleaf>
extern u32 __nx_applet_type;

extern "C"
{
    void __nx_win_init(void);
    void __libnx_init_time(void);

    void __appInit(void)
    {
        Result rc = smInitialize();
        if(R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

        rc = setsysInitialize();
        if(R_SUCCEEDED(rc))
        {
            SetSysFirmwareVersion fw;
            rc = setsysGetFirmwareVersion(&fw);
            if(R_SUCCEEDED(rc)) hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
            setsysExit();
        }

        rc = timeInitialize();
        if(R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_Time));

        __libnx_init_time();

        rc = fsInitialize();
        if(R_FAILED(rc)) fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

        fsdevMountSdmc();
    }
}

int main(int argc, char *argv[])
{
    gleaf::StartMode stmode = gleaf::StartMode::Normal;
    if(envHasArgv() && (argc > 1))
    {
        for(int i = 0; i < argc; i++)
        {
            const char *cargv = argv[i];
            if(strcasecmp(cargv, "hbmenu") == 0)
            {
                stmode = gleaf::StartMode::HomebrewMenu;
                break;
            }
            else if((strcasecmp(cargv, "qlaunch") == 0) || (strcasecmp(cargv, "home") == 0))
            {
                stmode = gleaf::StartMode::Qlaunch;
                __nx_applet_type = AppletType_SystemApplet;
                break;
            }
        }
    }
    gleaf::Initialize();
    atexit(gleaf::Finalize);
    gleaf::ui::MainApplication *mainapp = new gleaf::ui::MainApplication(stmode);
    gleaf::ui::SetMainApplication(mainapp);
    mainapp->Show();
    delete mainapp;
    return 0;
}