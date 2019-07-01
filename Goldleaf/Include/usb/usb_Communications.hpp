
/*

    Goldleaf - Multipurpose homebrew tool for Nintendo Switch

    Copyright 2018 - 2019 Goldleaf project, developed by XorTroll, emerged from Adubbz's work with Tinfoil

    This project is licensed under the terms of GPLv3 license: https://github.com/XorTroll/Goldleaf/blob/master/LICENSE

*/

#pragma once
#include <usb/usb_Commands.hpp>

namespace usb
{
    inline bool CallbackStub()
    {
        return false;
    }
    
    size_t ReadSimple(void *Out, size_t Size, UsbCallbackFn Callback = CallbackStub);
    size_t WriteSimple(const void *Buffer, size_t Size);
    size_t Read(void *Out, size_t Size, UsbCallbackFn Callback = CallbackStub);
    size_t Write(const void *Buffer, size_t Size);
    u8 Read8(UsbCallbackFn Callback = CallbackStub);
    u32 Read32(UsbCallbackFn Callback = CallbackStub);
    u64 Read64(UsbCallbackFn Callback = CallbackStub);
    std::string ReadString(UsbCallbackFn Callback = CallbackStub);
    bool WriteCommand(CommandId Id);
    bool Write8(u8 Data);
    bool Write32(u32 Data);
    bool Write64(u64 Data);
    bool WriteString(std::string Str);
    u32 GetState();
    bool IsStatePlugged();
    bool IsStateNotReady();
}