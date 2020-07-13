
/*

    Goldleaf - Multipurpose homebrew tool for Nintendo Switch
    Copyright (C) 2018-2020  XorTroll

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#pragma once
#include <switch.h>

namespace es
{
    union RightsId
    {
        struct {
            u64 app_id;
            u64 key_gen;
        };
        u8 id[0x10];
    };
    static_assert(sizeof(RightsId) == 0x10);

    constexpr u8 CommonCertificateData[] =
    {
        0x00, 0x01, 0x00, 0x03, 0x70, 0x41, 0x38, 0xef, 0xbb, 0xbd, 0xa1, 0x6a, 0x98, 0x7d, 0xd9, 0x01,
        0x32, 0x6d, 0x1c, 0x94, 0x59, 0x48, 0x4c, 0x88, 0xa2, 0x86, 0x1b, 0x91, 0xa3, 0x12, 0x58, 0x7a,
        0xe7, 0x0e, 0xf6, 0x23, 0x7e, 0xc5, 0x0e, 0x10, 0x32, 0xdc, 0x39, 0xdd, 0xe8, 0x9a, 0x96, 0xa8,
        0xe8, 0x59, 0xd7, 0x6a, 0x98, 0xa6, 0xe7, 0xe3, 0x6a, 0x0c, 0xfe, 0x35, 0x2c, 0xa8, 0x93, 0x05,
        0x82, 0x34, 0xff, 0x83, 0x3f, 0xcb, 0x3b, 0x03, 0x81, 0x1e, 0x9f, 0x0d, 0xc0, 0xd9, 0xa5, 0x2f,
        0x80, 0x45, 0xb4, 0xb2, 0xf9, 0x41, 0x1b, 0x67, 0xa5, 0x1c, 0x44, 0xb5, 0xef, 0x8c, 0xe7, 0x7b,
        0xd6, 0xd5, 0x6b, 0xa7, 0x57, 0x34, 0xa1, 0x85, 0x6d, 0xe6, 0xd4, 0xbe, 0xd6, 0xd3, 0xa2, 0x42,
        0xc7, 0xc8, 0x79, 0x1b, 0x34, 0x22, 0x37, 0x5e, 0x5c, 0x77, 0x9a, 0xbf, 0x07, 0x2f, 0x76, 0x95,
        0xef, 0xa0, 0xf7, 0x5b, 0xcb, 0x83, 0x78, 0x9f, 0xc3, 0x0e, 0x3f, 0xe4, 0xcc, 0x83, 0x92, 0x20,
        0x78, 0x40, 0x63, 0x89, 0x49, 0xc7, 0xf6, 0x88, 0x56, 0x5f, 0x64, 0x9b, 0x74, 0xd6, 0x3d, 0x8d,
        0x58, 0xff, 0xad, 0xda, 0x57, 0x1e, 0x95, 0x54, 0x42, 0x6b, 0x13, 0x18, 0xfc, 0x46, 0x89, 0x83,
        0xd4, 0xc8, 0xa5, 0x62, 0x8b, 0x06, 0xb6, 0xfc, 0x5d, 0x50, 0x7c, 0x13, 0xe7, 0xa1, 0x8a, 0xc1,
        0x51, 0x1e, 0xb6, 0xd6, 0x2e, 0xa5, 0x44, 0x8f, 0x83, 0x50, 0x14, 0x47, 0xa9, 0xaf, 0xb3, 0xec,
        0xc2, 0x90, 0x3c, 0x9d, 0xd5, 0x2f, 0x92, 0x2a, 0xc9, 0xac, 0xdb, 0xef, 0x58, 0xc6, 0x02, 0x18,
        0x48, 0xd9, 0x6e, 0x20, 0x87, 0x32, 0xd3, 0xd1, 0xd9, 0xd9, 0xea, 0x44, 0x0d, 0x91, 0x62, 0x1c,
        0x7a, 0x99, 0xdb, 0x88, 0x43, 0xc5, 0x9c, 0x1f, 0x2e, 0x2c, 0x7d, 0x9b, 0x57, 0x7d, 0x51, 0x2c,
        0x16, 0x6d, 0x6f, 0x7e, 0x1a, 0xad, 0x4a, 0x77, 0x4a, 0x37, 0x44, 0x7e, 0x78, 0xfe, 0x20, 0x21,
        0xe1, 0x4a, 0x95, 0xd1, 0x12, 0xa0, 0x68, 0xad, 0xa0, 0x19, 0xf4, 0x63, 0xc7, 0xa5, 0x56, 0x85,
        0xaa, 0xbb, 0x68, 0x88, 0xb9, 0x24, 0x64, 0x83, 0xd1, 0x8b, 0x9c, 0x80, 0x6f, 0x47, 0x49, 0x18,
        0x33, 0x17, 0x82, 0x34, 0x4a, 0x4b, 0x85, 0x31, 0x33, 0x4b, 0x26, 0x30, 0x32, 0x63, 0xd9, 0xd2,
        0xeb, 0x4f, 0x4b, 0xb9, 0x96, 0x02, 0xb3, 0x52, 0xf6, 0xae, 0x40, 0x46, 0xc6, 0x9a, 0x5e, 0x7e,
        0x8e, 0x4a, 0x18, 0xef, 0x9b, 0xc0, 0xa2, 0xde, 0xd6, 0x13, 0x10, 0x41, 0x70, 0x12, 0xfd, 0x82,
        0x4c, 0xc1, 0x16, 0xcf, 0xb7, 0xc4, 0xc1, 0xf7, 0xec, 0x71, 0x77, 0xa1, 0x74, 0x46, 0xcb, 0xde,
        0x96, 0xf3, 0xed, 0xd8, 0x8f, 0xcd, 0x05, 0x2f, 0x0b, 0x88, 0x8a, 0x45, 0xfd, 0xaf, 0x2b, 0x63,
        0x13, 0x54, 0xf4, 0x0d, 0x16, 0xe5, 0xfa, 0x9c, 0x2c, 0x4e, 0xda, 0x98, 0xe7, 0x98, 0xd1, 0x5e,
        0x60, 0x46, 0xdc, 0x53, 0x63, 0xf3, 0x09, 0x6b, 0x2c, 0x60, 0x7a, 0x9d, 0x8d, 0xd5, 0x5b, 0x15,
        0x02, 0xa6, 0xac, 0x7d, 0x3c, 0xc8, 0xd8, 0xc5, 0x75, 0x99, 0x8e, 0x7d, 0x79, 0x69, 0x10, 0xc8,
        0x04, 0xc4, 0x95, 0x23, 0x50, 0x57, 0xe9, 0x1e, 0xcd, 0x26, 0x37, 0xc9, 0xc1, 0x84, 0x51, 0x51,
        0xac, 0x6b, 0x9a, 0x04, 0x90, 0xae, 0x3e, 0xc6, 0xf4, 0x77, 0x40, 0xa0, 0xdb, 0x0b, 0xa3, 0x6d,
        0x07, 0x59, 0x56, 0xce, 0xe7, 0x35, 0x4e, 0xa3, 0xe9, 0xa4, 0xf2, 0x72, 0x0b, 0x26, 0x55, 0x0c,
        0x7d, 0x39, 0x43, 0x24, 0xbc, 0x0c, 0xb7, 0xe9, 0x31, 0x7d, 0x8a, 0x86, 0x61, 0xf4, 0x21, 0x91,
        0xff, 0x10, 0xb0, 0x82, 0x56, 0xce, 0x3f, 0xd2, 0x5b, 0x74, 0x5e, 0x51, 0x94, 0x90, 0x6b, 0x4d,
        0x61, 0xcb, 0x4c, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x52, 0x6f, 0x6f, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x43, 0x41, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x33, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x7b, 0xe8, 0xef, 0x6c, 0xb2, 0x79, 0xc9, 0xe2, 0xee, 0xe1, 0x21, 0xc6,
        0xea, 0xf4, 0x4f, 0xf6, 0x39, 0xf8, 0x8f, 0x07, 0x8b, 0x4b, 0x77, 0xed, 0x9f, 0x95, 0x60, 0xb0,
        0x35, 0x82, 0x81, 0xb5, 0x0e, 0x55, 0xab, 0x72, 0x11, 0x15, 0xa1, 0x77, 0x70, 0x3c, 0x7a, 0x30,
        0xfe, 0x3a, 0xe9, 0xef, 0x1c, 0x60, 0xbc, 0x1d, 0x97, 0x46, 0x76, 0xb2, 0x3a, 0x68, 0xcc, 0x04,
        0xb1, 0x98, 0x52, 0x5b, 0xc9, 0x68, 0xf1, 0x1d, 0xe2, 0xdb, 0x50, 0xe4, 0xd9, 0xe7, 0xf0, 0x71,
        0xe5, 0x62, 0xda, 0xe2, 0x09, 0x22, 0x33, 0xe9, 0xd3, 0x63, 0xf6, 0x1d, 0xd7, 0xc1, 0x9f, 0xf3,
        0xa4, 0xa9, 0x1e, 0x8f, 0x65, 0x53, 0xd4, 0x71, 0xdd, 0x7b, 0x84, 0xb9, 0xf1, 0xb8, 0xce, 0x73,
        0x35, 0xf0, 0xf5, 0x54, 0x05, 0x63, 0xa1, 0xea, 0xb8, 0x39, 0x63, 0xe0, 0x9b, 0xe9, 0x01, 0x01,
        0x1f, 0x99, 0x54, 0x63, 0x61, 0x28, 0x70, 0x20, 0xe9, 0xcc, 0x0d, 0xab, 0x48, 0x7f, 0x14, 0x0d,
        0x66, 0x26, 0xa1, 0x83, 0x6d, 0x27, 0x11, 0x1f, 0x20, 0x68, 0xde, 0x47, 0x72, 0x14, 0x91, 0x51,
        0xcf, 0x69, 0xc6, 0x1b, 0xa6, 0x0e, 0xf9, 0xd9, 0x49, 0xa0, 0xf7, 0x1f, 0x54, 0x99, 0xf2, 0xd3,
        0x9a, 0xd2, 0x8c, 0x70, 0x05, 0x34, 0x82, 0x93, 0xc4, 0x31, 0xff, 0xbd, 0x33, 0xf6, 0xbc, 0xa6,
        0x0d, 0xc7, 0x19, 0x5e, 0xa2, 0xbc, 0xc5, 0x6d, 0x20, 0x0b, 0xaf, 0x6d, 0x06, 0xd0, 0x9c, 0x41,
        0xdb, 0x8d, 0xe9, 0xc7, 0x20, 0x15, 0x4c, 0xa4, 0x83, 0x2b, 0x69, 0xc0, 0x8c, 0x69, 0xcd, 0x3b,
        0x07, 0x3a, 0x00, 0x63, 0x60, 0x2f, 0x46, 0x2d, 0x33, 0x80, 0x61, 0xa5, 0xea, 0x6c, 0x91, 0x5c,
        0xd5, 0x62, 0x35, 0x79, 0xc3, 0xeb, 0x64, 0xce, 0x44, 0xef, 0x58, 0x6d, 0x14, 0xba, 0xaa, 0x88,
        0x34, 0x01, 0x9b, 0x3e, 0xeb, 0xee, 0xd3, 0x79, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x00, 0x04, 0x96, 0x9f, 0xe8, 0x28, 0x8d, 0xa6, 0xb9, 0xdd, 0x52, 0xc7, 0xbd, 0x63,
        0x64, 0x2a, 0x4a, 0x9a, 0xe5, 0xf0, 0x53, 0xec, 0xcb, 0x93, 0x61, 0x3f, 0xda, 0x37, 0x99, 0x20,
        0x87, 0xbd, 0x91, 0x99, 0xda, 0x5e, 0x67, 0x97, 0x61, 0x8d, 0x77, 0x09, 0x81, 0x33, 0xfd, 0x5b,
        0x05, 0xcd, 0x82, 0x88, 0x13, 0x9e, 0x2e, 0x97, 0x5c, 0xd2, 0x60, 0x80, 0x03, 0x87, 0x8c, 0xda,
        0xf0, 0x20, 0xf5, 0x1a, 0x0e, 0x5b, 0x76, 0x92, 0x78, 0x08, 0x45, 0x56, 0x1b, 0x31, 0xc6, 0x18,
        0x08, 0xe8, 0xa4, 0x7c, 0x34, 0x62, 0x22, 0x4d, 0x94, 0xf7, 0x36, 0xe9, 0xa1, 0x4e, 0x56, 0xac,
        0xbf, 0x71, 0xb7, 0xf1, 0x1b, 0xbd, 0xee, 0x38, 0xdd, 0xb8, 0x46, 0xd6, 0xbd, 0x8f, 0x0a, 0xb4,
        0xe4, 0x94, 0x8c, 0x54, 0x34, 0xea, 0xf9, 0xbf, 0x26, 0x52, 0x9b, 0x7e, 0xb8, 0x36, 0x71, 0xd3,
        0xce, 0x60, 0xa6, 0xd7, 0xa8, 0x50, 0xdb, 0xe6, 0x80, 0x1e, 0xc5, 0x2a, 0x7b, 0x7a, 0x3e, 0x5a,
        0x27, 0xbc, 0x67, 0x5b, 0xa3, 0xc5, 0x33, 0x77, 0xcf, 0xc3, 0x72, 0xeb, 0xce, 0x02, 0x06, 0x2f,
        0x59, 0xf3, 0x70, 0x03, 0xaa, 0x23, 0xae, 0x35, 0xd4, 0x88, 0x0e, 0x0e, 0x4b, 0x69, 0xf9, 0x82,
        0xfb, 0x1b, 0xac, 0x80, 0x6c, 0x2f, 0x75, 0xba, 0x29, 0x58, 0x7f, 0x28, 0x15, 0xfd, 0x77, 0x83,
        0x99, 0x8c, 0x35, 0x4d, 0x52, 0xb1, 0x9e, 0x3f, 0xad, 0x9f, 0xbe, 0xf4, 0x44, 0xc4, 0x85, 0x79,
        0x28, 0x8d, 0xb0, 0x97, 0x81, 0x16, 0xaf, 0xc8, 0x2c, 0xe5, 0x4d, 0xac, 0xb9, 0xed, 0x7e, 0x1b,
        0xfd, 0x50, 0x93, 0x8f, 0x22, 0xf8, 0x5e, 0xec, 0xf3, 0xa4, 0xf4, 0x26, 0xae, 0x5f, 0xeb, 0x15,
        0xb7, 0x2f, 0x02, 0x2f, 0xb3, 0x6e, 0xcc, 0xe9, 0x31, 0x4d, 0xad, 0x13, 0x14, 0x29, 0xbf, 0xc9,
        0x67, 0x5f, 0x58, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x52, 0x6f, 0x6f, 0x74, 0x2d, 0x43, 0x41, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x33, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x58, 0x53, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x32, 0x30, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd2, 0x1d, 0x3c, 0xe6, 0x7c, 0x10, 0x69, 0xda,
        0x04, 0x9d, 0x5e, 0x53, 0x10, 0xe7, 0x6b, 0x90, 0x7e, 0x18, 0xee, 0xc8, 0x0b, 0x33, 0x7c, 0x47,
        0x23, 0xe3, 0x39, 0x57, 0x3f, 0x4c, 0x66, 0x49, 0x07, 0xdb, 0x2f, 0x08, 0x32, 0xd0, 0x3d, 0xf5,
        0xea, 0x5f, 0x16, 0x0a, 0x4a, 0xf2, 0x41, 0x00, 0xd7, 0x1a, 0xfa, 0xc2, 0xe3, 0xae, 0x75, 0xaf,
        0xa1, 0x22, 0x80, 0x12, 0xa9, 0xa2, 0x16, 0x16, 0x59, 0x7d, 0xf7, 0x1e, 0xaf, 0xcb, 0x65, 0x94,
        0x14, 0x70, 0xd1, 0xb4, 0x0f, 0x5e, 0xf8, 0x3a, 0x59, 0x7e, 0x17, 0x9f, 0xcb, 0x5b, 0x57, 0xc2,
        0xee, 0x17, 0xda, 0x3b, 0xc3, 0x76, 0x98, 0x64, 0xcb, 0x47, 0x85, 0x67, 0x67, 0x22, 0x9d, 0x67,
        0x32, 0x81, 0x41, 0xfc, 0x9a, 0xb1, 0xdf, 0x14, 0x9e, 0x0c, 0x5c, 0x15, 0xae, 0xb8, 0x0b, 0xc5,
        0x8f, 0xc7, 0x1b, 0xe1, 0x89, 0x66, 0x64, 0x2d, 0x68, 0x30, 0x8b, 0x50, 0x69, 0x34, 0xb8, 0xef,
        0x77, 0x9f, 0x78, 0xe4, 0xdd, 0xf3, 0x0a, 0x0d, 0xcf, 0x93, 0xfc, 0xaf, 0xbf, 0xa1, 0x31, 0xa8,
        0x83, 0x9f, 0xd6, 0x41, 0x94, 0x9f, 0x47, 0xee, 0x25, 0xce, 0xec, 0xf8, 0x14, 0xd5, 0x5b, 0x0b,
        0xe6, 0xe5, 0x67, 0x7c, 0x1e, 0xff, 0xec, 0x6f, 0x29, 0x87, 0x1e, 0xf2, 0x9a, 0xa3, 0xed, 0x91,
        0x97, 0xb0, 0xd8, 0x38, 0x52, 0xe0, 0x50, 0x90, 0x80, 0x31, 0xef, 0x1a, 0xbb, 0xb5, 0xaf, 0xc8,
        0xb3, 0xdd, 0x93, 0x7a, 0x07, 0x6f, 0xf6, 0x76, 0x1a, 0xb3, 0x62, 0x40, 0x5c, 0x3f, 0x7d, 0x86,
        0xa3, 0xb1, 0x7a, 0x61, 0x70, 0xa6, 0x59, 0xc1, 0x60, 0x08, 0x95, 0x0f, 0x7f, 0x5e, 0x06, 0xa5,
        0xde, 0x3e, 0x59, 0x98, 0x89, 0x5e, 0xfa, 0x7d, 0xee, 0xa0, 0x60, 0xbe, 0x95, 0x75, 0x66, 0x8f,
        0x78, 0xab, 0x19, 0x07, 0xb3, 0xba, 0x1b, 0x7d, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    constexpr u64 CommonCertificateSize = sizeof(CommonCertificateData);
}