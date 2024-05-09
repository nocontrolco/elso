# Including elso library path for testing
import git, sys

repo = git.Repo(".", search_parent_directories=True)
PYTHON_PATH = repo.working_dir + "/src/python"
sys.path.append(str(PYTHON_PATH))
