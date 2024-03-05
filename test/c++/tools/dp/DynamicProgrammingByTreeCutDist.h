
#ifndef DYNAMICPROGRAMMINGBYTREECUTDIST_H
#define DYNAMICPROGRAMMINGBYTREECUTDIST_H
#include <fstream>
#include <memory>
#include <functional>
#include <boost/mpi.hpp>
#include <Eigen/Dense>
#include "libflow/core/grids/SpaceGrid.h"
#include "libflow/dp/OptimizerDPCutTreeBase.h"

/* \file DynamicProgrammingByTreeCutDist.h
 * \brief Defines a simple  programm  showing how to optimize a problem by dynamic programming using parallel framework and distributing
 *        calculations and data
 *        Each transitional problem is solved by a LP and cuts to approximate the convex or concave Bellman values are return  by each LP resolution.
 *        A simple grid  is used, uncertainties ar defined on a tree
 * \author Xavier Warin
 */

/// \brief Principal function to optimize  a problem for a tree method
/// \param p_grid             grid used for  deterministic state (stocks for example)
/// \param p_optimize           optimizer defining the optimisation between two time steps
/// \param p_regressor          regressor object
/// \param p_funcFinalValue     function defining the final cut values
/// \param p_initialPointStock  point stock used for interpolation
/// \param p_initialRegime      regime at initial date
/// \param p_fileToDump         file to dump continuation values
/// \param p_bOneFile           do we store continuation values  in only one file
/// \param p_world             MPI communicator
///
double  DynamicProgrammingByTreeCutDist(const std::shared_ptr<libflow::FullGrid> &p_grid,
                                        const std::shared_ptr<libflow::OptimizerDPCutTreeBase > &p_optimize,
                                        const std::function< Eigen::ArrayXd(const int &, const Eigen::ArrayXd &, const Eigen::ArrayXd &)>   &p_funcFinalValue,
                                        const Eigen::ArrayXd &p_pointStock,
                                        const int &p_initialRegime,
                                        const std::string   &p_fileToDump,
                                        const bool &p_bOneFile,
                                        const boost::mpi::communicator &p_world);

#endif /* DYNAMICPROGRAMMINGBYTREECUTDIST_H */
