#pragma once

#include "definitions.hpp"

#include <cassert>
#include <string>
#include <vector>
#include <memory>
namespace elso::type
{

// Taxes Policies =================================================================================
enum TaxPolicyType
{
    tpNone = 0,

    // Imposto de Renda
    tpIR = 1,

    // Imposto sobre Operações Financeiras
    tpIOF = 2,

    // Imposto de Renda + Imposto sobre Operações Financeiras
    tpIRIOF = 3,

    // TODO
    tpStock = 4,

    // 20% do lucro p/ FIIs
    tpFII = 5,

    tpSIZE
};

template <TaxPolicyType TPType>
real TaxPolicy(const real value, uint32_t n_days);

// Assets =========================================================================================
enum AssetType
{
    atNone = 0,

    // Certificado de Depósito Bancário
    atCDB = 1, 

    // Letra de Crédito Imobiliário
    atLCI = 2,

    // Letra de Crédito Agrícola
    atLCA = 3,

    // Certificado de Recebíveis Imobiliários
    atCRI = 4,

    // Certificado de Recebíveis Agrícolas
    atCRA = 5,

    // Debênture
    atDebenture = 6,

    // Debênture incentivada
    atEncouragedDebenture = 7,

    // Ações
    atStock = 8,

    // Fundos de Investimento Imobiliário
    atFII = 9,

    atSIZE
};

struct Asset
{
    AssetType type;
    TaxPolicyType tp_type;
    std::string name;
    real capital;
    uint32_t purchase_date;

    virtual real get_income(uint32_t due_date) const
    {
        return 0.0f;
    }
};

// Fixed Income Assets ============================================================================
enum IndexerType
{
    itNone = 0,

    // Certificado de Depósito Interbancário
    itCDI = 1,

    // Índice Nacional de Preços ao Consumidor Amplo
    itIPCA = 2,

    // Taxa Selic
    itSELIC = 3,

    itSIZE
};

template <TaxPolicyType TPType>
struct FixedIncomeAsset : public Asset
{
    real rate;
    real extra_rate;
    IndexerType indexer;

    FixedIncomeAsset<TPType>(
        const std::string &name,
        real capital,
        IndexerType indexer,
        real rate,
        real extra_rate,
        uint32_t purchase_date)
    {
        this->tp_type = TPType;
        this->name = name;
        this->capital = capital;
        this->indexer = indexer;
        this->rate = rate;
        this->extra_rate = extra_rate;
        this->purchase_date = purchase_date;
    }

    real get_income(uint32_t due_date) const override;
};

#define CREATE_ASSET(class_name, asset_type, tax_policy) \
    struct class_name : public FixedIncomeAsset<tax_policy> \
    { \
        class_name( \
            const std::string &name, \
            real capital, \
            IndexerType indexer, \
            real rate, \
            real extra_rate, \
            uint32_t purchase_date) \
            : FixedIncomeAsset<tax_policy>(name, capital, indexer, rate, extra_rate, purchase_date) \
        { \
            this->type = asset_type; \
        } \
    };

CREATE_ASSET(CDBAsset, atCDB, tpIRIOF)
CREATE_ASSET(LCIAsset, atLCI, tpIOF)
CREATE_ASSET(LCAAsset, atLCA, tpIOF)
CREATE_ASSET(CRIAsset, atCRI, tpIOF)
CREATE_ASSET(CRAAsset, atCRA, tpIOF)
CREATE_ASSET(DebentureAsset, atDebenture, tpIRIOF)
CREATE_ASSET(DebentureInAsset, atEncouragedDebenture, tpIOF)

// Treasury Bonds ==================================================================================
// TODO: Tesouro Direto

// Variable Income Assets ==========================================================================
// TODO: Stocks, BDRs, FIIS, REITS, ETFs, etc.

#define CREATE_VAR_ASSET(class_name, asset_type, tax_type) \
    struct class_name : public Asset \
    { \
        uint32_t shares; \
        real value; \
        class_name( \
            const std::string &name, \
            real capital, \
            uint32_t shares, \
            uint32_t purchase_date) \
        { \
            this->tp_type = tax_type; \
            this->type = asset_type; \
            this->name = name; \
            this->value = this->capital = capital; \
            this->shares = shares; \
            this->purchase_date = purchase_date; \
        } \
        real get_income(uint32_t due_date) const override; \
    };

CREATE_VAR_ASSET(StockAsset, atStock, tpStock)
CREATE_VAR_ASSET(FIIAsset, atFII, tpFII)


} // namespace elso::type