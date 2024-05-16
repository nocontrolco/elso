import elso_testing

from elso import Model

import pytest


def testSolver():
    """
    
    """
    model = Model()
    model.Setup()
    
    assert model.gravity.x == 0.0 and pytest.approx(model.gravity.y) == -9.81 # [m/s²]
    assert pytest.approx(model.timestep) == 5e-5 # [s]
    
    assert model.current_time == 0.0 # [s]
    assert model.Run()
    assert pytest.approx(model.current_time) == 300.0 # [s]


def testBallGravityPhysics():
    '''
    Checks the effect of gravity for moving the ball towards the whole simulation
    '''
    
    model = Model()
    model.Setup()
    
    model.ball.virtual_mass = 5000 # [g]
    model.ball.gravity_center.y = 2.5 # [m]
    assert model.Run()
    assert model.ball.gravity_center.x == 0.0 # [m]
    assert pytest.approx(model.ball.gravity_center.y) == 2.3528499 # [m]
