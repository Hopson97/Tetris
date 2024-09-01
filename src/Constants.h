#pragma once

constexpr float SQUARE_SIZE = 32;
constexpr auto BOARD_WIDTH = 20;
constexpr auto BOARD_HEIGHT = 25;
constexpr auto BOARD_X = 800 - (BOARD_WIDTH * SQUARE_SIZE / 2);
constexpr auto BOARD_Y = 450 - (BOARD_HEIGHT * SQUARE_SIZE / 2);

constexpr auto PREVIEW_BOARD_X = BOARD_X + (BOARD_WIDTH * SQUARE_SIZE) + SQUARE_SIZE * 2;
constexpr auto PREVIEW_BOARD_Y = BOARD_Y * 2;
