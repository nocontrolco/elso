import elso_testing

import elso

import pytest


def testBasicBinding():
    """
    Assert that the basic bindings works.
    Also, ensure that no other bindings are exposed, if not necessary.
    """

    assert [f for f in dir(elso) if not f.startswith("_")] == sorted(
        [
            "TaxPolicyType",
            "AssetType",
            "IndexerType",
            "TaxPolicy",
            "Asset",
            "CDBAsset",
            "LCIAsset",
            "LCAAsset",
            "CRIAsset",
            "CRAAsset",
            "DebentureAsset",
            "DebentureInAsset",
            "Portfolio",
            "parsers",
        ]
    )


def testTaxPolicies():
    """
    Test the tax policies.
    """

    # IR
    IRTaxPolicy = elso.TaxPolicy(elso.TaxPolicyType.IR)
    assert IRTaxPolicy(1000.0, 1) == 0.225 * 1000.0, "Tax should be 22.5% of 1000.0"
    assert IRTaxPolicy(1000.0, 181) == 0.2 * 1000.0, "Tax should be 20% of 1000.0"
    assert IRTaxPolicy(1000.0, 361) == 0.175 * 1000.0, "Tax should be 17.5% of 1000.0"
    assert IRTaxPolicy(1000.0, 721) == 0.15 * 1000.0, "Tax should be 15% of 1000.0"


def testPortfolio():
    """
    Test the portfolio class and methods.
    """

    from elso import Portfolio, CRIAsset, DebentureInAsset, IndexerType

    START_DATE = 20200423
    END_DATE = 20230423
    INV_COST = 1000.0

    portfolio = Portfolio()
    assert portfolio is not None

    # Adding assets
    asset_index = portfolio.AddAsset(
        CRIAsset("CRI BTG", INV_COST, IndexerType.CDI, 1.02, 0.0, START_DATE), 0.5
    )
    assert portfolio.GetNumberOfAssets() == 1
    CRI = portfolio.GetAsset(asset_index)
    assert CRI is not None
    assert CRI.name == "CRI BTG"
    assert type(CRI) == CRIAsset
    assert CRI.indexer == IndexerType.CDI
    assert pytest.approx(CRI.capital, abs=1e-2) == INV_COST
    assert pytest.approx(CRI.GetIncome(END_DATE), abs=1e-2) == 1478.54

    asset_index = portfolio.AddAsset(
        DebentureInAsset(
            "DBIn Inter", INV_COST, IndexerType.Disabled, 0.14, 0.0, START_DATE
        ),
        0.5,
    )
    assert portfolio.GetNumberOfAssets() == 2
    DBIn = portfolio.GetAsset(asset_index)
    assert DBIn is not None
    assert DBIn.name == "DBIn Inter"
    assert type(DBIn) == DebentureInAsset
    assert DBIn.indexer == IndexerType.Disabled
    assert pytest.approx(DBIn.capital, abs=1e-2) == INV_COST
    assert pytest.approx(DBIn.GetIncome(END_DATE), abs=1e-2) == 1481.54
