// Copyright (C) 2016 EDF
// All Rights Reserved
// This code is published under the GNU Lesser General Public License (GNU LGPL)
#ifndef SDDPVISITEDSTATESGENERS_H
#define SDDPVISITEDSTATESGENERS_H
#include <Eigen/Dense>
#include "geners/GenericIO.hh"
#include "libflow/core/utils/eigenGeners.h"
#include "libflow/sddp/SDDPVisitedStates.h"

/** \file SDDPVisitedStatesGeners.h$
 * \brief Defines visited states by a sweep of SDDP
 * \author Xavier Warin
 */
/// specialize the ClassIdSpecialization template
/// so that a ClassId object can be associated with the class we want to
/// serialize.  The second argument is the version number.
///@{
gs_specialize_class_id(libflow::SDDPVisitedStates, 1)
gs_declare_type_external(libflow::SDDPVisitedStates)
///@}
namespace gs
{
//
// This is how the specialization of GenericWriter should look like
//
template <class Stream, class State>
struct GenericWriter < Stream, State, libflow::SDDPVisitedStates,   Int2Type<IOTraits<int>::ISEXTERNAL> >
{
    inline static bool process(const libflow::SDDPVisitedStates &p_state, Stream &p_os,
                               State *, const bool p_processClassId)
    {
        // If necessary, serialize the class id
        static const ClassId current(ClassId::makeId<libflow::SDDPVisitedStates>());
        const bool status = p_processClassId ? current.write(p_os) : true;
        // Serialize object data if the class id was successfully
        // written out
        if (status)
        {
            const std::vector< std::shared_ptr< Eigen::ArrayXd > > &states = p_state.getStateVisited();
            const std::vector< int  > &mesh  = p_state.getAssociatedMesh();
            const std::vector< std::vector< int> >   &meshToState = p_state.getMeshToState();
            write_item(p_os, states);
            write_item(p_os, mesh);
            write_item(p_os, meshToState);
        }
        // Return "true" on success, "false" on failure
        return status && !p_os.fail();
    }
};

// And this is the specialization of GenericReader
//
template <class Stream, class State>
struct GenericReader < Stream, State, libflow::SDDPVisitedStates,   Int2Type<IOTraits<int>::ISEXTERNAL> >
{
    inline static bool readIntoPtr(libflow::SDDPVisitedStates *&ptr, Stream &p_is,
                                   State *p_st, const bool p_processClassId)
    {
        // Make sure that the serialized class id is consistent with
        // the current one
        static const ClassId current(ClassId::makeId<libflow::SDDPVisitedStates>());
        const ClassId &stored = p_processClassId ? ClassId(p_is, 1) : p_st->back();
        current.ensureSameId(stored);

        // Deserialize object data.
        std::unique_ptr< std::vector< std::shared_ptr< Eigen::ArrayXd > > >   states = read_item< std::vector< std::shared_ptr< Eigen::ArrayXd > > >(p_is);
        std::unique_ptr<  std::vector< int  > > mesh  = read_item< std::vector< int  > > (p_is);
        std::unique_ptr< std::vector< std::vector< int> > > meshToState = read_item< std::vector< std::vector< int> > > (p_is);
        if (p_is.fail())
            // Return "false" on failure
            return false;
        // Build the object from the stored data
        if (ptr)
            *ptr = libflow::SDDPVisitedStates(*meshToState, *states, *mesh);
        else
            ptr = new  libflow::SDDPVisitedStates(*meshToState, *states, *mesh);
        return true;
    }

    inline static bool process(libflow::SDDPVisitedStates &s, Stream &is,
                               State *st, const bool p_processClassId)
    {
        // Simply convert reading by reference into reading by pointer
        libflow::SDDPVisitedStates *ps = &s;
        return readIntoPtr(ps, is, st, p_processClassId);
    }
};
}

#endif
