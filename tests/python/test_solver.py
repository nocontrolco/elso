import elso_testing

from elso import Model

import pytest


def testSolver():
    """
    
    """
    model = Model()
    
    assert model.gravity.x == 0.0 and pytest.approx(model.gravity.y) == -9.81 # [m/s²]
    assert pytest.approx(model.timestep) == 5e-5 # [s]
    
    assert model.current_time == 0.0 # [s]
    assert model.Run()
    assert pytest.approx(model.current_time) == 300.0 # [s]