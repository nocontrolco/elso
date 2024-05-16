#include "../cpp/utils/types.hpp"
#include "../cpp/physics/solver.hpp"

#include <pybind11/pybind11.h>

#include <string>

namespace py = pybind11;
using namespace elso;

PYBIND11_MODULE(libelso_bindings, m)
{
    // Definitions -------------------------------------------------------------------------------
    {
        py::class_<real2, std::shared_ptr<real2>>(m, "real2")
            .def(py::init<>())
            .def_readwrite("x", &real2::x)
            .def_readwrite("y", &real2::y)
            ;
    }

    // Types -------------------------------------------------------------------------------------
    {
        using namespace type;

        py::class_<Ball, std::shared_ptr<Ball>>(m, "Ball")
            .def(py::init<>())
            .def_readwrite("radius", &Ball::_radius)
            .def_readwrite("virtual_mass", &Ball::_virtual_mass)
            .def_readwrite("gravity_center", &Ball::_gravity_center)
            ;
        
        py::class_<BoundingBox, std::shared_ptr<BoundingBox>>(m, "BoundingBox")
            .def(py::init<>())
            .def_readwrite("min", &BoundingBox::_min)
            .def_readwrite("max", &BoundingBox::_max)
            ;

        py::class_<Car, std::shared_ptr<Car>>(m, "Car")
            .def(py::init<>())
            .def_readwrite("hitbox", &Car::_hitbox)
            .def_readwrite("levitation_height", &Car::_levitation_height)
            .def_readwrite("virtual_mass", &Car::_virtual_mass)
            .def_readwrite("gravity_center", &Car::_gravity_center)
            ;
        
        py::class_<Arena, std::shared_ptr<Arena>>(m, "Arena")
            .def(py::init<>())
            .def_readwrite("bbox", &Arena::_bbox)
            .def_readwrite("corner_arc", &Arena::_corner_arc)
            ;
    }

    // Solver -------------------------------------------------------------------------------------
    {
        using namespace solver;

        py::enum_<MatchStatus>(m, "MatchStatus")
            .value("NotStarted", _notStarted)
            .value("Kickoff", _kickoff)
            .value("Ended", _ended)
            .export_values()
            ;

        py::class_<Model, std::shared_ptr<Model>>(m, "Model")
            .def(py::init<>())
            .def_readonly("gravity", &Model::_gravity)
            .def_readonly("timestep", &Model::_timestep)
            .def_readwrite("arena", &Model::_arena)
            .def_readwrite("cars", &Model::_cars)
            .def_readwrite("ball", &Model::_ball)
            .def_readwrite("current_time", &Model::_current_time)
            .def_readwrite("status", &Model::_status)
            .def("Setup", &Model::setup)
            .def("Run", &Model::run, py::arg("output_frequency") = 0.0)
            ;
    }
}