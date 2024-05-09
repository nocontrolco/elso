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
