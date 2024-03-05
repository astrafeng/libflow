// Copyright (C) 2016 EDF
// All Rights Reserved
// This code is published under the GNU Lesser General Public License (GNU LGPL)
#ifndef SEMILAGRANGIANSIMU_H
#define SEMILAGRANGIANSIMU_H
#include <memory>
#include <Eigen/Dense>
#include <functional>
#ifdef USE_MPI
#include "boost/mpi.hpp"
#endif
#include "libflow/semilagrangien/OptimizerSLBase.h"


/** \file semiLagrangianSimu.h
 *  \brief Defines a simple program showing how to use simulation
 *        A simple grid  is used
 *  \author Xavier Warin
 */

/// \brief Simulate the optimal strategy
/// \param p_grid                  grid used for PDE
/// \param p_optimize              optimizer defining the optimisation between two time steps
/// \param p_funcFinalValue        function defining the final value (initial value for PDE)
/// \param p_nbStep                 number of step
/// \param p_stateInit             initial state
/// \param p_initialRegime         regime at initial date
/// \param p_nbSimul               number of simulations
/// \param p_fileToDump            name of the file used to dump continuation values in optimization
/// \param p_world  MPI communicator
double semiLagrangianSimu(const std::shared_ptr<libflow::SpaceGrid> &p_grid,
                          const std::shared_ptr<libflow::OptimizerSLBase > &p_optimize,
                          const std::function<double(const int &, const Eigen::ArrayXd &)>   &p_funcFinalValue,
                          const int &p_nbStep,
                          const Eigen::ArrayXd &p_stateInit,
                          const int &p_initialRegime,
                          const int &p_nbSimul,
                          const std::string   &p_fileToDump
#ifdef USE_MPI
                          , const boost::mpi::communicator &p_world
#endif

                         ) ;

#endif /* SEMILAGRANGIANSIMU_H */
