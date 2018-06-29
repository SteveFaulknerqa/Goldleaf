#include <switch.h>

#include <iostream>
#include "console_panel.hpp"
#include "menu.hpp"
#include "panel_changer.hpp"

Result servicesInit()
{
    Result rc = 0;
    return rc;
}

void servicesExit(void)
{

}

int main(int argc, char **argv)
{
    Result rc;
    gfxInitDefault();
    PrintConsole *console = consoleInit(NULL);

    if (R_FAILED(rc = servicesInit()))
        return rc;

    menu::Menu menu(console);

    auto mainPanel = std::make_shared<menu::ConsolePanel>(console, "Tinfoil 0.0.1");
    auto tinfoSection = mainPanel->addSection("Title Info");
    tinfoSection->addEntry("Display Install Info", std::bind(menu::install_info::displaySelectInstallLocation, std::placeholders::_1));
    menu.pushPanel(mainPanel);

    std::cout << "Press B to exit..." << std::endl;

    // Check if exit requested in menu, use public bool
    while (appletMainLoop() && !menu.m_exitRequested)
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
    
        if (kDown != 0)
            menu.processInput(kDown);

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

    servicesExit();
    gfxExit();
    return 0;
}