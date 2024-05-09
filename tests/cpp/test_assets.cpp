#include "../../src/cpp/utils/types.hpp"
#include "../../src/cpp/utils/math.hpp"

#include <cassert>

// Approximately 3 years
#define START_DATE 20200423
#define END_DATE 20230423
#define INV_COST 1000.0f

using namespace elso::type;

int main()
{
    assert(elso::math::days_between(START_DATE, END_DATE) == 1095);
    auto LCI = LCIAsset(
        "LCI", INV_COST, itCDI, 0.95f, 0.0f, START_DATE);
    assert(LCI.name == "LCI");
    assert(LCI.type == atLCI);
    assert(LCI.indexer == itCDI);
    assert(LCI.capital == INV_COST);
    assert(LCI.purchase_date == START_DATE);
    assert(LCI.rate == 0.95f);
    assert(LCI.extra_rate == 0.0f);

    auto CDB = CDBAsset(
        "CDB", INV_COST, itCDI, 1.12f, 0.0f, START_DATE);
    assert(CDB.name == "CDB");
    assert(CDB.type == atCDB);
    assert(CDB.indexer == itCDI);
    assert(CDB.capital == INV_COST);
    assert(CDB.purchase_date == START_DATE);
    assert(CDB.rate == 1.12f);
    assert(CDB.extra_rate == 0.0f);

    real LCI_income = LCI.get_income(END_DATE);
    real CDB_income = CDB.get_income(END_DATE);
    printf("LCI w/ 95%% CDI: %.20f\n", LCI_income);
    printf("CDB w/ 112%% CDI: %.20f\n", CDB_income);
    assert(elso::math::is_close(LCI_income, 1441.65f, 1e-2f));
    assert(elso::math::is_close(CDB_income, 1452.48f, 1e-2f));
    if (LCI_income >= CDB_income)
    {
        printf("ERROR!\nLCI w/ 95%% CDI is better than a CDB w/ 112%% CDI in 3 years\n");
        return 1;
    }
    else
    {
        printf("PASSED!\nLCI w/ 95%% CDI is worst than a CDB w/ 112%% CDI in 3 years\n");
        return 0;
    }
}