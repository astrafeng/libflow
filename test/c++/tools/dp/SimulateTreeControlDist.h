
#ifdef USE_MPI
#ifndef SIMULATEREGTREECONTROLDIST_H
#define SIMULATEREGTREECONTROLDIST_H
#include <functional>
#include <memory>
#include <Eigen/Dense>
#include <boost/mpi.hpp>
#include "geners/BinaryFileArchive.hh"
#include "libflow/core/grids/FullGrid.h"
#include "libflow/tree/StateTreeStocks.h"
#include "libflow/dp/SimulateStepTreeControlDist.h"
#include "libflow/dp/OptimizerDPTreeBase.h"
#include "libflow/dp/SimulatorDPBaseTree.h"


/** \file SimulateTreeControlDist.h
 *  \brief Defines a simple program showing how to use simulation to simulate optimal control with uncertainties on tree
 *        A simple grid  is used
 *  \author Xavier Warin
 */


/// \brief Simulate the optimal strategy using optimal controls calculated in optimization , mpi version
///        Uncertainties are discrete and defined on a tree
/// \param p_grid                   grid used for  deterministic state (stocks for example)
/// \param p_optimize               optimizer defining the optimization between two time steps
/// \param p_funcFinalValue         function defining the final value
/// \param p_pointStock             initial point stock
/// \param p_initialRegime          regime at initial date
/// \param p_fileToDump             name associated to dumped bellman values
/// \param p_bOneFile               do we store continuation values  in only one file
double SimulateTreeControlDist(const std::shared_ptr<libflow::FullGrid> &p_grid,
                               const std::shared_ptr<libflow::OptimizerDPTreeBase > &p_optimize,
                               const std::function<double(const int &, const Eigen::ArrayXd &, const Eigen::ArrayXd &)>  &p_funcFinalValue,
                               const Eigen::ArrayXd &p_pointStock,
                               const int &p_initialRegime,
                               const std::string   &p_fileToDump,
                               const bool &p_bOneFile,
                               const boost::mpi::communicator &p_world)
{
    // from the optimizer get back the simulator
    std::shared_ptr< libflow::SimulatorDPBaseTree> simulator = p_optimize->getSimulator();
    int nbStep = simulator->getNbStep();
    std::vector< libflow::StateTreeStocks> states;
    states.reserve(simulator->getNbSimul());
    for (int is = 0; is < simulator->getNbSimul(); ++is)
        states.push_back(libflow::StateTreeStocks(p_initialRegime, p_pointStock, 0));
    std::string toDump = p_fileToDump ;
    // test if one file generated
    if (!p_bOneFile)
        toDump +=  "_" + boost::lexical_cast<std::string>(p_world.rank());
    gs::BinaryFileArchive ar(toDump.c_str(), "r");
    // name for continuation object in archive
    std::string nameAr = "Continuation";
    // cost function
    Eigen::ArrayXXd costFunction = Eigen::ArrayXXd::Zero(p_optimize->getSimuFuncSize(), simulator->getNbSimul());
    for (int istep = 0; istep < nbStep; ++istep)
    {
        libflow::SimulateStepTreeControlDist(ar, nbStep - 1 - istep, nameAr, p_grid, p_grid, p_optimize, p_bOneFile, p_world).oneStep(states, costFunction);

        // new date
        simulator->stepForward();
        for (int is = 0; is < simulator->getNbSimul(); ++is)
            states[is].setStochasticRealization(simulator->getNodeAssociatedToSim(is));
    }
    // final : accept to exercise if not already done entirely (here suppose one function to follow)
    for (int is = 0; is < simulator->getNbSimul(); ++is)
        costFunction(0, is) += p_funcFinalValue(states[is].getRegime(), states[is].getPtStock(), simulator->getValueAssociatedToNode(states[is].getStochasticRealization()));

    return costFunction.mean();
}

#endif /* SIMULATETREECONTROLDIST_H */
#endif
