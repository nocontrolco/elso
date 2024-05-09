#include "../../src/cpp/utils/types.hpp"
#include "../../src/cpp/utils/calculators.hpp"
#include "../../src/cpp/utils/math.hpp"

#include <cassert>
#include <iostream>

// Approximately 3 years
#define START_DATE 20200423
#define END_DATE 20230423
#define INV_COST 1000.0f

using namespace elso;
using namespace elso::type;

int main()
{
    Portfolio portfolio;

    portfolio.add_asset(CRIAsset(
        "CRI BTG", INV_COST, itCDI, 1.02f, 0.0f, START_DATE), 0.5f);

    portfolio.add_asset(DebentureInAsset(
        "DBIn Inter", INV_COST, itNone, 0.14f, 0.0f, START_DATE), 0.5f);

    assert(portfolio[0].name == "CRI BTG");
    assert(portfolio[0].type == atCRI);
    assert(portfolio[0].capital == INV_COST);
    assert(portfolio.get_asset<CRIAsset>(0)->indexer == itCDI);

    real CRI_income = portfolio[0].get_income(END_DATE);
    assert(elso::math::is_close(CRI_income, 1478.54f, 1e-2f));
    assert(elso::math::is_close(
        portfolio.get_asset<CRIAsset>(0)->get_income(END_DATE), 1478.54f, 1e-2f));

    assert(portfolio[1].name == "DBIn Inter");
    assert(portfolio[1].type == atEncouragedDebenture);
    assert(portfolio.get_asset<DebentureInAsset>(1)->indexer == itNone);
    assert(portfolio[1].capital == INV_COST);

    real DBIn_income = portfolio[1].get_income(END_DATE);
    assert(elso::math::is_close(DBIn_income, 1481.54f, 1e-2f));
    assert(elso::math::is_close(
        portfolio.get_asset<DebentureInAsset>(1)->get_income(END_DATE), 1481.54f, 1e-2f));

    if (CRI_income >= DBIn_income)
    {
        printf("ERROR!\nCRI w/ 102%% CDI isn't better than a Debenture Incentivada w/ 14%% in 3 years\n");
        printf("CRI w/ 102%% CDI: %.20f\n", CRI_income);
        printf("Debenture Incentivada w/ 14%%: %.20f\n", DBIn_income);
        return 1;
    }
    else
    {
        printf("PASSED!\nCRI w/ 102%% CDI is worst than a Debenture Incentivada w/ 14%% in 3 years\n");
        printf("CRI w/ 102%% CDI: %.20f\n", CRI_income);
        printf("Debenture Incentivada w/ 14%%: %.20f\n", DBIn_income);
        return 0;
    }
}