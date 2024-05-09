#include "../cpp/utils/types.hpp"
#include "../cpp/utils/calculators.hpp"

#include <pybind11/pybind11.h>

#include <string>

namespace py = pybind11;
using namespace elso;
using namespace elso::type;

#define REGISTER_ASSET_TYPE(type) \
    py::class_<type, Asset, std::shared_ptr<type>>(m, #type) \
        .def(py::init< \
            const std::string&, \
            real, \
            IndexerType, \
            real, \
            real, \
            uint32_t>()) \
        .def_readwrite("rate", &type::rate) \
        .def_readwrite("extra_rate", &type::extra_rate) \
        .def_readwrite("purchase_date", &type::purchase_date) \
        .def_readwrite("indexer", &type::indexer) \
        .def("GetIncome", &type::get_income) \
        ;

#define REGISTER_PORTFOLIO_METHODS(portfolio, type) \
    portfolio.def("AddAsset", &Portfolio::py_add_asset<type>);
    // portfolio.def("AddAsset", &Portfolio::py_add_asset<type>); \
    // portfolio.def("GetAsset", &Portfolio::py_get_asset<type>);

PYBIND11_MODULE(libelso_bindings, m)
{
    // Enums --------------------------------------------------------------------------------------
    py::enum_<TaxPolicyType>(m, "TaxPolicyType")
        .value("IR", tpIR)
        .value("IOF", tpIOF)
        .value("IRIOF", tpIRIOF)
        .export_values()
        ;
    
    py::enum_<AssetType>(m, "AssetType")
        .value("CDB", atCDB)
        .value("LCI", atLCI)
        .value("LCA", atLCA)
        .value("CRI", atCRI)
        .value("CRA", atCRA)
        .value("Debenture", atDebenture)
        .value("DebentureIn", atEncouragedDebenture)
        .value("Stock", atStock)
        .value("FII", atFII)
        .export_values()
        ;

    py::enum_<IndexerType>(m, "IndexerType")
        .value("Disabled", itNone)
        .value("CDI", itCDI)
        .value("IPCA", itIPCA)
        .value("SELIC", itSELIC)
        .export_values()
        ;

    // Tax Policies -------------------------------------------------------------------------------
    m.def("IRTaxPolicy", &TaxPolicy<tpIR>);
    m.def("IOFTaxPolicy", &TaxPolicy<tpIOF>);
    m.def("IRIOFTaxPolicy", &TaxPolicy<tpIRIOF>);

    // Assets -------------------------------------------------------------------------------------
    py::class_<Asset, std::shared_ptr<Asset>>(m, "Asset")
        .def(py::init<>())
        .def_readwrite("type", &Asset::type)
        .def_readwrite("tax_type", &Asset::tp_type)
        .def_readwrite("name", &Asset::name)
        .def_readwrite("capital", &Asset::capital)
        .def("GetIncome", &Asset::get_income)
        ;
    
    REGISTER_ASSET_TYPE(CDBAsset)
    REGISTER_ASSET_TYPE(LCIAsset)
    REGISTER_ASSET_TYPE(LCAAsset)
    REGISTER_ASSET_TYPE(CRIAsset)
    REGISTER_ASSET_TYPE(CRAAsset)
    REGISTER_ASSET_TYPE(DebentureAsset)
    REGISTER_ASSET_TYPE(DebentureInAsset)

    // Portfolio ----------------------------------------------------------------------------------
    py::class_<Portfolio, std::shared_ptr<Portfolio>> p_class(m, "Portfolio");
    p_class.def(py::init<>());
    p_class.def("GetNumberOfAssets", &Portfolio::get_number_of_assets);
    p_class.def("GetAsset", &Portfolio::get_asset<Asset>);
    REGISTER_PORTFOLIO_METHODS(p_class, CDBAsset)
    REGISTER_PORTFOLIO_METHODS(p_class, LCIAsset)
    REGISTER_PORTFOLIO_METHODS(p_class, LCAAsset)
    REGISTER_PORTFOLIO_METHODS(p_class, CRIAsset)
    REGISTER_PORTFOLIO_METHODS(p_class, CRAAsset)
    REGISTER_PORTFOLIO_METHODS(p_class, DebentureAsset)
    REGISTER_PORTFOLIO_METHODS(p_class, DebentureInAsset)
}