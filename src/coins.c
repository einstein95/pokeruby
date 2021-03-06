#include "global.h"
#include "menu.h"
#include "string_util.h"

#define MAX_COINS 9999

extern u8 gOtherText_Coins2[];

void PrintCoins(s32, u8, u8, u8);

void UpdateCoinsWindow(s32 a, u8 b, u8 c)
{
    PrintCoins(a, 4, b + 2, c + 1);
}

void ShowCoinsWindow(u32 a, u8 b, u8 c)
{
    MenuDrawTextWindow(b, c, b + 9, c + 3);
    UpdateCoinsWindow(a, b, c);
}

void HideCoinsWindow(u8 a, u8 b)
{
    MenuZeroFillWindowRect(a, b, a + 9, b + 3);
}

void PrintCoins(s32 a, u8 b, u8 c, u8 d)
{
    u8 string[16];
    u8 *ptr;
    u8 r1;
    u8 r6;
    u8 foo;
    
    ConvertIntToDecimalString(string, a);
    r1 = (b * 6 + 0x21 - 8 * (b + 2));
    c = c - r1 / 8;
    foo = r1 % 8;
    ptr = gStringVar1;
    if(foo)
    {
        ptr[0] = 0xFC;
        ptr[1] = 0x11;
        ptr[2] = 8 - (foo);
        ptr += 3;
    }
    ptr[0] = 0xFC;
    ptr[1] = 0x11;
    ptr[2] = (b - StringLength(string)) * 6;
    ptr += 3;
    StringCopy(ptr, string);
    MenuPrint(gOtherText_Coins2, c, d);
}

u16 GetCoins(void)
{
    return gSaveBlock1.coins;
}

bool8 GiveCoins(u16 coins)
{
    u32 newCoins;
    
    if(GetCoins() >= MAX_COINS)
        return FALSE;
    newCoins = coins + gSaveBlock1.coins;
    if(gSaveBlock1.coins > (u16)newCoins)
        gSaveBlock1.coins = MAX_COINS;
    else
    {
        gSaveBlock1.coins = newCoins;
        if((u16)newCoins > MAX_COINS)
            gSaveBlock1.coins = MAX_COINS;
    }
    return TRUE;
}

bool8 TakeCoins(u16 coins)
{
    if(GetCoins() >= coins)
    {
        gSaveBlock1.coins -= coins;
        return TRUE;
    }
    else
        return FALSE;
}
