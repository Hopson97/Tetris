#include <cassert>
#include <vector>

struct Block
{
    int size;
    std::vector<int32_t> layout;

    int32_t get(int x, int y)
    {
        assert(x >= 0 && x < size && y >= 0 && y < size);
        return layout[(y * size + x)];
    }
};

const Block BLOCK_NONE{0, {}};

// clang-format off
const Block BLOCK_SQUARE  {
    2, 
    {
        1, 1, 
        1, 1
    }
};
const Block BLOCK_I  {
    4, 
    {
        1, 0, 0, 0, 
        1, 0, 0, 0,
        1, 0, 0, 0,
        1, 0, 0, 0,
    }
};

// clang-format on
const std::vector<Block> ALL_BLOCKS{BLOCK_SQUARE};