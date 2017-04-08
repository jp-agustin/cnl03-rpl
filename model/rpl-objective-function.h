/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 *
 * Authors: John Patrick Agustin <jcagustin3@up.edu.ph>
 *          Joshua Jacinto <jhjacinto@up.edu.ph>
 */

#ifndef RPL_OBJECTIVE_FUNCTION_H
#define RPL_OBJECTIVE_FUNCTION_H

#include <stdint.h> 
#include <ns3/log.h>

namespace ns3 {

class RplObjectiveFunction
{
public:
  
  /**
   * \brief Constructor.
   */
  RplObjectiveFunction (void);

  /**
   * \brief Destructor.
   */
  ~RplObjectiveFunction ();
  
  /**
   * \brief Compute the rank
   * \param parentRank the rank of the preferred parent
   */
  static uint16_t ComputeRank (uint16_t parentRank);

};

class RplObjectiveFunctionOf0 : public RplObjectiveFunction
{
public:                                                                                                   
  /**
   * \brief Constructor.
   */
  RplObjectiveFunctionOf0 (void);

  /**
   * \brief Destructor.
   */
  ~RplObjectiveFunctionOf0 ();
  
  /**
   * \brief Compute the rank
   * \param parentRank the rank of the preferred parent
   */
  static uint16_t ComputeRank (uint16_t parentRank);

};

}
#endif /* RPL_OBJECTIVE_FUNCTION_H */