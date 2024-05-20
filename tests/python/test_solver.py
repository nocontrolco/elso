import elso_testing

from elso import Model

import pytest


def testSolver():
    ''' '''
    model = Model()
    model.Setup()

    assert model.gravity.x == 0.0 and pytest.approx(model.gravity.y) == -9.81  # [m/s²]
    assert pytest.approx(model.timestep) == 5e-5  # [s]

    assert model.current_time == 0.0  # [s]
    assert model.Run(300.0)
    assert pytest.approx(model.current_time) == 300.0  # [s]


@pytest.mark.xfail(
    reason="Solver still has numerical instabilities due to increasing energy"
)
def testBallGravityPhysics():
    '''
    Checks the effect of gravity for moving the ball towards the whole simulation
    '''

    model = Model()
    model.Setup()

    model.ball.virtual_mass = 50000  # [g]
    model.ball.gravity_center.x = 1.500001  # [m]
    model.ball.gravity_center.y = 15.500001  # [m]
    model.ball.velocity.y = 10.0  # [m/s]
    assert model.arena.bbox.min.x == model.arena.bbox.min.y == 0.0
    assert model.arena.bbox.max.x == model.arena.bbox.max.y == 20.0
    assert model.Run(3.0, 0.1)
    assert model.ball.gravity_center.x == 1.500001  # [m]
    assert pytest.approx(model.ball.gravity_center.y) == 2.3528499  # [m]
