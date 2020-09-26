#include <minizinc/solvers/MIP/MIP_scip_solverfactory.hh>
#include <minizinc/solvers/MIP/MIP_scip_wrap.hh>
#include <minizinc/solvers/MIP/MIP_solverinstance.hh>

namespace MiniZinc {
namespace {
void get_wrapper() {
  static MIPSolverFactory<MIP_scip_wrapper> _scip_solver_factory;
  return;
}
}  // namespace
SCIP_SolverFactoryInitialiser::SCIP_SolverFactoryInitialiser(void) { get_wrapper(); }
}  // namespace MiniZinc
