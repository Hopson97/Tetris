#pragma once

#include <cassert>
#include <ranges>
#include <vector>

// Fixed size std::vector with 2D access
template <typename T, int PerData = 1>
class Array2D
{
  public:
    Array2D(unsigned width, unsigned height)
        : data_(width * height * PerData)
        , WIDTH(width)
        , HEIGHT(height)
    {
    }

    T& get(int x, int y)
    {
        assert(contains(x, y));
        return data_[index(x, y)];
    }

    const T& get(int x, int y) const
    {
        assert(contains(x, y));
        return data_[index(x, y)];
    }

    void set(int x, int y, const T& data)
    {
        assert(contains(x, y));
        data_[index(x, y)] = data;
    }

    bool contains(int x, int y)
    {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
    }

    void fill(const T& value)
    {
        std::ranges::fill(data_, value);
    }

  private:
    size_t index(int x, int y)
    {
        // TODO why returning 0 set the whole array?
        return (y * WIDTH + x) * PerData;
    }

  private:
    std::vector<T> data_;

  public:
    const size_t WIDTH;
    const size_t HEIGHT;
};