# Including bindings path to allow for importing Python DLL
import sys as _sys
import git as _git
from pathlib import Path as _Path

_repo = _git.Repo(".", search_parent_directories=True)
_bindings_path = _Path(_repo.working_dir + "/build/src/bindings")

if not _bindings_path.exists():
    raise RuntimeError("Build bindings path not created!")
else:
    _sys.path.append(str(_bindings_path))

try:
    import libelso_bindings as _elso
except:
    print("ELSO bindings libraries not generated!")

# Enums
TaxPolicyType = _elso.TaxPolicyType
AssetType = _elso.AssetType
IndexerType = _elso.IndexerType


# Tax Policies
def TaxPolicy(tax_policy_type):
    if tax_policy_type == TaxPolicyType.IR:
        return _elso.IRTaxPolicy
    elif tax_policy_type == TaxPolicyType.IOF:
        return _elso.IOFTaxPolicy
    elif tax_policy_type == TaxPolicyType.IRIOF:
        return _elso.IRIOFTaxPolicy
    else:
        raise RuntimeError("Invalid TaxPolicyType")


# Assets
Asset = _elso.Asset
CDBAsset = _elso.CDBAsset
LCIAsset = _elso.LCIAsset
LCAAsset = _elso.LCAAsset
CRIAsset = _elso.CRIAsset
CRAAsset = _elso.CRAAsset
DebentureAsset = _elso.DebentureAsset
DebentureInAsset = _elso.DebentureInAsset

# Porfolio
Portfolio = _elso.Portfolio
