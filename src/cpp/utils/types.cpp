#include "types.hpp"
#include "math.hpp"
#include "parsers.hpp"

#include <cmath>

namespace elso::type
{

// ================================================================================================
// TaxPolicy
// ================================================================================================
template <>
real TaxPolicy<tpNone>(const real value, uint32_t n_days)
{
    return 0.0f;
}

template <>
real TaxPolicy<tpIOF>(const real value, uint32_t n_days)
{
    static const real IOF_TABLE[] = {
        0.96f, 0.93f, 0.9f, 0.86f, 0.83f, 0.8f, 0.76f, 0.73f, 0.7f, 0.66f,
        0.66f, 0.63f, 0.6f, 0.56f, 0.53f, 0.5f, 0.46f, 0.43f, 0.4f, 0.36f,
        0.33f, 0.3f, 0.26f, 0.23f, 0.2f, 0.16f, 0.13f, 0.1f, 0.06f, 0.03f};
    if (n_days >= 30)
        return 0.0f;
    return IOF_TABLE[n_days] * value;
}

template <>
real TaxPolicy<tpIR>(const real value, uint32_t n_days)
{
    if (n_days <= 180)
        return 0.225f * value;
    else if (n_days <= 360)
        return 0.2f * value;
    else if (n_days <= 720)
        return 0.175f * value;
    else
        return 0.15f * value;
}

template <>
real TaxPolicy<tpIRIOF>(const real value, uint32_t n_days)
{
    return TaxPolicy<tpIR>(value, n_days) + TaxPolicy<tpIOF>(value, n_days);
}

template <>
real TaxPolicy<tpStock>(const real value, uint32_t n_days)
{
    // TODO
    return 0.0f;
}

template <>
real TaxPolicy<tpFII>(const real value, uint32_t n_days)
{
    if (value <= 0.0f)
        return 0.0f;
    return 0.2f * value;
}

// ================================================================================================
// FixedIncomeAsset
// ================================================================================================
template <TaxPolicyType TPType>
real FixedIncomeAsset<TPType>::get_income(uint32_t due_date) const
{
    const real anual_rate = [this]
    {
        if (this->indexer == itCDI)
            return this->rate * get_CDI_rate() + this->extra_rate;
        else if (this->indexer == itIPCA)
            return this->rate * get_IPCA_rate() + this->extra_rate;
        else if (this->indexer == itSELIC)
            return this->rate * get_SELIC_rate() + this->extra_rate;
        else
            return this->rate;
    }();
    const uint32_t n_days = elso::math::days_between(this->purchase_date, due_date);
    const real n_years = n_days / 365.0f;
    const real raw_income = this->capital * std::pow(1.0f + anual_rate, n_years);
    return raw_income - TaxPolicy<TPType>(raw_income - this->capital, n_days);
}

// Explicit instantiation
template struct FixedIncomeAsset<tpNone>;
template struct FixedIncomeAsset<tpIR>;
template struct FixedIncomeAsset<tpIOF>;
template struct FixedIncomeAsset<tpIRIOF>;

// ================================================================================================
// StockAsset
// ================================================================================================
real StockAsset::get_income(uint32_t due_date) const
{
    const real raw_income = this->value * this->shares;
    return raw_income - TaxPolicy<tpStock>(raw_income, due_date - this->purchase_date);
}

real FIIAsset::get_income(uint32_t due_date) const
{
    const real raw_income = this->value * this->shares;
    return raw_income - TaxPolicy<tpFII>(raw_income, due_date - this->purchase_date);
}

} // namespace elso::type
