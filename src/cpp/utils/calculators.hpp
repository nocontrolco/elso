#pragma once

#include "definitions.hpp"

#include <cassert>
#include <vector>
#include <memory>

namespace elso
{

namespace type
{
    struct Asset;
}

using AssetCollection = std::vector<std::shared_ptr<type::Asset>>;
struct Portfolio
{
    AssetCollection assets;
    std::vector<real> weights;

    template <typename AType>
    void add_asset(const AType& asset, real weight);

    template <typename AType>
    size_t py_add_asset(const std::shared_ptr<AType>& asset, real weight);

    template <typename AType> std::shared_ptr<AType> py_get_asset(size_t index);

    template <typename AType> const std::shared_ptr<AType> get_asset(size_t index) const;

    inline size_t get_number_of_assets() const
    {
        return assets.size();
    }

    type::Asset& operator[](size_t index)
    {
        assert (index < assets.size());
        return *assets[index];
    }

    const type::Asset& operator[](size_t index) const
    {
        assert (index < assets.size());
        return *assets[index];
    }
};

} // namespace elso