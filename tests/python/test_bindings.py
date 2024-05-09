import elso_testing

import elso

import pytest


def testBasicBinding():
    """
    Assert that the basic bindings works.
    Also, ensure that no other bindings are exposed, if not necessary.
    """

    assert [f for f in dir(elso) if not f.startswith("_")] == sorted(
        []
    )