﻿#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    unsigned int Cr;

    if (DxLib_Init() == -1)            // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }

    Cr = GetColor(0, 0, 255);        // 青色の値を取得
    int red, blue, green;

    for (int x = 0; x < 640; x += 20) {
        for (int y = 0; y < 480; y += 20) {
            red = GetRand(255);
            blue = GetRand(255);
            green = GetRand(255);
            DrawBoxAA(x, y, x + 18, y + 18, GetColor(red, green, blue), TRUE);    // 四角形を描画

        }
    }


    WaitKey();                // キーの入力待ち(『WaitKey』を使用)

    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}