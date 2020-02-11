#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "QrCode.hpp"
#include "raylib.h"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

void drawQrCode(const QrCode& qr, int startX, int startY, int blockSize, int border);

int main() {
	const char *text = "xxxxxx";
	const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;
	const QrCode qr = QrCode::encodeText(text, errCorLvl);
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "QR CODE RayLib");
    SetTargetFPS(30);
    int border = 4;
    while (!WindowShouldClose())   
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawQrCode(qr, 100, 100, 4, border);
        EndDrawing();
    }
    CloseWindow(); 
	return 0;
}

// startX and startY = starting coordinates of drawing
// blockSize = size of QrCode pixel
// border = additional white border size
void drawQrCode(const QrCode& qr, int startX, int startY, int blockSize, int border) {
    int realX = startX;
    int realY = startY;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            if(qr.getModule(x, y)){
                DrawRectangle(realX, realY, blockSize, blockSize, BLACK);
            } else {
                DrawRectangle(realX, realY, blockSize, blockSize, WHITE);
            }
            realX = realX + blockSize;
        }
        realY = realY + blockSize;
        realX = startX;
    }

}


