#include "calculators.hpp"
#include "types.hpp"

namespace elso
{

template <typename AType>
void Portfolio::add_asset(const AType &asset, real weight)
{
    this->assets.push_back(std::make_shared<AType>(asset));
    this->weights.push_back(weight);
}

template <typename AType>
size_t Portfolio::py_add_asset(const std::shared_ptr<AType>& asset, real weight)
{
    this->assets.push_back(asset);
    this->weights.push_back(weight);
    return this->assets.size() - 1;
}

template <typename AType>
std::shared_ptr<AType> Portfolio::py_get_asset(size_t index)
{
    assert (index < this->assets.size());
    return std::dynamic_pointer_cast<AType>(this->assets[index]);
}

template <typename AType>
const std::shared_ptr<AType> Portfolio::get_asset(size_t index) const
{
    assert (index < this->assets.size());
    return std::dynamic_pointer_cast<AType>(this->assets[index]);
}

// Explicit instantiation -------------------------------------------------------------------------
#define PORTFOLIO_EXPLICIT_INSTANTIATION(type) \
    template void Portfolio::add_asset(const type& asset, real weight); \
    template size_t Portfolio::py_add_asset(const std::shared_ptr<type>& asset, real weight); \
    template std::shared_ptr<type> Portfolio::py_get_asset<type>(size_t index); \
    template const std::shared_ptr<type> Portfolio::get_asset<type>(size_t index) const;

PORTFOLIO_EXPLICIT_INSTANTIATION(type::Asset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::CDBAsset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::LCIAsset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::LCAAsset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::CRIAsset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::CRAAsset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::DebentureAsset)
PORTFOLIO_EXPLICIT_INSTANTIATION(type::DebentureInAsset)

} // namespace elso